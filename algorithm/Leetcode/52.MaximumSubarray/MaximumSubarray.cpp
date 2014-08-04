// Find the contiguous subarray within an array (containing at least one
// number) which has the largest sum.

// For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
// the contiguous subarray [4,-1,2,1] has the largest sum = 6.

#include <iostream>
using namespace std;


class Solution {
public:
    int maxSubArray(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int max_sofar = 0, max = INT_MIN;

        for (int i = 0; i < n; i++) {
            max_sofar += A[i];
            if (max_sofar < 0) {
                max_sofar = 0;
            } else if (max_sofar > max) {
                max = max_sofar;
            }
        }

        if (max == INT_MIN) {
            for (int i = 0; i < n; i++) {
                max = max > A[i] ? max : A[i];
            }
        }
        return max;
    }
};


int main(void) {
    Solution solution;
    //int array[] = {-2,1,-3,4,-1,2,1,-5,4};
    int array[] = {-2};
    cout << solution.maxSubArray(array, sizeof(array)/sizeof(array[0])) << endl;
}
