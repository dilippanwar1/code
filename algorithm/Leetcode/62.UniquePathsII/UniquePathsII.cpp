// Follow up for "Unique Paths":

// Now consider if some obstacles are added to the grids. How many unique
// paths would there be?

// An obstacle and empty space is marked as 1 and 0 respectively in the grid.

// For example,
// There is one obstacle in the middle of a 3x3 grid as illustrated below.
// [
//   [0,0,0],
//   [0,1,0],
//   [0,0,0]
// ]
// The total number of unique paths is 2.

// Note: m and n will be at most 100.


#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {

        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        int numOfWays[m][n];

        // empty grid
        if (m == 0 || n == 0)
            return -1;

        // init number of ways to 0, and for two edges, init to 1
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i == m - 1 && j == n - 1) { // bottom right node
                    numOfWays[i][j] = (obstacleGrid[i][j] == 1) ? 0 : 1;
                } else if (j == n - 1) { // right line edge
                    numOfWays[i][j] = (obstacleGrid[i][j] == 1) ?
                        0 : numOfWays[i+1][j];
                } else if (i == m - 1) { // bottom line edge
                    numOfWays[i][j] = (obstacleGrid[i][j] == 1) ?
                        0 : numOfWays[i][j+1];
                } else {
                    numOfWays[i][j] = 0;
                }
            }
        }

        // dp computes # of unique path
        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                if (obstacleGrid[i][j] == 1) {
                    numOfWays[i][j] = 0;
                } else {
                    numOfWays[i][j] = numOfWays[i+1][j] + numOfWays[i][j+1];
                }
            }
        }

        return numOfWays[0][0];
    }
};


int main(void) {
    return 0;
}
