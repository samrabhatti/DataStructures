#include<iostream>
#include<stack>
#include<vector>
using namespace std;
#define COUNT 5

template<typename T>
class bst
{
private:
	struct Node
	{
		T data;
		Node* rchild;
		Node* lchild;

		Node(const T& d, Node* r = NULL, Node* l = NULL)
		{
			data = d;					//deep copy
			rchild = r;
			lchild = l;
		}

	};

	Node* root;
	int count;

	bool getAccess(const T& key, Node*& par, Node*& curr)
	{													//returns false when key doesnot exist previously
		par = NULL;
		curr = root;
		while (curr != NULL && curr->data != key)
		{
			par = curr;
			//if (key == curr->data)				//key found
			//	return false;
			if (key < curr->data)
				curr = curr->lchild;
			else
				curr = curr->rchild;
		}
		return(curr != NULL);
	}

	bool getAccessUpdated(const T& key, Node*& curr, stack<Node*>& ancestors)
	{													//returns false when key doesnot exist previously
		curr = root;

		if (curr == NULL)
			return false;

		if (key == root->data)
			return true;

		while (curr != NULL)
		{
			ancestors.push(curr);
			if (key == curr->data)				//key found
				return true;
			else if (key < curr->data)
				curr = curr->lchild;
			else
				curr = curr->rchild;
		}
		return false;							//key not found
	}

	void printinOrder(Node* curr)
	{
		if (curr != NULL)			//LNR (Left, Node, Right)
		{
			printinOrder(curr->lchild);
			cout << curr->data << ", ";
			printinOrder(curr->rchild);
		}
	}

	void printPostOrder(Node* curr)
	{
		if (curr != NULL)			//LRN (Left, Right, Node)
		{
			printPostOrder(curr->lchild);
			printPostOrder(curr->rchild);
			cout << curr->data << ", ";
		}
	}

	void cleanup(Node* curr)
	{
		if (curr != NULL)
		{							//LRN
			cleanup(curr->lchild);
			cleanup(curr->rchild);
			delete curr;
		}
	}

	void copy(Node*& curr, Node* objptr)
	{
		if (objptr != NULL)
		{										//NLR (Node, Left, Right)
			curr = new Node(objptr->data);
			copy(curr->lchild, objptr->lchild);
			copy(curr->rchild, objptr->rchild);
		}
	}

	int numOfChild(Node* curr)
	{
		if (curr == NULL)
			return -1;
		else
			return int(curr->lchild != NULL) + int(curr->rchild != NULL);
	}

	void eraseCase0(Node* curr, Node* par)
	{
		if (curr == root)		//only one node
			root = NULL;

		else
		{
			if (curr == par->lchild)
				par->lchild = NULL;
			else
				par->rchild = NULL;
		}

		delete curr;
	}

	void eraseCase1(Node* curr, Node* par)
	{
		if (curr == root)
		{
			if (curr->lchild != NULL)
				root = curr->lchild;
			else
				root = curr->rchild;

			//root = (curr->lchild != NULL) ? curr->lchild : curr->rchild;
		}

		else
		{
			if (curr == par->lchild)
				par->lchild = (curr->lchild != NULL) ? curr->lchild : curr->rchild;
			else                                       //curr==par->rchild
				par->rchild = (curr->lchild != NULL) ? curr->lchild : curr->rchild;
		}

		delete curr;
	}

	void eraseCase2(Node* curr, Node* par)
	{
		Node* temp1 = curr->rchild;
		Node* temp2 = curr;

		while (temp1->lchild != NULL)
		{
			temp2 = temp1;
			temp1 = temp1->lchild;
		}

		curr->data = temp1->data;

		if (numOfChild(temp1) == 0)
			eraseCase0(temp1, temp2);
		else
			eraseCase1(temp1, temp2);
	}

	int getDepth(const T& key)
	{
		int n = 0;
		Node* curr = root;

		while (curr != NULL && curr->data != key)
		{
			if (curr->data > key)
				curr = curr->lchild;
			else
				curr = curr->rchild;

			n++;

			if (curr == NULL)
			{
				cout << "Key not found\n";
				return -1;
			}
		}
		return n;
	}

