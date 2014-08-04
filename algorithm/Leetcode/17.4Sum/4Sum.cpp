// Given an array S of n integers, are there elements a, b, c, and d in S such
// that a + b + c + d = target? Find all unique quadruplets in the array which
// gives the sum of target.

// Note:

// Elements in a quadruplet (a,b,c,d) must be in non-descending order. The
// solution set must not contain duplicate quadruplets.
// For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
//     A solution set is:
//     (-1,  0, 0, 1)
//     (-2, -1, 1, 2)
//     (-2,  0, 0, 2)


#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {

        vector<vector<int> > res;
        vector<int> oneRes(4, 0);
        int size = num.size();

        if (size < 4)
            return res;
        sort(num.begin(), num.end());

        for (int i = 0; i < size; ++i) {
            if (i != 0 && num[i] == num[i - 1]) continue;
            for (int j = i + 1; j < size; ++j) {
                if (j != i+1 && num[j] == num[j - 1]) continue;
                int p = j + 1;
                int q = size - 1;
                while ( p < q) {
                    if (p != j + 1 && num[p] == num[p-1]) {
                        ++p;
                        continue;
                    }
                    if (q != size - 1 && num[q] == num[q + 1]) {
                        --q;
                        continue;
                    }
                    int sum = num[i] + num[j] + num[p] + num[q];
                    if (sum == target) {
                        oneRes[0] = num[i];
                        oneRes[1] = num[j];
                        oneRes[2] = num[p];
                        oneRes[3] = num[q];
                        res.push_back(oneRes);
                        ++p;
                        --q;
                    }
                    else if (sum > target) {
                        --q;
                    }
                    else ++p;
                }
            }
        }
        return res;
    }
};


int main(void) {

    Solution solution;
    int nums[] = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
    int size = sizeof(nums) / sizeof(nums[0]);
    vector<int> numbers (nums, nums + size);

    vector<vector<int> > result = solution.fourSum(numbers, 10);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}
