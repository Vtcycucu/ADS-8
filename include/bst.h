// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <utility>
#include <algorithm>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& value)
        : key(value), count(1), left(nullptr), right(nullptr) {}
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

  int search(Node* node, const T& value) const {
    if (!node) return 0;

    if (value == node->key) return node->count;
    if (value < node->key) return search(node->left, value);

    return search(node->right, value);
  }

  int depth(Node* node) const {
    if (!node) return 0;

    int l = depth(node->left);
    int r = depth(node->right);

    return std::max(l, r) + 1;
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
  int search(const T& value) const {
    return search(root, value);
  }
  int depth() const {
    if (!root) return 0;
    return depth(root) - 1;
  }
  std::vector<std::pair<T, int>> getData() const {
    std::vector<std::pair<T, int>> res;
    collect(root, res);
    return res;
  }
};

#endif  // INCLUDE_BST_H_
