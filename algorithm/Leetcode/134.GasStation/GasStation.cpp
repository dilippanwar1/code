// There are N gas stations along a circular route, where the amount of gas
// at station i is gas[i].

// You have a car with an unlimited gas tank and it costs cost[i] of gas to
// travel from station i to its next station (i+1). You begin the journey
// with an empty tank at one of the gas stations.

// Return the starting gas station's index if you can travel around the circuit
// once, otherwise return -1.

// Note:
// The solution is guaranteed to be unique.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int start = 0, before = 0, current = 0;
        for (int i = 0; i < gas.size(); i++) {
            current += gas[i] - cost[i]; // current gas with the car
            if (current < 0) { // if current gas is less than 0, we need update
                start = i + 1; // we have to start from next station
                before += current; // gas needed before next station
                current = 0;       // set current tank to zero
            }
        }

        if (before + current >= 0) // if we can reach the end, return index
            return start;
        else
            return -1;
    }

    int canCompleteCircuitNaive(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();
        int current;
        bool find;

        for (int i = 0; i < n; i++) { // we try every starting point
            current = 0;
            find = true;
            // update current as we proceed to next station
            for (int j = i; j < n + i; j++) {
                current += gas[j % n] - cost[j % n];
                if (current < 0) {
                    find = false;
                    break;
                }
            }
            if (find == true) {
                return i;
            }
        }

        return -1;
    }
};


int main(void) {

    Solution solution;
    int gas[]  = {2};
    int cost[] = {2};
    vector<int> input1(gas , gas+sizeof(gas)/sizeof(int));
    vector<int> input2(cost, cost+sizeof(cout)/sizeof(int));

    cout << solution.canCompleteCircuit(input1, input2) << endl;
}
