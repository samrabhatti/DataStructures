#include<iostream>
using namespace std;

template<typename T>
class InvertibleStack
{
private:
	T* arr;
	int size;			//current size
	int top;
	int cap;			//total size

	int next(int i)
	{
		return (i + 1) % 10;
	}

public:
	InvertibleStack()
	{
		arr = 0;
		size = 0;
		top = -1;
		cap = 0;
	}

	InvertibleStack(int s)
	{
		cap = s;
		arr = new T[cap];
		top = -1;
		size = 0;
	}

	InvertibleStack(const InvertibleStack& obj)
	{
		size = obj.size;
		top = obj.top;
		cap = obj.cap;
		arr = obj.arr;
	}

	~InvertibleStack()
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

		else if (size < cap)		// size less than capacity
		{
			top++;
			arr[top] = element;
			size++;
		}

		else                   //	size>=cap		size greater than capacity
		{						//array grows by double 
			T* temp = new T[cap * 2];
			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			cap = cap * 2;
			size++;
			top++;
			temp[top] = element;
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

	void FlipStack()
	{
		T* temp = new T[cap];
		for (int i = next(-1), j = size; i < size; i = next(i), j--)
		{
			temp[j - 1] = arr[i];
			if (i + 1 == size)
				break;
		}
		delete[]arr;
		arr = temp;
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

	int GetSize()
	{
		return size;
	}

};

int main()
{
	InvertibleStack<int> s(5);

	cout << "Stack:		(Before Flipping)\n\t";
	for (int i = 0; i < 9; i++)
	{
		s.Push(rand()%100+1);
	}
	s.Display();
	cout << "Top: " << s.Top() << endl;
	cout << "Peek: " << s.Peek() << endl << endl;

	cout << "Stack:		(After Flipping)\n\t";
	s.FlipStack();
	s.Display();

	cout << "Top: " << s.Top() << endl;
	cout << "Peek: " << s.Peek() << endl << endl;

	cout << "Stack:		(After popping 3 elements)\n\t";
	for (int i = 0; i < 3; i++)
	{
		s.Pop();
	}
	s.Display();

	cout << "Top: " << s.Top() << endl;
	cout << "Peek: " << s.Peek() << endl << endl;

	cout << "Stack:		(After Flipping)\n\t";
	s.FlipStack();
	s.Display();
	cout << endl;

	cout << "Top: " << s.Top() << endl;
	cout << "Peek: " << s.Peek() << endl << endl;

	system("pause");
	return 0;
}