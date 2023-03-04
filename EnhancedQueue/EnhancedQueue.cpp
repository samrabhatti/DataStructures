#include<iostream>
using namespace std;

template<typename T>
class EnhancedQueue
{
private:
	T* arr;
	int rear;
	int front;
	int cap;
	int size;

	int next(int i)
	{
		return (i + 1) % cap;
	}

public:
	EnhancedQueue()
	{
		arr = 0;
		rear = 0;
		front = 0;
		cap = 0;
		size = 0;
	}

	EnhancedQueue(int s)
	{
		cap = s;
		arr = new T[cap];
		rear = 0;
		front = 0;
		size = 0;
	}

	~EnhancedQueue()
	{
		delete[]arr;
		arr = 0;
		cap = size = front = rear = 0;
	}

	void EnqueueAtFront(const T& element)
	{
		if (cap == 0)
		{
			cap = 2;
			arr = new T[2];
			front = 1;
			rear++;
			arr[0] = element;
			size = 1;
		}

		else if (size + 1 < cap)
		{
			T* temp = new T[cap];
			for (int i = next(-1), k = 0; k < size + 1; i = next(i))
			{
				temp[k + 1] = arr[i];
				k++;
			}
			front++;
			rear++;
			temp[0] = element;
			size++;
			delete[]arr;
			arr = temp;
		}

		else                       //  size>=cap or size+1==cap
		{
			T* temp = new T[cap * 2];
			for (int i = next(-1), k = 0; k < size + 1; i = next(i))
			{
				temp[k + 1] = arr[i];
				k++;
			}
			cap = cap * 2;
			front++;
			rear++;
			temp[0] = element;
			size++;
			delete[]arr;
			arr = temp;
		}

	}

	void DequeueAtFront()
	{
		if (size == 0)
			return;

		else if (size < cap / 2)
		{
			T* temp = new T[cap / 2];
			for (int i = next(0), k = 0; k < size + 1; i = next(i))
			{
				temp[k] = arr[i];
				k++;
			}
			cap = cap / 2;
			front--;
			rear = front;
			size--;
			delete[]arr;
			arr = temp;
		}

		else                // size>=cap/2
		{
			T* temp = new T[cap];
			for (int i = next(0), k = 0; k < size + 1; i = next(i))
			{
				temp[k] = arr[i];
				k++;
			}
			front--;
			rear = front;
			size--;
			delete[]arr;
			arr = temp;
		}

	}

	void EnqueueAtRear(const T& element)
	{
		if (cap == 0)
		{
			cap = 2;
			arr = new T[2];
			rear = 1;
			arr[rear] = element;
			size = 1;
		}

		else if (size + 1 >= cap)
		{
			T* temp = new T[cap * 2];
			for (int i = next(front), k = 0; k < size + 1; i = next(i))
			{
				temp[k + 1] = arr[i];
				k++;
			}
			cap = cap * 2;
			rear = size;
			rear++;
			temp[rear] = element;
			size++;
			delete[]arr;
			arr = temp;
		}

		else								//    size<cap
		{
			rear = next(rear);
			arr[rear] = element;
			size++;
		}

	}

	void DequeueAtRear()
	{
		if (size == 0)
			return;

		else if (size < cap / 2)
		{
			T* temp = new T[cap / 2];
			for (int i = next(-1), k = 0; k < size; i = next(i))
			{
				temp[k] = arr[i];
				k++;
			}
			cap = cap / 2;
			rear--;
			size--;
			delete[]arr;
			arr = temp;
		}

		else
		{
			T* temp = new T[cap];
			for (int i = next(-1), k = 0; k < size; i = next(i))
			{
				temp[k] = arr[i];
				k++;
			}
			rear--;
			size--;
			delete[]arr;
			arr = temp;
		}
	}

	const T& PeekFront()
	{
		return arr[front - 1];
	}

	const T& PeekRear()
	{
		return arr[next(front)];
	}

	int Size()
	{
		return size;
	}

	bool Empty()
	{
		if (size == 0)
			return true;
	}

	void Display()
	{
		for (int i = next(-1), count = 0; count < size + 1; i = next(i))
		{
			cout << arr[i] << " ,";
			count++;
		}
		cout << endl;
	}

};

int main()
{
	EnhancedQueue<int>q(5);
	cout << "Enqueue At Front:\t";
	q.EnqueueAtFront(5);
	q.Display();
	cout << "Enqueue At Front:\t";
	q.EnqueueAtFront(3);
	q.Display();
	cout << "Enqueue At Front:\t";
	q.EnqueueAtFront(9);
	q.Display();

	cout << "Dequeue At Front:\t";
	q.DequeueAtFront();
	q.Display();

	cout << "Dequeue At Front:\t";
	q.DequeueAtFront();
	q.Display();

	cout << "Enqueue At Front:\t";
	q.EnqueueAtFront(2);
	q.EnqueueAtFront(1);
	q.EnqueueAtFront(0);
	q.EnqueueAtFront(4);
	q.EnqueueAtFront(6);
	q.Display();
	for (int i = 0; i < 4; i++)
	{
		cout << "Dequeue At Front:\t";
		q.DequeueAtFront();
		q.Display();
	}

	cout << "Enqueue At Rear:\t";
	q.EnqueueAtRear(7);
	q.EnqueueAtRear(8);
	q.Display();

	cout << "Enqueue At Front:\t";
	q.EnqueueAtFront(1);
	q.Display();

	cout << "Enqueue At Rear:\t";
	q.EnqueueAtRear(15);
	q.Display();

	cout << "Enqueue At Front:\t";
	q.EnqueueAtFront(0);
	q.Display();

	cout << "Enqueue At Rear:\t";
	q.EnqueueAtRear(22);
	q.Display();

	cout << "Dequeue At Rear:\t";
	q.DequeueAtRear();
	q.Display();

	cout << "Dequeue At Front:\t";
	q.DequeueAtFront();
	q.Display();

	cout << "Dequeue At Rear:\t";
	q.DequeueAtRear();
	q.Display();

	cout << "\n\nThe value -842150451 is the value of the index where the front is placed (the dummy node) \n\n";

	cout << "Peek of Rear:\t" << q.PeekRear() << endl;

	cout << "Peek of Front:\t" << q.PeekFront() << endl << endl;

	cout << "Dequeue At Front:\t";
	q.DequeueAtFront();
	q.Display();

	system("pause");
	return 0;
}