	int getHeight(Node* curr)
	{
		if (curr == NULL)
			return -1;
		else
		{
			int n1 = getHeight(curr->lchild);
			int n2 = getHeight(curr->rchild);

			int n = 0;
			if (n1 > n2)
				n = n1;
			else
				n = n2;

			return n + 1;
		}
	}

	bool checkBalance(Node* curr)
	{
		if (curr == NULL)
			return true;

		int right = (getHeight(curr->rchild) < 0) ? 0 : getHeight(curr->rchild);
		int left = (getHeight(curr->lchild) < 0) ? 0 : getHeight(curr->lchild);

		int bf = right - left;

		//	int bf = getHeight(curr->rchild) - getHeight(curr->lchild);

		if ((bf <= 1 && bf >= -1) && (checkBalance(curr->lchild) && checkBalance(curr->rchild)))
			return true;

		return false;
	}

	void printTree(Node* root, int space)
	{
		if (root == NULL)
			return;

		space += COUNT;

		printTree(root->rchild, space);
		cout << endl;

		for (int i = COUNT; i < space; i++)
			cout << " ";
		cout << root->data << "\n";

		printTree(root->lchild, space);
		cout << endl;
	}

	Node* createBST(T arr[], Node*& curr, int start, int end)
	{
		int middle = 0;

		if (start > end)
			return NULL;

		else if (start == 0 && end == 0)
			middle = 0;

		else
			middle = (start + end) / 2;

		curr = new Node(arr[middle]);

		createBST(arr, curr->lchild, start, middle - 1);

		createBST(arr, curr->rchild, middle + 1, end);

		return curr;
	}

	void calculateSum(Node* curr, stack<T> stack, vector<int>& sum)
	{
		if (curr != NULL)
		{
			int total = 0;
			stack.push(curr->data);
			if ((curr->lchild == NULL) && (curr->rchild == NULL))
			{
				while (stack.empty() == false)
				{
					total = total + stack.top();
					stack.pop();
				}
				sum.push_back(total);
			}
			else
			{
				calculateSum(curr->lchild, stack, sum);
				calculateSum(curr->rchild, stack, sum);
			}
		}
	}

	void OperatorWorking(Node* curr, stack<T>stack, vector<int>& temp)
	{
		int i = 0;
		if (curr != NULL)
		{
			stack.push(curr->data);
			if ((curr->lchild == NULL) && (curr->rchild == NULL))
			{
				while (stack.empty() == false)
				{
					temp.push_back(stack.top());

					for (int j = 0; j < temp.size() - 1; j++)
					{
						if (temp[j] == stack.top())
							temp.pop_back();
					}
					stack.pop();
				}
			}
			else
			{
				OperatorWorking(curr->lchild, stack, temp);
				OperatorWorking(curr->rchild, stack, temp);
			}
		}
	}

	bool checkEqual(vector<int>temp1, vector<int>temp2)
	{
		int count = 0;
		for (int i = 0; i < temp1.size(); i++)
		{
			for (int j = 0; j < temp2.size(); j++)
			{
				if (temp1[i] == temp2[j])
					count++;
			}
		}

		if (count == temp2.size())
			return true;
		else
			return false;
	}

	bool SameTrees(Node* tree, Node* subtree)
	{
		if (tree == NULL && subtree == NULL)
			return true;

		if (tree == NULL || subtree == NULL)
			return false;

		return (tree->data == subtree->data && SameTrees(tree->lchild, subtree->lchild) && SameTrees(tree->rchild, subtree->rchild));

	}

	bool IsSubTree(Node* tree, Node* subtree)
	{
		if (tree == NULL)
			return false;

		else if (subtree == NULL)
			return true;

		else if (SameTrees(tree, subtree))
			return true;

		return (IsSubTree(tree->lchild, subtree) || IsSubTree(tree->rchild, subtree));

	}

	bool IsSubset(Node* tree, Node* subtree)
	{
		if (tree == NULL || subtree == NULL)
			return false;
		else
		{
			if (tree->data == subtree->data)
			{
				IsSubset(tree->lchild, subtree->lchild);
				IsSubset(tree->rchild, subtree->rchild);

			}
		}
		return true;
	}

