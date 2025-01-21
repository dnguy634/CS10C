#include <iostream>
#include "Heap.h"

using namespace std;

Heap::Heap()
  : numItems(0)
{
}

 Heap::~Heap() {
  while (numItems > 0) { // iterate until all elements deleted
    delete arr[numItems - 1];
    --numItems; // update size 
  }
 }

void Heap::enqueue(PrintJob* job) { // add new job 
  if (numItems >=  MAX_HEAP_SIZE) { // if heap is full > error
    throw runtime_error("heap is full");
  } else {
    arr[numItems] = job;  // add new item to array and percolate up until max heap properties fulfilled
    trickleUp(numItems);
    numItems++; // update numItems
  }
}

void Heap::trickleUp(int index) {
  int parent = (index - 1) / 2; // find parent

  if (index > 0 && arr[index]->getPriority() > arr[parent]->getPriority()) {  // index must be greater than 0 because the root has no parent 
    swap(arr[index], arr[parent]);  // Swap index and parent if index is greater than parent
    trickleUp(parent); // Recursively call till correct position is found
  }
}


void Heap::dequeue() {
  if (numItems > 0) {
    if (numItems == 1) { // If only 1 item, make empty
      delete arr[0];
      arr[0] = nullptr;
      return;
    } else {
      delete arr[0];
      arr[0] = arr[numItems - 1]; // set top to last element
      arr[numItems - 1] = nullptr;
      numItems--; // Decrement numItems
      trickleDown(0); // Make sure all values are in right position
    }
  } else {
    throw runtime_error("heap is empty, can't dequeue"); // if numItems was 0 or less
  }
}

PrintJob* Heap::highest() {
  // check heap not empty
  if (numItems > 0) {
    return arr[0]; // return 1st
  } else {
    return nullptr;
  }
}

void Heap::print() const {
  if (numItems <= 0) {
    throw runtime_error("empty");
  } else {
    cout << "Priority: " << arr[0]->getPriority() << ", Job Number: " << arr[0]->getJobNumber() << ", Number of Pages: " << arr[0]->getPages() << endl; 
  }
}

void Heap::trickleDown(int index) {
  int leftChild = 2 * index + 1; // find left child
  int rightChild = 2 * index + 2; // find right child
  int maxIndex = index; // assign parameter as index

  // If leftChild is in range and priority of left child is greater than curr element priority
  if (leftChild < numItems && arr[leftChild]->getPriority() > arr[maxIndex]->getPriority()) {
    maxIndex = leftChild; // update max to left child
  }

  // If rightChild is in range and right child's priority is greater than curr element priority
  if (rightChild < numItems && arr[rightChild]->getPriority() > arr[maxIndex]->getPriority()) {
    maxIndex = rightChild; // update max to right child
  }

  // If maxIndex does not equal index, one of the children has higher priority than curr index
  if (maxIndex != index) { 
    swap(arr[index], arr[maxIndex]);  // Swap element at current index with maxIndex
    trickleDown(maxIndex); 
  }
}