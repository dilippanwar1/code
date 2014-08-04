// Given an array with n objects colored red, white or blue, sort them so that
// objects of the same color are adjacent, with the colors in the order red,
// white and blue.

// Here, we will use the integers 0, 1, and 2 to represent the color red, white,
// and blue respectively.

// Note:
// You are not suppose to use the library's sort function for this problem.

// Follow up:
// A rather straight forward solution is a two-pass algorithm using counting
// sort. First, iterate the array counting number of 0's, 1's, and 2's, then
// overwrite array with total number of 0's, then 1's and followed by 2's.
// Could you come up with an one-pass algorithm using only constant space?

#include <iostream>
using namespace std;


class Solution {
public:

    // We assume redIndex points to the last red (0) elements, blueIndex
    // points to the first blue (2) elements. Probe scan the array from
    // left to right. There is a hidden property of probe: Anything between
    // redIndex and probe are all white (1).
    void sortColors(int A[], int n) {

        if (n == 0 || n == 1)
            return;

        int redIndex = -1, blueIndex = n, probe = 0;
        while (probe < blueIndex) {
            if (A[probe] == 0) {
                swap(A, probe++, ++redIndex);
            } else if (A[probe] == 2) {
                swap(A, probe, --blueIndex);
            } else {
                probe++;
            }
        }
    }

    void swap(int A[], int i, int j) {
        int tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;
    }

    // Two passes
    void sortColors2(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n == 0 || n == 1)
            return;

        int numOf0 = 0, numOf1 = 0, numOf2 = 0;

        for (int i = 0; i < n; i++) {
            switch (A[i]) {
            case 0:
                numOf0++;
                break;
            case 1:
                numOf1++;
                break;
            case 2:
                numOf2++;
                break;
            default:
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            if (numOf0 != 0) {
                A[i] = 0;
                numOf0--;
            } else if (numOf1 != 0) {
                A[i] = 1;
                numOf1--;
            } else {
                A[i] = 2;
            }
        }
    }
};


int main(void) {

    Solution solution;
    int A[] = {0,0};
    int size = sizeof(A)/sizeof(A[0]);

    solution.sortColors(A, size);
    for (int i = 0; i < size; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    return 0;
}
