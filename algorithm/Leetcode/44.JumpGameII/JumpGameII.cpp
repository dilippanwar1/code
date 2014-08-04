// Given an array of non-negative integers, you are initially positioned
// at the first index of the array.

// Each element in the array represents your maximum jump length at that
// position.

// Your goal is to reach the last index in the minimum number of jumps.

// For example:
//    Given array A = [2,3,1,1,4]
//    The minimum number of jumps to reach the last index is 2. (Jump 1
//        step from index 0 to 1, then 3 steps to the last index.)


#include <iostream>
using namespace std;


class Solution {
public:

    int jump(int A[], int n) {

        if (n == 0 || n == 1 || A[0] == 0)
            return 0;

        int pre_canReach = 0, cur_canReach = 0, steps = 0;
        for (int i = 0; i < n; i++) {
            // cannot reach
            if (i > cur_canReach)
                return -1;
            // if index i is out of previous step's range, we must jump
            if (i > pre_canReach) {
                pre_canReach = cur_canReach;
                steps++;
            }
            cur_canReach = max(cur_canReach, i+A[i]);
        }

        return steps;
    }

    // O(n^2) running time. The solution has a lot of useless backtrak. For
    // example, when "i = 2", suppose we already know that from A[0] we can
    // jump to 4, and from A[1] we can jump to 5. But in later loops, say
    // "i = 3", we still check A[0], A[1], A[2], and obviously, checking A[0]
    // is redundant.
    int jumpSlow(int A[], int n) {

        if (n == 0 || n == 1)
            return 0;

        int table[n];           // min jump to reach A[i]
        table[0] = (A[0] == 0) ? -1 : 0;

        for (int i = 1; i < n; i++) {
            table[i] = INT_MAX;
            for (int j = 0; j < i; j++) {
                if (table[j] != INT_MAX && A[j] >= i-j) {
                    table[i] = min(table[i], table[j] + 1);
                }
            }
        }

        return table[n-1];
    }
};


int main(void) {

    Solution solution;
    int A[] = {2, 3, 1, 1, 4};
    //int A[] = {3, 2, 1, 0, 4};
    //int A[100000]; for (int i = 0; i < n; i++) A[i] = 3;
    int n = sizeof(A) / sizeof(A[0]);

    cout << solution.jump(A, n) << endl;
    return 0;
}
