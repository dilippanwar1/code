// Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

// For example,
//    Given:
//    s1 = "aabcc",
//    s2 = "dbbca",
// When s3 = "aadbbcbcac", return true.
// When s3 = "aadbbbaccc", return false.


#include <iostream>
using namespace std;


class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {

        int m = s1.size(), n = s2.size(), l = s3.size();
        // table[i][j] will be true if s3[0..i+j-1] is an interleaving
        // of s1[0..i-1] and s2[0..j-1].
        bool table[m+1][n+1];

        if (m + n != l) {       // check size
            return false;
        }

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 && j == 0) { // two empty string
                    table[i][j] = true;
                } else if (i == 0 && s2[j-1] == s3[j-1]) {
                    table[i][j] = table[i][j-1];
                } else if (j == 0 && s1[i-1] == s3[i-1]) {
                    table[i][j] = table[i-1][j];
                } else if (s1[i-1] == s3[i+j-1] && s2[j-1] == s3[i+j-1]) {
                    table[i][j] = table[i-1][j] || table[i][j-1];
                } else if (s1[i-1] == s3[i+j-1]) {
                    table[i][j] = table[i-1][j];
                } else if (s2[j-1] == s3[i+j-1]) {
                    table[i][j] = table[i][j-1];
                } else {
                    table[i][j] = false;
                }
            }
        }

        return table[m][n];
    }
};


int main(void) {

    Solution solution;
    cout << solution.isInterleave("aabcc", "dbbca", "aadbbcbcac") << endl;
    return 0;
}
