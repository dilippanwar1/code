// A message containing letters from A-Z is being encoded to numbers using
// the following mapping:

// 'A' -> 1
// 'B' -> 2
// ...
// 'Z' -> 26

// Given an encoded message containing digits, determine the total number of
// ways to decode it.

// For example,
//    Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
//    The number of ways decoding "12" is 2.

#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    int numDecodings(string s) {

        // three base cases
        if (s.length() == 0)
            return 0;
        if (s[0] == '0')        // string cannot start with '0'
            return 0;
        if (s.length() == 1)
            return 1;

        int n = s.length();
        int dp[n+1];

        dp[0] = 1;
        dp[1] = 1;
        // *** be carefull to handle '0' case ***
        for (int i = 2; i <= n; i++) {
            if (s[i-1] == '0') { // current character is '0'
                // only "10" and "20" is valid
                dp[i] = (s[i-2] == '1' || s[i-2] == '2') ? dp[i-2] : 0;
            } else {
                dp[i] = dp[i-1];
                if (s[i-2] == '1' || s[i-2] == '2' && s[i-1] <= '6')
                    dp[i] += dp[i-2];
            }
        }

        return dp[n];
    }

    // slow recursive version
    int numDecodingsSlow(string s) {
        if (s.length() == 0)
            return 0;
        return numDecodingsHelper(s);
    }

    int numDecodingsHelper(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s.length() == 0)    // we have reached end
            return 1;
        if (s[0] == '0')        // ignore string start with '0'
            return 0;
        if (s.length() == 1)
            return 1;

        int ways = numDecodingsHelper(s.substr(1));
        if (s[0] == '1' || (s[0] == '2' && s[1] <= '6'))
            ways += numDecodingsHelper(s.substr(2));

        return ways;
    }
};


int main(void) {

    Solution solution;

    cout << solution.numDecodings("12362") << endl;
    cout << solution.numDecodingsSlow("12362") << endl;

    return 0;
}
