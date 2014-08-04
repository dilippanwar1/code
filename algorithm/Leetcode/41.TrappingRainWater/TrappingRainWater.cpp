// Given n non-negative integers representing an elevation map where the width
// of each bar is 1, compute how much water it is able to trap after raining.

// For example,
//    Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

// http://leetcode.com/onlinejudge#question_42
// The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
// In this case, 6 units of rain water (blue section) are being trapped.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    // O(n) space solution. For each bar, find the max height bar on the left and
    // right; then for this bar, it can hold min(max_left, max_right) - height
    int trap(int A[], int n) {

        int leftMaxHeight[n];
        int rightMaxHeight[n];

        for (int i = 0; i < n; i++) {
            if (i == 0) {
                leftMaxHeight[i] = 0;
                rightMaxHeight[n-1] = 0;
            } else {
                leftMaxHeight[i] = max(leftMaxHeight[i-1], A[i-1]);
                rightMaxHeight[n-1-i] = max(rightMaxHeight[n-i], A[n-i]);
            }
        }

        int sum = 0;
        for (int i = 0; i < n; i++) {
            int height = min(leftMaxHeight[i], rightMaxHeight[i]);
            if (height > A[i]) {
                sum += height - A[i];
            }
        }

        return sum;
    }

    int trap2(int A[], int n) {

        if (!A || !n) return 0;

        // find max hight
        int mid = 0, water = 0, h = 0;
        for (int i = 0; i < n; ++i) {
            if (A[i] > A[mid])
                mid = i;
        }

        for (int i = 0; i < mid; ++i) {
            if (h > A[i])
                water += h - A[i];
            else
                h = A[i];
        }

        h = 0;
        for (int i = n - 1; i > mid; --i) {
            if (h > A[i])
                water += h - A[i];
            else
                h = A[i];
        }
        return water;
    }
};


int main(void) {

    Solution solution;
    int A[] = {0,1,0,2,1,0,1,3,2,1,2};
    //int A[] = {2,1,0,1,3};
    cout << solution.trap(A, sizeof(A)/sizeof(A[0])) << endl;
    cout << solution.trap2(A, sizeof(A)/sizeof(A[0])) << endl;
    return 0;
}
