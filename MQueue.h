#pragma once

template<class T>
class CQueue
{
public:
    CQueue(int capacity = 10)
        : Front(0)
        , rear(0)
        , Size(0)
        , capacity(capacity)
    {
        arr = new T[capacity];
    }

    ~CQueue()
    {
        delete[] arr;
        arr = nullptr;
    }

public:
    bool empty() const
    {
        return !Size;
    }

    int size() const
    {
        return Size;
    }

    void push(T value) // O(1),but O(n) if expand
    {
        if (Size + 1 == capacity)
        {
            expand(2 * capacity);
        }
        arr[rear] = value;
        rear = (rear + 1) % capacity;
        ++Size;
    }

    void pop() // O(1)
    {
        if (Size <= 0)
        {
            return;
        }
        Front = (Front + 1) % capacity;
        --Size;
    }

    T front() const // O(1)
    {
        if (Size <= 0)
        {
            throw "Queue is empty!";
        }
        return arr[Front];
    }

    T& front() // O(1)
    {
        if (Size <= 0)
        {
            throw "Queue is empty!";
        }
        return arr[Front];
    }

    T back() const // O(1)
    {
        if (Size <= 0)
        {
            throw "Queue is empty!";
        }
        return arr[rear == 0 ? capacity - 1 : rear - 1];
    }

    T& back() // O(1)
    {
        if (Size <= 0)
        {
            throw "Queue is empty!";
        }
        return arr[rear == 0 ? capacity - 1 : rear - 1];
    }

protected:
    T* arr;
    int Front;
    int rear;
    int Size;
    int capacity;

private:
    void expand(int newCapacity) // O(n)
    {
        T* newArr = new T[newCapacity];
        for (int i = 0; i < Size; ++i)
        {
            newArr[i] = arr[(Front + i) % capacity];
        }
        delete[] arr;

        arr = newArr;
        Front = 0;
        rear = Size;
        capacity = newCapacity;
    }

};

template<class T>
class LQueue
{
public:
    LQueue()
        : Size(0)
    {
        head = new Node();
        tail = head;
    }

    ~LQueue()
    {
        Node* curr = head;
        while (curr)
        {
            head = curr->next;
            delete curr;
            curr = head;
        }
    }

public:
    bool empty() const
    {
        return 0 == Size;
    }

    int size() const
    {
        return Size;
    }

    void push(T data) // O(1)
    {
        Node* newNode = new Node(data);
        tail->next = newNode;
        tail = newNode;
        Size++;
    }

    void pop() // O(1)
    {
        if (0 == Size)
        {
            return;
        }
        Node* temp = head->next;
        head->next = temp->next;
        delete temp;
        temp = nullptr;
        Size--;
    }

    T front() const // O(1)
    {
        if (0 == Size)
        {
            throw "Queue is empty!";
        }
        return head->next->data;
    }

    T& front() // O(1)
    {
        if (0 == Size)
        {
            throw "Queue is empty!";
        }
        return head->next->data;
    }

    T back() const // O(1)
    {
        if (0 == Size)
        {
            throw "Queue is empty!";
        }
        return tail->data;
    }

    T& back() // O(1)
    {
        if (0 == Size)
        {
            throw "Queue is empty!";
        }
        return tail->data;
    }

protected:
    struct Node
    {
        T data;
        Node* next;

        Node()
            : data(T())
            , next(nullptr)
        { }

        Node(T data)
            : data(data)
            , next(nullptr)
        { }

        Node(T data, Node* next)
            : data(data)
            , next(next)
        { }
    };

    Node* head;
    Node* tail;
    int Size;

};
