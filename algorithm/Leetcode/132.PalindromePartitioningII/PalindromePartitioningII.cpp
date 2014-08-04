// Given a string s, partition s such that every substring of the partition
// is a palindrome.

// Return the minimum cuts needed for a palindrome partitioning of s.

// For example, given s = "aab",
// Return 1 since the palindrome partitioning ["aa","b"] could be produced
// using 1 cut.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    // O(n^2) solution, from web
    int minCut(string str) {

        int len = str.size();
        int dp[len+1]; // dp[i] indicates the min cut of s[i ... len-1]
        bool palin[len][len]; // palin[i][j] indicate if s[i ... j] is palindrome

        // for s[i .. len-1], init min cut to len - i - 1 (cut at every character)
        for (int i = 0; i <= len; i++) {
            dp[i] = len - i - 1;
        }
        // init palin to all false
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                palin[i][j] = false;
            }
        }

        // compute minCut from end, until dp[0]
        for (int i = len - 1; i >= 0; i--) {
            for (int j = i; j < len; j++) {
                if (str[i] == str[j] && (j - i < 2 || palin[i+1][j-1])) {
                    palin[i][j] = true;
                    dp[i] = min(dp[i], dp[j+1]+1);
                }
            }
        }
        return dp[0];
    }

    // O(n^3), correct but slow solution
    int minCut2(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int size = s.length();
        int **minCuts = my2DAlloc(size, size);
        int **isPalindrome = my2DAlloc(size, size);

        // init two auxiliary arrays
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                minCuts[i][j] = 0;
                isPalindrome[i][j] = 0;
            }
        }

        // only one element, minCuts is 0 and isPalindrome is 1; also init
        // minCuts and isPalindrome for two elements
        for (int i = 0; i < size; i++) {
            minCuts[i][i] = 0;
            isPalindrome[i][i] = 1;
            if (i < size - 1 && s[i] == s[i+1]) {
                minCuts[i][i+1] = 0;
                isPalindrome[i][i+1] = 1;
            } else {
                minCuts[i][i+1] = 1;
                isPalindrome[i][i+1] = 0;
            }
        }

        for (int len = 3; len <= size; len++) {
            for (int i = 0; i < size; i++) {
                int j = i + len - 1;
                if (j >= size) continue;
                // compute isPalindrome
                if (s[i] == s[j]) {
                    isPalindrome[i][j] = isPalindrome[i+1][j-1];
                } else {
                    isPalindrome[i][j] = 0;
                }
                // compute minCut
                if (isPalindrome[i][j] == 1) {
                    minCuts[i][j] = 0;
                } else {
                    int min_val = INT_MAX;
                    for (int k = i; k < j; k++) { // different cutting point
                        min_val = min(min_val, 1 + minCuts[i][k] + minCuts[k+1][j]);
                    }
                    minCuts[i][j] = min_val;
                }
            }
        }

        int res = minCuts[0][size-1];
        my2DFree(minCuts, size, size);
        my2DFree(isPalindrome, size, size);
        return res;
    }

private:
    int** my2DAlloc(int m, int n) {

        int header_size = m * sizeof(int*);
        int content_size = m * n * sizeof(int);

        int **row = (int**) malloc(header_size + content_size);
        int *content = (int*) (row + m);

        for (int i = 0; i < m; i++) {
            row[i] = content + i * n;
        }

        return row;
    }

    void my2DFree(int **array, int m, int n) {
        free(array);
    }
};


int main(void) {

    Solution solution;
    printf("%d\n", solution.minCut("abba"));
}
