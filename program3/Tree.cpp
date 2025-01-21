#include <iostream>
#include "Tree.h"

using namespace std;

Tree::Tree() {
    root = nullptr;
}
Tree::~Tree() {
    killAll(root); // helper function
}

void Tree::killAll(Node *curr) {
    if (curr == nullptr) { // base case return if null
        return;
    }

    // traverse to last node then start deleting
    killAll(curr->left);
    killAll(curr->middle);
    killAll(curr->right);

    delete curr;
}

void Tree::insert(const string & key) {
    if (root == nullptr) {  // if empty, set root to key
        root = new Node(key);
    } 
    else {
        insert(key, root); // call helper function
    }
}

void Tree::insert(const string & key, Node *curr) {
    if (curr == nullptr) { 
        return;
    }

    if (key < curr->small) {  // edge case if key smaller than both keys
        // curr has room for another key if count = 1
        if (curr->count == 1) { 
            if (curr->left == nullptr) {  // if leaf node, shift small to large, insert key to small
                curr->large = curr->small;
                curr->small = key;
                curr->count++; // curr holds 2 keys now
            }
            else {
                insert(key, curr->left); // traverse down left until leaf
            }
        }
        else if (curr->count == 2) { // if curr is full with max amount of keys
            if (curr->left != nullptr) {
                insert(key, curr->left); // recursively call insert on curr->left is not null
            }
            else {
                splitTree(key, curr); // at leaf node > split curr
            }
        }
        else {
            splitTree(key, curr);
        }
    }
    else if (key > curr->small) { // if key is bigger than curr 
        if (curr->count == 1) {
            if (curr->right == nullptr) { // if theres room, insert as large key 
                curr->large = key; 
                curr->count++; // update count to hold 2 
            }
            else {
                insert(key, curr->right); // traverse down right
            }
        }
        else if (curr->count == 2 && key < curr->large) { // if key is in between 
            if (curr->middle != nullptr) {
                insert(key, curr->middle); // traverse down middle until leaf
            }
            else {
                splitTree(key, curr); // split at leaf node
            }
        }
        else {
            splitTree(key, curr);
        }
    }
}

void Tree::splitTree(const string & key, Node *curr) { // helper function for insert 
    Node *leftChild = nullptr;
    Node *rightChild = nullptr;
    string middleChild = "";

    if (curr->large == "") { // base case
        return;
    }
    if (key < curr->small) { // edge case if key smaller than both keys
        leftChild = new Node(key);
        rightChild = new Node(curr->large);
        middleChild = curr->small;
    }
    else if (key > curr->large) { // edge case if key bigger than both keys
        leftChild = new Node(curr->small);
        rightChild = new Node(key);
        middleChild = curr->large; 
    }
    else { // edge case if key is in between
        leftChild = new Node(curr->small);
        rightChild = new Node(curr->large);
        middleChild = key;
    }
    // make curr node a single key
    curr->large = "";
    curr->count--;

    if (curr->parent != nullptr) { // edge case if curr node has parent
        curr->parent->large = middleChild; // move middle key to parent node large key
        curr->parent->count++;
        curr->parent->middle = leftChild; // prev left and right updated to middle and right children
        leftChild->parent = curr->parent;
        curr->parent->right = rightChild;
        rightChild->parent = curr->parent;
    }
    else { // make middle key parent of left and right child
        curr->small = middleChild;
        curr->left = leftChild;
        curr->right = rightChild;
        leftChild->parent = curr;
        rightChild->parent = curr;
    }
}

void Tree::remove(const string & key) {
    remove(key, root); // call helper function
}

