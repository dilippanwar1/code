// Given a collection of numbers, return all possible permutations.

// For example,
//    [1,2,3] have the following permutations:
//    [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].

// not working
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    vector<vector<int> > permute(vector<int> &num) {

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


    vector<vector<int> > permute1(vector<int> &num) {

        if (num.size() == 0) {
            vector<vector<int> > result;
            return result;
        }

        return permuteHelper1(num, 0);
    }

    vector<vector<int> > permuteHelper1(vector<int> &num, int start) {

        vector<vector<int> > result;
        if (start == num.size() - 1) {
            vector<int> res;
            res.push_back(num[start]);
            result.push_back(res);
            return result;
        }

        result = permuteHelper1(num, start+1);

        vector<vector<int> > ret;
        for (int i = 0; i < result.size(); i++) {
            vector<int> res = result[i];

            vector<int>::iterator it = result[i].begin();
            for (int j = 0; j < result[i].size(); j++) {
                result[i].insert(it+j, num[start]);
            }

        }

        return result;
    }

    vector<vector<int> > permute2(vector<int> &num) {

        int size = 1;
        for (int i = 2; i <= num.size(); i++)
            size *= i;

        // total # of elements in result set is n!
        vector<vector<int> > result(size, vector<int>(num.size()));
        if (num.size() == 0)
            return result;

        int offset = 0;
        for (int i = 0; i < num.size(); i++) { // compute each position
            for (int j = 0; j < size; j++) {   // set each element
                if (j != 0 && j % num.size() == 0)
                    offset++;
                int k = (i+offset) % num.size();
                result[j][i] = num[k];
            }
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    int a[] = {1,2};
    vector<int> num(a, a+sizeof(a)/sizeof(a[0]));
    vector<vector<int> > result = solution.permute(num);

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
