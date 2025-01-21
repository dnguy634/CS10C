#include "Node.h"

Node::Node(const string & data) {
    key = data;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

Node::Node() {
    key = "";
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

Node::~Node() {
    delete left;
    delete right;
    delete parent;
}