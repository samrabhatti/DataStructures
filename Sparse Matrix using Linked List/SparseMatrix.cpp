#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

class SparseMatrix
{
private:
	struct Node
	{
		int data;
		int index;
		Node* next;

		Node()
		{
			data = 0;
			index = 0;
			next = NULL;
		}

		Node(const int& d, int i, Node* n = NULL)
		{
			data = d;
			index = i;
			next = n;
		}

	};

	int m, n;				//m->rows, n->columns
	vector<Node*>rowlist;

	void Int(string str, int*& arr, int& length)
	{
		length = str.length();
		arr = new int[length];

		int j = 0, i, sum = 0;

		for (i = 0; str[i] != '\0'; i++)
		{
			if (str[i] == ' ')
			{
				length--;
				continue;
			}
			if (str[i] >= '0' || str[i] <= '9')
			{
				arr[j] = str[i] - 48;
				j++;

			}
		}
	}

	void InsertAtTail(const int& element, Node*& head, Node*& tail, int size, int col)
	{
		if (size == 0)
		{
			tail = new Node(element, col, tail);
			head = tail;
		}

		else
		{
			Node* previous = tail;
			tail = new Node(element, col, tail->next);
			previous->next = tail;
		}
		size++;
	}


public:

	SparseMatrix()
	{
		m = n = 0;
		//rowlist = nullptr;
	}

	void ReadMatrix(string filename)
	{
		int r = 0, c = 0, k = 1, count = 0, size = 0;
		string str, space;
		int* temp = 0;

		ifstream file(filename);
		while (getline(file, str))
		{
			r++;
			if (r == 1)								// First row only: determine the number of columns
			{
				stringstream ss(str);               // Set up a stream from this line
				while (ss >> space)
					c++;							// Each item delineated by spaces adds one to cols
			}

			Int(str, temp, size);

			Node* head = NULL;
			Node* tail = NULL;
			for (int i = 0; i < size; i++)
			{
				if (temp[i] != 0)
				{
					if (count == 0)
					{
						head = new Node(temp[i], i + 1);
						tail = head;
					}
					else
						InsertAtTail(temp[i], head, tail, count, i + 1);
					count++;
				}

			}
			count = 0;
			rowlist.push_back(head);

		}

		file.close();

		this->m = r;
		this->n = c;

		//cout << "Rows: " << m << endl << "Columns: " << n << endl;
	}

	SparseMatrix(string filename)
	{
		ReadMatrix(filename);
	}

	SparseMatrix(const SparseMatrix& obj)
	{
		m = obj.m;
		n = obj.n;
		rowlist = obj.rowlist;
	}

	const SparseMatrix& operator = (const SparseMatrix& obj)
	{
		m = obj.m;
		n = obj.n;
		rowlist = obj.rowlist;
		return*this;
	}

	void PrintMatrix()
	{
		vector<Node*>temp = rowlist;
		for (int i = 0; i < temp.size(); i++)
		{
			Node* curr = temp[i];
			for (int j = 1; j <= n; j++)
			{
				if (curr == NULL)
				{
					while (j <= n)
					{
						cout << "0 ";
						j++;
					}
				}
				else if (curr->index == j)
				{
					cout << curr->data << " ";
					curr = curr->next;
				}
				else
					cout << "0 ";
			}
			cout << endl;
		}
	}

	bool operator == (const SparseMatrix& obj)
	{
		if (m == obj.m && n == obj.n && rowlist.size() == obj.rowlist.size())
		{
			for (int i = 0; i < rowlist.size(); i++)
			{
				if (rowlist[i] == NULL && obj.rowlist[i] == NULL)
					continue;
				else if (rowlist[i] == NULL && obj.rowlist[i] != NULL)
					return false;
				else if (rowlist[i] != NULL && obj.rowlist[i] == NULL)
					return false;
				else if (rowlist[i]->data == obj.rowlist[i]->data)
					continue;
				else
					return false;
			}
			return true;
		}
		else
			return false;
	}

