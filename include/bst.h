// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class BST
{
private:

    struct Node
    {
        T key;
        int count;
        Node* left;
        Node* right;
        Node(const T& value)
        {
            key = value;
            count = 1;
            left = nullptr;
            right = nullptr;
        }
    };
    Node* root;
private:

    void clear(Node* node)
    {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    Node* insert(Node* node, const T& value)
    {
        if (node == nullptr)
            return new Node(value);
        if (value < node->key)
            node->left = insert(node->left, value);
        else if (value > node->key)
            node->right = insert(node->right, value);
        else
            node->count++;
        return node;
    }
    bool search(Node* node, const T& value) const
    {
        if (!node)
            return false;
        if (value == node->key)
            return true;
        if (value < node->key)
            return search(node->left, value);
        return search(node->right, value);
    }
    int depth(Node* node) const
    {
        if (!node)
            return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return std::max(leftDepth, rightDepth) + 1;
    }
    void collect(Node* node,
                 std::vector<std::pair<T,int>>& words) const
    {
        if (!node)
            return;

        collect(node->left, words);

        words.push_back(
            std::make_pair(node->key, node->count)
        );

        collect(node->right, words);
    }
public:
    BST()
    {
        root = nullptr;
    }
    ~BST()
    {
        clear(root);
    }
    void insert(const T& value)
    {
        root = insert(root, value);
    }
    bool search(const T& value) const
    {
        return search(root, value);
    }
    int depth() const
    {
        return depth(root);
    }
    std::vector<std::pair<T,int>> getAllWords() const
    {
        std::vector<std::pair<T,int>> result;
        collect(root, result);
        return result;
    }
};

#endif
#endif  // INCLUDE_BST_H_
