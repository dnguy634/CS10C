#include "Node.h"

Node::Node(const string & key) {
    this->small = key;
    this->large = "";
    this->count = 1;
    this->left = nullptr;
    this->middle = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}