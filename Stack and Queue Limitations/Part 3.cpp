#include<iostream>
using namespace std;

template<typename T>
class Queue
{
private:
	T* arr;
	int cap;
	int size;
	int front;
	int rear;

	int next(int i)
	{
		return (i + 1) % cap;
	}

public:
	Queue()
	{
		arr = 0;
		cap = 0;
		size = 0;
		front = 0;
		rear = 0;
	}

	Queue(int s)
	{
		cap = s;
		arr = new T[cap + 1];
		size = 0;
		front = 0;
		rear = 0;
	}

	Queue(const Queue& obj)
	{
		this->arr = obj.arr;
		this->cap = obj.cap;
		this->front = obj.front;
		this->rear = obj.rear;
		this->size = obj.size;
	}

	~Queue()
	{
		delete[]arr;
		arr = 0;
		cap = size = front = rear = 0;
	}

	void Enqueue(const T& element)
	{
		if (cap == 0)
		{
			cap = 2;
			arr = new T[2];
			front = 0;
			rear = 1;
			arr[rear] = element;
			size = 1;
		}

		else if (size + 1 >= cap)				//    size+1==cap
		{
			T* temp = new T[cap * 2];
			for (int i = next(front), k = 0; k < size; i = next(i))
			{
				temp[k + 1] = arr[i];
				k++;
			}
			cap = cap * 2;
			front = 0;
			rear = size;
			rear++;
			temp[rear] = element;
			size++;
			delete[]arr;
			arr = temp;
		}

		else								//    size<cap
		{
			//front = 0;
			rear = next(rear);
			//rear++;
			arr[rear] = element;
			size++;
		}

	}

	void Dequeue()
	{
		if (size == 0)
			return;

		else if (size < cap / 2)
		{
			T* temp = new T[cap / 2];
			for (int i = next(front), k = 0; k < size; i = next(i))
			{
				temp[k + 1] = arr[i];
				k++;
			}
			cap = cap / 2;
			rear = size;
			front = 0;
			front++;
			size--;
			//rear = next(size);
			delete[]arr;
			arr = temp;
		}

		else                // size>=cap/2
		{
			front++;
			size--;
		}

	}

	const T& Peek()
	{
		return arr[next(front)];
	}

	void Display()
	{
		for (int i = next(front), count = 0; count < size; i = next(i))
		{
			cout << arr[i] << " ,";
			count++;
		}
		cout << endl;
	}

	int Size()
	{
		return size;
	}

};

int MinimumIndex(Queue<int>& q1, int sortIndex)
{
	Queue<int>temp1;
	int index = -1;
	int value = INT_MAX;
	int size = q1.Size();
	int x;

	for (int i = 0; i < size; i++)
	{
		x = q1.Peek();
		q1.Dequeue();
		temp1.Enqueue(x);
	}

	for (int i = 0; i < size; i++)
	{
		int curr = temp1.Peek();
		temp1.Dequeue();

		if (curr <= value && i <= sortIndex)
		{
			index = i;
			value = curr;
		}
		temp1.Enqueue(curr);
	}

	for (int i = 0; i < size; i++)
	{
		x = temp1.Peek();
		temp1.Dequeue();
		q1.Enqueue(x);
	}

	return index;
}

void Insert(Queue<int>& q1, int index)
{
	Queue<int>temp2;
	int value;
	int size = q1.Size();
	int x;

	for (int i = 0; i < size; i++)
	{
		x = q1.Peek();
		q1.Dequeue();
		temp2.Enqueue(x);
	}

	for (int i = 0; i < size; i++)
	{
		int curr = temp2.Peek();
		temp2.Dequeue();
		if (i != index)
			temp2.Enqueue(curr);
		else
			value = curr;
	}

	temp2.Enqueue(value);

	for (int i = 0; i < size; i++)
	{
		x = temp2.Peek();
		temp2.Dequeue();
		q1.Enqueue(x);
	}

}

void SortQueue(Queue<int>& q1)
{
	for (int i = 1; i <= q1.Size(); i++)
	{
		int min = MinimumIndex(q1, q1.Size() - i);
		Insert(q1, min);
	}

}

int main()
{
	int size = 6;
	Queue<int>q(size);

	q.Enqueue(4);
	q.Enqueue(1);
	q.Enqueue(6);
	q.Enqueue(9);
	q.Enqueue(0);

	cout << "Queue:				(Before ordering elements in ascending order from front to rear)\n";
	q.Display();
	cout << endl;

	SortQueue(q);

	cout << "Queue:				(After ordering elements in ascending order from front to rear)\n";
	while (q.Size() != 0)
	{
		cout << q.Peek() << ", ";
		q.Dequeue();
	}
	cout << endl << endl;

	system("pause");
	return 0;
}