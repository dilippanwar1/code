// Given an index k, return the kth row of the Pascal's triangle.

// For example, given k = 3,
// Return [1,3,3,1].

// Note:
// Could you optimize your algorithm to use only O(k) extra space?

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    vector<int> getRow(int rowIndex) {

        // number of elements in "rowIndex" is the same as "rowIndex"
        vector<int> result(rowIndex+1, 1);

        int left, right;        // left shoulder and right shoulder
        for (int i = 1; i <= rowIndex; i++) {
            left = 1;
            for (int j = 1; j < i; j++) {
                right = result[j];
                result[j] = left + right;
                left = right;
            }
        }

        return result;
    }

    vector<int> getRow2(int rowIndex) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> row1;
        vector<vector<int> > result;

        if (rowIndex < 0)
            return row1;

        row1.push_back(1);
        result.push_back(row1);
        if (rowIndex == 0)
            return row1;

        for (int i = 1; i <= rowIndex; i++) {
            vector<int> pre_row = result.back();
            result.pop_back();
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

        return result[0];
    }
};


int main(void) {

    Solution solution;
    vector<int> result = solution.getRow(1);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
