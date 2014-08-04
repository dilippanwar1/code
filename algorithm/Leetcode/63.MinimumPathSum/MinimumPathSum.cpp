// Given a m x n grid filled with non-negative numbers, find a path from top
// left to bottom right which minimizes the sum of all numbers along its path.

// Note: You can only move either down or right at any point in time.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int m = grid.size(), n = grid[0].size();
        int minPath[m][n];

        // empty grid
        if (m == 0 || n == 0)
            return -1;

        // init min path to max
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                minPath[i][j] = INT_MAX;
            }
        }

        // compute bottom right and two edges
        minPath[m-1][n-1] = grid[m-1][n-1];
        for (int i = m - 2; i >= 0; i--) {
            minPath[i][n-1] = minPath[i+1][n-1] + grid[i][n-1];
        }
        for (int j = n - 2; j >= 0; j--) {
            minPath[m-1][j] = minPath[m-1][j+1] + grid[m-1][j];
        }

        // dp computes min path
        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                minPath[i][j] = min(minPath[i+1][j], minPath[i][j+1]) +
                    grid[i][j];
            }
        }

        return minPath[0][0];
    }
};


int main(void) {
    return 0;
}