	int getBreadth(Node* curr, int level)
	{
		if (curr == NULL)
			return 0;

		if (level == 1)
			return 1;

		return getBreadth(curr->lchild, level - 1) + getBreadth(curr->rchild, level - 1);
	}

	const T& Lowest(const T& a, const T& b)
	{
		Node* curr1 = NULL;
		stack<Node*> ancestor1;
		Node* curr2 = NULL;
		stack<Node*> ancestor2;
		if (getAccessUpdated(a, curr1, ancestor1) == true)
		{
			if (getAccessUpdated(b, curr2, ancestor2) == true)
			{
				while (ancestor1.empty() == false && ancestor2.empty() == false)
				{
					if (ancestor1.size() == ancestor2.size())
					{
						if (ancestor1.top() == ancestor2.top())
							return ancestor1.top()->data;
						else
						{
							ancestor1.pop();
							ancestor2.pop();
						}
					}
					else if (ancestor1.size() > ancestor2.size())
					{
						if (ancestor1.top() == ancestor2.top())
							return ancestor1.top()->data;
						else
							ancestor1.pop();
					}
					else if (ancestor2.size() > ancestor1.size())
					{
						if (ancestor1.top() == ancestor2.top())
							return ancestor1.top()->data;
						else
							ancestor2.pop();
					}
				}
			}
		}
	}

	void Trim(const T& key, Node* curr, int level, int count, int d)
	{
		if (curr == NULL)
			return;

		else
		{
			Node* temp = NULL;
			stack<Node*>ancestor;
			if (count == 0)
			{
				if (getAccessUpdated(key, temp, ancestor) == true)
				{
					d = getDepth(temp->data);
					count++;
				}
			}
			if (curr != NULL)
			{
				if (level < d)
				{
					if (curr->rchild != NULL)
						Trim(d, curr->rchild, level + 1, count, d);
					else if (curr->lchild != NULL)
						Trim(d, curr->lchild, level + 1, count, d);
				}

				else if (level == d)
				{
					curr->lchild == NULL;
					curr->rchild == NULL;
				}
			}


		}
	}

public:

	bst()
	{
		root = NULL;
		count = 0;
	}

	//Task 6
	bst(T sortedData[], int n)
	{
		root = NULL;
		createBST(sortedData, root, 0, n - 1);
	}

	bst(const bst& obj)
	{
		copy(root, obj.root);
	}

	const bst& operator =(const bst& obj)
	{
		cleanup(this->root);
		copy(root, obj.root);
		return*this;
	}

	~bst()
	{
		cleanup(root);
	}

	void Insert(const T& data)
	{
		Node* par, * curr;
		if (getAccess(data, par, curr) == false)
		{
			Node* temp = new Node(data);

			if (par == NULL)				//tree is empty
				root = temp;
			else
			{
				if (par->data > data)
					par->lchild = temp;
				else
					par->rchild = temp;
			}

			count++;
			cout << "Insert ( " << data << " ) Performed\n";
		}

		else
		{
			cout << "Insert ( " << data << " ) Operation cannot be performed......SIMILAR DATA FOUND!!!!!\n";
		}
	}

	//Task 1
	void Erase(const T& key)
	{
		Node* par, * curr;
		if (getAccess(key, par, curr) == true)			//key found
		{
			/*if (par->data > key)
				Node* curr = par->lchild;
			else
				Node* curr = par->rchild;*/

				/*if (par == NULL)
					par = root;

				Node* curr = (par->data > key) ? par->lchild : par->rchild;		*/	//tertiary operator

			if (numOfChild(curr) == 0)
				eraseCase0(curr, par);
			else if (numOfChild(curr) == 1)
				eraseCase1(curr, par);
			else
				eraseCase2(curr, par);

			count--;
			cout << "Erase ( " << key << " ) Performed\n";
		}
	}

	void PrintInOrder()
	{
		//cout << "\nPrint In Order Called\n";
		printinOrder(root);
	}

	//Task 4
	int Depth(const T& key)
	{
		int depth = getDepth(key);
		return depth;
	}

	//Task 3
	int Heigth()
	{
		return getHeight(root);
	}

	//Task 5
	bool IsBalanced()
	{
		return checkBalance(root);
	}

