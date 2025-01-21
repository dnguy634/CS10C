#pragma once
#include "PrintJob.h"

const int MAX_HEAP_SIZE = 10;

class Heap {
private:
  PrintJob* arr[MAX_HEAP_SIZE];      // array of PrintJob pointers
  int numItems;  // current number of items in heap

public:
  Heap();
  ~Heap();

  void enqueue(PrintJob* job);
  void dequeue();
  PrintJob* highest();
  void print() const;

private:
  void trickleDown(int);
  void trickleUp(int);
  Heap & operator=(const Heap &) = delete;
  Heap(const Heap &copy) = delete;
};
