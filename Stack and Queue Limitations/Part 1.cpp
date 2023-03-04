#include<iostream>
using namespace std;

template<typename T>
class Stack
{
private:
	T* arr;
	int size;			//current size
	int top;
	int cap;			//total size
public:
	Stack()
	{
		arr = 0;
		size = 0;
		top = -1;
		cap = 0;
	}

	Stack(int s)
	{
		cap = s;
		arr = new T[cap];
		top = -1;
		size = 0;
	}

	Stack(const Stack& obj)
	{
		size = obj.size;
		top = obj.top;
		cap = obj.cap;
		arr = obj.arr;
	}

	~Stack()
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
			for (int i = 0; i < cap; i++)
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

	T Pop()
	{
		if (size == 0)
		{
			cout << "Stack Underflow\n";
			return 0;
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
			return arr[top];
		}

		else              // size>=cap/2
		{
			top--;
			size--;
			return arr[top];
		}
	}

	const T& Peek()
	{
		if (size == 0)
			cout << "Stack Underflow\n";
		else
			return arr[top];
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

};

template <typename T>
void TransferData(Stack<T>& s1, Stack<T>& s2, int size)
{
	Stack<T>temp;			//additional stack
	T x;

	for (int i = 0; i < size; i++)
	{
		x = s1.Peek();
		s1.Pop();
		temp.Push(x);
	}

	for (int i = 0; i < size; i++)
	{
		x = temp.Peek();
		temp.Pop();
		s2.Push(x);
	}

}


int main()
{
	int size = 5;
	Stack<int>s(size), t(size);

	for (int i = 3; i < 8; i++)
	{
		s.Push(i);
	}

	cout << "\tBefore Data Transfer: \n";
	cout << "Stack S: ";
	s.Display();
	cout << "Stack T: ";
	t.Display();
	cout << endl;

	TransferData(s, t, size);

	cout << "\tAfter Data Transfer: \n";
	cout << "Stack S: ";
	s.Display();
	cout << "Stack T: ";
	t.Display();
	cout << endl;

	system("pause");
	return 0;
}