	SparseMatrix operator + (const SparseMatrix& obj)
	{
		SparseMatrix t;
		if (m == obj.m && n == obj.n)
		{
			vector<Node*>temp1 = rowlist;
			Node* curr1 = NULL;
			vector<Node*>temp2 = obj.rowlist;
			Node* curr2 = NULL;
			t.m = obj.m;
			t.n = obj.n;
			int count = 0;
			for (int i = 0; i < t.m; i++)
			{
				Node* head = NULL;
				Node* tail = NULL;
				curr1 = temp1[i];
				curr2 = temp2[i];

				if (curr1 != NULL && curr2 != NULL)
				{
					while (curr1 != NULL && curr2 != NULL)
					{
						if (curr1->index == curr2->index)
						{
							int sum = curr1->data + curr2->data;
							int index = curr1->index;
							if (count == 0)
							{
								head = new Node(sum, index);
								tail = head;
							}
							else
								InsertAtTail(sum, head, tail, count, index);
							count++;
							curr1 = curr1->next;
							curr2 = curr2->next;
						}

						else
						{
							if (curr1->index < curr2->index)
							{
								int s = 0;
								int t = curr1->data;
								int sum = s + t;
								int index = curr1->index;
								if (count == 0)
								{
									head = new Node(sum, index);
									tail = head;
								}
								else
									InsertAtTail(sum, head, tail, count, index);
								count++;
								curr1 = curr1->next;
							}

							else
							{
								int s = 0;
								int t = curr2->data;
								int sum = s + t;
								int index = curr2->index;
								if (count == 0)
								{
									head = new Node(sum, index);
									tail = head;
								}
								else
									InsertAtTail(sum, head, tail, count, index);
								count++;
								curr2 = curr2->next;
							}

						}
					}
				}

				if (curr1 == NULL && curr2 != NULL)
				{
					while (curr2 != NULL)
					{
						int s = 0;
						int t = curr2->data;
						int index = curr2->index;
						int sum = t + s;
						if (count == 0)
						{
							head = new Node(sum, index);
							tail = head;
						}
						else
							InsertAtTail(sum, head, tail, count, index);
						count++;
						curr2 = curr2->next;
					}
				}

				if (curr2 == NULL && curr1 != NULL)
				{
					while (curr1 != NULL)
					{
						int s = 0;
						int t = curr1->data;
						int index = curr1->index;
						int sum = t + s;

						if (count == 0)
						{
							head = new Node(sum, index);
							tail = head;
						}
						else
							InsertAtTail(sum, head, tail, count, index);
						count++;
						curr1 = curr1->next;
					}
				}

				count = 0;
				t.rowlist.push_back(head);
			}

		}
		else
			cout << "Operation cannot be performed!!!!\nRow or Column size does not match\n";

		return t;
	}

	SparseMatrix transpose()
	{
		SparseMatrix t;
		t.m = n;
		t.n = m;
		vector<Node*>temp1 = rowlist;
		Node* curr = NULL;
		int index, count = 0;
		Node* head = NULL;
		Node* tail = NULL;
		vector<Node*>temp2;
		for (int i = 0; i < t.n; i++)
		{
			curr = temp1[i];
			for (int j = 1; j <= t.m; j++)
			{
				if (curr != NULL)
				{
					index = curr->index;
					if (index != j && count == 0)
					{
						temp2.push_back(NULL);
					}
					if (index == j && count == 0)
					{
						head = new Node(curr->data, i + 1);
						tail = head;
						curr = curr->next;
						temp2.push_back(head);
					}
					if (count > 0)
					{
						Node* a = temp2[index - 1];
						Node* b = a;
						head = a;
						tail = head;
						int size = 0;
						while (a != NULL)
						{
							size++;
							a = a->next;
						}
						if (b != NULL)
						{
							while (b != NULL)
							{
								tail = b;
								b = b->next;
							}
						}
						if (size != 0)
							InsertAtTail(curr->data, head, tail, size, i + 1);
						else
						{
							InsertAtTail(curr->data, head, tail, size, i + 1);
							if (temp2[index - 1] == NULL)
								temp2[index - 1] = tail;

						}
						curr = curr->next;
					}

				}

				else
				{
					if (temp2.size() != t.m)
					{
						while (temp2.size() != t.m)
							temp2.push_back(NULL);
					}
				}

			}
			count++;
		}

		for (int i = 0; i < temp2.size(); i++)
		{
			t.rowlist.push_back(temp2[i]);
		}
		return t;
	}

	~SparseMatrix()
	{
		stack<Node*>temp;
		for (int i = m; i > 0; i--)
		{
			temp.push(rowlist[i - 1]);
			rowlist.pop_back();
		}

		while (temp.empty() == false)
		{
			//delete temp.top();
			temp.pop();
		}

	}

};

int main()
{
	//parameterized constructor
	SparseMatrix m1("sparse-matrix.txt");
	cout << "Parameterized Constructor m1:\n";
	m1.PrintMatrix();
	cout << endl << endl;

	//copy constructor
	SparseMatrix m2(m1); 
	cout << "Copy Constructor m2:\n";
	m2.PrintMatrix();
	cout << endl << endl;

	//assignment operator
	SparseMatrix m3 = m2;
	cout << "Assignment operator m3:\n";
	m3.PrintMatrix();
	cout << endl << endl;

	//== operator
	cout << boolalpha;
	cout << "m3 is equal to m2: " << (m3 == m2) << endl << endl;

	//+ operator
	SparseMatrix m4 = m1 + m2;
	cout << "Sum of m1 and m2:\n";
	m4.PrintMatrix();
	cout << endl << endl;

	//Transpose
	SparseMatrix m5 = m1.transpose();
	cout << "Transpose of m1:\n";
	m5.PrintMatrix();
	cout << endl << endl;

	system("pause");
	return 0;
}