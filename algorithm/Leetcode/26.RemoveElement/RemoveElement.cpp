// Given an array and a value, remove all instances of that value in place and
// return the new length.

// The order of elements can be changed. It doesn't matter what you leave beyond
// the new length.

#include <stdio.h>


class Solution {
public:
    int removeElement(int A[], int n, int elem) {

        int i = 0;

        for (int j = 0; j < n; j++) {
            if (A[j] != elem) {
                A[i++] = A[j];
            }
        }

        return i;
    }

    int removeElement2(int A[], int n, int elem) {

        int count = 0;

        for (int k = 0; k < n; k++) {
            if (A[k] == elem) {
                count++;
            }
        }

        // `i` point to end of the array after dedup, `j` point to end of
        // original array
        int i = n - count - 1, j = n - 1;
        while (i >= 0) {
            if (A[i] == elem) {
                A[i] = A[j--];
            } else {
                i--;
            }
        }

        return n - count;
    }
};


int main(void) {

    int A[] = {1,2,3,4,5,6,6,9,6,2,8};
    Solution solution;

    int new_size = solution.removeElement(A, sizeof(A)/sizeof(int), 6);
    printf("%d\n", new_size);
    for (int i = 0; i < new_size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
