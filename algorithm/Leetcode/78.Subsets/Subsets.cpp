// Given a set of distinct integers, S, return all possible subsets.

// Note:
// Elements in a subset must be in non-descending order.
// The solution set must not contain duplicate subsets.

// For example,
// If S = [1,2,3], a solution is:
// [
//   [3],
//   [1],
//   [2],
//   [1,2,3],
//   [1,3],
//   [2,3],
//   [1,2],
//   []
// ]

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    // execent solution from web
    vector<vector<int> > subsets(vector<int> &S) {

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
            path.push_back(s[i]);
            sub(s, i + 1, path, result);
            path.pop_back();
        }
    }

    // elegent and faster
    vector<vector<int> > subsets1(vector<int> &S) {

        sort(S.begin(), S.end());
        vector<vector<int> > v(1);

        for (int i = 0; i < S.size(); ++i) {
            int j = v.size();
            while (j-- > 0) {
                v.push_back(v[j]);
                v.back().push_back(S[i]);
            }
        }
        return v;
    }

    // create subsets according to binary combination
    vector<vector<int> > subsets2(vector<int> &S) {

        vector<vector<int> > result;
        sort(S.begin(), S.end());
        for (int i = 0; i < (1<<S.size()); i++) {
            vector<int> tmp;
            for (int j = 0; j < S.size(); j++) {
                if ((i & (1 << j)) != 0) {
                    tmp.push_back(S[j]);
                }
            }
            result.push_back(tmp);
        }

        return result;
    }

    vector<vector<int> > subsets3(vector<int> &S) {
        sort(S.begin(), S.end());
        return subsets3Helper(S);
    }

    vector<vector<int> > subsets3Helper(vector<int> &S) {

        if (S.size() == 0) {
            vector<vector<int> > result(1);
            vector<int> empty;
            result[0] = empty;
            return result;
        }

        vector<vector<int> > result;
        int t = S.back(); S.pop_back();
        result = subsets3Helper(S);
        int n = result.size();
        for (int i = 0; i < n; i++) {
            result.push_back(result[i]);
            result[i].push_back(t);
        }
        S.push_back(t);

        return result;
    }
};


int main(void) {

    Solution solution;
    int a[] = {1,2,3};
    vector<int> input(a, a+sizeof(a)/sizeof(a[0]));
    vector<vector<int> > result = solution.subsets3(input);

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
