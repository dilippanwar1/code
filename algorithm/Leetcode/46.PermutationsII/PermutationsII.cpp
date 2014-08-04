// Given a collection of numbers that might contain duplicates, return all
// possible unique permutations.

// For example,
//    [1,1,2] have the following unique permutations:
//    [1,1,2], [1,2,1], and [2,1,1].

#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;


class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {

        vector<int> current(num.size(), 0);
        vector<bool> used(num.size(), false);
        vector<vector<int> > result;

        permuteHelper(num, used, current, 0, result);

        return result;
    }

    void permuteHelper(vector<int> &num, vector<bool> &used, vector<int> &current,
                       int index, vector<vector<int> > &result) {

        unordered_set<int> visited;

        if (index == num.size()) {
            result.push_back(current);
            return;
        }

        for (int i = 0; i < num.size(); i++) {
            if (used[i] == false && visited.count(num[i]) == 0) {
                visited.insert(num[i]);
                used[i] = true;
                current[index] = num[i];
                permuteHelper(num, used, current, index+1, result);
                used[i] = false;
            }
        }
    }
};


int main(void) {

    Solution solution;
    int A[] = {1, 1, 2, 2, 3};
    vector<int> input(A, A+sizeof(A)/sizeof(A[0]));

    vector<vector<int> > result = solution.permute(input);
    for (int i = 0; i < result.size(); i++) {
        cout << "[ ";
        vector<int> res = result[i];
        for (int j = 0; j < res.size(); j++) {
            cout << res[j] << " ";
        }
        cout << "]" << endl;
    }
}
