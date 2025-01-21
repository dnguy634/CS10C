#pragma once

#include <iostream>
#include "stack.h"
#include <stdexcept>
#include <string>

const int MAX_SIZE = 20;
using namespace std;

template<typename T>
class stack {
    private:
    int size;
    T data[MAX_SIZE];

    public:

    stack() { size = 0; } // default constructor with empty stack

    void push(T val) {              // insert new element at top of stack
        if (size == MAX_SIZE) {
            throw overflow_error("Called push on full stack."); // if size equals to max size, no more room to push onto stack
        } else {
            data[size++] = val;  // insert new value to stack, last size index of array
        }
    }
    void pop() {    // remove top element in stack
        if (empty()) {
            throw out_of_range("Called pop on empty stack."); // if empty, can't pop
        } else {
            size--; // remove top element in the stack, in this case last size index in array
        }
    }

    void pop_two() { // remove top 2 elements in stack
        if (empty()) {
            throw out_of_range("Called pop_two on empty stack."); // if empty or size < 2, can't pop
        } 
        else if (size == 1) {
            throw out_of_range("Called pop_two on a stack of size 1.");
        } else {
            size -= 2; // remove top 2 elements in the stack, last 2 size indexes in array
        }
    }

    T& top() {
        if (empty()){
            throw overflow_error("Called top on empty stack."); // if empty, nothing to return
        } else {
            return data[size-1]; // return top element of stack
        }
    }

    const T& top() const { 
        if (empty()){
            throw overflow_error("Called top on empty stack.")
        } else {
            return data[size-1];
        }
    }

    bool empty() {
        return (size == 0); // true if size = 0, otherwise false
    }
};