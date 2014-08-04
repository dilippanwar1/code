#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(S.begin(), S.end(), greater<int>());
        return subsetsHelper(S, 0);
    }

    vector<vector<int> > subsetsHelper(vector<int> &S, int index) {

        vector<vector<int> > result;

        if (index == S.size()) {
            vector<int> path;
            result.push_back(path);
            return result;
        }

        result = subsetsHelper(S, index+1);
        int size = result.size();
        for (int i = 0; i < size; i++) {
            result.push_back(result[i]);
            result[i].push_back(S[index]);
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    int a[] = {1, 2, 3};
    vector<int> input(a, a+sizeof(a)/sizeof(a[0]));

    vector<vector<int> > result = solution.subsets(input);
    for (int i = 0; i < result.size(); i++) {
        cout << "[ ";
        vector<int> res = result[i];
        for (int j = 0; j < res.size(); j++) {
            cout << res[j] << " ";
        }
        cout << "]" << endl;
    }
}
