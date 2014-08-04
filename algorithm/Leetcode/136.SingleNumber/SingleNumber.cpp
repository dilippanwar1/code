// Given an array of integers, every element appears twice except for one.
// Find that single one.

// Could you implement it without using extra memory?


#include <iostream>
using namespace std;


class Solution {
public:
    int singleNumber(int A[], int n) {

        int sum = 0;

        for (int i = 0; i < n; i++) {
            sum ^= A[i];
        }

        return sum;
    }
};


int main(void) {

    Solution solution;
    int A[] = {2,2,3,4,4,6,6};

    cout << solution.singleNumber(A, sizeof(A)/sizeof(A[0])) << endl;
}
