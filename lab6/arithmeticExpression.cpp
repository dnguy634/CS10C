#include <iostream>
#include <sstream>
#include <stack>

#include "arithmeticExpression.h"

using namespace std;

arithmeticExpression::arithmeticExpression(const string& expression)
  : infixExpression(expression),
    root(nullptr)
{
}

arithmeticExpression::~arithmeticExpression() { 
    arithmeticExprHelper(root); // call helper function 
}

void arithmeticExpression::arithmeticExprHelper(TreeNode* node) {
    if (node) { // recursively delete tree nodes
        arithmeticExprHelper(node->left);
        arithmeticExprHelper(node->right);
        delete node;
    }
}

void arithmeticExpression::buildTree() {
  string postfixStr = infix_to_postfix(); // infix to postfix
  stack<TreeNode*> s;
  for (const auto& c : postfixStr) { // iterate through each char in string
    if (isalpha(c)) {   // if char is alphabet, push to stack
        s.push(new TreeNode(c));
    } 
    else {
        TreeNode* expression = new TreeNode(c);
        TreeNode* right = s.top(); // temp node to store expression node's right > then pop to get second highest in stack
        s.pop();
        TreeNode* left = s.top();
        s.pop();
        expression->right = right; // set expression's right and left and push onto stack as one
        expression->left = left;
        s.push(expression);
    }
  }
  root = s.top();
}

void arithmeticExpression::infix() {
  infix(root);  // call private helper function
}

void arithmeticExpression::infix(TreeNode * root) {
    if (root != nullptr) {
        if (root->left != nullptr) {  // print ( if curr first thing that needs to be printed
            cout << "(";
        }
        infix(root->left);
        cout << root->key;
        infix(root->right);
        if (root->right != nullptr) { // print ) if curr last thing that needs to be printed
            cout << ")";
        }
    }
}

void arithmeticExpression::prefix() {
  prefix(root);     // call private helper function
}

void arithmeticExpression::prefix(TreeNode * root) {
    if (root != nullptr) {  // proceed if tree not empty
        cout << root->key;
        prefix(root->left);
        prefix(root->right);  // prints very left first then goes to the right of each left subtree
    }
}

void arithmeticExpression::postfix() {
  postfix(root);  // call private helper function
}

void arithmeticExpression::postfix(TreeNode * root) {
    if (root != nullptr) {  // proceed if tree not empty
        postfix(root->left);
        postfix(root->right);
        cout << root->key;  // prints after traversing the right, left, then curr of each subtree
    }
}

// helper function to determine the priority of operators in infix expressions
int arithmeticExpression::priority(char op){
    int priority = 0;
    if (op == '('){
        priority =  3;
    }
    else if (op == '*' || op == '/') {
        priority = 2;
    }
    else if (op == '+' || op == '-') {
        priority = 1;
    }
    return priority;
}

// converts an infix expression to a postfix expression using a stack
string arithmeticExpression::infix_to_postfix() {
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i) {
        c = infixExpression.at(i);
        if (c == ' ') {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
            if ( c == '(') {
                s.push(c);
            }
            else if (c == ')') {
                while(s.top() != '(') {
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())) {
                    if (s.top() == '(') {
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()) {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}
