#pragma once

template<class T>
struct Myless
{
    bool operator()(const T& a, const T& b) const
    {
        return a < b;
    }
};

template<class T>
T max(const T& a, const T& b)
{
    return (a > b) ? a : b;
}



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
        clear();
    }

    TreeBST(const TreeBST& other) = delete;
    TreeBST& operator=(const TreeBST& other) = delete;

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

    template<typename Func>
    void inorder(Func visit)
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
        }
    }

    template<typename Func>
    void inorder(Node* node, Func visit)
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
        return 1 + nodeCount(node->left) + nodeCount(node->right);
    }

};



template<class T, class Compare = Myless<T>>
class TreeAVL
{
public:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value = T()) 
            : data(value)
            , left(nullptr)
            , right(nullptr)
            , height(1)
        { }
    };

public:
    TreeAVL()
        : root(nullptr)
        , Size(0)
        , cmp(Compare())
    { }

    TreeAVL(Compare cmp)
        : root(nullptr)
        , Size(0)
        , cmp(cmp)
    { }

    ~TreeAVL()
    {
        clear();
    }

    TreeAVL(const TreeAVL& other) = delete;
    TreeAVL& operator=(const TreeAVL& other) = delete;

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
        root = insert(root, value);
    }

    void remove(const T& value)
    {
        root = remove(root, value);
    }

    Node* find(const T& value)
    {
        return find(root, value);
    }

    template<typename Func>
    void inorder(Func visit)
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
    Node* remove(Node* node, const T& value)
    {
        if (!node)
        {
            return node;
        }

        if (cmp(value, node->data))
        {
            node->left = remove(node->left, value);
        }
        else if (cmp(node->data, value))
        {
            node->right = remove(node->right, value);
        }
        else
        {
            --Size;
            if (!node->left)
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                ++Size;
                Node* temp = node->left;
                while (temp->right)
                {
                    temp = temp->right;
                }
                node->data = temp->data;
                node->left = remove(node->left, temp->data);
            }
        }
        return balance(node);
    }

    Node* find(Node* node, const T& value)
    {
        if (!node)
        {
            return nullptr;
        }

        if (cmp(value, node->data))
        {
            return find(node->left, value);
        }
        else if (cmp(node->data, value))
        {
            return find(node->right, value);
        }
        else
        {
            return node;
        }
    }

    Node* insert(Node* node, const T& value)
    {
        if (!node)
        {
            ++Size;
            return new Node(value);
        }
        if (cmp(value, node->data))
        {
            node->left = insert(node->left, value);
        }
        else if (cmp(node->data, value))
        {
            node->right = insert(node->right, value);
        }
        else
        {
            return node;
        }
        return balance(node);
    }

    Node* balance(Node* node)
    {
        updateHeight(node);
        int bf = balanceFactor(node);
        if (bf > 1)
        {
            if (balanceFactor(node->left) < 0)
            {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        else if (bf < -1)
        {
            if (balanceFactor(node->right) > 0)
            {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    int balanceFactor(Node* node)
    {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rotateRight(Node* node)
    {
        Node* left = node->left;
        Node* T2 = left->right;

        left->right = node;
        node->left = T2;

        updateHeight(node);
        updateHeight(left);

        return left;
    }

    Node* rotateLeft(Node* node)
    {
        Node* right = node->right;
        Node* T2 = right->left;

        right->left = node;
        node->right = T2;

        updateHeight(node);
        updateHeight(right);

        return right;
    }

    void updateHeight(Node* node)
    {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    int height(Node* node)
    {
        return node ? node->height : 0;
    }

    void del(Node* node)
    {
        if (node)
        {
            del(node->left);
            del(node->right);
            delete node;
        }
    }

    template<typename Func>
    void inorder(Node* node, Func visit)
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
        return 1 + nodeCount(node->left) + nodeCount(node->right);
    }

};
