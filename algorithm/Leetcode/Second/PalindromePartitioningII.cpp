#include <iostream>
using namespace std;


class Solution {
public:
    int minCut(string s) {

        if (s.length() == 0)
            return 0;

        int len = s.length();
        int dp[len + 1];
        bool isPalin[len][len];

        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++)
                isPalin[i][j] = false;
        for (int i = 0; i < len; i++)
            isPalin[i][i] = true;
        for (int cl = 2; cl <= len; cl++) {
            for (int i = 0; i < len - cl + 1; i++) {
                int j = i + cl - 1;
                if (cl == 2) {
                    isPalin[i][j] = (s[i] == s[j]) ? true : false;
                } else {
                    isPalin[i][j] = (s[i] == s[j]) ? isPalin[i+1][j-1] : false;
                }
            }
        }

        for (int i = 0; i <= len; i++)
            dp[i] = len - i - 1;

        for (int i = len - 1; i >= 0; i--) {
            for (int j = i; j < len; j++) {
                if (isPalin[i][j]) {
                    dp[i] = min(dp[i], dp[j+1] + 1);
                }
            }
        }

        return dp[0];
    }
};


int main(void) {

    Solution solution;
    cout << solution.minCut("cabababcbc") << endl;
}