void Tree::remove(const string & key, Node *curr) {
    if (curr == nullptr) {
        return;
    }
    // check if key to remove exists
    if (search(key, curr)) {
        // set curr as key to be removed
        curr = removeNode(key, curr); 
        if (curr->parent == nullptr) { // if node is root
            if (curr->left == nullptr && curr->right == nullptr) { // if leaf node
                if (curr->count == 1) { // if 1 key, delete and set to null
                    delete curr;
                    root = nullptr;
                }
                else { // if 2 keys
                    if (curr->small == key) { // shift large key to left if small key is removed
                        curr->small = curr->large;
                    }
                    // remove large key and decrease count
                    curr->large = "";
                    curr->count--;
                }
            }
            else { // if node has children
                curr->small = curr->left->small;
                curr->large = curr->right->small;
                curr->count++;
                delete curr->left;
                delete curr->right;
                curr->left = curr->right = nullptr;
            }
        }
        else { // if node is not root
            if (curr->count == 1) {
                Node *parent = curr->parent;
                if (parent->right == curr) { // node is right child of parent
                    parent->large = parent->small;
                    parent->small = parent->left->small;
                }
                else if (parent->left == curr) { // node is left child
                    parent->large = parent->right->small;
                }
                parent->count++;
                delete parent->left;
                delete parent->right;
                parent->left = parent->right = nullptr;
            }
            else { // if node has 2 keys
                if (curr->small == key) { // shift large if small key is removed
                    curr->small = curr->large;
                }
                curr->large = ""; // remove large key and decrease count
                curr->count--;
            }
        }
    }
}

void Tree::preOrder() const {
    preOrder(root); // call helper function
}

void Tree::preOrder(Node *curr) const {
    if (curr == nullptr) {
        return;
    }
    else {
        if (curr->count == 1) {  // edge case if 1 key on ndoe
            cout << curr->small << ", "; // output then recursively traverse left then right
            preOrder(curr->left);
            preOrder(curr->right);
        } 
        else {  // edge case if 2 key node
            cout << curr->small << ", ";
            preOrder(curr->left);
            cout << curr->large << ", ";
            preOrder(curr->middle);
            preOrder(curr->right);
        }
    }
}

void Tree::inOrder() const {
    inOrder(root); // call helper function
}

void Tree::inOrder(Node *curr) const {
    if (curr == nullptr) {
        return;
    }
    else {
        if (curr->count == 1) { // edge case if 1 key in node
            inOrder(curr->left);
            cout << curr->small << ", "; 
            inOrder(curr->right);
        }
        else {  // edge case if 2 keys in node
            inOrder(curr->left);
            cout << curr->small << ", ";
            inOrder(curr->middle);
            cout << curr->large << ", ";
            inOrder(curr->right);
        }
    }
}

void Tree::postOrder() const { 
    postOrder(root); // call helper function
}

void Tree::postOrder(Node *curr) const {
    if (curr == nullptr) {
        return;
    }
    if (curr->count == 1) { // edge case if 1 key in node
        postOrder(curr->left); // traverse to last node and output
        postOrder(curr->right);
        cout << curr->small << ", ";
    }
    else {  // edge case if 2 keys in node
        postOrder(curr->left); // traverse to middle first then start outputting
        postOrder(curr->middle);
        cout << curr->small << ", ";
        postOrder(curr->right);
        cout << curr->large << ", ";
    }
}

bool Tree::search(const string & key) const { // returns true if key found, else false
    return search(key, root); // call helper function
}

bool Tree::search(const string & key, Node *curr) const {
    if (curr == nullptr) { // base case if key not found 
        return false;
    }
    if (curr->small == key || curr->large == key) { // base case if key found
        return true;
    }
    else {
        if (key < curr->small) {
            // if key < curr key, traverse left
            return search(key, curr->left);
        }
        else if (key < curr->large && curr->count == 2) {
            // if key < large and > small, traverse down middle
            return search(key, curr->middle);
        }
        else {
            // if key > curr key, traverse right
            return search(key, curr->right);
        }
    }
}

// search function to return node for remove function
Node* Tree::removeNode(const string & key, Node *curr) {
    if (curr == nullptr) { // base case if key not found, return null
        return nullptr; 
    }
    if (curr->small == key || curr->large == key) {
        return curr; // base case if key is found, return curr node
    }
    else {
        if (key < curr->small) {
            // traverse left if key if < curr 
            return removeNode(key, curr->left);
        }
        else if (key < curr->large && curr->count == 2) {
            // traverse down middle if neighter > or < curr
            return removeNode(key, curr->middle);
        }
        else {
            // traverse right if key > curr
            return removeNode(key, curr->right);
        }
    }
}