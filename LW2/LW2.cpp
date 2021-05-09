#include <iostream>
#include "dynamic_array.h"
#include "linked_list.h"
#include "sequence.h"
#include "array_sequence.h"
#include "list_sequence.h"
#include "deque.h"

const bool MEMORY_MOD = false;

template<class T>
void seqInfo(Sequence<T>* s) {
    if (!MEMORY_MOD) {
        std::cout << "Length: " << s->GetLength() << '\n';
        for (int i = 0; i < s->GetLength(); i++)
            std::cout << s->Get(i) << ' ';
        std::cout << "\n\n";
    }
}

template<class T>
void linkedListInfo(LinkedList<T>* list) {
    if (!MEMORY_MOD) {
        std::cout << "Length: " << list->GetLength() << '\n';
        for (int i = 0; i < list->GetLength(); i++)
            std::cout << list->Get(i) << ' ';
        std::cout << "\n\n";
    }
}

template<class T>
void dequeInfo(Deque<T>* deque) {
    if (!MEMORY_MOD) {
        std::cout << "Length: " << deque->GetLength() << '\n';
        for (int i = 0; i < deque->GetLength(); i++) {
            T item = deque->PopFront();
            std::cout << item << ' ';
            deque->PushBack(item);
        }
            
        std::cout << "\n\n";
    }
}

bool compareInt(int a, int b) {
    return a > b;
}

bool isEven(int x) {
    return x % 2 == 0;
}

int plusOne(int x) {
    return x + 1;
}

float toFloat(int x) {
    return (float)x + 0.1;
}

int sum(int a, int b) {
    return a + b;
}

void test()
{
    
    Deque<int>* deque = new Deque<int>(Deque<int>::SequenceType::List);
    deque->PushFront(2);
    deque->PushFront(3);
    deque->PushFront(4);
    deque->PushBack(66);
    deque->PushBack(0);
    deque->PushBack(11);
    deque->PopFront();
    dequeInfo(deque);
    Deque<int>* deque3 = new Deque<int>(*deque);
    Deque<int>* deque4 = deque->Concat(deque3);
    deque4->Sort(compareInt);
    dequeInfo(deque4);
    Deque<int>* deque6 = deque4->Where(isEven);
    dequeInfo(deque6);
    Deque<int>* deque7 = deque4->Map(plusOne);
    dequeInfo(deque7);
    Deque<float>* deque8 = deque4->Map(toFloat);
    dequeInfo(deque8);
    int x = deque4->Reduce(sum, 0);
    if (!MEMORY_MOD)
        std::cout << "Sum: " << x << '\n';
    int idx1 = deque4->Find(11);
    if (!MEMORY_MOD)
        std::cout << "Find 11: " << idx1 << '\n';
    Sequence<int>* s8 = new ListSequence<int>();
    s8->Append(3);
    s8->Append(11);
    s8->Append(11);
    s8->Append(66);
    Deque<int>* ddd = new Deque<int>(*s8);
    int idx2 = deque4->Find(ddd);
    if (!MEMORY_MOD)
        std::cout << "Find 3, 11, 11, 66: " << idx2 << '\n';
    Deque<int>* deque5 = deque4->GetSubsequence(1, 2);
    dequeInfo(deque5);

    delete(deque);
    delete(deque3);
    delete(deque4);
    delete(deque5);
    
    /*
    Sequence<int>* s1 = new ArraySequence<int>;

    s1->Append(5);
    s1->Append(2);
    s1->Prepend(7);
    (*s1)[0] = 23;
    Sequence<int>* s = new ArraySequence<int>(*s1);
    s->Append(3);
    s->Prepend(1);
    s->InsertAt(100, 2);
    s->Delete(5);
    s->Delete(0);
    s->Delete(2);
    s->Append(1);
    s->Append(1);
    s->Append(1);

    seqInfo(s);
    if (!MEMORY_MOD) {
        std::cout << "First: " << s->GetFirst() << '\n';
        std::cout << "Last: " << s->GetLast() << '\n';
    }

    Sequence<int>* s2 = s->GetSubsequence(1, 3);
    seqInfo(s2);

    Sequence<int>* s3 = s->Concat(s2);
    seqInfo(s3);

    int values[5] = { 1, 2, 3, 4, 5 };
    Sequence<int>* s4 = new ArraySequence<int>(values, 5);
    seqInfo(s4);

    DynamicArray<int>* arr = new DynamicArray<int>(values, 5);
    Sequence<int>* s5 = new ArraySequence<int>(*arr);
    seqInfo(s5);
    
    delete(arr);
    delete(s);
    delete(s1);
    delete(s2);
    delete(s3);
    delete(s4);
    delete(s5);
    */

    /*
    //Linked list
    int items[5] = { 1, 2, 3, 4, 5 };
    LinkedList<int>* list = new LinkedList<int>(items, 5);
    linkedListInfo(list);
    list->Append(6);
    list->Append(7);
    list->Prepend(0);
    list->Prepend(-1);
    list->Get(0);
    list->GetFirst();
    list->GetLast();
    linkedListInfo(list);
    LinkedList<int>* list2 = list->GetSubList(2, 5);
    linkedListInfo(list2);
    list2->InsertAt(42, 3);
    linkedListInfo(list2);
    LinkedList<int>* list3 = list->Concat(list2);
    linkedListInfo(list3);
    */
}

int main()
{

    for (int j = 0; j < 1000000 && MEMORY_MOD; j++) {
        test();
    }
    test();

    if (MEMORY_MOD) {
        char x;
        std::cin >> x;
    }

}