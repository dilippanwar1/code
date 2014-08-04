// Follow up for "Remove Duplicates":
// What if duplicates are allowed at most twice?

// For example,
// Given sorted array A = [1,1,1,2,2,3],

// Your function should return length = 5, and A is now [1,1,2,2,3].

#include <iostream>
using namespace std;


class Solution {
public:
    int removeDuplicates(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n == 0 || n == 1 || n == 2)
            return n;

        int p = 0;    // elements at left side of p satisfy conditions
        bool already = false;   // whether we have seen duplicate before
        for (int i = 1; i < n; i++) {
            if (A[p] != A[i]) {
                if (already == true) {
                    A[p+1] = A[p]; // avoid "hole"
                    A[p+2] = A[i];
                    p = p + 2;
                    already = false;
                } else {
                    A[++p] = A[i];
                }
            } else {
                already = true;
            }
        }

        if (already == true)
            A[++p] = A[n-1];

        return p + 1;
    }
};


int main(void) {

    Solution solution;
    int A[] = {-3, -3, -3, 0, 0, 0, 0, 3, 3, 3, 4, 5, 5, 5};

    int new_size = solution.removeDuplicates(A, sizeof(A)/sizeof(int));
    printf("%d\n", new_size);
    for (int i = 0; i < new_size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
