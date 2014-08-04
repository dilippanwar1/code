// http://www.geeksforgeeks.org/dynamic-programming-set-12-longest-palindromic-subsequence/

// Given a sequence, find the length of the longest palindromic subsequence
// in it. For example, if the given sequence is “BBABCBCAB”, then the output
// should be 7 as "BABCBAB" is the longest palindromic subseuqnce in it. "BBBBB"
// and "BBCBB" are also palindromic subsequences of the given sequence, but not
// the longest ones.

// Let X[0..n-1] be the input sequence of length n and L(0, n-1) be the length
// of the longest palindromic subsequence of X[0..n-1].

// If last and first characters of X are same, then L(0, n-1) = L(1, n-2) + 2.
// Else L(0, n-1) = MAX (L(1, n-1), L(0, n-2)).


#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;


class MySolution {
public:
    int lps(char *seq, int i, int j) {

        if (i == j) {
            return 1;
        } else if (i > j) {
            return 0;
        } else if (i + 1 == j && seq[i] == seq[j]) {
            return 2;
        }

        if (seq[i] == seq[j]) {
            return 2 + lps(seq, i + 1, j - 1);
        } else {
            return max(lps(seq, i, j-1), lps(seq, i+1, j));
        }
    }

    int lpsDP(char *seq, int n) {

        // L[i][j] denotes substring seq[i] -> seq[j]
        int L[n][n];

        // strings of length 1 are palindrome of lentgh 1
        for (int i = 0; i < n; i++) {
            L[i][i] = 1;
        }

        for (int cl = 2; cl <= n; cl++) { // `cl` stands for current length
            // iterate all substring of length `cl`
            for (int i = 0; i < n - cl + 1; i++) {
                int j = i + cl - 1; // end of substring
                if (seq[i] == seq[j] && cl == 2) {
                    L[i][j] = 2;
                } else if (seq[i] == seq[j]) {
                    L[i][j] = L[i+1][j-1] + 2;
                } else {
                    L[i][j] = max(L[i][j-1], L[i+1][j]);
                }
            }
        }

        return L[0][n-1];
    }

private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
};


/* Driver program to test above functions */
int main() {

    MySolution solution;
    char seq[] = "GEEKSFORGEEKSEIGLEILA";
    //char seq[] = "ABFEFEFG";
    int n = strlen(seq);

    printf("The lnegth of the LPS is %d\n", solution.lps(seq, 0, n-1));
    printf("The lnegth of the LPS is %d\n", solution.lpsDP(seq, n));
    return 0;
}
