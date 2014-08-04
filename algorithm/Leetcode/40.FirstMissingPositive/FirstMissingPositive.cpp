// Given an unsorted integer array, find the first missing positive integer.

// For example,
//    Given [1,2,0] return 3,
//    and [3,4,-1,1] return 2.

// Your algorithm should run in O(n) time and uses constant space.

#include <iostream>
using namespace std;


class Solution {
public:
    // Use A[i] to store i+1
    int firstMissingPositive(int A[], int n) {

        int i = 0;
        while (i < n) {
            // now we put A[i] to its correct position, e.g, if A[i] == 3, then
            // we need to put it at position 2 (A[i]-1). we only swap positive
            // numbers when A[i]! = (i+1), the last condition means we shouldn't
            // swap when the other element has already been in the right position.
            if (A[i] != (i+1) && A[i] >= 1 && A[i] <= n && A[A[i]-1] != A[i]) {
                swap(A[i], A[A[i]-1]);
            } else {
                i++;
            }
        }

        for (i = 0; i < n; ++i)
            if (A[i] != (i + 1))
                return i+1;

        return n+1;
    }
};


int main(void) {

    Solution solution;
    int A[] = {-1,1,3,4};
    //int A[] = {1,2,0};
    //int A[] = {1,1};
    cout << solution.firstMissingPositive(A, sizeof(A)/sizeof(A[0])) << endl;
    return 0;
}
