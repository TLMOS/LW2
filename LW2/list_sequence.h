#pragma once
#include <cstdlib>
#include <cstring>
#include "sequence.h"
#include "linked_list.h"
#pragma once

template <class T>
class ListSequence : public Sequence<T>
{
private:
	LinkedList<T>* list_;
	size_t length_;

public:
	~ListSequence();

	ListSequence();
	ListSequence(T* items, size_t count);
	ListSequence(const LinkedList <T>& list);

	virtual T GetFirst() const;
	virtual T GetLast() const;
	virtual T Get(size_t index) const;
	virtual Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const;
	virtual size_t GetLength() const;

	virtual void Append(T item);
	virtual void Prepend(T item);
	virtual void InsertAt(T item, size_t index);
	virtual Sequence<T>* Concat(Sequence<T>* list);

	virtual T& operator[](size_t index);
	virtual const T& operator[](size_t index) const;
};

template<class T>
inline ListSequence<T>::~ListSequence()
{
	delete(list_);
}

template<class T>
inline ListSequence<T>::ListSequence()
{
	list_ = new LinkedList<T>();
	length_ = 0;
}

template<class T>
inline ListSequence<T>::ListSequence(T* items, size_t count)
{
	list_ = new LinkedList<T>(items, count);
	length_ = count;
}

template<class T>
inline ListSequence<T>::ListSequence(const LinkedList<T>& list)
{
	list_ = new LinkedList<T>(list);
	length_ = list.GetLength();
}

template<class T>
inline T ListSequence<T>::GetFirst() const
{
	if (!length_)
		throw std::out_of_range("Index out of range");

	return list_->GetFirst();
}

template<class T>
inline T ListSequence<T>::GetLast() const
{
	if (!length_)
		throw std::out_of_range("Index out of range");

	return list_->GetLast();
}

template<class T>
inline T ListSequence<T>::Get(size_t index) const
{
	if (index < 0 || index >= length_)
		throw std::out_of_range("Index out of range");

	return list_->Get(index);
}

template<class T>
inline Sequence<T>* ListSequence<T>::GetSubsequence(size_t startIndex, size_t endIndex) const
{
	if (startIndex < 0 || startIndex >= length_
		|| endIndex < 0 || endIndex >= length_)
		throw std::out_of_range("Index out of range");
	if (startIndex > endIndex)
		throw std::invalid_argument("End index should be greater than or equal to start index");

	LinkedList<T>* subList = list_->GetSubList(startIndex, endIndex);
	ListSequence<T>* subSeq = new ListSequence<T>(*subList);
	return subSeq;
}

template<class T>
inline size_t ListSequence<T>::GetLength() const
{
	return length_;
}

template<class T>
inline void ListSequence<T>::Append(T item)
{
	list_->Append(item);
	length_++;
}

template<class T>
inline void ListSequence<T>::Prepend(T item)
{
	list_->Prepend(item);
	length_++;
}

template<class T>
inline void ListSequence<T>::InsertAt(T item, size_t index)
{
	if (index < 0 || index >= length_)
		throw std::out_of_range("Index out of range");

	list_->InsertAt(item, index);
	length_++;
}

template<class T>
inline Sequence<T>* ListSequence<T>::Concat(Sequence<T>* list)
{
	LinkedList<T>* concatedList = new LinkedList<T>(*list_);
	for (int i = 0; i < list->GetLength(); i++)
		concatedList->Append(list->Get(i));
	ListSequence<T>* concatedSeq = new ListSequence<T>(*concatedList);
	return concatedSeq;
}

template<class T>
inline T& ListSequence<T>::operator[](size_t index)
{
	return (*list_)[index];
}

template<class T>
inline const T& ListSequence<T>::operator[](size_t index) const
{
	return (*list_)[index];
}
