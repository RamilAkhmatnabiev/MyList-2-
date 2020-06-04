

#include <iostream>
#include <string>
using namespace std;

enum BestPositionEnum
{
	FRONT,
	BACK
};

template <typename T>
class MyList
{
public:
	MyList<T>();
	~MyList<T>();
	int GetSize() { return Size; }
	T& operator[](int index);
	void PrintToConsole();
	void Clear();
	void Push_back(T data);
	void Push_front(T data);
	void Pop_back();
	void Pop_front();
	void Add_to(T data, int index);
	void Delete_to(int index);
	


private:
	template <typename T>
	class Node
	{
	public:
		T data;
		Node* pNext;
		Node* pPrev;

		Node(T data = T(), Node* pPrev = nullptr, Node* pNext = nullptr)
		{
			this->data = data;
			this->pPrev = pPrev;
			this->pNext = pNext;

		}
	};

	int Size;
	Node<T>* head;
	Node<T>* tail;

	BestPositionEnum GiveBestPosition(int index);
	Node<T>* GiveThisPosNode(int index)
	{
		int length = GetSize();
		if (index == 0)
		{
			return head;
		}
		else
		{
			if (index == length - 1)
			{
				return tail;
			}
			else
			{
				BestPositionEnum check = GiveBestPosition(index);
				if (check == BestPositionEnum::FRONT)
				{
					Node<T>* current = head;
					for (int i = 0; i < index; i++)
					{
						current = current->pNext;
					}
					return current;
				}
				if (check == BestPositionEnum::BACK)
				{
					Node<T>* current = tail;
					for (int i = Size - 1; i > index; i--)
					{
						current = current->pPrev;
					}
					return current;
				}
			}
		}

	}

};

template <typename T>
MyList<T>::MyList()
{
	head = nullptr;
	tail = nullptr;
	Size = 0;
}

template <typename T>
MyList<T>::~MyList()
{
	this->Clear();
}

template<typename T>
T& MyList<T>::operator[](int index)
{
	/*BestPositionEnum check = GiveBestPosition(index);
	if (check == BestPositionEnum::FRONT)
	{
		Node<T>* current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->pNext;
		}
		return current->data;
	}
	if (check == BestPositionEnum::BACK)
	{
		Node<T>* current = tail;
		for (int i = Size - 1; i > index; i--)
		{
			current = current->pPrev;
		}
		return current->data;
	}*/

	Node<T>* thisNode = GiveThisPosNode(index);
	return thisNode->data;
}

template<typename T>
void MyList<T>::PrintToConsole()
{
	int length = this->GetSize();
	if (length == 0)
	{
		cout << "empty list" << endl;
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			cout <<this->operator[](i)<< endl;
		}
	}
}

template<typename T>
void MyList<T>::Clear()
{
	//особый случай когда size = 1. Логиkа такая, что при сайз = 1 tail и head будут иметь одинакувую память
	int length = this->GetSize();
	if (length == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		if (length > 1)
		{
			for (int i = 0; i < length; i++)
			{
				Pop_front();

			}
		}
	}

}

template<typename T>
void MyList<T>::Push_back(T data)
{
	if ((this->head == nullptr) && (this->tail == nullptr)) // (Size == 0)
	{
		this->head = new Node<T>(data);
		this->tail = head;
		Size++;
	}
	else
	{
		//if (this->head == this->tail) // size == 1 ????
		//{
		//	this->tail = new Node<T>(data, head);
		//	this->head->pNext = tail;
		//}
		//else
		//{
		//	cout << "++";
		//}
		Node<T>* oldTail = tail;
		//tail = new Node<T>(data, oldTail);
		tail = new Node<T>(data, oldTail);
		oldTail->pNext = tail;
		Size++;
	}
}

template<typename T>
void MyList<T>::Push_front(T data)
{
	if (Size == 0) // (this->head == nullptr) && (this->tail == nullptr)
	{
		this->head = new Node<T>(data);
		this->tail = head;
		Size++;
	}
	else
	{
		
		Node<T>* oldHead = head;
		head = new Node<T>(data, nullptr, oldHead);
		oldHead->pPrev = head;
		Size++;
	}
}

template<typename T>
void MyList<T>::Pop_back()
{
	if (Size > 1)
	{
		Node<T>* newTail = tail->pPrev;
		newTail->pNext = nullptr;
		delete tail;
		tail = newTail;
		Size--;
	}
	else
	{
		if (Size == 1)
		{
			head = nullptr;
			tail = nullptr;
			Size = 0;
		}
	}
}

template<typename T>
void MyList<T>::Pop_front()
{
	if (Size > 1)
	{
		Node<T>* newHead = head->pNext;
		newHead->pPrev = nullptr;
		delete head;
		head = newHead;
		Size--;
	}
	else
	{
		if (Size == 1)
		{
			head = nullptr;
			tail = nullptr;
			Size = 0;
		}
	}
}

template<typename T>
void MyList<T>::Delete_to(int index)
{
	int length = GetSize();
	if (index ==0)
	{
		Pop_front();
	}
	else
	{
		if (index == length - 1)
		{
			Pop_back();
		}
		else
		{
			Node<T>* thisIndexNode = GiveThisPosNode(index);
			Node<T>* prevNode = thisIndexNode->pPrev;
			Node<T>* nextNode = thisIndexNode->pNext;
			prevNode->pNext = nextNode;
			nextNode->pPrev = prevNode;
			delete thisIndexNode;
			Size--;
			
		}
	}
}

template<typename T>
void MyList<T>::Add_to(T data, int index) // переделать с GiveThisPosNode
{
	int length = GetSize();
	if (index == 0)
	{
		Push_front(data);
	}
	else
	{
		if (index == length)
		{
			Push_back(data);
		}
		else
		{
			BestPositionEnum bestPosition = GiveBestPosition(index);
			if (bestPosition == BestPositionEnum::FRONT)
			{
				Node<T>* current = head;
				Node<T>* prevCurrent = nullptr;
				for (int i = 0; i < index; i++)
				{
					prevCurrent = current;
					current = current->pNext;
				}
				Node<T>* newNode = new Node<T>(data, prevCurrent, current);
				prevCurrent->pNext = newNode;// its ok
				current->pPrev = newNode;
				Size++;

			}
			if (bestPosition == BestPositionEnum::BACK)
			{
				Node<T>* current = tail;
				Node<T>* nextCurrent = nullptr;
				for (int i = length; i > index; i--)
				{
					nextCurrent = current;
					current = current->pPrev;
				}
				Node<T>* newNode = new Node<T>(data, current, nextCurrent);
				current->pNext = newNode;
				nextCurrent->pPrev = newNode;
				Size++;
			}


		}
	}
}

template<typename T>
BestPositionEnum MyList<T>::GiveBestPosition(int index)
{

	int midle = Size / 2;
	if (index + 1 <= midle)
	{
		return FRONT;
	}
	else
	{
		return BACK;
	}
}

int main()
{

	MyList<int> lst;
	int size;
	size = 10;
	for (size_t i = 0; i < size; i++)
	{
		lst.Push_back(rand() % 100);
	}
	lst.PrintToConsole();
	cout << endl;

	lst.Add_to(111111, 5);
	lst.PrintToConsole();

	

	cout << endl;
	lst.Clear();
	lst.PrintToConsole();
	
}
