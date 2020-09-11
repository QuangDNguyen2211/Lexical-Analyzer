#ifndef LINKEDLIST_LOCK
#define LINKEDLIST_LOCK

template<class T>
class Node
{
public:
	Node(void) {}
	Node(const T& _data1, const T& _data2, Node* _next);
	// Node( const Node<T> &source );
	// Node &operator=( const Node<T> &source );
	T data1;
	T data2;
	Node* next;
};

template<class T>
class LinkedList
{
public:
	LinkedList(void);
	LinkedList(const LinkedList<T>& source);

	LinkedList<T>& operator=(const LinkedList<T>& source);
	~LinkedList();

	void push_front(const T& item1, const T& item2);
	T showToken(void);
	T showLexeme(void);
	bool isEmpty(void);
	void pop_front(void);
	void clear();
	void reverse();

private:
	Node<T>* list;
	void copy(const LinkedList<T>& source);
};


template<class T>
Node<T>::Node(const T& _data1, const T& _data2, Node<T>* _next)
	: data1(_data1), data2(_data2), next(_next)
{}

template<class T>
LinkedList<T>::LinkedList(void)
	: list(nullptr)
{}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& source)
	: list(nullptr)
{	copy(source);	}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& source)
{
	copy(source);
	return *this;
}

template<class T>
LinkedList<T>::~LinkedList()
{	clear();	}

template<class T>
void LinkedList<T>::push_front(const T& item1, const T& item2)
{
	list = new Node<T>(item1, item2, list);
}

template<class T>
T LinkedList<T>::showToken(void)
{
	if (list == nullptr)
		return nullptr;
	else
		return (list->data1);
}

template<class T>
T LinkedList<T>::showLexeme(void)
{
	if (list == nullptr)
		return nullptr;
	else
		return (list->data2);
}

template<class T>
bool LinkedList<T>::isEmpty(void)
{
	return list == nullptr;
}

template<class T>
void LinkedList<T>::pop_front(void)
{
	Node<T>* junk = list;
	list = list->next;
	delete junk;
}

template<class T>
void LinkedList<T>::clear()
{
	while (list != nullptr)
		pop_front();
}

template<class T>
void LinkedList<T>::reverse()
{
	Node<T>* reversed = nullptr;
	while (list != nullptr)
	{
		// remove a node from list
		Node<T>* aNode = list;
		list = list->next;

		// link that node onto reversed
		aNode->next = reversed;
		reversed = aNode;
	}
	list = reversed;
}

template<class T>
void LinkedList<T>::copy(const LinkedList<T>& source)
{
	clear();
	// make a reversed copy of source into list
	for (Node<T>* np = source.list; np != nullptr; np = np->next)
		// copy each node onto reversed list
		list = new Node<T>(np->data, list);
	reverse();
}

#endif