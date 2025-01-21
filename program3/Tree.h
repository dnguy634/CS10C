#pragma once

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree();
  ~Tree();
  void insert(const string &);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove(const string &);
  bool search (const string &) const;

private:
  // Add additional functions/variables here
  void splitTree(const string &, Node *);
  void insert(const string &, Node *);
  void preOrder(Node *) const;
  void inOrder(Node *) const;
  void postOrder(Node *) const;
  void remove(const string &, Node *);
  bool search(const string &, Node *) const;
  Node* removeNode(const string &, Node *);

  void killAll(Node *); // helper function for destructor
  Tree & operator=(const Tree &) = delete;
  Tree(const Tree &) = delete;
};