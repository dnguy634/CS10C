#include "HashTable.h"
#include "WordEntry.h"

HashTable::HashTable(int s) {
    size = s;
    hashTable = new list<WordEntry>[size];
}

HashTable::~HashTable() {
    delete[] hashTable; // free dynamically allocated memory
    hashTable = nullptr; // prevent dangling pointer
}

int HashTable::computeHash(const string &s) {
    int sum = 0;
    for (unsigned int i = 0; i < s.size(); ++i) {
        sum = (sum * 31 + i) % size; // made with help of chatgpt, returns unique hash
    }
    return sum;
}

void HashTable::put(const string &s, int score) { 
    if (contains(s)) { // if word exists
        list<WordEntry>::iterator i; 
        // traverse through the list using iterator to check each value
        for (i = hashTable[computeHash(s)].begin(); i != hashTable[computeHash(s)].end(); i++) {
            // update appearance if word exists
            if (i->getWord() == s) {
                i->addNewAppearance(score);
            }
        }
    } 
    else { // if it doesn't exist
        WordEntry newWord = WordEntry(s, score);
        hashTable[computeHash(s)].push_front(newWord); 
    }
}

double HashTable::getAverage(const string &s) {
    if (contains(s)) { // if word exists 
        list<WordEntry>::iterator i; 
        // traverse through the list using iterator to check each value
        for (i = hashTable[computeHash(s)].begin(); i != hashTable[computeHash(s)].end(); i++) {
            // return average score if word is found
            if (i->getWord() == s) {
                return i->getAverage();
            }
        }
    } 
    // return neutral result (2.0) if not found
    return 2.0;
}

bool HashTable::contains(const string &s) {
    // traverse through the list using iterator to check each value
    for (list<WordEntry>::iterator i = hashTable[computeHash(s)].begin(); i != hashTable[computeHash(s)].end(); i++) {
        // true word exists in the hash table
        if (i->getWord() == s) {
            return true;
        }
    }
    // false if word not found
    return false;
}

