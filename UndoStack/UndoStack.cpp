#include<iostream>
using namespace std;

template<typename T>
class UndoStack
{
private:
	T* arr;
	int size;			//current size
	int top;
	int cap;			//total size
public:
	UndoStack()
	{
		arr = 0;
		size = 0;
		top = -1;
		cap = 0;
	}

	UndoStack(int s)
	{
		cap = s;
		arr = new T[cap];
		top = -1;
		size = 0;
	}

	UndoStack(const UndoStack& obj)
	{
		size = obj.size;
		top = obj.top;
		cap = obj.cap;
		arr = obj.arr;
	}

	~UndoStack()
	{
		delete[]arr;
		arr = 0;
		cap = size = top = 0;
	}

	void Push(const T& element)
	{
		if (cap == 0)				//capacity is zero
		{
			cap = 1;
			arr = new T[cap];
			top++;
			arr[top] = element;
			size = 1;
		}

		if (size < cap)		// size less than capacity
		{
			top++;
			arr[top] = element;
			size++;
		}

		else                   //	size>=100		size greater than capacity
		{
			T* temp = new T[100];
			for (int i = 1, j = 0; i < size; i++, j++)
			{
				temp[j] = arr[i];
			}
			temp[top] = element;
			top++;
			//size++;
			delete[]arr;
			arr = temp;
		}
	}

	void Pop()
	{
		if (size == 0)
		{
			cout << "Stack Underflow\n";
		}

		else if (size < cap / 2)
		{								//array shrinks to half
			T* temp = new T[cap / 2];
			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			cap = cap / 2;
			top--;
			size--;
			delete[]arr;
			arr = temp;
		}

		else              // size>=cap/2
		{
			top--;
			size--;
		}
	}

	const T& Peek()
	{
		if (size == 0)
			cout << "Stack Underflow\n";
		else
			return arr[top];
	}

	bool Empty()
	{
		if (size == 0 && top == -1)
			return true;
		else
			return false;
	}

	bool Full()
	{
		if (size == cap)
			return true;
		else
			return false;
	}

	void Display()
	{
		for (int i = 0; i < size - 1; i++)
		{
			cout << arr[i] << ", ";
		}

		for (int i = size - 1; i < size; i++)
		{
			cout << arr[i];
		}

		cout << endl;
	}

	int Top()
	{
		return top;
	}

};

int main()
{
	UndoStack<int>s(100), s1(100);
	cout << "100 elements pushed: " << endl;
	for (int i = 0; i < 100; i++)
	{
		s.Push(i+1);
	}
	s.Display();

	cout << "\n101 elements pushed: " << endl;
	for (int i = 0; i < 101; i++)
	{
		s1.Push(i+1);
	}
	s1.Display();

	cout << "\n1 element popped: " << endl;
	s1.Pop();
	s1.Display();

	cout << "\n1 element popped: " << endl;
	s1.Pop();
	s1.Display();

	system("pause");
	return 0;
}