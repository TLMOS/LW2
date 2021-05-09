#include <cstdlib>
#include <cstring>
#include "sequence.h"
#include "array_sequence.h"
#include "list_sequence.h"

#pragma once

template<class T>
class Deque
{
public:
	enum class SequenceType
	{
		None = 1,
		Same,
		List,
		Array
	};

private:
	Sequence<T>* sequence_;
	SequenceType sequenceType_;

public:
	static const SequenceType kDefaultSequenceType = SequenceType::List;

	~Deque();

	Deque(SequenceType seqType = SequenceType::None);
	Deque(const Sequence<T>& sequence,
		SequenceType seqType = SequenceType::None);
	Deque(const Deque<T>& deque,
		SequenceType seqType = SequenceType::Same);

	void PushBack(T item);
	void PushFront(T item);
	T PopBack();
	T PopFront();
	size_t GetLength() const;
	int GetSequenceType() const;
	bool IsEmpty() const;

	Deque<T>* Concat(Deque<T>* deque) const;
	Deque<T>* GetSubsequence(size_t startIndex, size_t endIndex) const;
	//void Sort(bool (*compare)(T, T));
	//Deque<T>* Sorted(bool (*compare)(T, T)) const;
	//Deque<T>* Map(T (*f)(T)) const;
	//Deque<T>* Where(bool (*f)(T)) const;
	//Deque<T>* Reduce(T (*f)(T, T)) const;
	//size_t Find(T item);
	//size_t Find(Deque<T> deque);
	//size_t Find(Sequence deque);
};

template<class T>
inline Deque<T>::~Deque()
{
	delete sequence_;
}

template<class T>
inline Deque<T>::Deque(SequenceType seqType)
{
	sequenceType_ = seqType;
	switch (seqType)
	{
		case SequenceType::None:
			seqType = kDefaultSequenceType;
			sequenceType_ = seqType;
		case SequenceType::Array:
			sequence_ = new ArraySequence<T>();
			break;
		case SequenceType::List:
			sequence_ = new ListSequence<T>();
			break;
		default:
			throw std::invalid_argument("Got wrong sequence type.");
			break;
	}
}

template<class T>
inline Deque<T>::Deque(const Sequence<T>& sequence, SequenceType seqType)
{
	sequenceType_ = seqType;
	switch (seqType)
	{
		case SequenceType::None:
			seqType = kDefaultSequenceType;
			sequenceType_ = seqType;
		case SequenceType::Array:
			sequence_ = new ArraySequence<T>(sequence);
			break;
		case SequenceType::List:
			sequence_ = new ListSequence<T>(sequence);
			break;
		default:
			throw std::invalid_argument("Got wrong sequence type.");
			break;
	}
}

template<class T>
inline Deque<T>::Deque(const Deque<T>& deque, SequenceType seqType)
{
	sequenceType_ = seqType;
	switch (seqType)
	{
		case SequenceType::None:
			seqType = kDefaultSequenceType;
			sequenceType_ = seqType;
		case SequenceType::Same:
			seqType = deque.sequenceType_;
			sequenceType_ = seqType;
		case SequenceType::Array:
			sequence_ = new ArraySequence<T>(*deque.sequence_);
			break;
		case SequenceType::List:
			sequence_ = new ListSequence<T>(*deque.sequence_);
			break;
		default:
			throw std::invalid_argument("Got wrong sequence type.");
			break;
	}
}

template<class T>
inline void Deque<T>::PushBack(T item)
{
	sequence_->Append(item);
}

template<class T>
inline void Deque<T>::PushFront(T item)
{
	sequence_->Prepend(item);
}

template<class T>
inline T Deque<T>::PopBack()
{
	T item = sequence_->GetLast();
	sequence_->Delete(GetLength() - 1);
	return item;
}

template<class T>
inline T Deque<T>::PopFront()
{
	T item = sequence_->GetFirst();
	sequence_->Delete(0);
	return item;
}

template<class T>
inline size_t Deque<T>::GetLength() const
{
	return sequence_->GetLength();
}

template<class T>
inline int Deque<T>::GetSequenceType() const
{
	return sequenceType_;
}

template<class T>
inline bool Deque<T>::IsEmpty() const
{
	return (sequence_->GetLength() == 0);
}

template<class T>
inline Deque<T>* Deque<T>::Concat(Deque<T>* deque) const
{
	Deque<T>* concated = new Deque<T>(sequenceType_);
	delete(concated->sequence_);
	concated->sequence_ = sequence_->Concat(deque->sequence_);
	return concated;
}

template<class T>
inline Deque<T>* Deque<T>::GetSubsequence(size_t startIndex, size_t endIndex) const
{
	Deque<T>* subDeque = new Deque<T>(sequenceType_);
	delete(subDeque->sequence_);
	subDeque->sequence_ = sequence_->GetSubsequence(startIndex, endIndex);
	return subDeque;
}
