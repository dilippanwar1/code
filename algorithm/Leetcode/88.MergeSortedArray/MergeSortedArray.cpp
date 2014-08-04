// Given two sorted integer arrays A and B, merge B into A as one sorted array.

// Note:
// You may assume that A has enough space to hold additional elements from B.
// The number of elements initialized in A and B are m and n respectively.

#include <iostream>
using namespace std;


class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int A_index = m-1;
        int B_index = n-1;
        int C_index = m+n-1;

        while (A_index >= 0 && B_index >= 0) {
            if (A[A_index] > B[B_index]) {
                A[C_index--] = A[A_index--];
            } else {
                A[C_index--] = B[B_index--];
            }
        }

        // copy remaining part in B; we don't care A since it's already sorted
        while (B_index >= 0) {
            A[C_index--] = B[B_index--];
        }
    }
};


int main(void) {

    Solution solution;
    int A[] = {10,15,19,0,0,0,0};
    int B[] = {4,6,10,12};

    solution.merge(A, 3, B, 4);
    for (int i = 0; i < sizeof(A)/sizeof(A[0]); i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}
