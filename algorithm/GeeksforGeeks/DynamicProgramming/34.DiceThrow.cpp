// http://www.geeksforgeeks.org/dice-throw-problem/

// Given n dice each with m faces, numbered from 1 to m, find the number of
// ways to get sum X. X is the summation of values on each face when all the
// dice are thrown.

With above conditions added, time complexity becomes O(1) when x >= m*n or when x <= n.

Exercise:
Extend the above algorithm to find the probability to get Sum > X.


#include <iostream>
using namespace std;


class MySolution {
public:
    // returns number of ways to get sum 'x' with 'n' dice and 'm' faces,
    // can be changed to memorization easily by using a two dimentional
    // array cache[n][x]
    int findWays(int m, int n, int x) {

        if (x == 0 && n == 0) {
            return 1;
        } else if (x < 0) {
            return 0;
        }
        int sum = 0;
        for (int i = 1; i <= m; i++) {
            sum += findWays(m, n-1, x-i);
        }

        return sum;
    }

    int findWaysDP(int m, int n, int x) {

        // When x is so high that sum can not go beyond x even when we
        // get maximum value in every dice throw.
        if (m * n <= x)
            return (m * n == x);

        // When x is too low
        if (n >= x)
            return (n == x);

        // sums[i][j] means for i dices, sum is j
        int sums[n+1][x+1];
        memset(sums, 0, sizeof(sums)); // must init to zero first

        // when sum is 0 and n != 0, we have no way
        for (int i = 1; i <= n; i++) {
            sums[i][0] = 0;
        }
        // when only one dice, we have one way for 0 to m (make sure x < m)
        for (int i = 1; i <= m && i <= x; i++) {
            sums[1][i] = 1;
        }

        for (int i = 2; i <= n; i++) { // start from 2 dices
            for (int j = 1; j <= x; j++) { // all sums
                for (int k = 1; k <= m; k++) {
                    if (j - k > 0) {
                        sums[i][j] += sums[i-1][j-k];
                    }
                }
            }
        }

        return sums[n][x];
    }
};

// Driver program to test above functions
int main()
{
    MySolution solution;

    cout << solution.findWays(4, 2, 1) << endl;
    cout << solution.findWays(2, 2, 3) << endl;
    cout << solution.findWays(6, 3, 8) << endl;
    cout << solution.findWays(4, 2, 5) << endl;
    cout << solution.findWays(4, 3, 5) << endl;

    cout << solution.findWaysDP(4, 2, 1) << endl;
    cout << solution.findWaysDP(2, 2, 3) << endl;
    cout << solution.findWaysDP(6, 3, 8) << endl;
    cout << solution.findWaysDP(4, 2, 5) << endl;
    cout << solution.findWaysDP(4, 3, 5) << endl;

    return 0;
}
