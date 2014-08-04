// http://www.geeksforgeeks.org/dynamic-programming-set-31-optimal-strategy-for-a-game/

// Problem statement: Consider a row of n coins of values v1 . . . vn, where n
// is even. We play a game against an opponent by alternating turns. In each
// turn, a player selects either the first or last coin from the row, removes
// it from the row permanently, and receives the value of the coin. Determine
// the maximum possible amount of money we can definitely win if we move first.
// Note: The opponent is as clever as the user.

// Let us understand the problem with few examples:
//     (1). 5, 3, 7, 10 : The user collects maximum value as 15 (10 + 5)
//     (2). 8, 15, 3, 7 : The user collects maximum value as 22 (7 + 15)
// Does choosing the best at each move give an optimal solution?
// No. In the second example, this is how the game can finish:
// 1.
// ......User chooses 8.
// ......Opponent chooses 15.
// ......User chooses 7.
// ......Opponent chooses 3.
// Total value collected by user is 15 (8 + 7)

// 2.
// ......User chooses 7.
// ......Opponent chooses 8.
// ......User chooses 15.
// ......Opponent chooses 3.
// Total value collected by user is 22 (7 + 15)

// So if the user follows the second game state, maximum value can be collected
// although the first move is not the best.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <iostream>
using namespace std;


// Utility functions to get maximum and minimum of two intgers
int max(int a, int b)  {    return a > b ? a : b;  }
int min(int a, int b)  {    return a < b ? a : b;  }

// Returns optimal value possible that a player can collect from
// an array of coins of size n. Note than n must be even
int optimalStrategyOfGame(int* arr, int n)
{
    // Create a table to store solutions of subproblems
    int table[n][n], gap, i, j, x, y, z;

    // Fill table using above recursive formula. Note that the table
    // is filled in diagonal fashion (similar to http://goo.gl/PQqoS),
    // from diagonal elements to table[0][n-1] which is the result.
    for (gap = 0; gap < n; ++gap)
    {
        for (i = 0, j = gap; j < n; ++i, ++j)
        {
            // Here x is value of F(i+2, j), y is F(i+1, j-1) and
            // z is F(i, j-2) in above recursive formula
            x = ((i+2) <= j) ? table[i+2][j] : 0;
            y = ((i+1) <= (j-1)) ? table[i+1][j-1] : 0;
            z = (i <= (j-2))? table[i][j-2]: 0;

            table[i][j] = max(arr[i] + min(x, y), arr[j] + min(y, z));
        }
    }

    return table[0][n-1];
}


class MySolution {
public:
    int optimalStrategyOfGame(int arr[], int n) {
        return optimalStrategyOfGameHelper(arr, 0, n-1);
    }

    int optimalStrategyOfGameDP(int arr[], int n) {

        // table[i][j] means coins [i...j]
        int table[n][n];
        // we need to set table to all zero, so that in the double for loop
        // we don't need to check if table[i+2][j] or table[i][j-1] is valid.
        memset(table, 0, sizeof(table));

        // when only one coin, choose it
        for (int i = 0; i < n; i++) {
            table[i][i] = arr[i];
        }
        // when two coins, choose bigger one
        for (int i = 0; i < n - 1; i++) {
            table[i][i+1] = max(arr[i], arr[i+1]);
        }

        for (int num = 2; num <= n; num++) {
            for (int i = 0; i < n - num + 1; i++) {
                int j = i + num - 1;
                int opt1 = arr[i] + min(table[i+2][j], table[i+1][j-1]);
                int opt2 = arr[j] + min(table[i][j-2], table[i+1][j-1]);
                table[i][j] = max(opt1, opt2);
            }
        }

        return table[0][n-1];
    }
private:
    int optimalStrategyOfGameHelper(int arr[], int left, int right) {

        if (left == right) {
            return arr[left];   // only one coin, choose it
        } else if (left + 1 == right) {
            return max(arr[left], arr[right]); // two coins, choose bigger one
        }

        // choose first coin
        int opt1 = arr[left] + min( // min according to how our opponent choose
            optimalStrategyOfGameHelper(arr, left+2, right),
            optimalStrategyOfGameHelper(arr, left+1, right-1));
        // choose last coin
        int opt2 = arr[right] + min(
            optimalStrategyOfGameHelper(arr, left, right-2),
            optimalStrategyOfGameHelper(arr, left+1, right-1));

        return max(opt1, opt2);
    }

    int max(int a, int b) {
        return a > b ? a : b;
    }

    int min(int a, int b) {
        return a < b ? a : b;
    }
};


// Driver program to test above function
int main()
{
    MySolution solution;

    int arr1[] = {8, 15, 3, 7};
    int n = sizeof(arr1)/sizeof(arr1[0]);
    printf("%d\n", solution.optimalStrategyOfGame(arr1, n)); // 22
    printf("%d\n", solution.optimalStrategyOfGameDP(arr1, n));

    int arr2[] = {2, 2, 2, 2};
    n = sizeof(arr2)/sizeof(arr2[0]);
    printf("%d\n", solution.optimalStrategyOfGame(arr2, n)); // 4
    printf("%d\n", solution.optimalStrategyOfGameDP(arr2, n));

    int arr3[] = {20, 30, 2, 2, 2, 10};
    n = sizeof(arr3)/sizeof(arr3[0]);
    printf("%d\n", solution.optimalStrategyOfGame(arr3, n)); // 42
    printf("%d\n", solution.optimalStrategyOfGameDP(arr3, n));

    return 0;
}
