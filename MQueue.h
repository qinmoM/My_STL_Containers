#pragma once

#include <functional>

// Circular queue
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

// Linked queue
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

// Priority queue
template<class T>
class PriorityQueue
{
public:
    using Compare = std::function<bool(const T&, const T&)>;

    PriorityQueue(int capacity = 20, Compare comparator = std::greater<T>())
        : Size(0)
        , capacity(capacity)
        , comparator(comparator)
    {
        arr = new T[capacity];
    }

    PriorityQueue(Compare comparator)
        : Size(0)
        , capacity(20)
        , comparator(comparator)
    {
        arr = new T[capacity];
    }

    ~PriorityQueue()
    {
        delete[] arr;
        arr = nullptr;
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

    void push(T data)
    {
        if (0 == Size)
        {
            arr[0] = data;
        }
        else
        {
            if (Size == capacity)
            {
                expand(2 * capacity);
            }
            int i = Size;
            int father = (i - 1) / 2;
            while (i > 0 && comparator(data, arr[father]))
            {
                arr[i] = arr[father];
                i = father;
                father = (i - 1) / 2;
            }
            arr[i] = data;
        }
        ++Size;
    }

    void pop()
    {
        if (0 == Size)
        {
            return;
        }

        --Size;

        T temp = arr[Size];
        int i = 0;
        int tempIndex = index(Size, 1, 2);
        while (tempIndex != -1 && comparator(arr[tempIndex], temp))
        {
            arr[i] = arr[tempIndex];
            i = tempIndex;
            tempIndex = index(Size, 2 * i + 1, 2 * i + 2);
        }
        arr[i] = temp;
    }

    T top() const
    {
        if (0 == Size)
        {
            throw "Container is empty! | PriorityQueue::top() const";
        }
        return arr[0];
    }

    T& top()
    {
        if (0 == Size)
        {
            throw "Container is empty! | PriorityQueue::top()";
        }
        return arr[0];
    }

protected:
    T* arr;
    int Size;
    int capacity;
    Compare comparator;

private:
    void expand(int newCapacity)
    {
        T* newArr = new T[newCapacity];
        for (int i = 0; i < Size; ++i)
        {
            std::swap(arr[i], newArr[i]);
            // newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        newArr = nullptr;
        capacity = newCapacity;
    }

    int index(int Size, int left, int right)
    {
        if (left >= Size)
        {
            return -1;
        }

        if (right >= Size)
        {
            return left;
        }

        if (comparator(arr[left], arr[right]))
        {
            return left;
        }
        else
        {
            return right;
        }
    }

};
