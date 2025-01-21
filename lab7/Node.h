#pragma once
#include <iostream>
using namespace std;

struct Node{
    string key;
    Node* left;
    Node* right;
    Node* parent;

    Node();
    Node(const string & other);

    // rule of 3
    ~Node();
    Node(const Node& other) = delete;
    Node& operator=(const Node& rhs) = delete;
};

