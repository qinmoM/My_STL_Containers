#pragma once

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>

using uint = unsigned int;

class Huffman
{
public:
    struct Node
    {
        Node(char character, uint key)
            : character_(character)
            , key_(key)
            , left_(nullptr)
            , right_(nullptr)
        { }

        bool operator>(const Node& other) const
        {
            return key_ > other.key_;
        }

        char character_;
        uint key_;
        Node* left_;
        Node* right_;
    };

public:
    Huffman()
        : root_(nullptr)
        , minHeap_(
            [](Node* a, Node* b) -> bool 
            {
                return *a > *b;
            }
        )
    { }

    ~Huffman()
    {
        std::function<void(Node*)> deleteTree = [&deleteTree](Node* node) -> void
        {
            if (!node)
            {
                return;
            }
            deleteTree(node->left_);
            deleteTree(node->right_);
        };
        deleteTree(root_);
    }

    void create(const std::string& text)
    {
        std::unordered_map<char, uint> hash;
        for (char c : text)
        {
            ++hash[c];
        }

        if (hash.size() == 1)
        {
            char_to_code_[hash.begin()->first] = "0";
            return;
        }

        for (auto& [c, u] : hash)
        {
            minHeap_.push(new Node(c, u));
        }

        while (minHeap_.size() > 1)
        {
            Node* left = minHeap_.top();
            minHeap_.pop();
            Node* right = minHeap_.top();
            minHeap_.pop();
            Node* parent = new Node('\0', left->key_ + right->key_);
            parent->left_ = left;
            parent->right_ = right;
            minHeap_.push(parent);
        }
        root_ = minHeap_.top();
        minHeap_.pop();

        generateCodes(root_, "");
    }

    std::string encode(const std::string& text)
    {
        std::string encoded;
        for (char c : text)
        {
            encoded += char_to_code_[c];
        }
        return encoded;
    }

    std::string decode(const std::string& bits)
    {
        if (!root_)
        {
            return "";
        }
        std::string decoded;
        Node* curr = root_;
        for (char bit : bits)
        {
            if (!curr->left_ && !curr->right_)
            {
                decoded += curr->character_;
                curr = root_;
            }
            if ('0' == bit)
            {
                curr = curr->left_;
            }
            else if ('1' == bit)
            {
                curr = curr->right_;
            }
        }
        if (!curr->left_ && !curr->right_)
        {
            decoded += curr->character_;
        }
        return decoded;
    }

private:
    using MinHeap = std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>>;

    Node* root_;
    std::unordered_map<char, std::string> char_to_code_;
    MinHeap minHeap_;

private:
    void generateCodes(Node* node, std::string code)
    {
        if (!node)
        {
            return;
        }
        if (!node->left_ && !node->right_)
        {
            char_to_code_[node->character_] = code;
        }
        generateCodes(node->left_, code + "0");
        generateCodes(node->right_, code + "1");
    }

};
