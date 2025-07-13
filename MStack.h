#pragma once

//          Sequentail Stack
template<class T>
class SStack
{
public:
    SStack(int size = 10)
        : Top(0)
        , capacity(size)
    {
        ptr = new T[size];
    }

    ~SStack()
    {
        delete[] ptr;
        ptr = nullptr;
    }

public:
    bool empty() const
    {
        return !Top;
    }

    int size() const
    {
        return Top;
    }

    void push(const T& value) // O(1), but O(n) if expand.
    {
        if (Top == capacity)
        {
            expand(2 * capacity);
        }
        ptr[Top++] = value;
    }

    void pop()  // O(1)
    {
        if (0 == Top)
        {
            throw "Stack is empty!";
        }
        --Top;
    }

    T top() const // O(1)
    {
        if (0 >= Top)
        {
            throw "Stack is empty!";
        }
        return ptr[Top - 1];
    }

    T& top() // O(1)
    {
        if (0 >= Top)
        {
            throw "Stack is empty!";
        }
        return ptr[Top - 1];
    }

private:
    void expand(int newCapacity) // O(n)
    {
        T* newPtr = new T[newCapacity];
        for (int i = 0; i < Top; ++i)
        {
            newPtr[i] = ptr[i];
        }
        delete[] ptr;
        ptr = newPtr;
        capacity = newCapacity;
    }

protected:
    T* ptr;
    int Top;
    int capacity;
};


//          Linked Stack
template<class T>
class LStack
{
public:
    LStack()
        : Size(0)
    {
        head = new Node();
    }

    ~LStack()
    {
        Node* curr = head;
        while (curr)
        {
            curr = curr->next;
            delete head;
            head = curr;
        }
    }

public:
    bool empty() const
    {
        return !head->next;
    }

    int size() const
    {
        return Size;
    }

    void push(T value) // O(1)
    {
        Node* newNode = new Node(value);
        newNode->next = head->next;
        head->next = newNode;
        ++Size;
    }

    void pop() // O(1)
    {
        if (Size <= 0)
        {
            throw "Stack is empty!";
        }
        Node* temp = head->next;
        head->next = temp->next;
        delete temp;
        --Size;
    }

    T top() const // O(1)
    {
        if (nullptr == head->next)
        {
            throw "Stack is empty!";
        }
        return head->next->data;
    }

    T& top() // O(1)
    {
        if (nullptr == head->next)
        {
            throw "Stack is empty!";
        }
        return head->next->data;
    }

protected:
    struct Node
    {
        T data;
        Node* next;

        Node() : data(T()), next(nullptr) { }

        Node(T data) : data(data), next(nullptr) { }
    };

    Node* head;
    int Size;

};