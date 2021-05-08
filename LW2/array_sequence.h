#include <cstdlib>
#include <cstring>
#include "sequence.h"
#include "dynamic_array.h"
#pragma once

template <class T>
class ArraySequence : public Sequence<T>
{
private:
	DynamicArray<T>* array_;
	size_t length_;

public:
	~ArraySequence();

	ArraySequence();
	ArraySequence(T* items, size_t count);
	ArraySequence(const DynamicArray <T>& array);

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
inline ArraySequence<T>::~ArraySequence()
{
	delete(array_);
}

template<class T>
inline ArraySequence<T>::ArraySequence()
{
	array_ = new DynamicArray<T>(0);
	length_ = 0;
}

template<class T>
inline ArraySequence<T>::ArraySequence(T* items, size_t count)
{
	array_ = new DynamicArray<T>(items, count);
	length_ = count;
}

template<class T>
inline ArraySequence<T>::ArraySequence(const DynamicArray<T>& array)
{
	array_ = new DynamicArray<T>(array);
	length_ = array.GetSize();
}

template<class T>
inline T ArraySequence<T>::GetFirst() const
{
	if (!length_)
		throw std::out_of_range("Index out of range");

	return array_->Get(0);
}

template<class T>
inline T ArraySequence<T>::GetLast() const
{
	if (!length_)
		throw std::out_of_range("Index out of range");

	return array_->Get(length_ - 1);
}

template<class T>
inline T ArraySequence<T>::Get(size_t index) const
{
	if (index < 0 || index >= length_)
		throw std::out_of_range("Index out of range");

	return array_->Get(index);
}

template<class T>
inline Sequence<T>* ArraySequence<T>::GetSubsequence(size_t startIndex, size_t endIndex) const
{
	if (startIndex < 0 || startIndex >= length_
		|| endIndex < 0 || endIndex >= length_)
		throw std::out_of_range("Index out of range");
	if (startIndex > endIndex)
		throw std::invalid_argument("End index should be greater than or equal to start index");

	size_t length = endIndex - startIndex + 1;
	T* items = (T*)std::malloc(length * sizeof(T));
	if (!items)
		throw std::runtime_error("Cannot allocate memory");
	for (size_t i = 0; i < length; i++)
		items[i] = array_->Get(startIndex + i);
	ArraySequence<T>* subseq = new ArraySequence<T>(items, length);
	free(items);
	return subseq;
}

template<class T>
inline size_t ArraySequence<T>::GetLength() const
{
	return length_;
}

template<class T>
inline void ArraySequence<T>::Append(T item)
{
	if (array_->GetSize() == 0)
		array_->Resize(1);
	while (length_ + 1 > array_->GetSize())
		array_->Resize(array_->GetSize() * 2);

	array_->Set(length_, item);
	length_++;
}

template<class T>
inline void ArraySequence<T>::Prepend(T item)
{
	if (array_->GetSize() == 0)
		array_->Resize(1);
	while (length_ + 1 > array_->GetSize())
		array_->Resize(array_->GetSize() * 2);

	for (size_t i = length_; i > 0; i--)
		array_->Set(i, array_->Get(i - 1));
	array_->Set(0, item);
	length_++;
}

template<class T>
inline void ArraySequence<T>::InsertAt(T item, size_t index)
{
	if (index < 0 || index >= length_)
		throw std::out_of_range("Index out of range");

	if (array_->GetSize() == 0)
		array_->Resize(1);
	while (length_ + 1 > array_->GetSize())
		array_->Resize(array_->GetSize() * 2);

	for (size_t i = length_; i > index; i--)
		array_->Set(i, array_->Get(i - 1));
	array_->Set(index, item);
	length_++;

}

template<class T>
inline Sequence<T>* ArraySequence<T>::Concat(Sequence<T>* list)
{
	size_t length = length_ + list->GetLength();
	T* items = (T*)std::malloc(length * sizeof(T));
	if (!items)
		throw std::runtime_error("Cannot allocate memory");
	for (size_t i = 0; i < array_->GetSize(); i++)
		items[i] = array_->Get(i);
	for (size_t i = 0; i < list->GetLength(); i++)
		items[length_ + i] = list->Get(i);
	ArraySequence<T>* concated = new ArraySequence<T>(items, length);
	free(items);
	return concated;
}

template<class T>
inline T& ArraySequence<T>::operator[](size_t index)
{
	return (*array_)[index];
}

template<class T>
inline const T& ArraySequence<T>::operator[](size_t index) const
{
	return (*array_)[index];
}
