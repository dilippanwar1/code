// Given a sorted array of integers, find the starting and ending position
// of a given target value.

// Your algorithm's runtime complexity must be in the order of O(log n).

// If the target is not found in the array, return [-1, -1].

// For example,
//    Given  [5, 7, 7, 8, 8, 10] and target value 8,
//    Return [3, 4].


#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    vector<int> searchRange(int A[], int n, int target) {

        int left = 0, right = n-1;
        vector<int> result(2, -1);

        // search left range
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target < A[mid]) {
                right = mid - 1;
            } else if (target > A[mid]) {
                left = mid + 1;
            } else {
                result[0] = mid;
                right = mid - 1;
            }
        }

        left = 0, right = n-1;
        // search right range
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target < A[mid]) {
                right = mid - 1;
            } else if (target > A[mid]) {
                left = mid + 1;
            } else {
                result[1] = mid;
                left = mid + 1;
            }
        }

        return result;
    }

    vector<int> searchRange2(int A[], int n, int target) {

        int left = 0, right = n-1;
        vector<int> result(2, -1);

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target < A[mid]) {
                right = mid - 1;
            } else if (target > A[mid]) {
                left = mid + 1;
            } else {
                int n1 = mid, n2 = mid;
                while (n1 > 0 && A[n1] == A[n1-1])
                    n1--;
                while (n1 < n-1 && A[n2] == A[n2+1])
                    n2++;
                result[0] = n1; result[1] = n2;
                return result;
            }
        }
        return result;
    }
};


int main(void) {

    Solution solution;
    int A[] = {3,3,3};
    vector<int> result = solution.searchRange(A,sizeof(A)/sizeof(A[0]), 3);
    cout << result[0] << " " << result[1] << endl;
    return 0;
}
