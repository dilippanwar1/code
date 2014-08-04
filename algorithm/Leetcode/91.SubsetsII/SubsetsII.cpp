// Given a collection of integers that might contain duplicates, S, return
// all possible subsets.

// Note:
// Elements in a subset must be in non-descending order.
// The solution set must not contain duplicate subsets.

// For example,
// If S = [1,2,2], a solution is:
// [
//   [2],
//   [1],
//   [1,2,2],
//   [2,2],
//   [1,2],
//   []
// ]

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    // execent solution from web
    vector<vector<int> > subsetsWithDup(vector<int> &S) {

        vector<int> path;
        vector<vector<int> > result;

        sort(S.begin(), S.end());
        sub(S, 0, path, result);
        return result;
    }

    void sub(vector<int> &s, int begin, vector<int> &path,
             vector<vector<int> > &result) {

        // path contains nodes currently choose to include
        result.push_back(path);

        for (int i = begin; i < s.size(); ++i) {

            if (i != begin && s[i] == s[i - 1])
                continue;

            path.push_back(s[i]);
            sub(s, i + 1, path, result);
            path.pop_back();
        }
    }


    vector<vector<int> > subsetsWithDup1(vector<int> &S) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return subsetsWithDupHelper(S, 0);
    }

    // error when duplicate at last
    vector<vector<int> > subsetsWithDupHelper(vector<int> &S, int start) {

        int n = S.size();
        vector<vector<int> > result;

        // Base case, when we reach end, return empty list. "[ [] ]"
        if (start == n-1) {
            vector<int> empty;
            result.push_back(empty);
            empty.push_back(S[start]);
            result.push_back(empty);
            return result;
        }

        int end = start+1;

        if (S[start] == S[end]) {
            end++;
        }

        result = subsetsWithDupHelper(S, end);

        if (start + 1 == end) {
            int j = result.size();
            while (j-- > 0) {
                result.push_back(result[j]);
                result.back().push_back(S[start]);
            }
        } else {
            int numOfDup = end - start;
            int k = result.size();
            while (numOfDup-- > 0) {
                int p = k;
                int j = result.size();
                while (p-- > 0) {
                    result.push_back(result[--j]);
                    result.back().push_back(S[start]);
                }
            }
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    int a[] = {1,1,2,2,3};
    vector<int> input(a, a+sizeof(a)/sizeof(a[0]));
    vector<vector<int> > result = solution.subsetsWithDup(input);

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
