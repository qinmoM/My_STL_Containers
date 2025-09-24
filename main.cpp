#include <iostream>
#include "Array.h"
#include "SList.h"
#include "DList.h"
#include "MStack.h"
#include "MQueue.h"
#include "Hash.h"
#include "Tree.h"
#include "TrieTree.h"

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

// Sngle-linked List
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

// Sngle-circular-linked List
void print(const SCList<int>& list)
{
    SNode<int>* tempHead = list.headNode();
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

// Double-linked List
void print(const DList<int>& list)
{
    DNode<int>* node = list.begin();
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

// Double-circular-linked List
void print(const DCList<int>& list)
{
    DNode<int>* tempHead = list.headNode();
    DNode<int>* node = list.begin();
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

// Chaining Hash
void print(ChainingHash<int>& hashTable, int range)
{
    bool empty = true;
    for (int i = 0; i <= range; ++i)
    {
        if (hashTable.find(i))
        {
            std::cout << i << " : " << hashTable[i] << std::endl;
            empty = false;
        }
    }
    if (empty)
    {
        std::cout << "Hash table is empty" << std::endl;
    }
}

// Open Hash
void print(OpenHash<int>& hashTable, int range)
{
    bool empty = true;
    for (int i = 0; i <= range; ++i)
    {
        if (hashTable.find(i))
        {
            std::cout << i << " : " << hashTable[i] << std::endl;
            empty = false;
        }
    }
    if (empty)
    {
        std::cout << "Hash table is empty" << std::endl;
    }
}

// Main
int main()
{
    // Array
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
    // SList<int> list;
    // list.push_back(2);
    // print(list);
    // list.push_front(1);
    // print(list);
    // list.push_back(3);
    // list.pop_front();
    // list.pop_back();
    // print(list);
    // list.insert(1, 4);
    // print(list);
    // list.push_front(1);
    // list.push_front(0);
    // print(list);
    // SList<int> list2;
    // list2.push_back(5);
    // list2.push_back(6);
    // SNode<int>* temporary = list.hasIntersection(list2);
    // if (nullptr != temporary)
    // {
    //     std::cout << temporary->data << std::endl;
    // }
    // list2.endAt(1)->next = list.endAt(1);
    // list2.Size += 1;
    // print(list2);
    // temporary = list2.hasIntersection(list);
    // if (nullptr != temporary)
    // {
    //     std::cout << temporary->data << std::endl;
    // }
    // temporary = nullptr;
    // list2.Size -= 1;
    // list2.endAt(2)->next = nullptr;
    // print(list2);
    // list.merge(list2, true);
    // print(list);
    // list.reverse();
    // print(list);
    // std::cout << list.endAt(2)->data << std::endl;
    // print(list);
    // // make a loop
    // temporary = list.endAt(1);
    // temporary->next = list.begin()->next;
    // if (nullptr != list.hasLoop())
    //     std::cout << list.hasLoop()->data << std::endl;
    // temporary->next = nullptr;
    // temporary = nullptr;
    // list.remove(1);
    // print(list);
    // list.clear();
    // print(list);

    // Sngle-circular-linked List
    // SCList<int> list;
    // list.push_back(2);
    // print(list);
    // list.push_front(1);
    // print(list);
    // list.push_back(3);
    // list.pop_front();
    // print(list);
    // list.pop_back();
    // print(list);
    // list.insert(1, 4);
    // print(list);
    // list.insert(1, 3);
    // print(list);
    // list.push_front(1);
    // print(list);
    // list.josephusSort(2, 3);
    // print(list);
    // list.remove(1);
    // print(list);
    // list.clear();
    // print(list);

    // Double-linked List
    // DList<int> list;
    // list.push_back(2);
    // print(list);
    // list.push_front(1);
    // print(list);
    // list.push_back(3);
    // list.pop_front();
    // print(list);
    // list.pop_back();
    // print(list);
    // list.insert(1, 3);
    // list.insert(0, 1);
    // print(list);
    // list.remove(2);
    // print(list);
    // list.clear();
    // print(list);

    // Double-Circular-linked List
    // DCList<int> list;
    // list.push_back(2);
    // print(list);
    // list.push_front(1);
    // print(list);
    // list.push_back(3);
    // list.pop_front();
    // print(list);
    // list.pop_back();
    // print(list);
    // list.insert(1, 3);
    // print(list);
    // list.insert(0, 1);
    // print(list);
    // list.remove(2);
    // print(list);
    // list.clear();
    // print(list);

    // Sequential Stack
    // SStack<int> stack;
    // stack.push(1);
    // stack.push(2);
    // stack.push(3);
    // std::cout << stack.top() << std::endl;
    // stack.pop();
    // std::cout << stack.top() << std::endl;
    // stack.pop();
    // std::cout << stack.top() << std::endl;
    // stack.pop();
    // std::cout << static_cast<int>(stack.empty()) << std::endl;

    // Linked Stack
    // LStack<int> stack;
    // stack.push(1);
    // stack.push(2);
    // stack.push(3);
    // std::cout << stack.top() << std::endl;
    // stack.pop();
    // std::cout << stack.top() << std::endl;
    // stack.pop();
    // std::cout << stack.top() << std::endl;
    // stack.pop();
    // std::cout << static_cast<int>(stack.empty()) << std::endl;

    // Circular Queue
    // CQueue<int> queue;
    // for (int i = 0; i < 11; i++)
    // {
    //     queue.push(i);
    // }
    // std::cout << queue.size() << std::endl;
    // for (int i = 0; i < 11; i++)
    // {
    //     std::cout << queue.front() << std::endl;
    //     queue.pop();
    // }

    // Linked Queue
    // LQueue<int> queue;
    // for (int i = 0; i < 10; ++i)
    // {
    //     queue.push(i);
    // }
    // std::cout << queue.size() << std::endl;
    // for (int i = 0; i < 10; ++i)
    // {
    //     std::cout << queue.front() << std::endl;
    //     queue.pop();
    // }

    // Priority Queue
    // PriorityQueue<int> queue(
    //     [](int a, int b) -> bool
    //     {
    //         return a > b;
    //     }
    // );
    // for (int i = 0; i < 30; ++i)
    // {
    //     queue.push(i);
    // }
    // while (!queue.empty())
    // {
    //     std::cout << queue.top() << std::endl;
    //     queue.pop();
    // }

    // Chaining Hash Table
    // ChainingHash<int> hashTable;
    // hashTable.insert({ 1, 2 });
    // hashTable[0] = 4;
    // hashTable[1] = 5;
    // hashTable.insert({ 2, 6 });
    // hashTable.insert({ 3, 7 });
    // hashTable.insert({ 4, 8 });
    // hashTable.insert({ 5, 9 });
    // hashTable.insert({ 6, 10 });
    // hashTable.insert({ 7, 11 });
    // hashTable.insert({ 8, 12 });
    // hashTable.insert({ 9, 13 });
    // hashTable.insert({ 10, 14 });
    // hashTable.insert({ 11, 15 });
    // hashTable.insert({ 12, 16 });
    // print(hashTable, 12);
    // if (hashTable.count(1))
    // {
    //     std::cout << "1 is present" << std::endl;
    // }
    // hashTable.erase(9);
    // print(hashTable, 12);
    // hashTable.clear();
    // print(hashTable, 12);
    
    // Open Hash Table
    // OpenHash<int> hashTable;
    // hashTable.insert({ 1, 2 });
    // hashTable[0] = 4;
    // print(hashTable, 1);
    // hashTable[1] = 5;
    // hashTable.insert({ 2, 6 });
    // hashTable.insert({ 3, 7 });
    // hashTable.insert({ 4, 8 });
    // hashTable.insert({ 5, 9 });
    // hashTable.insert({ 6, 10 });
    // hashTable.insert({ 7, 11 });
    // hashTable.insert({ 8, 12 });
    // hashTable.insert({ 9, 13 });
    // hashTable.insert({ 10, 14 });
    // hashTable.insert({ 11, 15 });
    // hashTable.insert({ 12, 16 });
    // print(hashTable, 12);
    // if (hashTable.count(1))
    // {
    //     std::cout << "1 is present" << std::endl;
    // }
    // hashTable.erase(9);
    // print(hashTable, 12);
    // hashTable.clear();
    // print(hashTable, 12);

    // BST Tree
    // TreeBST<int> tree;
    // tree.insert(58);
    // tree.insert(24);
    // tree.insert(67);
    // tree.insert(0);
    // tree.insert(34);
    // tree.insert(62);
    // tree.insert(69);
    // tree.insert(5);
    // tree.insert(41);
    // tree.insert(64);
    // tree.insert(78);
    //
    // void (*print)(int&) =
    //     [](int& data) -> void
    //     {
    //         std::cout << data << std::endl;
    //     }
    // ;
    //
    // tree.inorder(print);
    //
    // tree.remove(67);
    // tree.remove(62);
    // tree.remove(69);
    // tree.remove(5);
    //
    // tree.inorder(print);
    //
    // int temp = 58;
    // TreeBST<int>::Node* t = nullptr;
    // if (t = tree.find(temp))
    // {
    //     std::cout << t->data << " is present" << std::endl;
    // }
    // temp = 69;
    // if (tree.find(temp))
    // {
    //     std::cout << temp << " is present" << std::endl;
    // }
    //
    // tree.clear();
    // tree.inorder(print);

    // AVL Tree
    // TreeAVL<int> tree;
    // int arr[] = { 14, 9, 5, 17, 11, 12, 7, 19, 16, 27 };
    // for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
    // {
    //     tree.insert(arr[i]);
    // }
    //
    // int temp = 12;
    // TreeAVL<int>::Node* it = nullptr;
    // if (it = tree.find(temp))
    // {
    //     std::cout << it->data << " is present" << std::endl;
    // }
    //
    // temp = 1;
    // if (it = tree.find(temp))
    // {
    //     std::cout << it->data << " is present" << std::endl;
    // }
    //
    // tree.remove(14);
    // tree.remove(9);
    // tree.remove(5);
    //
    // tree.inorder(
    //     [](int& data) -> void
    //     {
    //         std::cout << data << std::endl;
    //     }
    // );
    //
    // tree.clear();
    //
    // std::cout << std::endl;
    // tree.inorder(
    //     [](int& data) -> void
    //     {
    //         std::cout << data << std::endl;
    //     }
    // );

    // Red_Black Tree
    // TreeRB<int> tree;
    // int arr[] = { 17, 18, 23, 34, 27, 15, 9, 6, 8, 5, 25 };
    //
    // for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
    // {
    //     tree.insert(arr[i]);
    // }
    //
    // void (*print)(int&) =
    //     [](int& data) -> void
    //     {
    //         std::cout << data << std::endl;
    //     }
    // ;
    //
    // tree.inorder(print);
    //
    // tree.clear();
    // tree.inorder(print);
    //
    // TreeRB<int>::Node* tree2 = new TreeRB<int>::Node(15, nullptr, nullptr, nullptr, TreeRB<int>::BLACK);
    // tree2->left = new TreeRB<int>::Node(9, tree2, nullptr, nullptr, TreeRB<int>::BLACK);
    // tree2->right = new TreeRB<int>::Node(18, tree2, nullptr, nullptr, TreeRB<int>::BLACK);
    // tree2->left->left = new TreeRB<int>::Node(6, tree2->left, nullptr, nullptr, TreeRB<int>::BLACK);
    // tree2->left->right = new TreeRB<int>::Node(13, tree2->left, nullptr, nullptr, TreeRB<int>::BLACK);
    // tree2->left->right->left = new TreeRB<int>::Node(10, tree2->left->right, nullptr, nullptr, TreeRB<int>::RED);
    // tree2->right->left = new TreeRB<int>::Node(17, tree2->right, nullptr, nullptr, TreeRB<int>::BLACK);
    // tree2->right->right = new TreeRB<int>::Node(27, tree2->right, nullptr, nullptr, TreeRB<int>::RED);
    // tree2->right->right->left = new TreeRB<int>::Node(23, tree2->right->right, nullptr, nullptr, TreeRB<int>::BLACK);
    // tree2->right->right->right = new TreeRB<int>::Node(34, tree2->right->right, nullptr, nullptr, TreeRB<int>::BLACK);
    // tree2->right->right->right->right = new TreeRB<int>::Node(37, tree2->right->right->right, nullptr, nullptr, TreeRB<int>::RED);
    // tree2->right->right->left->right = new TreeRB<int>::Node(25, tree2->right->right->left, nullptr, nullptr, TreeRB<int>::RED);
    // TreeRB<int> treeTemp(tree2);
    // int arr2[] = { 18, 25, 15, 6, 13, 37, 27, 17, 34, 9, 10, 23 };
    //
    // for (int i = 0; i < sizeof(arr2) / sizeof(int); ++i)
    // {
    //     treeTemp.remove(arr2[i]);
    // }

    // Trie Tree
    TrieTree trie;
    trie.add("hello");
    trie.add("hello");
    trie.add("hel");
    trie.add("he");
    trie.add("world");
    trie.add("word");
    std::cout << "hello : " << trie.query("hello") << std::endl;
    std::cout << "hel : " << trie.query("hel") << std::endl;

    trie.preOrder(
        [](const std::string& str) -> void
        {
            std::cout << str << std::endl;
        }
    );

    trie.remove("hello");
    std::cout << "hello : " << trie.query("hello") << std::endl;
        trie.preOrder(
        [](const std::string& str) -> void
        {
            std::cout << str << std::endl;
        }
    );
    trie.remove("hel");
    trie.remove("he");
    trie.remove("world");
    trie.remove("word");

    return 0;
}