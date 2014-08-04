// http://www.geeksforgeeks.org/dynamic-programming-set-10-0-1-knapsack-problem/

// Given weights and values of n items, put these items in a knapsack of capacity
// W to get the maximum total value in the knapsack. In other words, given two
// integer arrays val[0..n-1] and wt[0..n-1] which represent values and weights
// associated with n items respectively. Also given an integer W which represents
// knapsack capacity, find out the maximum value subset of val[] such that sum of
// the weights of this subset is smaller than or equal to W. You cannot break an
// item, either pick the complete item, or don’t pick it (0-1 property).

#include <stdio.h>
#include <limits.h>
using namespace std;


// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
   // Base Case
   if (n == 0 || W == 0)
       return 0;

   // If weight of the nth item is more than Knapsack capacity W, then
   // this item cannot be included in the optimal solution
   if (wt[n-1] > W)
       return knapSack(W, wt, val, n-1);

   // Return the maximum of two cases: (1) nth item included (2) not included
   else return max( val[n-1] + knapSack(W-wt[n-1], wt, val, n-1),
                    knapSack(W, wt, val, n-1)
                  );
}


class MySolution {
public:
    // Returns the maximum value that can be put in a knapsack of capacity W
    int knapSack(int W, int wt[], int val[], int n) {

        if (W < 0 || n < 0)
            return 0;

        // **** if current item's weight is bigger than W, we can't choose it
        // Note that this is important for correctness. Even though knapSack()
        // will return 0 when W < 0, we have add val[n-1] to the return value.
        if (wt[n-1] > W)
            return knapSack(W, wt, val, n-1);

        // for item [n-1], we have two choices: choose it or not
        return max(knapSack(W-wt[n-1], wt, val, n-1) + val[n-1],
                   knapSack(W, wt, val, n-1));
    }

    int knapSackDP(int W, int wt[], int val[], int n) {

        // table[i][j] means use first i items, and total weight allowed is j
        int table[n+1][W+1];

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= W; j++) {
                if (i == 0 || j == 0) {
                    // base case, if there is no item, or weight is 0, there
                    // is no value at all
                    table[i][j] = 0;
                } else if (wt[i] <= j) {
                    // two cases; first we use current item, and value from
                    // i-1 items and weight is j-wt[i-1]; second we do not
                    // use current item; set to the max
                    table[i][j] = max(val[i-1] + table[i-1][j-wt[i-1]],
                                      table[i-1][j]);
                } else {
                    // no choice, current value is the same as weight j-1
                    table[i][j] = table[i][j-1];
                }
            }
        }

        return table[n][W];
    }

private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
};


// Driver program to test above function
int main() {

    MySolution solution;
    int val[] = {60, 100, 120, 80, 90, 10, 90, 100};
    int wt[]  = {10, 20,  30,  10, 35, 15, 20, 10};
    int W = 200;
    int n = sizeof(val)/sizeof(val[0]);

    printf("%d\n", knapSack(W, wt, val, n));
    printf("%d\n", solution.knapSack(W, wt, val, n));
    printf("%d\n", solution.knapSackDP(W, wt, val, n));
    return 0;
}
