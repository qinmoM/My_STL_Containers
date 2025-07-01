#include <iostream>
#include "Array.h"

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

int main()
{
    // Array
    Array<int> arr(1);
    print(arr);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    print(arr);
    arr.pop_back();
    print(arr);
    arr.insert(1, 4);
    print(arr);
    arr[1] = 3;
    print(arr);
    arr.remove(1);
    print(arr);
    arr.clear();
    print(arr);
    return 0;
}