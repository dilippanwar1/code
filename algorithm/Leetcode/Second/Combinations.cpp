#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
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
};


int main(void) {

    Solution solution;
    vector<vector<int> > result = solution.combine(3, 2);

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
