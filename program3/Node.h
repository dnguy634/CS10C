#pragma once

#include <string>

using namespace std;

class Node {

  friend class Tree;

private:
  string small;
  string large;
  int count;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  Node(const string & key);
};

