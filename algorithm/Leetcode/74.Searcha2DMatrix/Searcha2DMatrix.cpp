// Write an efficient algorithm that searches for a value in an m x n matrix.
// This matrix has the following properties:

// Integers in each row are sorted from left to right.
// The first integer of each row is greater than the last integer of the
//    previous row.

// For example,
//    Consider the following matrix:
//    [
//      [1,   3,  5,  7],
//      [10, 11, 16, 20],
//      [23, 30, 34, 50]
//    ]
//    Given target = 3, return true.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    // O(log(m) + log(n)) running time
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        int numRow = matrix.size();
        int numCol = matrix[0].size();

        if (numRow == 0 || numCol == 0)
            return false;

        int row_l = 0, row_h = numRow - 1;
        while (row_l <= row_h) {
            int row_m = (row_l + row_h) / 2;
            if (target >= matrix[row_m][0] && target <= matrix[row_m][numCol-1])
                return binary_search(matrix[row_m].begin(), matrix[row_m].end(),
                                     target);
            else if (target < matrix[row_m][0])
                row_h = row_m - 1;
            else
                row_l = row_m + 1;
        }
    }

    // O(m + n) running time
    bool searchMatrixLinear(vector<vector<int> > &matrix, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int numRow = matrix.size();
        int numCol = matrix[0].size();
        bool discard = false;   // we chould discard all next rows

        if (numRow == 0 || numCol == 0)
            return false;

        int row = 0, col = numCol - 1;
        while (row < numRow && col >= 0) {
            if (target < matrix[row][col]) {
                discard = true;
                col--;
            } else if (target > matrix[row][col]) {
                if (discard == true)
                    return false;
                row++;
            } else {
                return true;
            }
        }

        return false;
    }
};


int main(void) {
    return 0;
}
