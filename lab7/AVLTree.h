#pragma once
#include <iostream>
#include "Node.h"

using namespace std;

class AVLTree {
    public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();
    void insert(const string &);
    int balanceFactor(Node*);
    void printBalanceFactor();
    void visualizeTree(const string &);

    private:
    Node* root;
    //priv helper functions
    int height(Node*);
    void printBalanceFactor(Node*);
    void rotate(Node*);
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void setChild(Node* parent, Node* child, const string & data);
    void replaceChild(Node*, Node*, Node*);
    void visualizeTree(ofstream &, Node *);

    void killAll(Node*);
    AVLTree(const AVLTree& other) = delete;
    AVLTree& operator=(const AVLTree& rhs) = delete;
};

