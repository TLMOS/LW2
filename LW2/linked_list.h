#include <cstdlib>
#include <cstring>
#include <stdexcept>

#pragma once

template<class T>
class LinkedList
{
private:	
	struct Node
	{
		T item;
		Node* previous;
		Node* next;
	};

	Node* first_;
	Node* last_;
	int length_;

public:
	LinkedList();
	LinkedList(T* items, int count);
	LinkedList(const LinkedList<T>& list);
	~LinkedList();

	T GetFirst();
	T GetLast();
	T Get(int index);
	LinkedList<T> GetSubList(int startIndex, int endIndex);
	int length();

	void Append(T item);
	void Prepend(T item);
	void InsertAt(T item, int index);
	LinkedList<T> Concat(LinkedList<T>& list);

	T& operator[](int index);
	const T& operator[](int index) const;
};

template<class T>
inline LinkedList<T>::LinkedList() {
	first_ = NULL;
	last_ = NULL;
	length_ = 0;
}

template<class T>
inline LinkedList<T>::LinkedList(T* items, int count) : LinkedList()
{
	if (count < 0)
		throw std::invalid_argument("Received negative count");

	for(int i = 0; i < count; i++)
		Append(items[i]);
}

template<class T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& list) : LinkedList()
{
	Node* node = list.first_;
	for (int i = 0; i < list.length_; i++) {
		Append(node->item);
		node = node->next;
	}
}

template<class T>
inline LinkedList<T>::~LinkedList()
{
	struct Node* tmp;
	last_ = NULL;
	while (first_ != NULL)
	{
		tmp = first_->next;
		delete first_;
		first_ = tmp;
	}
}

template<class T>
inline T LinkedList<T>::GetFirst()
{
	if (!length_)
		throw std::out_of_range("Index out of range");

	return first_->item;
}

template<class T>
inline T LinkedList<T>::GetLast()
{
	if (!length_)
		throw std::out_of_range("Index out of range");

	return last_->item;
}

template<class T>
inline T LinkedList<T>::Get(int index)
{
	if (index < 0 || index >= length_)
		throw std::out_of_range("Index out of range");

	Node* node = first_;
	for (int i = 0; i < index; i++)
		node = node->next;
	return node->item;
}

template<class T>
inline LinkedList<T> LinkedList<T>::GetSubList(int startIndex, int endIndex)
{
	if (startIndex < 0 || startIndex >= length_ 
		|| endIndex < 0 || endIndex >= length_)
		throw std::out_of_range("Index out of range");
	if (startIndex > endIndex)
		throw std::invalid_argument("End index should be greater than or equal to start index");

	int length = endIndex - startIndex + 1;
	LinkedList list;
	Node* node = first_;
	for (int i = 0; i < startIndex; i++)
		node = node->next;
	for (int i = 0; i < length; i++) {
		list.Append(node->item);
		node = node->next;
	}
	return list;
}

template<class T>
inline int LinkedList<T>::length()
{
	return length_;
}

template<class T>
inline void LinkedList<T>::Append(T item)
{
	Node* node = new Node();
	node->item = item;
	node->previous = last_;
	node->next = NULL;
	if (length_)
		last_->next = node;
	else
		first_ = node;
	last_ = node;
	length_++;
}

template<class T>
inline void LinkedList<T>::Prepend(T item)
{
	Node* node = new Node();
	node->item = item;
	node->previous = NULL;
	node->next = first_;
	if (length_)
		first_->previous = node;
	else
		last_ = node;
	first_ = node;
	length_++;
}

template<class T>
inline void LinkedList<T>::InsertAt(T item, int index)
{
	if (index < 0 || index >= length_)
		throw std::out_of_range("Index out of range");

	Node* node = first_;
	for (int i = 0; i < index; i++)
		node = node->next;
	Node* newNode = new Node();

	newNode->item = node->item;
	node->item = item;
	newNode->next = node->next;
	newNode->previous = node;
	node->next = newNode;
}

template<class T>
inline LinkedList<T> LinkedList<T>::Concat(LinkedList<T>& list)
{
	LinkedList<T> concatedList(*this);
	Node* node = list.first_;
	for (int i = 0; i < list.length_; i++) {
		concatedList.Append(node->item);
		node = node->next;
	}
	return concatedList;
}

template<class T>
inline T& LinkedList<T>::operator[](int index)
{
	if (index < 0 || index >= length_)
		throw std::out_of_range("Index out of range");

	Node* node = first_;
	for (int i = 0; i < index; i++)
		node = node->next;
	return node->item;
}

template<class T>
inline const T& LinkedList<T>::operator[](int index) const
{
	if (index < 0 || index >= length_)
		throw std::out_of_range("Index out of range");

	Node* node = first_;
	for (int i = 0; i < index; i++)
		node = node->next;
	return node->item;
}