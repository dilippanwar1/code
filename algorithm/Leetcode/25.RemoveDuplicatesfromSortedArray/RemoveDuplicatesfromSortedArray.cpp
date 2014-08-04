// Given a sorted array, remove the duplicates in place such that each element
// appear only once and return the new length.

// Do not allocate extra space for another array, you must do this in place with
// constant memory.

// For example,
//    Given input array A = [1,1,2],
//    Your function should return length = 2, and A is now [1,2].

#include <stdio.h>


class Solution {
public:
    int removeDuplicates(int A[], int n) {

        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return 1;
        }

        int start = 0, end = 0;

        // two pointers, first one is the position to insert, second one
        // is the unique value to be inserted
        while (end != n) {
            A[start++] = A[end++];
            while (A[end-1] == A[end]) {
                end++;
                if (end == n) {
                    break;
                }
            }
        }

        return start;
    }

    int removeDuplicatesForum(int A[], int n) {

        if (n <= 1)
            return n;

        int i = 0;
        for (int j = 1; j < n; j++) {
            if (A[j] != A[i]) {
                A[++i] = A[j];
            }
        }

        return i+1;
    }
};


int main(void) {

    Solution solution;
    int A[] = {-3,-3,-2,-1,-1,0,0,0,0,0};

    int new_size = solution.removeDuplicates(A, sizeof(A)/sizeof(int));
    printf("%d\n", new_size);
    for (int i = 0; i < new_size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
