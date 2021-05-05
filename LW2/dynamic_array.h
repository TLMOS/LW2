#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <algorithm>

#pragma once

template<class T>
class DynamicArray
{
private:
	T* items_;
	int size_;

public:
	DynamicArray(int size);
	DynamicArray(T* items, int count);
	DynamicArray(const DynamicArray<T>& dynamicArray);
	~DynamicArray();

	T Get(int i);
	int size();
	void Set(int i, T value);
	void Resize(int size);

	T& operator[](int ind);
	const T& operator[](int ind) const;
};

template<class T>
DynamicArray<T>::DynamicArray(int size)
{
	if (size < 0)
		throw std::invalid_argument("Received negative size");

	items_ = (T*)std::malloc(size * sizeof(T));
	size_ = size;
}

template<class T>
DynamicArray<T>::DynamicArray(T* const items, int count)
{
	if (count < 0)
		throw std::invalid_argument("Received negative count");

	items_ = (T*)std::malloc(count * sizeof(T));
	std::memcpy(items_, items, count * sizeof(T));
	size_ = count;
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray):
	DynamicArray(dynamicArray.items_, dynamicArray.size_) {}

template<class T>
DynamicArray<T>::~DynamicArray()
{
	free(items_);
}

template<class T>
T DynamicArray<T>::Get(int i)
{
	if (i < 0 || i >= size_)
		throw std::out_of_range("Index out of range");

	return items_[i];
}

template<class T>
int DynamicArray<T>::size()
{
	return size_;
}

template<class T>
void DynamicArray<T>::Set(int i, T value)
{
	if (i < 0 || i >= size_)
		throw std::out_of_range("Index out of range");

	items_[i] = value;
}

template<class T>
void DynamicArray<T>::Resize(int newSize)
{
	if(newSize < 0)
		throw std::invalid_argument("Received negative size");

	T* tmp = (T*)malloc(newSize * sizeof(T));
	memcpy(tmp, items_, std::min(size_, newSize) * sizeof(T));
	free(items_);
	items_ = tmp;
	size_ = newSize;
}

template<class T>
T& DynamicArray<T>::operator[](int i)
{
	if (i < 0 || i >= size_)
		throw std::out_of_range("Index out of range");

	return items_[i];
}

template<class T>
const T& DynamicArray<T>::operator[](int i) const
{
	if (i < 0 || i >= size_)
		throw std::out_of_range("Index out of range");

	return items_[i];
}