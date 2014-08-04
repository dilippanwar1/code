// Given an array of non-negative integers, you are initially positioned
// at the first index of the array.

// Each element in the array represents your maximum jump length at that
// position.

// Determine if you are able to reach the last index.

// For example:
//    A = [2,3,1,1,4], return true.
//    A = [3,2,1,0,4], return false.

#include <iostream>
using namespace std;


class Solution {
public:

    bool canJump(int A[], int n) {

        if (n == 0 || n == 1)
            return true;

        int max_reach = A[0];
        for (int i = 1; i < n; i++) {
            if (i > max_reach)  // outside of max reachable index, retur false
                return false;
            // update the max reachable index so far
            max_reach = max(max_reach, i + A[i]);
        }

        return true;
    }

    bool canJumpSlow(int A[], int n) {

        if (n == 0 || n == 1)
            return true;

        bool table[n];
        table[0] = true;
        for (int i = 1; i < n; i++)
            table[i] = false;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (table[j] == true && A[j] >= i-j) {
                    table[i] = true;
                    break;
                }
            }
        }

        return table[n-1];
    }
};


int main(void) {

    Solution solution;
    //int A[] = {2, 3, 1, 1, 4};
    //int A[] = {3, 2, 1, 0, 4};
    int A[100000];
    int n = sizeof(A) / sizeof(A[0]);
    for (int i = 0; i < n; i++)
        A[i] = 3;

    cout << solution.canJump(A, n) << endl;
    return 0;
}
