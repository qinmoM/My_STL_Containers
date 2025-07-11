#pragma once

template<class T>
struct SNode
{
    T data;
    SNode<T>* next;

    SNode() : data(T()), next(nullptr) { }

    SNode(T data) : data(data), next(nullptr) { }
};

template<class T>
class SList
{
// public:
protected:
    SNode<T>* head;
    int Size; 
public:
    SList()
    {
        head = new SNode<T>();
        Size = 0;
    }

    ~SList()
    {
        SNode<T>* curr = head;
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

    inline SNode<T>* begin() const
    {
        return head->next;
    }

    inline void push_front(T data) // O(1)
    {
        SNode<T>* newNode = new SNode<T>(data);
        newNode->next = head->next;
        head->next = newNode;
        Size++;
    }

    inline void pop_front() // O(1)
    {
        if (0 == Size)
        {
            return;
        }
        SNode<T>* temp = head->next;
        head->next = temp->next;
        delete temp;
        Size--;
    }

    void push_back(T data) // O(n)
    {
        SNode<T>* newNode = new SNode<T>(data);
        SNode<T>* curr = head;
        while (nullptr != curr->next)
        {
            curr = curr->next;
        }
        curr->next = newNode;
        Size++;
    }

    void pop_back() // O(n)
    {
        if (0 == Size)
        {
            return;
        }
        SNode<T>* curr = head;
        while (nullptr != curr->next->next)
        {
            curr = curr->next;
        }
        delete curr->next;
        curr->next = nullptr;
        Size--;
    }

    void insert(int index, T data) // O(n)
    {
        if (index < 0 || index > Size)
        {
            return;
        }
        SNode<T>* newNode = new SNode<T>(data);
        SNode<T>* curr = head;
        while (index) // if index is not zero
        {
            curr = curr->next;
            index--;
        }
        newNode->next = curr->next;
        curr->next = newNode;
        Size++;
    }

    void remove(int index) // O(n)
    {
        if (index < 0 || index >= Size)
        {
            return;
        }
        SNode<T>* curr = head;
        while (index) // if index is not zero
        {
            curr = curr->next;
            index--;
        }
        SNode<T>* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        Size--;
    }

    inline void clear()
    {
        while (nullptr != head->next)
        {
            pop_front();
        }
    }

    void reverse() // O(n)
    {
        if (2 > Size)
        {
            return;
        }
        SNode<T>* curr = head->next->next;
        SNode<T>* last = head->next;
        while (nullptr != curr)
        {
            last->next = curr->next;
            curr->next = head->next;
            head->next = curr;
            curr = last->next;
        }
    }

    // Find the index from the end of the list // Here is a demonstration of the situation without size:
    SNode<T>* endAt(int index) // O(n)
    {
        if (0 >= index)
        {
            return nullptr;
        }
        SNode<T>* curr = head;
        SNode<T>* result = head;
        while (nullptr != curr)
        {
            if (nullptr != curr)
            {
                curr = curr->next;
            }
            else
            {
                return nullptr;
            }

            if (0 == index)
            {
                result = result->next;
            }
            else
            {
                index--;
            }
        }
        if (index)
        {
            return nullptr;
        }
        else
        {
            return result;
        }
    }

    // merge two sorted lists // O(n)
    void merge(SList<T>& other, bool ascending = true)
    {
        SNode<T>* curr = head;
        SNode<T>* temp = other.head->next;
        while (nullptr != curr)
        {
            if (nullptr == curr->next)
            {
                curr->next = temp;
                other.head->next = nullptr;
                Size += other.Size;
                other.Size = 0;
                break;
            }
            if (nullptr == temp)
            {
                break;
            }
            if (ascending ? (curr->next->data >= temp->data) : (curr->next->data <= temp->data))
            {
                other.head->next = temp->next;
                temp->next = curr->next;
                curr->next = temp;
                curr = curr->next;
                temp = other.head->next;
                Size++;
                other.Size--;
            }
            else
            {
                curr = curr->next;
            }
        }
        other.~SList();
    }

    // Judge whether these is a loop in the list.If not,return nullptr.Conversely,return the beginning of the loop. // O(n)
    SNode<T>* hasLoop()
    {
        SNode<T>* slow = head;
        SNode<T>* fast = head;
        while (nullptr != fast && nullptr != fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                slow = head;
                while (slow != fast)
                {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return nullptr;
    }

    // Find the intersection point of two linked lists.If not,return nullptr.Conversely,return the intersection point. // O(n)
    SNode<T>* hasIntersection(SList<T>& other)
    {
        SNode<T>* curr1 = head;
        SNode<T>* curr2 = other.head;
        int len = size() - other.size();
        if (len < 0)
        {
            curr1 = other.head;
            curr2 = head;
            len = -len;
        }
        while (len)
        {
            curr1 = curr1->next;
            len--;
        }
        while (curr1 != nullptr && curr1 != curr2)
        {
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return curr1;
    }
};