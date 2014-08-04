// http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/

// Given a value N, if we want to make change for N cents, and we have infinite
// supply of each of S = { S1, S2, .. , Sm} valued coins, how many ways can we
// make the change? The order of coins doesn’t matter.

// For example, for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},
// {1,1,2},{2,2},{1,3}. So output should be 4. For N = 10 and S = {2, 5, 3, 6},
// there are five solutions: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}.
// So the output should be 5.

// 1) Optimal Substructure
//    To count total number solutions, we can divide all set solutions in two sets.
//    1) Solutions that do not contain mth coin (or Sm).
//    2) Solutions that contain at least one Sm.
//    Let count(S[], m, n) be the function to count the number of solutions, then
//    it can be written as sum of count(S[], m-1, n) and count(S[], m, n-Sm).
//    Therefore, the problem has optimal substructure property as the problem can be
//    solved using solutions to subproblems.
// 2) Overlapping Subproblems
//    Following is a simple recursive implementation of the Coin Change problem.
//    The implementation simply follows the recursive structure mentioned above.

#include <stdio.h>


// Returns the count of ways we can sum  S[0...m-1] coins to get sum n
int count1(int S[], int m, int n)
{
    // If n is 0 then there is 1 solution (do not include any coin)
    if (n == 0)
        return 1;

    // If n is less than 0 then no solution exists
    if (n < 0)
        return 0;

    // If there are no coins and n is greater than 0, then no solution exist
    if (m <=0 && n >= 1)
        return 0;

    // count is sum of solutions (i) including S[m-1] (ii) excluding S[m-1]
    return count1( S, m - 1, n ) + count1( S, m, n-S[m-1] );
}


int count2(int S[], int m, int n)
{
    int i, j, x, y;

    // We need n+1 rows as the table is consturcted in bottom up manner using
    // the base case 0 value case (n = 0)
    int table[n+1][m];

    // Fill the enteries for 0 value case (n = 0)
    for (i=0; i<m; i++)
        table[0][i] = 1;

    // Fill rest of the table enteries in bottom up manner
    for (i = 1; i < n+1; i++)
    {
        for (j = 0; j < m; j++)
        {
            // Count of solutions including S[j]
            x = (i-S[j] >= 0)? table[i - S[j]][j]: 0;

            // Count of solutions excluding S[j]
            y = (j >= 1)? table[i][j-1]: 0;

            // total count
            table[i][j] = x + y;
        }
    }
    return table[n][m-1];
}


class MySolution {
public:
    int count1(int arr[], int size, int n) {
        return count_helper(arr, size-1, n);
    }

    int count2(int arr[], int size, int n) {

        // table[i][j] means for coins range from 0..j-1, number of changes
        // for total amount of i
        int table[n+1][size];

        // for total amout of 0, we set to 1, since we have a chnage
        for (int i = 0; i < size; i++) {
            table[0][i] = 1;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < size; j++) {
                // use arr[j]
                int x = (i - arr[j]) >= 0 ? table[i-arr[j]][j] : 0;
                // do not use arr[j]
                int y = (j >= 1) ? table[i][j-1] : 0;
                // total
                table[i][j] = x + y;
            }
        }

        return table[n][size-1];
    }

private:
    int count_helper(int arr[], int i, int n) {

        if (n == 0)
            return 1;

        if (i < 0 || n < 0) {
            return 0;
        }

        // either choose current coin or not
        return count_helper(arr, i, n - arr[i]) + count_helper(arr, i-1, n);
    }
};


// Driver program to test above function
int main() {

    MySolution solution;
    int arr[] = {2, 3, 5, 6};
    int m = sizeof(arr)/sizeof(arr[0]);
    int n = 10;

    printf("%d\n", solution.count1(arr, m, n));
    printf("%d\n", solution.count2(arr, m, n));
    printf("%d\n", count1(arr, m, n));
    return 0;
}
