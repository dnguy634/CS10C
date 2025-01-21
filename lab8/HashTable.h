#pragma once

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

 private:
	list<WordEntry> *hashTable;
	int size;

 public:
	HashTable(int);
    ~HashTable(); // destructor
	bool contains(const string &);
	double getAverage(const string &);
	void put(const string &, int);
 
 private:
	int computeHash(const string &);

	// rule of 3
    HashTable(const HashTable& ) = delete;
    HashTable& operator=(const HashTable& ) = delete;
};
