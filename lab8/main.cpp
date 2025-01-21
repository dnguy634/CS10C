#include <iostream>
#include <fstream>
#include <cstdlib>

#include "HashTable.h"

using namespace std;

int main() {
    // Declare variables for inputing the data
    string line;    
    int score;
    string message = " ";
    
    // Open input file
    ifstream myfile("movieReviews.txt");
    if (myfile.fail()) {
        cout << "Could not open file" << endl;
        exit(1);
    }
    
    // Create hash table
    HashTable table(10708);
    
    // Read data from the input file
    while (!myfile.eof()) {
        myfile >> score;     // Get score
        myfile.get();        // Get blank space
        getline(myfile, line);
        int len = line.size();
        // Identify all individual strings
        while(len > 0) {
            string sub;
            len = line.find(" ");
            if (len > 0) {
                sub = line.substr(0, len);
                line = line.substr(len + 1, line.size());
            } else {
                sub = line.substr(0, line.size() - 1);
            }
            // Insert string with the score into the hash table
            table.put(sub, score);
        }
    }

    while(message.length() > 0) {
        cout << "Enter a review -- Press return to exit: " << endl;
        getline(cin, message);
    
        // Variables used for calculating the average
        double sum = 0;
        int count = 0;
        
        double sentiment = 0.0;
        
        size_t len = message.size();
        // Get each individual word from the input
        while(len != string::npos) {
            string sub;
            len = message.find(" ");
            if (len != string::npos) {
                sub = message.substr(0, len);
                message = message.substr(len + 1, message.size());
            } else {
                sub = message;
            }
            // Calculate the score of each word
            sum += table.getAverage(sub);
            ++count;
        }
    
        if (message.size() > 0) {
            sentiment = sum / count;
            cout << "The review has an average value of " << sentiment << endl;
            // Determine sentiment category based on average score
            if (sentiment >= 3.0) {
                cout << "Positive Sentiment" << endl;
            } else if (sentiment >= 2.0) {
                cout << "Somewhat Positive Sentiment" << endl;
            } else if (sentiment >= 1.0) {
                cout << "Somewhat Negative Sentiment" << endl;
            } else {
                cout << "Negative Sentiment" << endl;
            }
            cout << endl;
        }
    }
    
    return 0;
}