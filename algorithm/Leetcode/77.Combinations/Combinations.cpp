// Given two integers n and k, return all possible combinations of k numbers
// out of 1 ... n.

// For example,
// If n = 4 and k = 2, a solution is:
// [
//   [2,4],
//   [3,4],
//   [2,3],
//   [1,2],
//   [1,3],
//   [1,4],
// ]

#include <stack>
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<int> > combine(int n, int k) {

        vector<vector<int> > result;
        vector<int> path;

        combineHelper(n, k, 1, path, result);
        return result;
    }

    void combineHelper(int n, int k, int index, vector<int> &path,
                       vector<vector<int> > &result) {

        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        if (k > n) {
            return;
        }

        for (int i = index; i <= n; i++) {
            path.push_back(i);
            combineHelper(n, k, i + 1, path, result);
            path.pop_back();
        }
    }


    vector<vector<int> > combine1(int n, int k) {

        // Corner cases
        if (n <= 0 || k <= 0 || n < k) {
            vector<vector<int> > result;
            return result;
        }

        return combineHelper1(n, k);
    }

    vector<vector<int> > combineHelper1(int n, int k) {

        vector<vector<int> > result;

        if (n < k)
            return result;

        // if we only choose one element, then result should be [[1], [2] ...]
        if (k == 1) {
            for (int i = 1; i <= n; i++) {
                vector<int> tmp;
                tmp.push_back(i);
                result.push_back(tmp);
            }
        } else {               // we choose from last, i.e. i = n to 1
            for (int i = n; i > 0; i--) {
                vector<vector<int> > tmp = combineHelper1(i - 1, k - 1);
                for (int j = 0; j < tmp.size(); j++) {
                    tmp[j].push_back(i);
                    result.push_back(tmp[j]);
                }
            }
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    vector<vector<int> > result = solution.combine(10, 3);

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
