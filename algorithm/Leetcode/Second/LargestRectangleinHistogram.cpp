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

    int largestRectangleArea(vector<int> &height) {

        stack<int> stk;

        int i = 0, max_area = 0;
        while (i < height.size()) {
            if (stk.empty() || height[stk.top()] <= height[i]) {
                stk.push(i++);
            } else {
                int tp = stk.top(); stk.pop();
                int area = height[tp] * (stk.empty() ? i: i - stk.top() - 1);
                max_area = max(max_area, area);
            }
        }

        while (!stk.empty()) {
            int tp = stk.top(); stk.pop();
            int area = height[tp] * (stk.empty() ? i: i - stk.top() - 1);
            max_area = max(max_area, area);
        }

        return max_area;
    }

    int largestRectangleAreaSlow(vector<int> &height) {

        int max_area = 0;

        for (int i = 0; i < height.size(); i++) {
            int min_height = height[i];
            for (int j = i; j < height.size(); j++) {
                min_height = min(min_height, height[j]);
                int area = (j - i + 1) * min_height;
                max_area = max(max_area, area);
            }
        }

        return max_area;
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
