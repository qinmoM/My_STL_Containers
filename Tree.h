#pragma once

template<class T>
struct Myless
{
    bool operator()(const T& a, const T& b) const
    {
        return a < b;
    }
};



template<class T, class Compare = Myless<T>>
class TreeBST
{
public:
    struct Node
    {
        T data;
        Node* left;
        Node* right;

        Node(const T& value = T()) 
            : data(value)
            , left(nullptr)
            , right(nullptr)
        { }
    };

public:
    TreeBST()
        : root(nullptr)
        , Size(0)
        , cmp(Compare())
    { }

    TreeBST(Compare cmp)
        : root(nullptr)
        , Size(0)
        , cmp(cmp)
    { }

    ~TreeBST()
    {
        del(root);
    }

public:
    bool empty() const
    {
        return !root;
    }

    int size() const
    {
        return Size;
    }

    void insert(const T& value)
    {
        Node** temp = &root;
        while (*temp)
        {
            if (cmp(value, (*temp)->data))
            {
                temp = &((*temp)->left);
            }
            else if (cmp((*temp)->data, value))
            {
                temp = &((*temp)->right);
            }
            else
            {
                return;
            }
        }
        *temp = new Node(value);
        ++Size;
    }

    void remove(const T& value)
    {
        Node** temp = &root;
        while (*temp)
        {
            if (cmp(value, (*temp)->data))
            {
                temp = &((*temp)->left);
            }
            else if (cmp((*temp)->data, value))
            {
                temp = &((*temp)->right);
            }
            else
            {
                break;
            }
        }

        if (!*temp)
        {
            return;
        }

        --Size;
        int childNum = nodeNum(*temp);

        if (0 == childNum)
        {
            delete *temp;
            *temp = nullptr;
        }
        else if (1 == childNum)
        {
            Node* t = *temp;
            *temp = (*temp)->left ? (*temp)->left : (*temp)->right;
            delete t;
        }
        else
        {
            Node** t = &((*temp)->right);
            while ((*t)->left)
            {
                t = &((*t)->left);
            }
            (*temp)->data = (*t)->data;
            Node* del = *t;
            *t = del->right;
            delete del;
        }
    }

    Node* find(const T& value)
    {
        Node* temp = root;
        while (temp)
        {
            if (cmp(value, temp->data))
            {
                temp = temp->left;
            }
            else if (cmp(temp->data, value))
            {
                temp = temp->right;
            }
            else
            {
                return temp;
            }
        }
        return nullptr;
    }

    void inorder(void (*visit)(T&))
    {
        inorder(root, visit);
    }

    void clear()
    {
        del(root);
        root = nullptr;
        Size = 0;
    }

protected:
    Node* root;
    int Size;
    Compare cmp;

private:
    void del(Node* node)
    {
        if (node)
        {
            del(node->left);
            del(node->right);
            delete node;
            node = nullptr;
        }
    }

    void inorder(Node* node, void (*visit)(T&))
    {
        if (node)
        {
            inorder(node->left, visit);
            visit(node->data);
            inorder(node->right, visit);
        }
    }

    int nodeNum(Node* node) const
    {
        if (!node)
        {
            return 0;
        }
        return (node->left ? 1 : 0) + (node->right ? 1 : 0);
    }

    int nodeCount(Node* node) const
    {
        if (!node)
        {
            return 0;
        }
        return node->left ? nodeCount(node->left) + 1 : 0 + node->right ? nodeCount(node->right) + 1 : 0;
    }

};