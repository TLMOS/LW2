#include <iostream>
#include "dynamic_array.h"
#include "linked_list.h"
#include "sequence.h"
#include "array_sequence.h"
#include "list_sequence.h"

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

void test()
{
    Sequence<int>* s = new ListSequence<int>;

    s->Append(5);
    s->Append(2);
    s->Prepend(7);
    (*s)[0] = 23;
    s->Append(3);
    s->Prepend(1);
    s->InsertAt(100, 2);

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
    delete(s2);
    delete(s3);
    delete(s4);
    delete(s5);

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

    for (int j = 0; j < 100000 && MEMORY_MOD; j++) {
        test();
    }
    test();

    if (MEMORY_MOD) {
        char x;
        std::cin >> x;
    }

}