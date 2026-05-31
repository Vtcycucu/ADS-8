// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& value) {
      key = value;
      count = 1;
      left = nullptr;
      right = nullptr;
    }
  };
  Node* root;
  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node* insert(Node* node, const T& value) {
    if (!node) return new Node(value);

    if (value < node->key) {
      node->left = insert(node->left, value);
    } else if (value > node->key) {
      node->right = insert(node->right, value);
    } else {
      node->count++;
    }
    return node;
  }

  bool search(Node* node, const T& value) const {
    if (!node) return false;
    if (value == node->key) return true;
    if (value < node->key)
      return search(node->left, value);

    return search(node->right, value);
  }
  int depth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(depth(node->left), depth(node->right));
  }
  void collect(Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;

    collect(node->left, out);
    out.emplace_back(node->key, node->count);
    collect(node->right, out);
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    clear(root);
  }
  void insert(const T& value) {
    root = insert(root, value);
  }
  bool search(const T& value) const {
    return search(root, value);
  }
  int depth() const {
    return depth(root);
  }
  std::vector<std::pair<T, int>> getAllWords() const {
    std::vector<std::pair<T, int>> res;
    collect(root, res);
    return res;
  }
  std::vector<std::pair<T, int>> getData() const {
    return getAllWords();
  }
};

#endif  // INCLUDE_BST_H_
