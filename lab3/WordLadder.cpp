#include "WordLadder.h"

#include <iostream>
#include <fstream>
 
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

WordLadder::WordLadder(const string& filename) { // open input file and check if words are 5 characters long to add to dictionary list
  ifstream inFS(filename);
  if (!inFS.is_open()) {                          // check if file can open
    throw runtime_error("Unable to open file");  // throw exception if file not open
    return;
  }
  string word;
  while(inFS >> word) {   
    if (!word.empty()) {      // read in each word from file, if word is valid, continue 
      if (word.size() != 5) {
        throw runtime_error("Word not 5 characters long");   // throw exeption if word not 5 characters
        return;
      } else {
        dict.push_back(word);   // otherwise, add word to dict if its 5 characters
      }
    }
  }
  inFS.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {   // output word ladder from dict list
  ofstream outFS(outputFile);
  if (!outFS.is_open()) {
    throw runtime_error("Unable to open file");   // throw exeption if output file can't open
    return;
  }

  if (start == end) {             // check if start = end, then create stack with one word
    stack<string> oneWordStack;
    oneWordStack.push(start);
    outFS << oneWordStack.top();
    return;
  }

  if (find(dict.begin(), dict.end(), start) == dict.begin() || find(dict.begin(), dict.end(), end) == dict.end()) { 
    throw runtime_error("start/end word not in list");      // check if start/end word not in dict list
    return;
  }

  stack<string> startStack;         // create first stack and push the start word into stack
  startStack.push(start);
  queue<stack<string>> ladderQueue;  // create queue and push startStack in it
  ladderQueue.push(startStack);

  while(!ladderQueue.empty()) {       // while queue is not empty, continue
    stack<string> currStack = ladderQueue.front();  // make new stack equal to first stack in queue, then clear queue
    ladderQueue.pop();                             
    string topWord = currStack.top();             // create string to compare to dictionary list of words

    for(auto it = dict.begin(); it != dict.end();) {  // traverse through dict list until end string is reached
      string currWord = *it;
      if (misMatchByOne(topWord, currWord) == true) {   // if word from stack and list satisfies misMatch function, continue
        stack<string> newStack = currStack;       // make a new stack that takes in currStack (prev word/words), and push the new word on top of stack
        newStack.push(*it);
        if (currWord == end) {      // output words from newStack to output file if end of dictionary list is reached
          stack<string> reverseStack;
          while (!newStack.empty()) {     // create a new stack (reverseStack) that takes each word from top of old stack, then pop old stack until empty
            reverseStack.push(newStack.top());
            newStack.pop();
          }
          while(!reverseStack.empty()) {         // output the new stack (reverseStack) from the top, list will be in correct order now (at first it was reverse order)
            outFS << reverseStack.top() << " ";
            reverseStack.pop();
          }
          return;
        }
        ladderQueue.push(newStack);   // if end of list not reached, push new stack with new word found in ladder to queue
        it = dict.erase(it);         // delete word from dictionary
      } else {
        *it++;                     // traverse through next word in dictionary if misMatch function is not satisfied
      }
    }
  }
  outFS << "No Word Ladder Found." << endl;  // if queue it empty, there is no word ladder found
  outFS.close();
}

  bool WordLadder::misMatchByOne(const string& word1, const string& word2) {  // check if comparison satisfies word ladder
    int diff = 0;
    for (int i = 0; i < 5; i++) {         // compare each word in string, starting at index 0-4
      if (word1.at(i) != word2.at(i)) {  // compare both words at each index and update diff if character is not equal
        diff++;
      }
    }
    return (diff == 1);   // only return true if diff is 1
  }



