// http://www.geeksforgeeks.org/longest-common-substring/

// Given two strings 'X' and 'Y', find the length of the longest common
// substring. For example, if the given strings are "GeeksforGeeks" and
// "GeeksQuiz", the output should be 5 as longest common substring is "Geeks".

// The longest substring can also be solved in O(n+m) time using Suffix Tree.
// We will be covering Suffix Tree based solution in a separate post.

// Exercise: The above solution prints only length of the longest common
// substring. Extend the solution to print the substring also.

// Dynamic Programming can be used to find the longest common substring in
// O(m*n) time. The idea is to find length of the longest common suffix for
// all substrings of both strings and store these lengths in a table.
// The longest common suffix has following optimal substructure property
//    LCSuff(X, Y, m, n) = LCSuff(X, Y, m-1, n-1) + 1 if X[m-1] = Y[n-1]
//                         0  Otherwise (if X[m-1] != Y[n-1])
// The maximum length Longest Common Suffix is the longest common substring.
//    LCSubStr(X, Y, m, n)  = Max(LCSuff(X, Y, i, j)) where 1 <= i <= m
//                                                      and 1 <= j <= n

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <iostream>
using namespace std;


class MySolution {
public:
    // O(n*m) DP solution, can be solved in O(n+m) using suffix tree
    int LCSubStr(char *X, char *Y, int m, int n) {

        // LCSuffix[i][j] means longest common suffix for strings
        // X[0...i-1] and Y[0...j-1]
        int LCSuffix[m+1][n+1];
        int max_len = INT_MIN;

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {

                if (i == 0 || j == 0) {
                    LCSuffix[i][j] = 0;
                    continue;
                }

                if (X[i] == Y[j]) {
                    LCSuffix[i][j] = LCSuffix[i-1][j-1] + 1;
                    max_len = max(max_len, LCSuffix[i][j]);
                } else {
                    LCSuffix[i][j] = 0;
                }
            }
        }

        return max_len;
    }

private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
};


/* Driver program to test above function */
int main()
{
    MySolution solution;
    char X[] = "OldSite:GeeksforGeeks.org";
    char Y[] = "NewSite:GeeksQuiz.com";

    int m = strlen(X);
    int n = strlen(Y);

    cout << "Length of Longest Common Substring is " <<
        solution.LCSubStr(X, Y, m, n) << endl;
    return 0;
}
