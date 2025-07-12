#pragma once

//          Double Linked Node
template<class T>
struct DNode
{
    DNode()
        : data(T())
        , prev(nullptr)
        , next(nullptr)
    { }

    DNode(T data)
        : data(data)
        , prev(nullptr)
        , next(nullptr)
    { }

    DNode(T data, DNode<T>* prev, DNode<T>* next)
        : data(data)
        , prev(prev)
        , next(next)
    { }

    T data;
    DNode<T>* prev;
    DNode<T>* next;

};


//          Double Linked List
template<class T>
class DList
{
public:
    DList()
    {
        head = new DNode<T>();
        tail = head;
        Size = 0;
    }

    ~DList()
    {
        DNode<T>* curr = head;
        while (nullptr != head)
        {
            curr = head->next;
            delete head;
            head = curr;
        }
    }

    inline bool empty() const
    {
        return !Size;
    }

    inline int size() const
    {
        return Size;
    }

    inline DNode<T>* begin() const
    {
        return head->next;
    }

    inline void push_front(T data)
    {
        DNode<T>* newNode = new DNode<T>(data, head, head->next);
        head->next = newNode;
        newNode->next->prev = newNode;
        Size++;
        if (1 == Size)
        {
            tail = newNode;
        }
    }

    inline void pop_front()
    {
        if (0 >= Size)
        {
            return;
        }
        if (1 == Size)
        {
            delete head->next;
            head->next = nullptr;
            tail = head;
            Size--;
            return;
        }
        DNode<T>* curr = head->next;
        curr->next->prev = head;
        head->next = curr->next;
        delete curr;
        Size--;
    }

    void push_back(T data)
    {
        DNode<T>* newNode = new DNode<T>(data, tail, nullptr);
        tail->next = newNode;
        tail = newNode;
        Size++;
    }

    void pop_back() // O(1)
    {
        if (0 >= Size)
        {
            return;
        }
        if (1 == Size)
        {
            delete head->next;
            head->next = nullptr;
            tail = head;
            Size--;
            return;
        }
        DNode<T>* temp = tail->prev;
        temp->next = nullptr;
        delete tail;
        tail = temp;
        Size--;
    }

    void insert(int index, T data) // O(n) / 2
    {
        if (index < 0 || index > Size)
        {
            return;
        }
        if (0 == index)
        {
            push_front(data);
            return;
        }
        if (Size == index)
        {
            push_back(data);
            return;
        }

        DNode<T>* curr = nullptr;
        if (Size / 2 >= index)
        {
            curr = head->next;
            while (index)
            {
                curr = curr->next;
                index--;
            }
        }
        else
        {
            curr = tail;
            while (Size - index - 1)
            {
                curr = curr->prev;
                index++;
            }
        }
        DNode<T>* newNode = new DNode<T>(data, curr->prev, curr);
        curr->prev->next = newNode;
        curr->prev = newNode;
        Size++;
    }

    void remove(int index)
    {
        if (index < 0 || index >= Size)
        {
            return;
        }
        if (0 == index)
        {
            pop_front();
            return;
        }
        if (Size - 1 == index)
        {
            pop_back();
            return;
        }

        DNode<T>* curr = nullptr;
        if (Size / 2 >= index)
        {
            curr = head->next;
            while (index)
            {
                curr = curr->next;
                index--;
            }
        }
        else
        {
            curr = tail;
            while (Size - index - 1)
            {
                curr = curr->prev;
                index++;
            }
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        Size--;
    }

    void clear() // O(n)
    {
        if (0 >= Size)
        {
            return;
        }
        DNode<T>* curr = head->next;
        DNode<T>* temp = nullptr;
        while (nullptr != curr)
        {
            temp = curr->next;
            delete curr;
            curr = temp;
        }
        head->next = nullptr;
        tail = head;
        Size = 0;
    }

protected:
    DNode<T>* head;
    DNode<T>* tail;
    int Size;
};


//          Double-Connected Linked List
template<class T>
class DCList
{
public:
    DCList()
    {
        head = new DNode<T>();
        head->prev = head;
        head->next = head;
        tail = head;
        Size = 0;
    }

    ~DCList()
    {
        head->prev->next = nullptr;
        DNode<T>* curr = head;
        while (nullptr != head)
        {
            curr = head->next;
            delete head;
            head = curr;
        }
    }

    inline bool empty() const
    {
        return !Size;
    }

    inline int size() const
    {
        return Size;
    }

    inline DNode<T>* begin() const
    {
        if (0 >= Size)
        {
            return nullptr;
        }
        return head->next;
    }

    inline DNode<T>* headNode() const
    {
        return head;
    }

    inline void push_front(T data)
    {
        DNode<T>* newNode = new DNode<T>(data, head, head->next);
        head->next = newNode;
        newNode->next->prev = newNode;
        Size++;
        if (1 == Size)
        {
            tail = newNode;
            head->prev = tail;
        }
    }

    inline void pop_front()
    {
        if (0 >= Size)
        {
            return;
        }
        if (1 == Size)
        {
            delete head->next;
            head->next = head;
            tail = head;
            head->prev = tail;
            Size--;
            return;
        }
        DNode<T>* curr = head->next;
        curr->next->prev = head;
        head->next = curr->next;
        delete curr;
        Size--;
    }

    void push_back(T data)
    {
        DNode<T>* newNode = new DNode<T>(data, tail, head);
        tail->next = newNode;
        tail = newNode;
        head->prev = tail;
        Size++;
    }

    void pop_back() // O(1)
    {
        if (0 >= Size)
        {
            return;
        }
        if (1 == Size)
        {
            delete head->next;
            head->next = head;
            tail = head;
            Size--;
            return;
        }
        head->prev = tail->prev;
        tail->prev->next = head;
        delete tail;
        tail = head->prev;
        Size--;
    }

    void insert(int index, T data) // O(n) / 2
    {
        if (index < 0 || index > Size)
        {
            return;
        }
        if (0 == index)
        {
            push_front(data);
            return;
        }
        if (Size == index)
        {
            push_back(data);
            return;
        }

        DNode<T>* curr = nullptr;
        if (Size / 2 >= index)
        {
            curr = head->next;
            while (index)
            {
                curr = curr->next;
                index--;
            }
        }
        else
        {
            curr = tail;
            while (Size - index - 1)
            {
                curr = curr->prev;
                index++;
            }
        }
        DNode<T>* newNode = new DNode<T>(data, curr->prev, curr);
        curr->prev->next = newNode;
        curr->prev = newNode;
        Size++;
    }

    void remove(int index)
    {
        if (index < 0 || index >= Size)
        {
            return;
        }
        if (0 == index)
        {
            pop_front();
            return;
        }
        if (Size - 1 == index)
        {
            pop_back();
            return;
        }

        DNode<T>* curr = nullptr;
        if (Size / 2 >= index)
        {
            curr = head->next;
            while (index)
            {
                curr = curr->next;
                index--;
            }
        }
        else
        {
            curr = tail;
            while (Size - index - 1)
            {
                curr = curr->prev;
                index++;
            }
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        Size--;
    }

    void clear() // O(n)
    {
        if (0 >= Size)
        {
            return;
        }
        DNode<T>* curr = head->next;
        DNode<T>* temp = nullptr;
        while (head != curr)
        {
            temp = curr->next;
            delete curr;
            curr = temp;
        }
        head->next = head;
        head->prev = head;
        tail = head;
        Size = 0;
    }

protected:
    DNode<T>* head;
    DNode<T>* tail;
    int Size;
};
