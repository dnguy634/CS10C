#pragma once

#include "Node.h"

class BSTree {
  Node* root;

public:
  BSTree() : root(nullptr) {}
  ~BSTree() { delete root; }
  BSTree(const BSTree&) = delete;
  BSTree& operator=(const BSTree&) = delete;
  
  void insert(const string& key);
  bool search(const string& key) const;
  string largest() const;
  string smallest() const;
  int height(const string& key) const;
  void remove(const string& key);

  void preOrder() const;
  void postOrder() const;
  void inOrder() const;

private:
  // helper functions
  Node* remove(Node* tree, const string& key);
  bool search(const Node* curr, const string& key) const;
  string largest(const Node* curr) const;
  string smallest(const Node* curr) const;
  int height_of(Node* tree) const;
  void preOrder(Node* tree) const;
  void postOrder(Node* tree) const;
  void inOrder(Node* tree) const;
};