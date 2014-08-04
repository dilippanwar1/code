// Given a m x n matrix, if an element is 0, set its entire row and column
// to 0. Do it in place.

// Follow up:
// Did you use extra space?
// A straight forward solution using O(mn) space is probably a bad idea.
// A simple improvement uses O(m + n) space, but still not the best solution.
// Could you devise a constant space solution?

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    // O(1) space
    void setZeroes(vector<vector<int> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int numRow = matrix.size();
        int numCol = matrix[0].size();
        if (numRow == 0 || numCol == 0)
            return;

        // compute whether first row & col has zero
        bool firstRowHasZero = false, firstColHasZero = false;
        for (int i = 0; i < numCol; i++) {
            if (matrix[0][i] == 0) {
                firstRowHasZero = true;
                break;
            }
        }
        for (int i = 0; i < numRow; i++) {
            if (matrix[i][0] == 0) {
                firstColHasZero = true;
                break;
            }
        }

        // use first row & col to store information, then set to 0
        for (int i = 1; i < numRow; i++) {
            for (int j = 1; j < numCol; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < numRow; i++) { // i,j must start from 1 here
            for (int j = 1; j < numCol; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // handle first row & col
        if (firstRowHasZero) {
            for (int i = 0; i < numCol; i++) {
                matrix[0][i] = 0;
            }
        }
        if (firstColHasZero) {
            for (int i = 0; i < numRow; i++) {
                matrix[i][0] = 0;
            }
        }
    }

    // O(m + n) space
    void setZeroesLinear(vector<vector<int> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int numRow = matrix.size();
        int numCol = matrix[0].size();
        bool rows[numRow], cols[numCol];

        if (numRow == 0 || numCol == 0)
            return;

        for (int i = 0; i < numRow; i++)
            rows[i] = false;
        for (int i = 0; i < numCol; i++)
            cols[i] = false;

        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < numCol; j++) {
                if (matrix[i][j] == 0) {
                    rows[i] = true;
                    cols[j] = true;
                }
            }
        }

        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < numCol; j++) {
                if (rows[i] == true || cols[j] == true) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};


int main(void) {

}
