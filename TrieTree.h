#pragma once

#include <string>

class TrieTree
{
public:
    struct TrieNode
    {
        TrieNode(char c = '\0', int cnt = 0)
            : ch(c)
            , count(cnt)
        {
            for (TrieNode*& child : children)
            {
                child = nullptr;
            }
        }

        char ch;
        TrieNode* children[26];
        int count;
    };

public:
    TrieTree()
        : root(new TrieNode())
        , Capacity(0)
        , Size(0)
    { }

    ~TrieTree()
    {
        del(root);
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

    int capacity() const
    {
        return Capacity;
    }

    int query(const std::string& word)
    {
        TrieNode* temp = root;
        for (char c : word)
        {
            if (c < 'a' || c > 'z')
            {
                continue;
            }

            if (nullptr == temp->children[c - 'a'])
            {
                return 0;
            }
            temp = temp->children[c - 'a'];
        }
        return temp->count;
    }

    void add(const std::string& word)
    {
        TrieNode* temp = root;
        for (char c : word)
        {
            if (c < 'a' || c > 'z')
            {
                continue;
            }

            if (temp->children[c - 'a'])
            {
                temp = temp->children[c - 'a'];
            }
            else
            {
                temp->children[c - 'a'] = new TrieNode(c, 0);
                temp = temp->children[c - 'a'];
            }
        }
        if (!temp->count)
        {
            Size += 1;
        }
        temp->count += 1;
        Capacity += 1;
    }

    void remove(const std::string& word)
    {
        TrieNode* temp = root;
        TrieNode* last = nullptr;
        char lastChar = '\0';
        for (char c : word)
        {
            if (c < 'a' || c > 'z')
            {
                continue;
            }

            if (nullptr == temp->children[c - 'a'])
            {
                return;
            }

            if (temp->count || (temp != root && !ispath(temp)))
            {
                lastChar = c;
                last = temp;
            }
            temp = temp->children[c - 'a'];
        }
        if (0 == temp->count)
        {
            return;
        }

        Size -= 1;
        Capacity -= temp->count;
        temp->count = 0;

        if (!isleaf(temp))
        {
            return;
        }

        if (!last)
        {
            last = root;
            lastChar = word[0];
        }
        for (TrieNode*& child : last->children)
        {
            if (child && child->ch == lastChar)
            {
                del(child);
                child = nullptr;
                break;
            }
        }
    }

    template<class Func>
    void preOrder(Func func)
    {
        for (TrieNode* child : root->children)
        {
            if (child)
            {
                preOrder(child, func, std::string(1, child->ch));
            }
        }
    }

    void clear()
    {
        for (TrieNode* child : root->children)
        {
            if (child)
            {
                del(child);
                child = nullptr;
            }
        }
        root->count = 0;
        Capacity = 0;
        Size = 0;
    }

private:
    TrieNode* root;
    int Capacity;
    int Size;

private:
    template<class Func>
    void preOrder(TrieNode* node, Func func, std::string str)
    {
        for (TrieNode* child : node->children)
        {
            if (child)
            {
                std::string temp = str + std::string(1, child->ch);
                if (child->count)
                {
                    func(temp);
                }
                preOrder(child, func, temp);
            }
        }
    }

    void del(TrieNode* node)
    {
        for (TrieNode* child : node->children)
        {
            if (child)
            {
                del(child);
            }
        }
        delete node;
    }

    bool ispath(TrieNode* node)
    {
        if (!node)
        {
            return false;
        }
        int countTemp = 0;
        for (TrieNode* child : node->children)
        {
            if (child)
            {
                countTemp += 1;
            }
        }
        return countTemp == 1;
    }

    bool isleaf(TrieNode* node)
    {
        for (TrieNode* child : node->children)
        {
            if (child)
            {
                return false;
            }
        }
        return true;
    }

};