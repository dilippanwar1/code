// Follow up for "Search in Rotated Sorted Array":
// What if duplicates are allowed?

// Would this affect the run-time complexity? How and why?

// Write a function to determine if a given target is in the array.


#include <iostream>
using namespace std;


class Solution {
public:
    bool search(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n == 0)
            return false;

        return searchHelper(A, 0, n-1, target);
    }

    bool searchHelper(int A[], int left, int right, int target) {

        if (left > right)
            return false;

        int mid = left + (right - left) / 2;
        if (A[mid] == target) {
            return true;
        } else if (A[left] < A[mid]) {  // left part is sorted, must be "<"
            if (target >= A[left] && target < A[mid]) {
                return searchHelper(A, left, mid-1, target);
            } else {
                return searchHelper(A, mid+1, right, target);
            }
        } else if (A[mid] < A[right]) { // right part is sorted
            if (target <= A[right] && target > A[mid]) {
                return searchHelper(A, mid+1, right, target);
            } else {
                return searchHelper(A, left, mid-1, target);
            }
        } else {
            return searchHelper(A, left, mid-1, target) ||
                searchHelper(A, mid+1, right, target);
        }
    }


    bool searchFaster(int A[], int n, int target) {

        int l = 0, r = n - 1;

        while (l <= r) {
            int m = l + (r - l)/2;

            if (A[m] == target)
                return true;    // found target

            if (A[l] < A[m]) {  // left half is sorted
                if (A[l] <= target && target < A[m]) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            } else if (A[l] > A[m]) { // right half is sorted
                if (A[m] < target && target <= A[r]) {
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            } else {
                l++;
            }
        }

        return false;
    }
};


int main(void) {

    Solution solution;
    int A[] = {3,3,4,4,4,5,0,1,1,1,2};
    cout << solution.search(A, sizeof(A)/sizeof(A[0]), 2) << endl;
    return 0;
}
