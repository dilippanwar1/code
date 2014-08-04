// Given a collection of candidate numbers (C) and a target number (T), find
// all unique combinations in C where the candidate numbers sums to T.

// Each number in C may only be used once in the combination.

// Note:
// All numbers (including target) will be positive integers.
// Elements in a combination (a1, a2, ... , ak) must be in non-descending order.
// The solution set must not contain duplicate combinations.

// For example, given candidate set 10,1,2,7,6,1,5 and target 8,
// A solution set is:
//    [1, 7]
//    [1, 2, 5]
//    [2, 6]
//    [1, 1, 6]

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {

        vector<int> path;
        vector<vector<int> > result;
        sort(candidates.begin(), candidates.end());
        combinationSumHelper(candidates, target, 0, path, result);
        return result;
    }

    void combinationSumHelper(vector<int> &candidates, int target, int index,
                        vector<int> &path, vector<vector<int> > &result) {
        if (target == 0) {
            result.push_back(path);
            return;
        } else if (target < 0) {
            return;
        } else if (index == candidates.size()) {
            return;
        }

        // find the end index of duplicate
        int end_index = index;
        while (end_index + 1 < candidates.size() &&
               candidates[end_index] == candidates[end_index+1]) {
            end_index++;
        }

        // if there is no duplicate with current candidates[index], then we
        // just recurse twice, one with candidates[index] and one without.
        if (index == end_index) {
            path.push_back(candidates[index]);
            combinationSumHelper(candidates, target - candidates[index], index+1,
                                 path, result);
            path.pop_back();
            combinationSumHelper(candidates, target, index+1, path, result);
        } else {
            // if there is duplicates, the number of duplicates can be computed
            // by end_index and index. so we try to use duplicates range from
            // 0 to end_index-index+1, update path at each iteration. At last,
            // remember to pop all duplicates.
            for (int i = 0; i <= end_index - index + 1; i++) {
                combinationSumHelper(candidates, target - i*candidates[index],
                                     end_index+1, path, result);
                path.push_back(candidates[index]);
            }
            for (int i = 0; i <= end_index - index + 1; i++) {
                path.pop_back();
            }
        }
    }


    vector<vector<int> > combinationSum2Web(vector<int> &candidates, int target) {

        vector<int> solution;
        vector<vector<int> > result;
        int sum = 0;

        sort(candidates.begin(), candidates.end());
        GetCombinations(candidates,sum, 0, target, solution, result);
        return result;
    }

    void GetCombinations(vector<int>& candidates, int& sum, int level, int target,
                         vector<int>& solution, vector<vector<int> >& result) {
        if (sum > target)
            return;

        if (sum == target) {
            result.push_back(solution);
            return;
        }

        // choose ith element
        for (int i = level; i< candidates.size(); i++) {
            sum += candidates[i];
            solution.push_back(candidates[i]);
            // use i+1 here if we cannot use more than once
            GetCombinations(candidates, sum, i+1, target, solution, result);
            solution.pop_back();
            sum -= candidates[i];
            // remove duplicates
            while (i<candidates.size()-1 && candidates[i] == candidates[i+1]) i++;
        }
    }
};


int main(void) {

    Solution solution;
    int A[] = {10,1,-2,7,-6,1,5,1};
    //int A[] = {1,1};
    vector<int> input(A, A+sizeof(A)/sizeof(A[0]));

    vector<vector<int> > result = solution.combinationSum2(input, 8);

    for (int i = 0; i < result.size(); i++) {
        cout << "[ ";
        vector<int> res = result[i];
        for (int j = 0; j < res.size(); j++) {
            cout << res[j] << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
