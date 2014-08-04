// Given an array S of n integers, are there elements a, b, c in S such that
// a + b + c = 0? Find all unique triplets in the array which gives the sum
// of zero.

// Note:
// Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ? b ? c)
// The solution set must not contain duplicate triplets.
// For example, given array S = {-1, 0, 1, 2, -1, -4},
// A solution set is:
//     (-1, 0, 1)
//     (-1, -1, 2)
//     xx (-4, 2, 2) xx, 2 is duplicate

#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {

        vector<int> triplet;
        vector<vector<int> > result;

        if (num.size() < 3) {
            return result;
        }

        sort(num.begin(), num.end());

        // find start index of positive and negative number
        int pos_index = -1, neg_index = -1, zero_num = 0;
        for (int i = 0; i < num.size(); i++) {
            if (neg_index == -1 && num[i] >= 0) {
                neg_index = i-1;
            }
            if (pos_index == -1 && num[i] > 0) {
                pos_index = i;
            }
            if (num[i] == 0) {
                zero_num++;
            }
        }

        // consider only one negtive number
        for (int i = 0; i < pos_index; i++) {
            int left = pos_index, right = num.size() - 1, sum = -num[i];
            while (left < right) {
                if (num[left] + num[right] == sum) {
                    triplet.push_back(num[i]);
                    triplet.push_back(num[left]);
                    triplet.push_back(num[right]);
                    result.push_back(triplet);
                    triplet.clear();
                    left++;
                    right--;
                } else if (num[left] + num[right] < sum) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        // consider only one positive number
        for (int i = pos_index; i < num.size(); i++) {
            int left = 0, right = neg_index, sum = -num[i];
            while (left < right) {
                if (num[left] + num[right] == sum) {
                    triplet.push_back(num[left]);
                    triplet.push_back(num[right]);
                    triplet.push_back(num[i]);
                    result.push_back(triplet);
                    triplet.clear();
                    left++;
                    right--;
                } else if (num[left] + num[right] < sum) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        // consider zeros
        if (zero_num >= 3) {
            triplet.push_back(0);
            triplet.push_back(0);
            triplet.push_back(0);
            result.push_back(triplet);
            triplet.clear();
        }
        if (zero_num > 0) {
            for (int i = 0; i <= neg_index; i++) {
                for (int j = pos_index; j < num.size(); j++) {
                    if (num[i] + num[j] == 0) {
                        triplet.push_back(num[i]);
                        triplet.push_back(0);
                        triplet.push_back(num[j]);
                        result.push_back(triplet);
                        triplet.clear();
                    }
                }
            }
        }

        vector<vector<int> >::iterator end = result.end();
        sort(result.begin(), result.end(), less<vector<int> >());
        vector<vector<int> >::iterator new_end = unique(result.begin(), end);
        result.erase(new_end, end);

        return result;
    }


    vector<vector<int> > threeSum2(vector<int> &num) {

        vector<int> triplet;
        vector<vector<int> > result;

        sort(num.begin(), num.end());
        for (int i = 0; i < num.size(); i++) {
            if (i != 0 && num[i] == num[i-1]) // handle duplicate
                continue;
            int j = i + 1;
            int k = num.size() - 1;
            while (j < k) {
                if (j != i + 1 && num[j] == num[j-1]) {
                    j++; continue;
                }
                if (k != num.size() - 1 && num[k] == num[k+1]) {
                    k--; continue;
                }
                int sum_two = num[i] + num[j];
                if (sum_two + num[k] < 0) {
                    j++;
                } else if (sum_two + num[k] > 0) {
                    k--;
                } else {
                    triplet.push_back(num[i]);
                    triplet.push_back(num[j]);
                    triplet.push_back(num[k]);
                    result.push_back(triplet);
                    triplet.clear();
                    j++;
                    k--;
                }
            }
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    int nums[] = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
    int size = sizeof(nums) / sizeof(nums[0]);
    vector<int> numbers (nums, nums + size);

    //vector<vector<int> > result = solution.threeSum(numbers);
    vector<vector<int> > result = solution.threeSum2(numbers);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}
