// A robot is located at the top-left corner of a m x n grid (marked 'Start'
// in the diagram below).

// The robot can only move either down or right at any point in time. The robot
// is trying to reach the bottom-right corner of the grid (marked 'Finish' in
// the diagram below).

// How many possible unique paths are there?

// Note: m and n will be at most 100.

#include <iostream>
using namespace std;


class Solution {
public:
    // Use only O(min(m,n)), from web
    int uniquePaths(int m, int n) {

        int x = min(m, n);
        int y = max(m, n);
        int ret[x];

        for(int i = 0; i < x; i++)
            ret[i] = 1;

        for (int i = 1; i < y; i++)
            for (int j = 1; j < x; j++)
                ret[j] += ret[j - 1];

        return ret[x - 1];
    }

    // Use only O(m+n) memory
    int uniquePaths2(int m, int n) {

        int rows[n];
        int cols[m];

        // empty grid
        if (m == 0 || n == 0)
            return -1;

        // init number of ways to 1 at two edges
        for (int i = 0; i < n; i++) {
            rows[i] = 1;
        }
        for (int i = 0; i < m; i++) {
            cols[i] = 1;
        }

        // dp computes # of unique path
        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                int current = cols[i] + rows[j];
                cols[i] = rows[j] = current;
            }
        }

        return cols[0];
    }

    // Use O(m*n) memory
    int uniquePaths3(int m, int n) {

        int numOfWays[m][n];

        // empty grid
        if (m == 0 || n == 0)
            return -1;

        // init number of ways to 0, and for two edges, init to 1
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == m - 1) {
                    numOfWays[i][j] = 1;
                } else if (j == n - 1) {
                    numOfWays[i][j] = 1;
                } else {
                    numOfWays[i][j] = 0;
                }
            }
        }

        // dp computes # of unique path
        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                numOfWays[i][j] = numOfWays[i+1][j] + numOfWays[i][j+1];
            }
        }

        return numOfWays[0][0];
    }
};


int main(void) {

    Solution solution;

    cout << solution.uniquePaths(10,3) << endl;
    cout << solution.uniquePaths2(10,3) << endl;
    cout << solution.uniquePaths3(10,3) << endl;
    return 0;
}
