// You are climbing a stair case. It takes n steps to reach to the top.

// Each time you can either climb 1 or 2 steps. In how many distinct ways
// can you climb to the top?

#include <iostream>
using namespace std;


class Solution {
public:
    int climbStairs(int n) {
        if (n < 0)
            return 0;
        if (n == 0 || n == 1)
            return 1;

        int dp[n+1];
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }

        return dp[n];
    }


    int climbStairsSlow(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n < 0)
            return 0;
        if (n == 0 || n == 1)
            return 1;

        return climbStairsSlow(n-1) + climbStairsSlow(n-2);
    }
};


int main(void) {

    Solution solution;
    cout << solution.climbStairs(5) << endl;
    cout << solution.climbStairsSlow(5) << endl;
    return 0;
}
