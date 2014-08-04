#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
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
};


int main(void) {

    Solution solution;
    int a[] = {2, 2};
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
}