	//Task 2 (a)
	const T& Successor(const T& key)
	{
		stack<Node*>ancestor;
		Node* curr = NULL;
		Node* temp = NULL;

		if (getAccessUpdated(key, curr, ancestor))
		{
			//Case 1: curr has a right subtree
			if (curr->rchild != NULL)
			{
				curr = curr->rchild;
				while (curr->lchild != NULL)
				{
					curr = curr->lchild;
				}
				return curr->data;
			}

			//Case 2: curr dont have a right subtree
			if (curr->rchild == NULL)
			{
				while (ancestor.empty() == false)
				{
					temp = ancestor.top();
					if (temp->data > curr->data)
						return temp->data;
					else
						ancestor.pop();
				}
			}

			cout << "No Successor Found\n";
			return 0;
		}

	}

	//Task 2(b)
	const T& Predecessor(const T& key)
	{
		stack<Node*>ancestor;
		Node* curr = NULL;
		Node* temp = NULL;

		if (getAccessUpdated(key, curr, ancestor))
		{
			//Case 1: curr has a left subtree
			if (curr->lchild != NULL)
			{
				curr = curr->lchild;
				while (curr->rchild != NULL)
				{
					curr = curr->rchild;
				}
				return curr->data;
			}

			//Case 2: curr has no left subtree
			if (curr->lchild == NULL)
			{
				while (ancestor.empty() == false)
				{
					temp = ancestor.top();
					if (temp->data < curr->data)
						return temp->data;
					else
						ancestor.pop();
				}
			}

			cout << "No Predecessor Found\n";
			return 0;
		}

	}

	void PrintTree()
	{
		printTree(root, 0);
	}

	//Task 7
	void PathSum()
	{
		vector<int> sum;
		stack<T> s;
		calculateSum(root, s, sum);

		for (int i = 0; i < sum.size(); i++)
			cout << sum[i] << ", ";
	}

	//Task 8
	bool operator==(const bst& obj)
	{
		vector<int> temp1, temp2;
		stack<int>stack1, stack2;

		OperatorWorking(root, stack1, temp1);
		OperatorWorking(obj.root, stack2, temp2);

		return checkEqual(temp1, temp2);

	}

	//Task 9
	bool SubTree(const bst& obj)
	{
		return IsSubTree(root, obj.root);
	}

	//Task 10
	bool SubSet(const bst& obj)
	{
		return IsSubset(root, obj.root);
	}

	//Task 11
	void SearchAndPromote(const T& element)
	{
		Node* curr = NULL;
		Node* par = NULL;
		Node* temp = NULL;
		stack<Node*>ancestor;
		if (getAccessUpdated(element, curr, ancestor) == true)
		{
			if (ancestor.empty() == true)
				return;
			else
			{
				while (!ancestor.empty())
				{
					if (ancestor.size() == 1)
					{
						Erase(element);
						temp = new Node(element);
						par = ancestor.top();
						ancestor.pop();
						if (temp->data > par->data)
							temp->lchild = par;
						else
							temp->rchild = par;

						root = temp;

					}
					else
					{
						ancestor.pop();
					}
				}
			}
		}
	}

	//Task 12
	int Breadth()
	{
		int max = 0;
		int breadth = 0;

		for (int i = 0; i < getHeight(root) + 1; i++)
		{
			breadth = getBreadth(root, i + 1);
			if (max < breadth)
				max = breadth;
		}
		return breadth;
	}

	//Task 13
	void TrimBelowK(const T& k)
	{
		Trim(k, root, 0, 0, 0);
	}

	//Task 14
	const T& LowestCommonAncestor(const T& a, const T& b)
	{
		T res = Lowest(a, b);
		if (res == a)
			cout << a << " is the key as well\n";
		else if (res == b)
			cout << b << " is the key as well\n";
		return res;
	}

};

