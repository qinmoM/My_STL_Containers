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



template<class T, class Compare = Myless<T>>
class TreeRB
{
public:
    constexpr static bool RED = true;
    constexpr static bool BLACK = false;

    struct Node
    {
        Node(const T& value = T())
            : data(value)
            , parent(nullptr)
            , left(nullptr)
            , right(nullptr)
            , color(RED)
        { }

        Node(const T& value, Node* parent, Node* left, Node* right, bool color)
            : data(value)
            , parent(parent)
            , left(left)
            , right(right)
            , color(color)
        { }

        T data;
        Node* parent;
        Node* left;
        Node* right;
        bool color;
    };

public:
    TreeRB(Compare cmp = Myless<T>())
        : root(nullptr)
        , Size(0)
        , cmp(cmp)
    { }

    TreeRB(Node* root)
        : root(root)
        , cmp(Compare())
        , Size(nodeCount(root))
    { }

    ~TreeRB()
    {
        clear();
    }

    TreeRB(const TreeRB& other) = delete;
    TreeRB& operator=(const TreeRB& other) = delete;

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
        Node** curr = &root;
        Node* parent = nullptr;
        while (*(curr))
        {
            if (cmp(value, (*curr)->data))
            {
                parent = *curr;
                curr = &((*curr)->left);
            }
            else if (cmp((*curr)->data, value))
            {
                parent = *curr;
                curr = &((*curr)->right);
            }
            else
            {
                return;
            }
        }
        *curr = new Node(value);
        (*curr)->parent = parent;
        ++Size;

        Node* node = *curr;
        while (parent && parent->color == RED)
        {
            Node* grand = parent->parent;
            if (parent == grand->left)
            {
                Node* uncle = grand->right;
                if (colorOf(uncle) == RED)
                {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grand->color = RED;
                    parent = grand->parent;
                    node = grand;
                }
                else
                {
                    if (node == parent->right)
                    {
                        rotateLeft(parent);
                        parent = node;
                    }
                    rotateRight(grand);
                    parent->color = BLACK;
                    grand->color = RED;
                    return;
                }
            }
            else
            {
                Node* uncle = grand->left;
                if (colorOf(uncle) == RED)
                {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grand->color = RED;
                    parent = grand->parent;
                    node = grand;
                }
                else
                {
                    if (node == parent->left)
                    {
                        rotateRight(parent);
                        parent = node;
                    }
                    rotateLeft(grand);
                    parent->color = BLACK;
                    grand->color = RED;
                    return;
                }
            }
        }
        root->color = BLACK;
        root->parent = nullptr;
    }

    void remove(const T& value)
    {
        Node* curr = root;
        while (curr)
        {
            if (cmp(value, curr->data))
            {
                curr = curr->left;
            }
            else if (cmp(curr->data, value))
            {
                curr = curr->right;
            }
            else
            {
                break;
            }
        }
        if (!curr)
        {
            return;
        }
        --Size;

        if (curr->left && curr->right)
        {
            Node* temp = curr->right;
            while (temp->left)
            {
                temp = temp->left;
            }
            curr->data = temp->data;
            curr = temp;
        }

        if (curr->left || curr->right)
        {
            Node* child = curr->left ? curr->left : curr->right;
            if (root == curr)
            {
                root = child;
                child->parent = nullptr;
                child->color = BLACK;
                delete curr;
                return;
            }
            if (curr->left)
            {
                if (curr->parent->left == curr)
                {
                    curr->parent->left = child;
                }
                else
                {
                    curr->parent->right = child;
                }
                child->parent = curr->parent;
                child->color = BLACK;
                delete curr;
                return;
            }
            else
            {
                if (curr->parent->left == curr)
                {
                    curr->parent->left = child;
                }
                else
                {
                    curr->parent->right = child;
                }
                child->parent = curr->parent;
                child->color = BLACK;
                delete curr;
                return;
            }
        }

        if (root == curr)
        {
            delete curr;
            root = nullptr;
            return;
        }

        bool needDelete = true;
        if (RED == colorOf(curr))
        {
            if (curr->parent->left == curr)
            {
                curr->parent->left = nullptr;
            }
            else
            {
                curr->parent->right = nullptr;
            }
            delete curr;
            return;
        }

        while (true)
        {
            Node* parent = curr->parent;
            Node* sister = (parent->left == curr) ? parent->right : parent->left;
            if (RED == colorOf(sister))
            {
                parent->color = RED;
                sister->color = BLACK;
                if (parent->left == curr)
                {
                    rotateLeft(parent);
                }
                else
                {
                    rotateRight(parent);
                }
            }
            else
            {
                if ((BLACK == colorOf(sister->left)) && (BLACK == colorOf(sister->right)))
                {
                    sister->color = RED;
                    if (RED == parent->color || root == parent)
                    {
                        if (RED == parent->color)
                        {
                            parent->color = BLACK;
                        }
                        if (needDelete)
                        {
                            if (parent->left == curr)
                            {
                                parent->left = nullptr;
                            }
                            else
                            {
                                parent->right = nullptr;
                            }
                            delete curr;
                        }
                        return;
                    }
                    if (parent->left == curr)
                    {
                        parent->left = nullptr;
                    }
                    else
                    {
                        parent->right = nullptr;
                    }
                    delete curr;
                    needDelete = false;
                    curr = parent;
                }
                else
                {
                    if (parent->left == sister)
                    {
                        if (RED == colorOf(sister->left))
                        {
                            sister->color = parent->color;
                            parent->color = BLACK;
                            sister->left->color = BLACK;
                        }
                        else
                        {
                            sister->right->color = parent->color;
                            parent->color = BLACK;
                            rotateLeft(sister);
                        }
                        rotateRight(parent);
                        if (needDelete)
                        {
                            parent->right = nullptr;
                            delete curr;
                        }
                    }
                    else
                    {
                        if (RED == colorOf(sister->right))
                        {
                            sister->color = parent->color;
                            parent->color = BLACK;
                            sister->right->color = BLACK;
                        }
                        else
                        {
                            sister->left->color = parent->color;
                            parent->color = BLACK;
                            rotateRight(sister);
                        }
                        rotateLeft(parent);
                        if (needDelete)
                        {
                            parent->left = nullptr;
                            delete curr;
                        }
                    }
                    return;
                }
            }
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
    int nodeCount(Node* node) const
    {
        if (!node)
        {
            return 0;
        }
        return 1 + nodeCount(node->left) + nodeCount(node->right);
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

    void rotateRight(Node* node)
    {
        Node* left = node->left;

        node->left = left->right;
        if (left->right)
        {
            left->right->parent = node;
        }
        
        if (root == node)
        {
            root = left;
            left->right = node;
            node->parent = left;
            root->parent = nullptr;
            return;
        }

        left->parent = node->parent;
        if (node->parent->left == node)
        {
            left->parent->left = left;
        }
        else
        {
            left->parent->right = left;
        }

        left->right = node;
        node->parent = left;
    }

    void rotateLeft(Node* node)
    {
        Node* right = node->right;

        node->right = right->left;
        if (right->left)
        {
            right->left->parent = node;
        }

        if (root == node)
        {
            root = right;
            right->left = node;
            node->parent = right;
            root->parent = nullptr;
            return;
        }

        right->parent = node->parent;
        if (node->parent->left == node)
        {
            right->parent->left = right;
        }
        else
        {
            right->parent->right = right;
        }

        right->left = node;
        node->parent = right;
    }

    bool colorOf(Node* node)
    {
        return node ? node->color : BLACK;
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

};
