// Given an array of integers, find two numbers such that they add up to a
// specific target number.

// The function twoSum should return indices of the two numbers such that
// they add up to the target, where index1 must be less than index2. Please
// note that your returned answers (both index1 and index2) are not zero-based.

// You may assume that each input would have exactly one solution.

// Input: numbers={2, 7, 11, 15}, target=9
// Output: index1=1, index2=2#include <vector>

#include <iostream>
#include <unordered_map>
using namespace std;


class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        unordered_map<int, int> map;
        vector<int> result(2, -1);

        for (int i = 0; i < numbers.size(); i++) {
            if (map.count(target-numbers[i]) != 0) {
                result[0] = min(map[target-numbers[i]], i) + 1;
                result[1] = max(map[target-numbers[i]], i) + 1;
                return result;
            } else {
                map[numbers[i]] = i;
            }
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    int A[] = {10,1,-2,7,-6,1,5,1};
    vector<int> input(A, A+sizeof(A)/sizeof(A[0]));

    vector<int> result = solution.twoSum(input, 6);
    cout << result[0] << " " << result[1] << endl;

    return 0;
}
