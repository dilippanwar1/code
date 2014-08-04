// The n-queens puzzle is the problem of placing n queens on an n×n
// chessboard such that no two queens attack each other.

// Given an integer n, return all distinct solutions to the n-queens puzzle.

// Each solution contains a distinct board configuration of the n-queens'
// placement, where 'Q' and '.' both indicate a queen and an empty space
// respectively.

#include <vector>
#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {

        vector<vector<string> > result;
        int rows[n];

        if (n == 0)
            return result;

        solveNQueensHelper(0, rows, n, result);
        return result;
    }


    void solveNQueensHelper(int rowIndex, int rows[], int n,
                            vector<vector<string> > &result) {

        if (rowIndex == n) {
            parseBoard(rows, n, result);
            return;
        }

        for (int i = 0; i < n; i++) {
            rows[rowIndex] = i;
            if (validUntil(rows, rowIndex)) {
                solveNQueensHelper(rowIndex + 1, rows, n, result);
            }
        }
    }


    bool validUntil(int rows[], int rowIndex) {

        // we can check it in O(n), since for elements before row, there
        // is no duplicate (otherwise, it won't pass to here)
        for (int i = 0; i < rowIndex; i++) {
            int diff = abs(rows[i] - rows[rowIndex]);
            if (diff == 0 || diff == (rowIndex - i)) {
                return false;
            }
        }

        return true;
    }


    void parseBoard(int rows[], int n, vector<vector<string> > &result) {

        vector<string> current(n, string(n, '.'));

        for (int i = 0; i < n; i++) {
            current[i][rows[i]] = 'Q';
        }

        result.push_back(current);
    }
};


int main(void) {

    Solution solution;

    vector<vector<string> > result = solution.solveNQueens(5);

    for (int i = 0; i < result.size(); i++) {
        cout << "[ " << endl;
        vector<string> res = result[i];
        for (int j = 0; j < res.size(); j++) {
            cout << res[j] << endl;
        }
        cout << "]" << endl;
        cout << endl;
    }

    return 0;
}
