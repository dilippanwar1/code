// http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/

// Given a cost matrix cost[][] and a position (m, n) in cost[][], write a
// function that returns cost of minimum cost path to reach (m, n) from (0, 0).
// Each cell of the matrix represents a cost to traverse through that cell.
// Total cost of a path to reach (m, n) is sum of all the costs on that path
// (including both source and destination). You can only traverse down, right
// and diagonally lower cells from a given cell, i.e., from a given cell (i, j),
// cells (i+1, j), (i, j+1) and (i+1, j+1) can be traversed. You may assume that
// all costs are positive integers.


#include <stdio.h>
#include <limits.h>
#define R 3
#define C 3


class MySolution {
public:
    // Returns cost of minimum cost path from (0,0) to (m, n) in cost[R][C]
    // Naive recursive solution
    int minCost1(int cost[R][C], int m, int n) {

        if (m < 0 || n < 0) {
            return INT_MAX;
        } else if (m == 0 && n == 0) {
            return cost[m][n];
        } else {
            return cost[m][n] + min(minCost1(cost, m-1, n),
                                    minCost1(cost, m, n-1),
                                    minCost1(cost, m-1, n-1));
        }
    }

    // Dynamic programming solution
    int minCost2(int cost[R][C], int m, int n) {

        int L[R][C];

        // initialize first row and first column
        L[0][0] = cost[0][0];
        for (int i = 1; i < R; i++) {
            L[i][0] = L[i-1][0] + cost[i][0];
        }
        for (int j = 1; j < C; j++) {
            L[0][j] = L[0][j-1] + cost[0][j];
        }

        for (int i = 1; i < R; i++) {
            for (int j = 1; j < C; j++) {
                // minimal of three directions
                L[i][j] = cost[i][j] + min(L[i-1][j], L[i][j-1], L[i-1][j-1]);
            }
        }

        return L[m][n];
    }

private:
    // Return minimum of 3 integers
    int min(int x, int y, int z) {
        if (x < y) {
            return (x < z)? x : z;
        } else {
            return (y < z)? y : z;
        }
    }
};



/* Driver program to test above functions */
int main() {

    MySolution solution;
    int cost[R][C] = { {1, 2, 3},
                       {4, 8, 2},
                       {1, 5, 3} };
    printf("Min cost %d\n", solution.minCost2(cost, 2, 2));
    return 0;
}
