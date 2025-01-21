#include <iostream>
#include "AVLTree.h"
#include <ostream>
#include <fstream>

AVLTree::~AVLTree() {
    killAll(root);
}

void AVLTree::killAll(Node* curr) {
    if (curr == nullptr) { // base case return if null
        return;
    }
    // traverse to last node then start deleting
    killAll(curr->left);
    killAll(curr->right);
    delete curr;
}

void AVLTree::insert(const string & data) { // insert new string to tree
    if (root == nullptr) { // if tree empty
        root = new Node(data);
        return;
    }
    
    Node* curr = root; // temp node to traverse down to leaf node

    while (true) { // loop exits at break or return
        if (curr->key == data) { // if duplicate return
            throw runtime_error("duplicate"); 
        }
        if (data < curr->key) { // go left 
            if (curr->left == nullptr) { // if left child empty, insert
                curr->left = new Node(data);
                curr->left->parent = curr;
                break;
            }
            curr = curr->left; // traverse down left
        } 
        else { // go right if key > curr key
            if (curr->right == nullptr) { // if right child empty, insert
                curr->right = new Node(data);
                curr->right->parent = curr;
                break;
            }
            curr = curr->right; // traverse down right
        }
    }

    while (curr) { // while curr != root
        if (balanceFactor(curr) > 1 || balanceFactor(curr) < -1) {
            rotate(curr); // adjust height if < -1 or > 1
        }
        curr = curr->parent; // keep going up
    }
}

void AVLTree::rotate(Node* curr) { // rotate tree to maintain AVL properties
    if (balanceFactor(curr) == 2) { // if tree unbalanced left
        if (balanceFactor(curr->left) == -1) { // edge case double rotation
            rotateLeft(curr->left);
        }
        rotateRight(curr);
    }
    else if(balanceFactor(curr) == -2) { // if tree unbalanced right
        if (balanceFactor(curr->right) == 1) { // edge case double rotation
            rotateRight(curr->right);
        }
        rotateLeft(curr);
    }
}

void AVLTree::rotateLeft(Node* curr) { // rotate subtree left
    Node* rightGrandChild = curr->right->left;
    if (curr->parent != nullptr) {
        replaceChild(curr->parent, curr, curr->right); // swap curr and curr->right with replaceChild
    } else {
        // edge case for root
        root = curr->right; 
        root->parent = nullptr;
    }
    // fix curr and curr->right
    setChild(curr->right, curr, "left");
    setChild(curr, rightGrandChild, "right");
}

void AVLTree::rotateRight(Node* curr) { // rotate subtree right
    Node* leftGrandChild = curr->left->right;
    if (curr->parent != nullptr) {
        replaceChild(curr->parent, curr, curr->left); // swap curr and curr->left
    } else {
        // edge case for root
        root = curr->left;
        root->parent = nullptr;
    }
    // fix curr and curr->left
    setChild(curr->left, curr, "right");
    setChild(curr, leftGrandChild, "left");
}

void AVLTree::setChild(Node* parent, Node* child, const string & data) { // set child of a parent node
    if (data == "left") { // if location for child to be set is left then set parent's left to child
        parent->left = child;
    } else { // location set is right so set parent's right to child
        parent->right = child;
    }
    if (child != nullptr) { // update child's parent
        child->parent = parent;
    }
}

void AVLTree::replaceChild(Node* parent, Node* child1, Node* child2) { // replace child of parent node
    if (parent->left == child1) { // if parent's left is child, replace
        setChild(parent, child2, "left");
    } else { // if parent's right is child, replace
        setChild(parent, child2, "right");
    }
}

int AVLTree::balanceFactor(Node* curr) { // get balance factor 
    if (curr == nullptr) { // base case, also if empty balance factor is 0
        return 0; 
    }
    return height(curr->left) - height(curr->right); // recursive case
}

int AVLTree::height(Node* curr) {
    if (curr == nullptr) { // base case, tree with one node has height of -1
        return - 1;
    }

    return max(height(curr->left), height(curr->right)) + 1; // recursive case
}

void AVLTree::printBalanceFactor() {  // print balance factors of nodes in tree
    printBalanceFactor(root); // call helper function
}

void AVLTree::printBalanceFactor(Node* curr) {
    if (curr != nullptr){
        // recursively travel left, print, then right (in order)
        printBalanceFactor(curr->left);
        cout << curr->key 
             << "(" << balanceFactor(curr) << ")"
             << ", ";
        printBalanceFactor(curr->right);
    }
    else {
        throw runtime_error("printing empty tree");
    }
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout << "Error" << endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
} 

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<< n->key << " -> " << n->left->key << ";" << endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<< n->key << " -> " << n->right->key<< ";" <<endl;    
        }
    }
} 




