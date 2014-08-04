// Given numRows, generate the first numRows of Pascal's triangle.

// For example, given numRows = 5,
// Return
// [
//      [1],
//     [1,1],
//    [1,2,1],
//   [1,3,3,1],
//  [1,4,6,4,1]
// ]

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > result;

        if (numRows == 0)
            return result;
        vector<int> row1;
        row1.push_back(1);
        result.push_back(row1);

        for (int i = 1; i < numRows; i++) {
            vector<int> pre_row = result.back();
            vector<int> cur_row;
            for (int j = 0; j <= pre_row.size(); j++) {
                if (j == 0) {
                    cur_row.push_back(pre_row[0]);
                } else if (j == pre_row.size()) {
                    cur_row.push_back(pre_row[j-1]);
                } else {
                    cur_row.push_back(pre_row[j-1] + pre_row[j]);
                }
            }
            result.push_back(cur_row);
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    vector<vector<int> > result = solution.generate(5);

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
