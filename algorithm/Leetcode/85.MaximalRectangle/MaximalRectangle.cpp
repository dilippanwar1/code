// Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
// containing all ones and return its area.

#include <stack>
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    // First, setup a table to maintain the length of continuous 1's in a column.
    // i.e. table[i][j] = k means that matrix[i ... i+k-1][j] are all 1's. Use
    // the O(n) algorithm for "Largest Rectangle in Histogram" as a subroutine
    // and run on each row.
    // E.g. for array
    //    0 0 1 0  =>  0 0 1 0
    //    1 1 0 1  =>  3 1 0 3
    //    1 0 1 1  =>  2 0 2 2
    //    1 0 1 1  =>  1 0 1 1
    int maximalRectangle(vector<vector<char> > &matrix) {

        if (matrix.empty())
            return 0;

        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<vector<int> > C(rows, vector<int>(cols, 0));
        int max_val = 0;

        for (int j = 0; j < cols; j++) {
            for (int i = rows-1; i >= 0; i--) {
                if (i == rows-1) {
                    C[i][j] = matrix[i][j] - '0';
                } else {
                    C[i][j] = (matrix[i][j]-'0') ? (C[i+1][j]+1) : 0;
                }
            }
        }

        for (int i = 0; i < rows; i++) {
            max_val = max(max_val, largestRectangleArea(C[i]));
        }

        return max_val;
    }

    int largestRectangleArea(vector<int> &height) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<int> s;
        int i = 0, t, m = 0;
        vector<int> h = height;
        h.push_back(0);

        while (i < h.size()) {
            if (s.empty() || h[i] >= h[s.top()]) {
                s.push(i++);
            }
            else {
                t = s.top();
                s.pop();
                m = max(m, h[t] * (s.empty() ? i : (i-s.top()-1)));
            }
        }

        return m;
    }

    int maximalRectangle2(vector<vector<char> > &matrix) {

        if (matrix.empty()) {
            return 0;
        }

        int n = matrix[0].size();
        vector<int> H(n);
        vector<int> L(n);
        vector<int> R(n, n);

        int ret = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            int left = 0, right = n;
            // calculate L(i, j) from left to right
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    ++H[j];
                    L[j] = max(L[j], left);
                } else {
                    left = j+1;
                    H[j] = 0; L[j] = 0; R[j] = n;
                }
            }
            // calculate R(i, j) from right to right
            for (int j = n-1; j >= 0; --j) {
                if (matrix[i][j] == '1') {
                    R[j] = min(R[j], right);
                    ret = max(ret, H[j]*(R[j]-L[j]));
                } else {
                    right = j;
                }
            }
        }

        return ret;
    }
};


int main(void) {

    Solution solution;
    vector<vector<char> > matrix(4, vector<char>(4, 0));
    int a[][4] = {{0,0,1,0}, {1,1,0,1}, {1,0,1,1}, {1,0,1,1}};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = a[i][j] + '0';
        }
    }

    cout << solution.maximalRectangle(matrix) << endl;
    return 0;
}
