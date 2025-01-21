#pragma once

#include <iostream>
#include <cstdlib>

using namespace std;
struct TreeNode{
    char key;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char key):key(key),left(nullptr),right(nullptr){}
};

class arithmeticExpression{
  private:
    string infixExpression;
    TreeNode* root;

  public:
    arithmeticExpression(const string &);
    ~arithmeticExpression(); // rule of 3 destructor
    void arithmeticExprHelper(TreeNode*);

    void buildTree();
    void infix();
    void prefix();
    void postfix();

 private:
    int priority(char);
    string infix_to_postfix();
    void infix(TreeNode *);
    void prefix(TreeNode *);
    void postfix(TreeNode *);

    // rule of 3 (copy and assignment operator)
    arithmeticExpression & operator=(const arithmeticExpression &) = delete;
    arithmeticExpression(const arithmeticExpression &copy) = delete;
};
