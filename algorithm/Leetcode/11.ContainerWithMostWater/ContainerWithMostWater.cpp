// Given n non-negative integers a1, a2, ..., an, where each represents a point
// at coordinate (i, ai). n vertical lines are drawn such that the two endpoints
// of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis
// forms a container, such that the container contains the most water.

// Note: You may not slant the container.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    int maxArea(vector<int> &height) {

        int left = 0, right = height.size() - 1;
        int max_area = 0;

        while (left < right) {
            // compute new area
            int area = (right - left) * min(height[right], height[left]);

            if (area > max_area)
                max_area = area;

            // since height[left] is the smaller one, we have found the max
            // area that can be formed by left. That is to say, no matter
            // how we move right, we can never find a bigger area using left.
            // Therefore, we can safely discard left. The same explaination
            // applies to right line.
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return max_area;
    }
};


int main(void) {

    Solution solution;
    vector<int> height;

    height.push_back(3);
    height.push_back(1);
    cout << solution.maxArea(height) << endl;
}
