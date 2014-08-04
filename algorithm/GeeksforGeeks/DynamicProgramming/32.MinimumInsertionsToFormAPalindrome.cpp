// http://www.geeksforgeeks.org/dynamic-programming-set-28-minimum-insertions-to-form-a-palindrome/

// Given a string, find the minimum number of characters to be inserted to
// convert it to palindrome.

// Before we go further, let us understand with few examples:
//     ab: Number of insertions required is 1. bab
//     aa: Number of insertions required is 0. aa
//     abcd: Number of insertions required is 3. dcbabcd
//     abcda: Number of insertions required is 2. adcbcda
//     abcde: Number of insertions required is 4. edcbabcde

#include <stdio.h>
#include <limits.h>
#include <string.h>


class MySolution {
public:
    int findMinInsertions(char *str) {
        return findMinInsertionsHelper(str, 0, strlen(str) - 1);
    }

    int findMinInsertionsDP(char *str) {

        int n = strlen(str);
        int table[n][n];

        for (int i = 0; i < n; i++) {
            table[i][i] = 0;
        }

        for (int cl = 2; cl <= n; cl++) { // current length
            for (int i = 0; i < n - cl + 1; i++) { // start point
                int j = i + cl - 1;                // end point
                if (cl == 2) {
                    if (str[i] == str[j]) {
                        table[i][j] = 0;
                    } else {
                        table[i][j] = 1;
                    }
                } else {
                    if (str[i] == str[j]) {
                        table[i][j] = table[i+1][j-1];
                    } else {
                        table[i][j] = min(table[i+1][j], table[i][j-1]) + 1;
                    }
                }
            }
        }

        return table[0][n-1];
    }
private :
    // following is the recursion implementation, we can use a two dimention
    // array to memorize the results.
    int findMinInsertionsHelper(char *str, int left, int right) {

        if (left == right) {
            return 0;
        } else if (left + 1 == right) {
            if (str[left] == str[right]) {
                return 0;
            } else {
                return 1;
            }
        }

        if (str[left] == str[right]) {
            return findMinInsertionsHelper(str, left+1, right-1);
        } else {
            // e.g. for "geeks", we can make "sgeeks" or "geeksg"
            return min(findMinInsertionsHelper(str, left+1, right),
                       findMinInsertionsHelper(str, left, right-1)) + 1;
        }
    }

    int min(int a, int b) {
        return a < b ? a : b;
    }
};

// Driver program to test above functions
int main()
{
    MySolution solution;
    char str[] = "geeksfowaeijfaweon";

    printf("%d\n", solution.findMinInsertions(str));
    printf("%d\n", solution.findMinInsertionsDP(str));
    return 0;
}
