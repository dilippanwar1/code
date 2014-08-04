// Given two words word1 and word2, find the minimum number of steps required
// to convert word1 to word2. (each operation is counted as 1 step.)

// You have the following 3 operations permitted on a word:
//    a) Insert a character
//    b) Delete a character
//    c) Replace a character

#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    int minDistance(string word1, string word2) {

        int n1 = word1.length(), n2 = word2.length();
        if (n1 == 0)
            return n2;
        if (n2 == 0)
            return n1;

        int dp[n1+1][n2+1];
        for (int i = 0; i <= n1; i++) {
            for (int j = 0; j <= n2; j++) {
                if (i == 0) {
                    dp[i][j] = j;
                } else if (j == 0) {
                    dp[i][j] = i;
                } else {
                    dp[i][j] = 0;
                }
            }
        }

        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
                }
            }
        }

        return dp[n1][n2];
    }


    int minDistanceSlow(string word1, string word2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (word1.length() == 0)
            return word2.length();
        if (word2.length() == 0)
            return word1.length();

        return minDistanceHelper(word1, word2, word1.length()-1, word2.length()-1);
    }

    int minDistanceHelper(string word1, string word2, int p1, int p2) {

        if (p1 == -1 && p2 == -1)
            return 0;
        if (p1 == -1) // if p1 reaches empty string, return word2's length
            return p2 + 1;      // remember to add 1
        if (p2 == -1) // if p2 reaches empty string, return word1's length
            return p1 + 1;

        if (word1[p1] == word2[p2]) {
            return minDistanceHelper(word1, word2, p1-1, p2-1);
        } else {
            // minimal of three edits
            return min(min(minDistanceHelper(word1, word2, p1-1, p2-1),
                           minDistanceHelper(word1, word2, p1, p2-1)),
                       minDistanceHelper(word1, word2, p1-1, p2)) + 1;
        }
    }
};


int main(void) {

    Solution solution;
    cout << solution.minDistance("ac", "abc") << endl;
}
