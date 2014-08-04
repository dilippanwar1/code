// Given an array of integers, every element appears three times except for one.
// Find that single one.

// Could you implement it without using extra memory?


#include <iostream>
using namespace std;


#define  NBITS    32


class Solution {
public:
    int singleNumber(int A[], int n) {

        int bits[NBITS]; // store sum of every bits
        for (int i = 0; i < NBITS; i++) {
            bits[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < NBITS; j++) { // constant for loop
                int bit = (A[i] >> j) & 0x01;
                bits[j] += bit;
                bits[j] %= 3;
            }
        }

        // restore number
        int result = 0;
        for (int i = 0; i < NBITS; i++) {
            result |= (bits[i] << i);
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    int A[] = {2,2,2,3,3,3,4,4,4,5,6,6,6};

    cout << solution.singleNumber(A, sizeof(A)/sizeof(A[0])) << endl;
}
