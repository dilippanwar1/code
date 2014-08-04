// Given a sorted array and a target value, return the index if the target
// is found. If not, return the index where it would be if it were inserted
// in order.

// You may assume no duplicates in the array.

// Here are few examples.
//    [1,3,5,6], 5 → 2
//    [1,3,5,6], 2 → 1
//    [1,3,5,6], 7 → 4
//    [1,3,5,6], 0 → 0

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    int searchInsert(int A[], int n, int target) {

        int left = 0, right = n-1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target < A[mid]) {
                if (mid == 0 || A[mid-1] < target)
                    return mid;
                right = mid - 1;
            } else if (target > A[mid]) {
                if (mid == n-1 || A[mid+1] > target)
                    return mid+1; // need to add 1
                left = mid + 1;
            } else {
                return mid;
            }
        }

        return -1;
    }
};


int main(void) {

    Solution solution;
    int A[] = {1,3,5,8};
    cout << solution.searchInsert(A,sizeof(A)/sizeof(A[0]), 7) << endl;
    return 0;
}

