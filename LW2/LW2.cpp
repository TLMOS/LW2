#include <iostream>
#include "dynamic_array.h"
#include "linked_list.h"

int main()
{
    //DynamicArray
    int values[] = {1, 2, 3};
    DynamicArray<int> arr_tmp(values, 3);
    DynamicArray<int> arr(arr_tmp);
    
    arr.Set(0, 0);
    arr.Resize(4);
    arr.Set(3, 23);
    arr.Resize(2);
    arr.Resize(0);
    arr.Resize(1);
    arr.Set(0, 11);
    arr[0] = 23;

    std::cout << arr.size() << '\n';
    for (int i = 0; i < arr.size(); i++) {
        std::cout << i << ' ' << arr.Get(i) << '\n';
    }

    std::cout << arr.size() << '\n';
    for (int i = 0; i < arr.size(); i++) {
        std::cout << i << ' ' << arr[i] << '\n';
    }

    //LinkedList
    std::cout << '\n';
    int items[] = { 1, 2, 3 };
    
    LinkedList<int> list;
    list.Prepend(7);
    list.Append(4);
    list.Append(2);
    list.Append(6);
    list.Prepend(1);
    list[2] = 23;
    std::cout << list.length() << '\n';
    for (int i = 0; i < list.length(); i++) {
        std::cout << i << ' ' << list.Get(i) << '\n';
    }
    std::cout << list.GetFirst() << '\n';
    std::cout << list.GetLast() << '\n';
    LinkedList<int> list2(items, 3);
    for (int i = 0; i < list2.length(); i++) {
        std::cout << i << ' ' << list2.Get(i) << '\n';
    }
    std::cout << '\n';
    LinkedList<int> list3(list);
    for (int i = 0; i < list3.length(); i++) {
        std::cout << i << ' ' << list3.Get(i) << '\n';
    }
    std::cout << '4' << '\n';
    LinkedList<int> list4 = list2.Concat(list3);
    std::cout << list4.length() << '\n';
    for (int i = 0; i < list4.length(); i++) {
        std::cout << i << ' ' << list4.Get(i) << '\n';
    }
    LinkedList<int> list5 = list4.GetSubList(2, 5);
    std::cout << list5.length() << '\n';
    for (int i = 0; i < list5.length(); i++) {
        std::cout << i << ' ' << list5[i] << '\n';
    }

    LinkedList<int> a;
    LinkedList<int> b;
    LinkedList<int> c = a.Concat(b);

    char x;
    std::cin >> x;
}