#include <iostream>
#include "IntList.h"

using namespace std;

int main() {
  IntList list;
  
  cout << "empty: " << list << endl;
  list.push_front(3);
  cout << "push front 3: " << list << endl;
  list.push_back(1);
  cout << "push back 1: " << list << endl;
  list.push_back(5);
  cout << "push back 5: " << list << endl;
  list.push_front(2);
  cout << "push front 2: " << list << endl;
  list.pop_back();
  cout << "pop back: " << list << endl;   // remove node at end (5), new order 2 3 1
  list.pop_front();
  cout << "pop front: " << list << endl;  // remove node at front (2), new order 3 1

  cout << "list in reverse: ";
  list.printReverse();    // new order 1 3
  cout << endl;
       
  return 0;
}
