// http://www.geeksforgeeks.org/largest-rectangle-under-histogram/

// Given n non-negative integers representing the histogram's bar height
// where the width of each bar is 1, find the area of largest rectangle in
// the histogram.

// For example,
//    Given height = [2,1,5,6,2,3],
//    return 10.

#include <stack>
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    // For every bar 'x', we calculate the area with 'x' as the smallest bar
    // in the rectangle. If we calculate such area for every bar 'x' and find
    // the maximum of all areas, our task is done. How to calculate area with
    // 'x' as smallest bar? We need to know index of the first smaller (smaller
    // than 'x') bar on left of 'x' and index of first smaller bar on right of
    // 'x'. Let us call these indexes as 'left index' and 'right index'
    // respectively. We traverse all bars from left to right, maintain a stack
    // of bars. Every bar is pushed to stack once. A bar is popped from stack
    // when a bar of smaller height is seen. When a bar is popped, we calculate
    // the area with the popped bar as smallest bar. How do we get left and right
    // indexes of the popped bar - the current index tells us the 'right index'
    // and index of previous item in stack is the 'left index'.
    int largestRectangleArea(vector<int> &height) {

        // Create an empty stack. The stack holds indexes of height[] array. The
        // bars stored in stack are always in increasing order of their heights.
        stack<int> s;

        int max_area = 0;       // Initalize max area
        int area_with_top; // To store area with top bar as the smallest bar
        int n = height.size();

        // Run through all bars of given histogram
        int i = 0;
        while (i < n)
        {
            // If this bar is higher than the bar on top stack, push it to stack
            if (s.empty() || height[s.top()] <= height[i])
                s.push(i++);
            // If this bar is lower than top of stack, then calculate area of
            // rectangle with stack top as the smallest (or minimum height)
            // bar. 'i' is 'right index' for the top and element before top in
            // stack is 'left index'
            else
            {
                int tp = s.top();   // store the top index
                s.pop();            // pop the top

                // Calculate the area with hist[tp] stack as smallest bar
                area_with_top = height[tp] * (s.empty() ? i : i - s.top() - 1);

                // Update max area, if needed
                if (max_area < area_with_top)
                    max_area = area_with_top;
            }
        }

        // Now pop the remaining bars from stack and calculate area with every
        // popped bar as the smallest bar
        while (s.empty() == false)
        {
            int tp = s.top();
            s.pop();
            area_with_top = height[tp] * (s.empty() ? i : i - s.top() - 1);

            if (max_area < area_with_top)
                max_area = area_with_top;
        }

        return max_area;
    }

    int largestRectangleAreaSlow(vector<int> &height) {

        int n = height.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return height[0];

        int max_area = INT_MIN;
        for (int i = 0; i < n; i++) {
            int minHeight = height[i];
            for (int j = i; j < n; j++) {
                minHeight = min(minHeight, height[j]);
                int area = minHeight * (j - i + 1);
                max_area = max(max_area, area);
            }
        }

        return max_area;
    }

    // Only pass small test (1. two much memory required; 2. O(N^2) too slow)
    int largestRectangleAreaSlowBig(vector<int> &height) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = height.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return height[0];

        // keep min value between i...j
        int **dp = my2DAlloc2(n, n);
        int max_area = 0;
        for (int i = 0; i < n; i++) {
            dp[i][i] = height[i];
            max_area = max(max_area, dp[i][i]);
            if (i < n - 1) {
                dp[i][i+1] = min(height[i], height[i+1]);
                max_area = max(max_area, dp[i][i+1]*2);
            }
        }

        for (int len = 3; len <= n; len++) {
            for (int i = 0; i < n - len + 1; i++) {
                int j = i + len - 1;
                dp[i][j] = min(dp[i+1][j-1], min(height[i], height[j]));
                max_area = max(max_area, dp[i][j]*len);
            }
        }

        my2DFree2(dp, n, n);
        return max_area;
    }

private:
    int** my2DAlloc2(int m, int n) {

        int header_size = m * sizeof(int*);
        int content_size = m * n * sizeof(int);

        int **row = (int**) malloc(header_size + content_size);
        int *content = (int*) (row + m);

        for (int i = 0; i < m; i++) {
            row[i] = content + i * n;
        }

        return row;
    }

    void my2DFree2(int **array, int m, int n) {
        free(array);
    }
};


int main(void) {

    Solution solution;
    int a[] = {1,2,3,4,5,4,3};
    vector<int> height(a, a+sizeof(a)/sizeof(a[0]));

    cout << solution.largestRectangleArea(height) << endl;
    cout << solution.largestRectangleAreaSlow(height) << endl;
    return 0;
}
