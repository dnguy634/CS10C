#include "Jug.h"
#include <algorithm>

using namespace std;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) 
    : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {}

Jug::~Jug() {} 

// check if target state is reached
bool Jug::isTarget(int a, int b) const { 
    return (a == 0 && b == N);  // true if conditions met
}

// helper function to prioritize states and add them to the priority queue
void Jug::priorityEnqueue(priority_queue<State>& pq, int a, int b, int c, const string& s) {
    // ensure water in both jugs is non negative and capacity per jug not exceeded
    if (a >= 0 && b >=0 && a <= Ca && b <= Cb) {
        string state = to_string(a) + "," + to_string(b); // make key for the new state

        // check if state key has not been visited 
        if (find(visited.begin(), visited.end(), state) == visited.end()) {
            visited.push_back(state); // push the state key string into visited vector
            pq.push(State(a, b, c, s)); // push the new state onto the priority queue
        }
    }
}

// solves  problem using Dijkstra's Algorithm
int Jug::solve(string& solution) {
    solution = "";

    // check edge cases
    if (N > Ca + Cb) throw runtime_error("target > both jugs"); // target greater than both jugs 
    if (N > Cb) throw runtime_error("target > cap of jug B"); // target greater than capacity of jug B
    if (Ca == 0 && Cb != N) throw runtime_error("jug A = 0 && jug B cap != target"); // jug A capacity = 0 and Jug B capacity != target
    if (Cb == 0 && Ca != N) throw runtime_error("jug B = 0 && jug B cap != target"); // jug B capacity = 0 and Jug A's capacity != target
    if (Ca < 0 || Cb < 0 || N < 0 || ceB < 0 || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0 ) throw runtime_error("input negative"); // any input is negative
    if (Ca > 1000 || Cb > 1000) throw runtime_error("cap is too high"); // capacities too high

    // Dijkstra's Algorithm
    priority_queue<State> pq;
    visited.clear();

    pq.push(State(0, 0 , 0, ""));
    visited.push_back("0,0");

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int a = current.A;
        int b = current.B;
        int cost = current.cost;
        string steps = current.steps;

        if (isTarget(a, b)) {
            solution = steps + "success " + to_string(cost);
            return 1;
        }

        // fill A
        priorityEnqueue(pq, Ca, b, cost + cfA, steps + "fill A\n");
        // fill B
        priorityEnqueue(pq, a, Cb, cost + cfB, steps + "fill B\n");
        // empty A
        priorityEnqueue(pq, 0, b, cost + ceA, steps + "empty A\n");
        // empty B
        priorityEnqueue(pq, a, 0, cost + ceB, steps + "empty B\n");
        // pour A to B
        int pourAB = min(a, Cb - b);
        priorityEnqueue(pq, a - pourAB, b + pourAB, cost + cpAB, steps + "pour A B\n");
        // pour B to A
        int pourBA = min(b, Ca - a);
        priorityEnqueue(pq, a + pourBA, b - pourBA, cost + cpBA, steps + "pour B A\n");
    }
    // no solution found
    solution = "";
    return 0;
}
