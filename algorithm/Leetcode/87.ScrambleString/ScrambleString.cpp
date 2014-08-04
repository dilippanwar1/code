// Given a string s1, we may represent it as a binary tree by partitioning it
// to two non-empty substrings recursively.

// Below is one possible representation of s1 = "great":
//     great
//    /    \
//   gr    eat
//  / \    /  \
// g   r  e   at
//            / \
//           a   t

// To scramble the string, we may choose any non-leaf node and swap its two
// children.

// For example, if we choose the node "gr" and swap its two children, it
// produces a scrambled string "rgeat".
//     rgeat
//    /    \
//   rg    eat
//  / \    /  \
// r   g  e   at
//            / \
//           a   t
// We say that "rgeat" is a scrambled string of "great".

// Similarly, if we continue to swap the children of nodes "eat" and "at",
// it produces a scrambled string "rgtae".
//     rgtae
//    /    \
//   rg    tae
//  / \    /  \
// r   g  ta  e
//        / \
//       t   a
// We say that "rgtae" is a scrambled string of "great".

// Given two strings s1 and s2 of the same length, determine if s2 is a
// scrambled string of s1.

#include <string>
#include <iostream>
using namespace std;


class Solution {
public:

    // dp solution
    bool isScramble(string s1, string s2) {

        if (s1.length() != s2.length())
            return false;
        if (s1.length() == 0)
            return true;

        int len = s1.length();
        bool scrambled[len][len][len+1];

        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                scrambled[i][j][0] = true;
                scrambled[i][j][1] = (s1[i] == s2[j]);
                for (int k = 2; k <= len; k++) {
                    scrambled[i][j][k] = false;
                }
            }
        }

        for (int i = len - 1; i >= 0 ; i--) {
            for (int j = len - 1; j >= 0; j--) {
                for (int n = 2; n <= min(len - i, len - j); n++) {
                    for (int m = 1; m < n; m++) {
                        scrambled[i][j][n] |=
                            scrambled[i][j][m] && scrambled[i + m][j + m][n - m] ||
                            scrambled[i][j + n - m][m] && scrambled[i + m][j][n - m];
                        if (scrambled[i][j][n])
                            break;
                    }
                }
            }
        }

        return scrambled[0][0][len];
    }


    // recursive solution
    bool isScramble1(string s1, string s2) {

        if (s1.length() != s2.length())
            return false;
        if (s1.length() == 0)
            return true;

        return isScrambleHelper(s1, s2);
    }

    bool isScrambleHelper(string s1, string s2) {

        int n = s1.length();
        if (n == 1)
            return (s1[0] == s2[0]);
        if (!isPermutation(s1, s2))
            return false;

        for (int i = 1; i < n; i++) {

            // partition s1 into two part
            string s1_l = s1.substr(0, i);
            string s1_r = s1.substr(i);

            // pass both left and right part
            string s2_l = s2.substr(0, i);
            string s2_r = s2.substr(i);
            if (isScrambleHelper(s1_l, s2_l) && isScrambleHelper(s1_r, s2_r)) {
                return true;
            }

            // pass s1's left part and s2's right part
            s2_l = s2.substr(0, s1_r.length());
            s2_r = s2.substr(s1_r.length());
            if (isScrambleHelper(s1_l, s2_r) && isScrambleHelper(s1_r, s2_l)) {
                return true;
            }
        }

        return false;
    }

    bool isPermutation(string s1, string s2) {

        int sum = 0;

        for (int i = 0; i < s1.length(); i++) {
            sum += s1[i];
            sum -= s2[i];
        }

        return (sum == 0);
    }
};


int main(void) {

    Solution solution;
    cout << solution.isScramble("great", "rgtae") << endl;
}