int main()
{
	bst <int> t1;
	t1.Insert(50);
	t1.Insert(35);
	t1.Insert(70);
	t1.Insert(2);
	t1.Insert(61);
	t1.Insert(81);
	t1.Insert(55);
	t1.Insert(63);
	t1.Insert(93);
	cout << "\n\t********* Tree 1 *************\n";
	t1.PrintInOrder();
	cout << endl;
	t1.PrintTree();
	cout << endl << endl;

	//********* Task 1: Erase *************
	cout << "\t********* Task 1: Erase *************\n";
	t1.Erase(70);
	t1.PrintInOrder();
	cout << endl;
	t1.PrintTree();
	cout << endl << endl;

	//********* Task 2(a): Successor ************
	cout << "\t********* Task 2(a): Successor ************\n";
	cout << "Successor(61) in T1: ";
	cout << t1.Successor(61);
	cout << endl << endl;

	//********* Task 2(b): Predecessor ************
	cout << "\t********* Task 2(b): Predecessor ************\n";
	cout << "Predecessor(61) in T1: ";
	cout << t1.Predecessor(61);
	cout << endl << endl;

	//********* Task 3: Height ************
	cout << "\t********* Task 3: Height ************\n";
	cout << "Height of tree is: ";
	cout << t1.Heigth();
	cout << endl << endl;


	//******** Task 4: Depth ************
	cout << "\t******** Task 4: Depth ************\n";
	cout << "Depth(61) in T1: ";
	cout << t1.Depth(61);
	cout << endl << endl;

	//******** Task 5: Balanced ************
	cout << "\t******** Task 5: Balanced ************\n";
	cout << "Is T1 balanced? : ";
	if (t1.IsBalanced() == true)
		cout << "Yes\n";
	else
		cout << "No\n";
	cout << endl;


	//******************TREE 2 *********************
	cout << "\t********* Tree 2 *************\n";

	//******* Task 6: Sorted Array *************
	cout << "\t******* Task 6: Sorted Array *************\n";
	cout << "\n\n\t\t\tTree 2 is: \n";
	int arr[8] = { 2, 35, 50, 55, 61, 63, 81, 93 };
	bst<int> t2(arr, 8);
	t2.PrintInOrder();
	cout << endl;
	if (t2.IsBalanced() == true)
		cout << "Balanced\n";
	else
		cout << "Not Balanced\n";

	t2.PrintTree();

	//******** Task 7: Path Sum *************
	cout << "\t******** Task 7: Path Sum *************\n";
	cout << "Path Sum in T2 is: ";
	t2.PathSum();
	cout << endl << endl;

	//********* Task 8: Operator ==  ************
	cout << "\t********* Task 8: Operator ==  ************\n";
	cout << "Are both trees equal? : ";
	if (t1 == t2)
		cout << "Yes\n";
	else
		cout << "No\n";
	cout << endl;

	//********* Task 9: Subtree ************
	cout << "\t********* Task 9: Subtree ************\n";
	cout << "Is T2 a subtree of T1? : ";
	if (t1.SubTree(t1) == false)
		cout << " No\n";
	else
		cout << "Yes\n";
	cout << endl;

	//********* Task 10: Subset ************
	cout << "\t********* Task 10: Subset ************\n";
	cout << "Is T2 a subset of T1? : ";
	if (t1.SubSet(t2) == true)
		cout << " Yes\n";
	else
		cout << "No\n";
	cout << endl;

	//******* Task 11: Search And Promote *********
	cout << "\t******* Task 11: Search And Promote *********\n";
	cout << "Search And Promote (93) in T2: ";
	t2.SearchAndPromote(93);
	t2.PrintInOrder();
	cout << endl;
	t2.PrintTree();

	//******** Task 12: Breadth **************
	cout << "\t******** Task 12: Breadth **************\n";
	cout << "Maximum Breadth of T2: ";
	cout << t2.Breadth() << endl;
	cout << endl;

	//******** Task 13: Trim Below K ***********
	cout << "\t******** Task 13: Trim Below K ***********\n";
	cout << "Trim Below k (63) in T2: ";
	t2.TrimBelowK(63);
	t2.PrintInOrder();
	cout << endl;
	t2.PrintTree();

	//******* Task 14: Lowest Common Ancestor *********
	cout << "\t******* Task 14: Lowest Common Ancestor *********\n";
	cout << "Lowest Common Ancestor (55,81) in T2: ";
	cout << t2.LowestCommonAncestor(55, 81);
	cout << endl << endl << endl;

	system("pause");
	return 0;

}
