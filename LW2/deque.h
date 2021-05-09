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

	T Get(size_t index) const;
	size_t GetLength() const;
	int GetSequenceType() const;
	bool IsEmpty() const;

	int Find(T item) const;
	int Find(Sequence<T>* sequence) const;
	int Find(Deque<T>* deque) const;

	Deque<T>* Concat(Deque<T>* deque) const;
	Deque<T>* GetSubsequence(size_t startIndex, size_t endIndex) const;
	void Sort(bool (*compare)(T, T));
	Deque<T>* Sorted(bool (*compare)(T, T)) const;

	template<class G> Deque<G>* Map(G (*f)(T)) const;
	Deque<T>* Where(bool (*f)(T)) const;
	T Reduce(T (*f)(T, T), T c) const;
	
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
inline T Deque<T>::Get(size_t index) const
{
	return sequence_->Get(index);
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
inline int Deque<T>::Find(T item) const
{
	for (int i = 0; i < GetLength(); i++)
		if (sequence_->Get(i) == item)
			return i;
	return -1;
}

template<class T>
inline int Deque<T>::Find(Sequence<T>* sequence) const
{
	for (size_t i = 0; i < GetLength(); i++) {
		for (size_t j = i; j < GetLength() &&
			sequence_->Get(j) == sequence->Get(j - i); j++)
			if (j - i + 1 == sequence->GetLength())
				return i;
	}
	return -1;
}

template<class T>
inline int Deque<T>::Find(Deque<T>* deque) const
{
	return Find(deque->sequence_);
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

template<class T>
inline void Deque<T>::Sort(bool(*compare)(T, T))
{
	for (int i = 0; i < sequence_->GetLength(); i++){
		for (int j = i; j < sequence_->GetLength(); j++){
			if (compare(sequence_->Get(i), sequence_->Get(j))) {
				T tmp = sequence_->Get(i);
				sequence_->Set(i, sequence_->Get(j));
				sequence_->Set(j, tmp);
			}
		}
	}
}

template<class T>
inline Deque<T>* Deque<T>::Sorted(bool(*compare)(T, T)) const
{
	Deque<T>* deque = new Deque<T>(this);
	deque->Sort();
	return deque;
}

template<class T>
inline Deque<T>* Deque<T>::Where(bool(*f)(T)) const
{
	Deque<T>* deque = new Deque<T>();
	for (int i = 0; i < GetLength(); i++) {
		T item = sequence_->Get(i);
		if (f(item))
			deque->PushBack(item);
	}
	return deque;
}

template<class T>
inline T Deque<T>::Reduce(T(*f)(T, T), T c) const
{
	for (int i = 0; i < GetLength(); i++)
		c = f(sequence_->Get(i), c);
	return c;
}

template<class T>
template<class G>
inline Deque<G>* Deque<T>::Map(G(*f)(T)) const
{
	Deque<G>* deque = new Deque<G>();
	for (int i = 0; i < GetLength(); i++)
		deque->PushBack(f(sequence_->Get(i)));
	return deque;
}
