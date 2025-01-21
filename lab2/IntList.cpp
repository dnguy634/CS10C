#include "IntList.h"

#include <iostream>
#include <exception>

using namespace std;

// This is just for the throws during the
// development phase... it is a turd once
// you remove all the HERE's
#define STRINGIZE(x) #x
#define STR(x) STRINGIZE(x)
#define HERE ("Broken at\n" __FILE__ ":" STR(__LINE__) ": broken")

#include <iostream>

ostream & operator<<(ostream &out, const IntList &rhs) {  // output to stream all integer values of node
  if (!rhs.empty()) {
    IntNode* curr = rhs.dummyHead.next;
    while (curr != &rhs.dummyTail) {      //  if not empty, traverse through list until curr is not dummyTail, output data at each node
      out << curr->data;
      curr = curr->next;
      if (curr != &rhs.dummyTail) {   // if curr is not last node, output space
        out << " ";
      }
    }
  }
  return out;
}

IntList::~IntList() {    // destructor, deallocates all remaining dynamically allocated memory (all the remaining IntNodes)
  IntNode* curr = dummyHead.next;
  while (curr != &dummyTail) {  // traverse through list to clear
    IntNode* temp = curr;
    curr = curr->next;
    delete temp;
  }
}

void IntList::push_front(int value) {   // insert node in front of list (after dummyHead)
  IntNode* curr = new IntNode(value); 

  curr->prev = &dummyHead;      // curr prev points to dummyHead, curr next points to node after dummyHead
  curr->next = dummyHead.next;
  dummyHead.next->prev = curr;  // update node after dummyHead to point to curr, and dummyHead to point to curr
  dummyHead.next = curr;
}

void IntList::pop_front() {   // remove node in front of list, if empty throw excemption
  if (empty() == true) {
    throw runtime_error("empty");
  }
  else {
    IntNode* curr = dummyHead.next;   // set curr to be removed
    dummyHead.next = curr->next;    // dummyHead points to 2nd node in list, that node's prev is updated to point to dummyHead
    curr->next->prev = &dummyHead;
    delete curr;
  } 
}

void IntList::push_back(int value) {    // insert node at end of list (before dummyTail)
  IntNode* curr = new IntNode(value);
  curr->next = &dummyTail;            // set curr to point to dummyTail, and curr->prev to point to node before dummyTail
  curr->prev = dummyTail.prev;
  dummyTail.prev->next = curr;      // update dummyTail prev to point to curr, and node before dummyTail to point to curr
  dummyTail.prev = curr;
}

void IntList::pop_back() {    // remove node at end of list, if empty throw excemption
  if (empty() == true) {
    throw runtime_error("empty");
  }
  else {
    IntNode* curr = dummyTail.prev;   // set curr to point to node before dummyTail, update tail prev to point to node before curr 
    dummyTail.prev = curr->prev;
    curr->prev->next = &dummyTail;    // that node points to dummyTail, skipping curr 
    delete curr;
  }
}

bool IntList::empty() const {   // list empty if dummyHead points to dummyTail, vice versa
  return (dummyHead.next == &dummyTail && dummyTail.prev == &dummyHead);   // returns true if empty
}

void IntList::printReverse() const {    // print nodes in reverse if list not empty
  if (!empty()) {
    IntNode* curr = dummyTail.prev;
    while (curr != &dummyHead) {      // traverse through list until curr is not dummyHead
      cout << curr->data;
      if (curr->prev != &dummyHead) {   // if curr is not first node in list, output a space
        cout << " ";
      }
      curr = curr->prev;
    }
  } 
}

