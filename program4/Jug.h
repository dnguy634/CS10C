#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Jug {
    public:
        // constructor ; capA, capB, target, fillA, fillB, emptyA, emptyB, A>B, B>A)
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug(); 

        // solve used to check input and find the solution if one exists
        int solve(string &solution);
    private:
        struct State {
            int A, B, cost;
            string steps;

            // Constructor
            State(int a, int b, int c, const string& s) : A(a), B(b), cost(c), steps(s) {}

            // need to define overload operator< for priority queue (some stl priority queue .push silly behavior) since we will be push()'ing
            bool operator<(const State& other) const {
                return cost > other.cost; // Inversed for the min-heap
            }
        };

        // vector of visited state keys
        vector<string> visited;
        int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
        // capA, capB, target, fillA, fillB, emptyA, emptyB, A>B, B>A)
        
        // checks if target state has been reached
        bool isTarget(int a, int b) const;

        // enqueues a new state to priority queue
        void priorityEnqueue(priority_queue<State>& pq, int a, int b, int c, const string& s);
};