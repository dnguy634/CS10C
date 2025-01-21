#include <iostream>
#include "Node.h"
#include "BSTree.h"

using namespace std;

void BSTree::insert(const string& key) { // insert new node to tree
    if (root == nullptr) {      // check if tree empty, insert node
        root = new Node(key);
        return;
    }
    Node* curr = root; // temp node to traverse through tree
    while (true) {
        if (curr->key == key) { // if key is duplicate, increase count
            curr->count++;
            return;
        }
        else if (key < curr->key) {   // if key less than current key
            if (curr->left == nullptr) {
                curr->left = new Node(key); // insert new node once at bottom of tree (leaf node)
                return;
            }
            curr = curr->left;  // go left 
        }
        else {                              // if key more than curr key
            if (curr->right == nullptr) {   // insert new node once at bottom of tree (leaf node)
                curr->right = new Node(key);   
                return;
            }
            curr = curr->right;    // go right
        }
    }
}

bool BSTree::search(const string& key) const { // call search helper function 
    return search(root, key); 
}

bool BSTree::search(const Node* curr, const string& key) const {
    while (curr != nullptr) {
        if (curr->key == key) {    // return true of key is found
            return true;
        }
        else if (key < curr->key) {   // if key is less than curr key, go left
            curr = curr->left;
        }
        else {
            curr = curr->right; // go right if key is more than curr key
        }
    }
    return false;   // return false if key is not found
}

string BSTree::largest() const { // call largest helper function to find largest key
    if (root == nullptr) {  // if tree empty, return empty string
        return "";
    } else {
        return largest(root); 
    }
}

string BSTree::largest(const Node* curr) const  {
    while (curr->right != nullptr) {    // traverse down right side of tree until the end
        curr = curr->right;
    }
    return curr->key;   // return largest key (string)
}
string BSTree::smallest() const {   // call smallest helper function to find smallest key
    if (root == nullptr) {  // if empty tree empty, return empty string
        return "";
    } else {
        return smallest(root); 
    }
}

string BSTree::smallest(const Node* curr) const {
    while (curr->left != nullptr) {     // traverse down left side of tree until the end
        curr = curr->left;
    }
    return curr->key;   // return smallest key
}

int BSTree::height(const string& key) const { // determine height of tree with specific key
    // temp node to traverse down tree
    Node* curr = root;
    while (curr != nullptr) { 
        if (curr->key == key) {  // break once key is found
            break;
        }
        else if (key < curr->key) { // if key is less than curr key, go left
            curr = curr->left;
        }
        else {
            curr = curr->right; // if key is more than curr key, go right
        }
    }
    return height_of(curr); // call helper function
}

int BSTree::height_of(Node* tree) const {   // private helper function for height
    if (tree == nullptr) { // if node is null, return -1 (height of just root)
        return -1;
    }
    int leftHeight = height_of(tree->left); // get height of left side of tree
    int rightHeight = height_of(tree->right); // get height of right side of tree
    
    return max(leftHeight, rightHeight) + 1; // compares left and right height of tree, gets largest value, plus 1 for curr node
}

void BSTree::remove(const string& key) { // call remove helper function to remove node with specified key
    root = remove(root, key);
}

Node* BSTree::remove(Node* tree, const string& key) {
    if (tree == nullptr) {  // if tree empty, return null
        return nullptr;
    }
    else if (tree->key == key) {    // if key matches current tree key
        if (tree->count > 1) {  // if count > 1 (duplicate), decrease count 
            --tree->count;
            return tree;
        }
        if (tree->left == nullptr && tree->right == nullptr) {  // if leaf node, delete 
            delete tree;
            return nullptr;
        }
        else if (tree->right == nullptr) {  // if only left child
            Node* victim = tree->left; 
            while (victim->right != nullptr) { 
                // traverse down right side of victim node to find biggest smallest child
                victim = victim->right; 
            }
            // copy victim info to tree
            tree->key = victim->key; 
            tree->count = victim->count;
            victim->count = 1; 
            tree->left = remove(tree->left, victim->key); // recursively call again
            return tree;
        }
        else if (tree->left == nullptr) { // if only right child
            Node* victim = tree->right;
            while (victim->left != nullptr) { 
                // traverse down left side of victim node to find smallest biggest child
                victim = victim->left; 
            }
            // copy victim info to tree
            tree->key = victim->key; 
            tree->count = victim->count;
            victim->count = 1; 
            tree->right = remove(tree->right, victim->key); // recursively call again
            return tree;
        }
        else {  // if both left and right child exist, find biggest child in left subtree
            Node* victim = tree->left; 
            while (victim->right != nullptr) { 
                // traverse down right side of victim node to find biggest smallest child
                victim = victim->right; 
            }
            // copy victim info to tree
            tree->key = victim->key; 
            tree->count = victim->count;
            victim->count = 1; 
            tree->left = remove(tree->left, victim->key); // recursively call again
            return tree;
        }
    }
    else if (key < tree->key) { // if key in left subtree
        tree->left = remove(tree->left, key);
        return tree;
    }
    else {  // if key in right subtree
        tree->right = remove(tree->right, key);
        return tree;
    }
}

void BSTree::preOrder() const { // traverse tree in preorder, prints each node and count
    preOrder(root);
}

void BSTree::preOrder(Node* tree) const {   // private helper function for preOrder
    if (tree != nullptr) {
        cout << tree->key << "(" << tree->count << "), "; // print curr node 
        preOrder(tree->left);   // traverse left subtree
        preOrder(tree->right);  // traverse right subtree
    } else {
        return;
    }
}

void BSTree::postOrder() const { // traverse tree in post order, prints each node and count
    postOrder(root);
}

void BSTree::postOrder(Node* tree) const {   // private helper function for postOrder
    if (tree != nullptr) {
        postOrder(tree->left); // traverse left subtree
        postOrder(tree->right); // traverse right subtree
        cout << tree->key << "(" << tree->count << "), "; 
    } else {
        return;
    }
}

void BSTree::inOrder() const { // traverse tree in order from least to greatest
    inOrder(root);
}

void BSTree::inOrder(Node* tree) const {   // private helper function for inOrder
    if (tree != nullptr) {
        inOrder(tree->left); // traverse left subtree
        cout << tree->key << "(" << tree->count << "), ";
        inOrder(tree->right); // traverse right subtree
    } else {
        return;
    }
}