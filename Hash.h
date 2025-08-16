#pragma once

#include <vector>
#include <list>

template<typename T>
struct HashNode
{
    int key;
    T data;

    HashNode(int key)
        : key(key)
        , data(T())
    { }

    HashNode(int key, const T& data)
        : key(key)
        , data(data)
    { }
};

class OpenHash
{
public:

};

template<typename T>
class ChainingHash
{
public:
    ChainingHash(int capacity = 7, double loadFactor = 0.75)
        : loadFactor(loadFactor)
        , Size(0)
    {
        if (capacity != 7)
        {
            if (capacity >= primes[primeSize - 1])
            {
                primeIndex = primeSize - 1;
                numBuckets = primes[primeIndex];
            }
            for (; primeIndex < primeSize; ++primeIndex)
            {
                if (primes[primeIndex] >= capacity)
                {
                    numBuckets = primes[primeIndex];
                    break;
                }
            }
        }
        else
        {
            numBuckets = primes[primeIndex];
        }

        table.resize(numBuckets);
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

    void clear()
    {
        Size = 0;
        for (std::list<HashNode<T>>& bucket : table)
        {
            bucket.clear();
        }
    }

    HashNode<T>* find(int key)
    {
        int index = key % numBuckets;
        for (HashNode<T>& node : table[index])
        {
            if (node.key == key)
            {
                return &node;
            }
        }
        return nullptr;
    }

    int count(int key)
    {
        if (find(key))
        {
            return 1;
        }
        return 0;
    }

    void insert(const HashNode<T>& node)
    {
        if (find(node.key))
        {
            return;
        }
        int index = node.key % numBuckets;
        table[index].push_back(node);
        ++Size;
        rehash();
    }

    bool erase(int key)
    {
        int index = key % numBuckets;
        std::list<HashNode<T>>& bucket = table[index];
        for (typename std::list<HashNode<T>>::iterator it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->key == key)
            {
                --Size;
                bucket.erase(it);
                return true;
            }
        }
        return false;
    }

    T& operator[](int key)
    {
        HashNode<T>* node = find(key);
        if (node)
        {
            return node->data;
        }
        else
        {
            int index = key % numBuckets;
            HashNode<T> newNode(key);
            table[index].push_back(std::move(newNode));
            ++Size;
            rehash();
            return find(key)->data;
        }
    }

protected:
    std::vector<std::list<HashNode<T>>> table;
    double loadFactor = 0.75;
    int numBuckets;
    int Size;

    static const int primeSize = 10;
    static constexpr int primes[primeSize] = { 7, 23, 53, 97, 193, 389, 1543, 6151, 12289, 42773 };
    int primeIndex = 0;

private:
    void rehash()
    {
        if (static_cast<double>(Size) / numBuckets > loadFactor && primeIndex < primeSize - 1)
        {
            ++primeIndex;
            numBuckets = primes[primeIndex];
            std::vector<std::list<HashNode<T>>> newTable(numBuckets);
            for (std::list<HashNode<T>>& bucket : table)
            {
                for (HashNode<T>& node : bucket)
                {
                    int index = node.key % numBuckets;
                    newTable[index].push_back(node);
                }
            }
            table.swap(newTable);
        }
    }

};
