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

    void push(const T& value)
    {
        if (Top == capacity)
        {
            expand(2 * capacity);
        }
        ptr[Top++] = value;
    }

    void pop()
    {
        if (0 == Top)
        {
            throw "Stack is empty!";
        }
        --Top;
    }

    T top() const
    {
        if (0 >= Top)
        {
            throw "Stack is empty!";
        }
        return ptr[Top - 1];
    }

    T& top()
    {
        if (0 >= Top)
        {
            throw "Stack is empty!";
        }
        return ptr[Top - 1];
    }

private:
    void expand(int newCapacity)
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
{};