// http://www.geeksforgeeks.org/check-whether-a-given-string-is-an-interleaving-of-two-other-given-strings-set-2/

// Given three strings A, B and C. Write a function that checks whether C is an
// interleaving of A and B. C is said to be interleaving A and B, if it contains
// all characters of A and B and order of all characters in individual strings
// is preserved.

#include <stdio.h>
#include <iostream>
using namespace std;


class MySolution {
public:
    // return if `C` is an interleaving of `A` and `B`
    bool isInterleaved(char *A, char *B, char *C) {

        // if all strings come to an end, then we succeed
        if (*A == '\0' && *B == '\0' && *C == '\0') {
            return true;
        } // if only `C` ends, then false
        if (*C == '\0') {
            return false;
        }

        // if *A == *C and *B == *C, then we need to try both sides
        if (*A == *C && *B == *C) {
            return isInterleaved(A+1, B, C+1) || isInterleaved(A, B+1, C+1);
        }

        if (*A == *C) {
            return isInterleaved(A+1, B, C+1);
        } else if (*B == *C) {
            return isInterleaved(A, B+1, C+1);
        } else {
            return false;
        }
    }

    bool isInterleavedDP(char *A, char *B, char *C) {

        int m = strlen(A), n = strlen(B), l = strlen(C);
        // Let us create a 2D table to store solutions of subproblems.
        // table[i][j] will be true if C[0..i+j-1] is an interleaving
        // of A[0..i-1] and B[0..j-1]. ******
        bool table[m+1][n+1];

        if (m + n != l) {
            return false;
        }

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {

                // two empty string
                if (i == 0 && j == 0) {
                    table[i][j] = true;
                } else if (i == 0 && B[j-1] == C[j-1]) {
                    table[i][j] = table[i][j-1];
                } else if (j == 0 && A[i-1] == C[i-1]) {
                    table[i][j] = table[i-1][j];
                } else if (A[i-1] == C[i+j-1] && B[j-1] == C[i+j-1]) {
                    table[i][j] = table[i-1][j] || table[i][j-1];
                } else if (A[i-1] == C[i+j-1]) {
                    table[i][j] = table[i-1][j];
                } else if (B[j-1] == C[i+j-1]) {
                    table[i][j] = table[i][j-1];
                } else {
                    table[i][j] = false;
                }
            }
        }

        return table[m][n];
    }
};


// A function to run test cases
void test(char *A, char *B, char *C)
{
    MySolution solution;
    if (solution.isInterleaved(A, B, C))
        cout << C <<" is interleaved of " << A <<" and " << B << endl;
    else
        cout << C <<" is not interleaved of " << A <<" and " << B << endl;

    if (solution.isInterleavedDP(A, B, C))
        cout << C <<" is interleaved of " << A <<" and " << B << endl;
    else
        cout << C <<" is not interleaved of " << A <<" and " << B << endl;
}


// Driver program to test above functions
int main()
{
    test("XXY", "XXZ", "XXZXXXY");
    test("XY" ,"WZ" ,"WZXY");
    test ("XY", "X", "XXY");
    test ("YX", "X", "XXY");
    test ("XXY", "XXZ", "XXXXZY");
    test ("aabc", "abad", "aabcabad");
    return 0;
}
