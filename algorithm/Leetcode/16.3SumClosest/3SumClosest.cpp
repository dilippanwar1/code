// Given an array S of n integers, find three integers in S such that the sum
// is closest to a given number, target. Return the sum of the three integers.
// You may assume that each input would have exactly one solution.

// For example, given array S = {-1 2 1 -4}, and target = 1.
// The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {

        if (num.size() < 3)
            return -1;

        sort(num.begin(), num.end());

        int closest, min_diff = INT_MAX;

        // fix middle element
        for (int k = 1; k < num.size()-1; k++) {

            int i = k - 1, j = k + 1;
            while (i >= 0 && j < num.size()) {
                int sum = num[i] + num[j] + num[k];
                min_diff = min(min_diff, abs(sum - target));
                if (min_diff == abs(sum - target)) {
                    closest = sum;
                }
                if (sum > target) {
                    i--;
                } else if (sum < target) {
                    j++;
                } else {
                    return target;
                }
            }
        }

        return closest;
    }
};


int main(void) {

    Solution solution;
    // int nums[] = {0,-16,-11,-4,6,20,-17,10,14,-11,-16,17,-14,-11,8,-4,0,-2,
    //               10,15,0,-2,-3,19,17,-18,8,-16,-4,-16,-20,16,-16,5,-3,-18,
    //               -12,-18,-9,11,3,-14,-18,8,11,-9,-1,6,1,-17,-9,-7,11,-10,
    //               18,-1,4,-8,1,-20,-19,-19,12,13,14,15,0,18,3,8,-4,18,-1,6,
    //               -19,-11,11,14,12,11,-15,2,4,-1,5,3,-17,15,-1,-15,3,16,-11,
    //               -14,14,4,-7,-20,-2,-14,-8,-12,-12,18,4,-12,16};
    int nums[] = {-4,0,2,3,6};
    int size = sizeof(nums) / sizeof(nums[0]);
    vector<int> numbers (nums, nums + size);

    cout << solution.threeSumClosest(numbers, -31) << endl;
}
