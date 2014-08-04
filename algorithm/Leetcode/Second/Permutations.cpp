#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> current(num.size(), 0);
        vector<bool> used(num.size(), false);
        vector<vector<int> > result;

        permuteHelper(num, used, current, 0, result);

        return result;
    }

    void permuteHelper(vector<int> &num, vector<bool> &used, vector<int> &current,
                       int index, vector<vector<int> > &result) {

        if (index == num.size()) {
            result.push_back(current);
            return;
        }

        for (int i = 0; i < num.size(); i++) {
            if (used[i] == false) {
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
    int a[] = {1, 2, 3};
    vector<int> input(a, a+sizeof(a)/sizeof(a[0]));

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
