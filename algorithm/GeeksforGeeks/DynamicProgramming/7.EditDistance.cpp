// http://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/

// Problem: Given two strings of size m, n and set of operations replace (R),
// insert (I) and delete (D) all at equal cost. Find minimum number of edits
// (operations) required to convert one string into another.

// Identifying Recursive Methods:

// What will be sub-problem in this case? Consider finding edit distance of
// part of the strings, say small prefix. Let us denote them as [1...i] and
// [1...j] for some 1 < i < m and 1 < j < n. Clearly it is solving smaller
// instance of final problem, denote it as E(i, j). Our goal is finding E(m, n)
// and minimizing the cost.

// In the prefix, we can right align the strings in three ways (i, -), (-, j)
// and (i, j). The hyphen symbol (-) representing no character. An example can
// make it more clear.

// Given strings SUNDAY and SATURDAY. We want to convert SUNDAY into SATURDAY
// with minimum edits. Let us pick i = 2 and j = 4 i.e. prefix strings are SUN
// and SATU respectively (assume the strings indices start at 1). The right
// most characters can be aligned in three different ways.

// Case 1: Align characters U and U. They are equal, no edit is required. We
// still left with the problem of i = 1 and j = 3, E(i-1, j-1).

// Case 2: Align right character from first string and no character from second
// string. We need a deletion (D) here. We still left with problem of i = 1
// and j = 4, E(i-1, j).

// Case 3: Align right character from second string and no character from first
// string. We need an insertion (I) here. We still left with problem of i = 2
// and j = 3, E(i, j-1).

// Combining all the subproblems minimum cost of aligning prefix strings ending
// at i and j given by: E(i, j) = min( [E(i-1, j) + D], [E(i, j-1) + I],
// [E(i-1, j-1) + R if i,j characters are not same] )

// We still not yet done. What will be base case(s)?

// When both of the strings are of size 0, the cost is 0. When only one of the
// string is zero, we need edit operations as that of non-zero length string.
// Mathematically,
// E(0, 0) = 0, E(i, 0) = i, E(0, j) = j


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Change these strings to test the program
#define STRING_X "SUNDAYEGFE"
#define STRING_Y "SATURDAYEGE"

#define SENTINEL (-1)
#define EDIT_COST (1)

inline int min(int a, int b) {
    return a < b ? a : b;
}

// Returns Minimum among a, b, c
int Minimum(int a, int b, int c)
{
    return min(min(a, b), c);
}

// Strings of size m and n are passed.
// Construct the Table for X[0...m, m+1], Y[0...n, n+1]
int EditDistanceDP(char X[], char Y[])
{
    // Cost of alignment
    int cost = 0;
    int leftCell, topCell, cornerCell;

    int m = strlen(X)+1;
    int n = strlen(Y)+1;

    // T[m][n]
    int *T = (int *)malloc(m * n * sizeof(int));

    // Initialize table
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            *(T + i * n + j) = SENTINEL;

    // Set up base cases
    // T[i][0] = i
    for(int i = 0; i < m; i++)
        *(T + i * n) = i;

    // T[0][j] = j
    for(int j = 0; j < n; j++)
        *(T + j) = j;

    // Build the T in top-down fashion
    for(int i = 1; i < m; i++)
    {
        for(int j = 1; j < n; j++)
        {
            // T[i][j-1]
            leftCell = *(T + i*n + j-1);
            leftCell += EDIT_COST; // deletion

            // T[i-1][j]
            topCell = *(T + (i-1)*n + j);
            topCell += EDIT_COST; // insertion

            // Top-left (corner) cell
            // T[i-1][j-1]
            cornerCell = *(T + (i-1)*n + (j-1) );

            // edit[(i-1), (j-1)] = 0 if X[i] == Y[j], 1 otherwise
            cornerCell += (X[i-1] != Y[j-1]); // may be replace

            // Minimum cost of current cell
            // Fill in the next cell T[i][j]
            *(T + (i)*n + (j)) = Minimum(leftCell, topCell, cornerCell);
        }
    }

    // Cost is in the cell T[m][n]
    cost = *(T + m*n - 1);
    free(T);
    return cost;
}

// Recursive implementation
int EditDistanceRecursion( char *X, char *Y, int m, int n )
{
    // Base cases
    if( m == 0 && n == 0 )
        return 0;

    if( m == 0 )
        return n;

    if( n == 0 )
        return m;

    // Recurse
    int left = EditDistanceRecursion(X, Y, m-1, n) + 1;
    int right = EditDistanceRecursion(X, Y, m, n-1) + 1;
    int corner = EditDistanceRecursion(X, Y, m-1, n-1) + (X[m-1] != Y[n-1]);

    return Minimum(left, right, corner);
}


class MySolution {
public:
    // input two strings and their respective length
    int EditDistanceRecursion(char *X, char *Y, int m, int n) {

        if (m == 0) {
            return n;
        }

        if (n == 0) {
            return m;
        }

        if (X[m-1] == Y[n-1]) {
            return EditDistanceRecursion(X, Y, m-1, n-1);
        } else {
            // three choices: insert, replace and delete
            return 1 + Minimum(EditDistanceRecursion(X, Y, m-1, n-1),
                               EditDistanceRecursion(X, Y, m-1, n),
                               EditDistanceRecursion(X, Y, m, n-1));
        }
    }

    int EditDistanceDP(char *X, char *Y, int m, int n) {

        int table[m+1][n+1];

        for (int i = 0; i <= m; i++) {
            table[i][0] = i;
        }
        for (int j = 0; j <= n; j++) {
            table[0][j] = j;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int center = table[i-1][j-1] + (X[i-1] != Y[j-1]);
                int left  = 1 + table[i-1][j];
                int right = 1 + table[i][j-1];
                table[i][j] = Minimum(center, left, right);
            }
        }

        return table[m][n];
    }

private:
    inline int min(int a, int b) {
        return a < b ? a : b;
    }

    // Returns Minimum among a, b, c
    int Minimum(int a, int b, int c) {
        return min(min(a, b), c);
    }
};


/* Driver program to test EditDistance */
int main(void ) {

    MySolution solution;
    char X[] = STRING_X; // vertical
    char Y[] = STRING_Y; // horizontal

    printf("Minimum edits required to convert %s into %s is %d\n",
           X, Y, EditDistanceDP(X, Y) );
    printf("Minimum edits required to convert %s into %s is %d by recursion\n",
           X, Y, solution.EditDistanceRecursion(X, Y, strlen(X), strlen(Y)));
    printf("Minimum edits required to convert %s into %s is %d by DP\n",
           X, Y, solution.EditDistanceDP(X, Y, strlen(X), strlen(Y)));

    return 0;
}
