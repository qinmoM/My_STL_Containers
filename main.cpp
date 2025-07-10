#include <iostream>
#include "Array.h"
#include "SList.h"

// Array
void print(const Array<int>& arr)
{
    int size = arr.size();
    std::cout << "[";
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i];
        if (i != size - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

// List
void print(const SList<int>& list)
{
    SNode<int>* node = list.begin();
    std::cout << "[";
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << node->data;
        if (i != list.size() - 1)
        {
            std::cout << ", ";
            node = node->next;
        }
    }
    std::cout << "]" << std::endl;
}

// Main
int main()
{
    // // Array
    // Array<int> arr(1);
    // print(arr);
    // arr.push_back(1);
    // arr.push_back(2);
    // arr.push_back(3);
    // print(arr);
    // arr.pop_back();
    // print(arr);
    // arr.insert(1, 4);
    // print(arr);
    // arr[1] = 3;
    // print(arr);
    // arr.remove(1);
    // print(arr);
    // arr.clear();
    // print(arr);

    // Sngle-linked List
    SList<int> list;
    list.push_back(2);
    print(list);
    list.push_front(1);
    print(list);
    list.push_back(3);
    list.pop_front();
    list.pop_back();
    print(list);
    list.insert(1, 4);
    print(list);
    list.push_front(1);
    list.push_front(0);
    print(list);
    SList<int> list2;
    list2.push_back(5);
    list2.push_back(6);
    list.merge(list2, true);
    print(list);
    list.reverse();
    print(list);
    std::cout << list.endAt(2)->data << std::endl;
    print(list);
    // make a loop
    SNode<int>* temporary = list.endAt(1);
    temporary->next = list.begin()->next;
    if (nullptr != list.hasLoop())
        std::cout << list.hasLoop()->data << std::endl;
    temporary->next = nullptr;
    temporary = nullptr;

    list.remove(1);
    print(list);
    list.clear();
    print(list);
    return 0;
}