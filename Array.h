#ifndef __ARRAY_H__
#define __ARRAY_H__

template<class T>
class Array
{
protected:
    T* mpArr;
    int mCapacity;
    int mCurrent;
    
protected:
    void expend(int newCapacity)
    {
        T* newArr = new T[newCapacity];
        for (int i = 0; i < mCurrent; i++)
        {
            newArr[i] = mpArr[i];
        }
        delete[] mpArr;

        mpArr = newArr;
        mCapacity = newCapacity;
    }

public:
    Array(int capacity = 10) : mCurrent(0), mCapacity(capacity)
    {
        mpArr = new T[capacity]();
    }

    ~Array()
    {
        delete[] mpArr;
        mpArr = nullptr;
    }

public:
    inline int size() const
    {
        return mCurrent;
    }

    inline int capacity() const
    {
        return mCapacity;
    }

    inline void push_back(T value) // O(1)
    {
        if (mCurrent == mCapacity)
        {
            expend(2 * mCapacity);
        }
        mpArr[mCurrent++] = value;
    }

    inline void pop_back() // O(1)
    {
        if (0 == mCurrent)
        {
            return;
        }
        mCurrent--;
    }

    void insert(int index, T value) // O(n)
    {
        if (0 > index || mCurrent < index)
        {
            return;
        }
        if (mCurrent == mCapacity)
        {
            expend(2 * mCapacity);
        }
        for (int i = mCurrent; i > index; i--)
        {
            mpArr[i] = mpArr[i - 1];
        }
        mpArr[index] = value;
        mCurrent++;
    }

    void remove(int index) // O(n)
    {
        if (0 > index || mCurrent <= index)
        {
            return;
        }
        for (int i = index; i < mCurrent - 1; i++)
        {
            mpArr[i] = mpArr[i + 1];
        }
        mCurrent--;
    }

    inline void clear()
    {
        mCurrent = 0;
    }

    inline T& operator[](const int& index) const
    {
        return *(mpArr + index);
    }

};

#endif // __ARRAY_H__