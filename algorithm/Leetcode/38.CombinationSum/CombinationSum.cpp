// Given a set of candidate numbers (C) and a target number (T), find all
// unique combinations in C where the candidate numbers sums to T.

// The same repeated number may be chosen from C unlimited number of times.

// Note:
// All numbers (including target) will be positive integers.
// Elements in a combination (a1, a2, ... , ak) must be in non-descending order.
// The solution set must not contain duplicate combinations.

// For example, given candidate set 2,3,6,7 and target 7,
// A solution set is:
//    [7]
//    [2, 2, 3]

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {

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

        // get rid of duplicates for input like {1,1,2,3}
        while (index != 0 && candidates[index] == candidates[index-1]) index++;
        path.push_back(candidates[index]);
        combinationSumHelper(candidates, target - candidates[index], index,
                             path, result);
        path.pop_back();
        combinationSumHelper(candidates, target, index+1, path, result);
    }


    vector<vector<int> > combinationSumWeb(vector<int> &candidates, int target) {

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
            GetCombinations(candidates, sum, i, target, solution, result);
            solution.pop_back();
            sum -= candidates[i];
            // remove duplicates
            while (i<candidates.size()-1 && candidates[i] == candidates[i+1]) i++;
        }
    }
};


int main(void) {

    Solution solution;
    int A[] = {1,1,2,3,4,5,6,6};
    vector<int> input(A, A+sizeof(A)/sizeof(A[0]));

    vector<vector<int> > result = solution.combinationSumWeb(input, 7);

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
