// http://www.geeksforgeeks.org/dynamic-programming-set-9-binomial-coefficient/

// Following are common definition of Binomial Coefficients.
// 1) A binomial coefficient C(n, k) can be defined as the coefficient of X^k in
// the expansion of (1 + X)^n. C(n,m) = C(n-1,m-1) + C(n-1,m).

// 2) A binomial coefficient C(n, k) also gives the number of ways, disregarding
// order, that k objects can be chosen from among n objects; more formally, the
// number of k-element subsets (or k-combinations) of an n-element set.

// The Problem
// Write a function that takes two parameters n and k and returns the value of
// Binomial Coefficient C(n, k). For example, your function should return 6 for
// n = 4 and k = 2, and it should return 10 for n = 5 and k = 2.

#include <stdio.h>
#include <stdlib.h>


class MySolution {
public:
    int binomialCoeff(int n, int k) {

        if (k == 0 || k == n)
            return 1;

        return binomialCoeff(n-1, k-1) + binomialCoeff(n-1, k);
    }

    int binomialCoeffDP(int n, int k) {

        int table[n+1][k+1];

        for (int i = 0; i <= n; i++) {
            table[i][0] = 1;
        }

        for (int i = 0; i <= k; i++) {
            table[i][i] = 1;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                table[i][j] = table[i-1][j] + table[i-1][j-1];
            }
        }

        return table[n][k];
    }
};


/* Drier program to test above function*/
int main() {

    MySolution solution;
    int n = 6, k = 2;

    printf("Value of C(%d, %d) is %d\n", n, k, solution.binomialCoeff(n, k));
    printf("Value of C(%d, %d) is %d\n", n, k, solution.binomialCoeffDP(n, k));
    return 0;
}
