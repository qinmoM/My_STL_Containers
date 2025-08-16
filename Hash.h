#pragma once

#include <vector>
#include <list>
#include <optional>



template<typename T>
struct HashNode
{
    int key;
    T data;

    HashNode()
        : key(-1)
        , data(T())
    { }

    HashNode(int key)
        : key(key)
        , data(T())
    { }

    HashNode(int key, const T& data)
        : key(key)
        , data(data)
    { }
};



template<typename T>
class OpenHash
{
public:
    struct OpenHashNode
    {
        std::optional<HashNode<T>> node;
        bool isDeleted = false;

        OpenHashNode() = default;

    };

public:
    OpenHash(int capacity = 8, double loadFactor = 0.75)
        : loadFactor(loadFactor)
        , numBuckets(capacity)
        , Size(0)
    {
        if (capacity != 8)
        {
            int temp = 8;
            while (capacity > temp)
            {
                temp *= 2;
            }
            numBuckets = temp;
        }
        table.resize(numBuckets, OpenHashNode());
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
        table.clear();
        numBuckets = 8;
        table.resize(numBuckets, OpenHashNode());
    }

    HashNode<T>* find(int key)
    {
        int index = key & (numBuckets - 1);
        while (table[index].node.has_value())
        {
            if (!table[index].isDeleted && table[index].node->key == key)
            {
                return &table[index].node.value();
            }
            ++index;
            if (index == numBuckets)
            {
                index = 0;
            }
        }
        return nullptr;
    }

    int count(int key)
    {
        return find(key) ? 1 : 0;
    }

    void insert(const HashNode<T>& node)
    {
        if (find(node.key))
        {
            return;
        }
        ++Size;
        int index = node.key & (numBuckets - 1);
        while (table[index].node.has_value())
        {
            if (table[index].isDeleted)
            {
                table[index].node = node;
                table[index].isDeleted = false;
                return;
            }
            ++index;
            if (index == numBuckets)
            {
                index = 0;
            }
        }
        table[index].node = node;
        rehash();
    }

    bool erase(int key)
    {
        int index = key & (numBuckets - 1);
        while (table[index].node.has_value())
        {
            if (table[index].node->key == key)
            {
                --Size;
                table[index].isDeleted = true;
                return true;
            }
            else
            {
                ++index;
                if (index == numBuckets)
                {
                    index = 0;
                }
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
            insert({ key, T() });
            return find(key)->data;
        }
    }

protected:
    std::vector<OpenHashNode> table;
    double loadFactor = 0.75;
    int numBuckets;
    int Size;

private:
    void rehash()
    {
        if (static_cast<double>(Size) / numBuckets > loadFactor)
        {
            numBuckets *= 2;
            std::vector<OpenHashNode> newTable(numBuckets, OpenHashNode());
            for (OpenHashNode& temp : table)
            {
                if (temp.node.has_value() && !temp.isDeleted)
                {
                    int index = temp.node->key & (numBuckets - 1);
                    while (newTable[index].node.has_value())
                    {
                        ++index;
                        if (index == numBuckets)
                        {
                            index = 0;
                        }
                    }
                    newTable[index] = temp;
                }
            }
            table.swap(newTable);
        }
    }

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
