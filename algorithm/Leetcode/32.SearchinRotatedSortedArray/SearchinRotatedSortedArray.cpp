// Suppose a sorted array is rotated at some pivot unknown to you beforehand.
// (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

// You are given a target value to search. If found in the array return its
// index, otherwise return -1.

// You may assume no duplicate exists in the array.

#include <iostream>
using namespace std;


class Solution {
public:
    int search(int A[], int n, int target) {

        if (n == 0)
            return -1;

        return searchHelper(A, 0, n-1, target);
    }

    int searchHelper(int A[], int left, int right, int target) {

        if (left > right)
            return -1;

        int mid = left + (right - left) / 2;
        if (A[mid] == target) {
            return mid;
        } else if (A[left] <= A[mid]) { // left part is sorted, we need <=
            if (target >= A[left] && target < A[mid]) {
                return searchHelper(A, left, mid-1, target);
            } else {
                return searchHelper(A, mid+1, right, target);
            }
        } else {                // right part is sorted
            if (target <= A[right] && target > A[mid]) {
                return searchHelper(A, mid+1, right, target);
            } else {
                return searchHelper(A, left, mid-1, target);
            }
        }
    }
};


int main(void) {

    Solution solution;
    int A[] = {3,4,5,0,1,2};
    cout << solution.search(A, sizeof(A)/sizeof(A[0]), 3) << endl;
    return 0;
}
