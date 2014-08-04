#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    int numDecodings(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = s.length();
        int dp[n+1];

        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (s[i-1] == '0') {
                if (s[i-2] != '1' && s[i-2] != '2') {
                    dp[i] = 0;
                } else {
                    dp[i] = dp[i-2];
                }
            } else if (s[i-1] > '6') {
                if (s[i-2] == '1') {
                    dp[i] = dp[i-1] + dp[i-2];
                } else {
                    dp[i] = dp[i-1];
                }
            } else {
                if (s[i-2] == '1' || s[i-2] == '2') {
                    dp[i] = dp[i-1] + dp[i-2];
                } else {
                    dp[i] = dp[i-1];
                }
            }
        }

        return dp[n];
    }
};


int main(void) {

    Solution solution;

    cout << solution.numDecodings("12362") << endl;

    return 0;
}
