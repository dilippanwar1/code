// Given a string S and a string T, count the number of distinct subsequences
// of T in S.

// A subsequence of a string is a new string which is formed from the original
// string by deleting some (can be none) of the characters without disturbing
// the relative positions of the remaining characters. (ie, "ACE" is a subsequence
// of "ABCDE" while "AEC" is not).

// Here is an example:
//    S = "rabbbit", T = "rabbit"
//    Return 3.

#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    int numDistinct(string S, string T) {

        if (S.length() < T.length())
            return 0;

        // dp[i][j] means for T[0...i], and S[0...j]
        int m = T.length(), n = S.length();
        int dp[m+1][n+1];
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = 0;
                if (i == 0)  // for empty string T, there is one match
                    dp[0][j] = 1;
            }
        }

        // current dp[i][j] based on dp[i][j-1] (one less character of S) and
        // depending on T[i-1] and S[j-1], we need to consider the case where
        // we can use dp[i-1][j-1]
        for (int i = 1; i <= m; i++) {
            for (int j = i; j <= n; j++) {
                dp[i][j] = dp[i][j-1] + (T[i-1] == S[j-1]) * dp[i-1][j-1];
            }
        }

        return dp[m][n];
    }


    // Let f(i, j) to be the number of distinct subsequences of T(j:) in S(i:).
    // Consider the ith character in S. If we can use it to match T[j],
    // namely S[i] == T[j], then f(i, j) = f(i+1, j+1). If we do not want use
    // it in our matching, then f(i, j) = f(i+1, j).
    // Thus,f(i, j) = f(i+1, j) + (S[i] == T[j]) * f(i+1, j+1).
    // It is very much the same as how we solve C(n, m) or the knapsack problem.
    int numDistinctBetter(string S, string T) {

        if (S.length() < T.length())
            return 0;

        vector<int> dp(T.size()+1);
        dp[T.size()] = 1;

        for (int i = S.size() - 1; i >= 0; i--) {
            for (int j = 0; j < T.size(); j++) {
                dp[j] += (S[i]==T[j]) * dp[j+1];
            }
        }

        return dp[0];
    }
};


int main(void) {

    Solution solution;
    cout << solution.numDistinct("rbbt", "rbt") << endl;
    cout << solution.numDistinct("eee", "eee") << endl;
    cout << solution.numDistinct("eee", "e") << endl;
    cout << solution.numDistinct("e", "c") << endl;

    cout << solution.numDistinctFaster("rbbt", "rbt") << endl;
    cout << solution.numDistinctFaster("eee", "eee") << endl;
    cout << solution.numDistinctFaster("eee", "e") << endl;
    cout << solution.numDistinctFaster("e", "c") << endl;

    return 0;
}
