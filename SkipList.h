#pragma once

#include <random>

template<class T>
struct MySLless
{
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs < rhs;
    }
};

template<class Key, class Value, class Compare = MySLless<Key>>
class SkipList
{
public:
    struct KeyNode
    {
        KeyNode(Key k, bool isData, KeyNode* next = nullptr, KeyNode* down = nullptr)
            : key(k)
            , next(next)
            , down(down)
            , isData(isData)
        { }

        virtual ~KeyNode() = default;

        Key key;
        KeyNode* next;
        KeyNode* down;
        bool isData;
    };

    struct Node : public KeyNode
    {
        Node(Key k, bool isData, Value v = Value(), Node* next = nullptr, Node* down = nullptr)
            : KeyNode(k, isData, next, down)
            , value(v)
        { }

        Value value;
    };

public:
    SkipList()
        : size_(0)
        , level_(1)
        , comp_(Compare())
    {
        dataHead_ = new Node(Key(), false);
        head_ = new KeyNode(Key(), false, nullptr, dataHead_);
    }

    ~SkipList()
    {
        while (level_-- > -1)
        {
            KeyNode* toBeDel = head_;
            levelDel(head_->next);
            head_ = head_->down;
            delete toBeDel;
        }
    }

public:
    bool empty() const
    {
        return 0 == size_;
    }

    int size() const
    {
        return size_;
    }

    int getLevel() const
    {
        return level_;
    }

    Node* begin() const
    {
        return dataHead_->next;
    }

    Node* find(const Key& key)
    {
        KeyNode* curr = head_;
        while (true)
        {
            while (curr->next && !comp_(key, curr->next->key))
            {
                curr = curr->next;
            }

            if (curr->down)
            {
                curr = curr->down;
            }
            else
            {
                break;
            }
        }

        Node* dataCurr = dynamic_cast<Node*>(curr);
        if (dataCurr && dataCurr->isData && dataCurr->key == key)
        {
            return dataCurr;
        }
        return nullptr;
    }

    void insert(const Key& key, const Value& value)
    {
        if (find(key))
        {
            return;
        }

        ++size_;
        int newlevel = getlevel();
        newlevel = newlevel > level_ ? level_ + 1 : newlevel;

        KeyNode* curr = head_;
        if (newlevel > level_)
        {
            head_ = new KeyNode(Key(), false, nullptr, head_);
            curr = head_;
            ++level_;
        }

        KeyNode* prev = nullptr;
        int levelTemp = level_;
        while (true)
        {
            while (curr->next && comp_(curr->next->key, key))
            {
                curr = curr->next;
            }

            if (!curr->down)
            {
                break;
            }
            if (levelTemp-- <= newlevel)
            {
                curr->next = new KeyNode(key, true, curr->next, nullptr);
                if (prev)
                {
                    prev->down = curr->next;
                }
                prev = curr->next;
            }
            curr = curr->down;
        }
        curr->next = new Node(key, true, value, dynamic_cast<Node*>(curr->next), nullptr);
        if (prev)
        {
            prev->down = curr->next;
        }
    }

    void remove(const Key& key)
    {
        if (!find(key))
        {
            return;
        }

        --size_;
        KeyNode* curr = head_;
        KeyNode* prev = nullptr;
        bool currIsToBeDel = false;
        while (curr)
        {
            if (currIsToBeDel)
            {
                while (curr != prev->next)
                {
                    prev = prev->next;
                }

                KeyNode* toDel = curr;
                prev->next = curr->next;
                curr = curr->down;
                delete toDel;
                prev = prev->down;
            }
            else
            {
                while (curr->next && !comp_(key, curr->next->key))
                {
                    prev = curr;
                    curr = curr->next;
                }

                if (prev && !comp_(curr->key, key))
                {
                    currIsToBeDel = true;
                }
                else
                {
                    curr = curr->down;
                }
            }
        }

        while (level_ > 1 && nullptr == head_->next)
        {
            KeyNode* toBeDel = head_;
            head_ = head_->down;
            delete toBeDel;
            --level_;
        }
    }

    void clear()
    {
        while (level_-- > 1)
        {
            KeyNode* toBeDel = head_;
            levelDel(head_->next);
            head_ = head_->down;
            delete toBeDel;
        }
        
        levelDel(head_->next);
        levelDel(dataHead_->next);
        head_->next = nullptr;
        dataHead_->next = nullptr;
        size_ = 0;
        level_ = 1;
    }

private:
    KeyNode* head_;
    Node* dataHead_;
    int size_;
    int level_;
    Compare comp_;

    static constexpr int MAXLEVEL = 32;

private:
    void levelDel(KeyNode* node)
    {
        while (node)
        {
            KeyNode* temp = node->next;
            delete node;
            node = temp;
        }
    }

    int getlevel()
    {
        int l = 1;
        while (rand() % 2)
        {
            ++l;
        }
        return l > MAXLEVEL ? MAXLEVEL : l;
    }

};