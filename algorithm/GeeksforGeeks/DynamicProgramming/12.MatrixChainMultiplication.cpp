// http://www.geeksforgeeks.org/dynamic-programming-set-8-matrix-chain-multiplication/

// Given a sequence of matrices, find the most efficient way to multiply these
// matrices together. The problem is not actually to perform the multiplications,
// but merely to decide in which order to perform the multiplications.

// We have many options to multiply a chain of matrices because matrix
// multiplication is associative. In other words, no matter how we parenthesize
// the product, the result will be the same. For example, if we had four matrices
// A, B, C, and D, we would have:
//    (ABC)D = (AB)(CD) = A(BCD) = ....

// However, the order in which we parenthesize the product affects the number of
// simple arithmetic operations needed to compute the product, or the efficiency.
// For example, suppose A is a 10 × 30 matrix, B is a 30 × 5 matrix, and C is a
// 5 × 60 matrix. Then,
//    (AB)C = (10×30×5) + (10×5×60) = 1500 + 3000 = 4500 operations
//    A(BC) = (30×5×60) + (10×30×60) = 9000 + 18000 = 27000 operations.
// Clearly the first method is the more efficient.

// Given an array p[] which represents the chain of matrices such that the ith
// matrix Ai is of dimension p[i-1] x p[i]. We need to write a function
// MatrixChainOrder() that should return the minimum number of multiplications
// needed to multiply the chain.

// Input: p[] = {40, 20, 30, 10, 30}
// Output: 26000
// There are 4 matrices of dimensions 40x20, 20x30, 30x10 and 10x30.
// Let the input 4 matrices be A, B, C and D.  The minimum number of
// multiplications are obtained by putting parenthesis in following way
// (A(BC))D --> 20*30*10 + 40*20*10 + 40*10*30

// Input: p[] = {10, 20, 30, 40, 30}
// Output: 30000
// There are 4 matrices of dimensions 10x20, 20x30, 30x40 and 40x30.
// Let the input 4 matrices be A, B, C and D.  The minimum number of
// multiplications are obtained by putting parenthesis in following way
// ((AB)C)D --> 10*20*30 + 10*30*40 + 10*40*30

// Input: p[] = {10, 20, 30}
// Output: 6000
// There are only two matrices of dimensions 10x20 and 20x30. So there
// is only one way to multiply the matrices, cost of which is 10*20*30

#include <stdio.h>
#include <limits.h>
using namespace std;


// Matrix Ai has dimension p[i-1] x p[i] for i = 1..n
int MatrixChainOrder(int p[], int i, int j)
{
    if (i == j)
        return 0;
    int k;
    int min = INT_MAX;
    int count;

    // place parenthesis at different places between first and last matrix,
    // recursively calculate count of multiplcations for each parenthesis
    // placement and return the minimum count
    for (k = i; k < j; k++)
    {
        // for a specific k, it means k will not be eliminated from the whole
        // array. Notice no matter how we divide the sub-problem, at last, it
        // is p[k] multiply first and last element.
        // e.g.  1   2   3   4   5   6   7   8   9
        //           ^           ^               ^
        //           i           k               j
        // it means for the left part of k, find the best chain order which
        // multiply to 1x5, and find the best chain order which multiply to
        // 5x9, then current count is the sum of the two plus 1x5x9, which
        // is p[i-1]*p[k]*p[j]
        count = MatrixChainOrder(p, i, k) +
            MatrixChainOrder(p, k+1, j) +
            p[i-1]*p[k]*p[j];

        if (count < min)
            min = count;
    }

    // Return minimum count
    return min;
}


// Matrix Ai has dimension p[i-1] x p[i] for i = 1..n
int MatrixChainOrderDP(int p[], int n)
{
    /* For simplicity of the program, one extra row and one extra column are
       allocated in m[][].  0th row and 0th column of m[][] are not used */
    int m[n][n];

    int i, j, k, L, q;

    /* m[i,j] = Minimum number of scalar multiplications needed to compute
       the matrix A[i]A[i+1]...A[j] = A[i..j] where dimention of A[i] is
       p[i-1] x p[i] */

    // cost is zero when multiplying one matrix.
    for (i = 1; i < n; i++)
        m[i][i] = 0;

    // L is chain length.
    for (L = 2; L < n; L++)
    {
        for (i = 1; i <= n-L+1; i++)
        {
            j = i+L-1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j-1; k++)
            {
                // q = cost/scalar multiplications
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    return m[1][n-1];
}


class MySolution {
public:
    // Matrix Ai has dimension p[i-1] x p[i] for i = 1..n
    int MatrixChainOrder(int p[], int n) {
        return MatrixChainOrderHelper(p, 1, n-1);
    }

    int MatrixChainOrderDP(int p[], int n) {

        int table[n][n];

        for (int i = 0; i < n; i++) {
            table[i][i] = 0;
        }

        // current length of matrix multiplication, start from two matrix
        for (int cl = 2; cl < n; cl++) {
            for (int i = 1; i <= n - cl + 1; i++) {
                int j = i + cl - 1;
                table[i][j] = INT_MAX;
                for (int k = i; k <= j; k++) {
                    int operations = table[i][k] + table[k+1][j] +
                        p[i-1]*p[k]*p[j];
                    if (table[i][j] > operations) {
                        table[i][j] = operations;
                    }
                }
            }
        }

        return table[1][n-1];
    }
private:
    int MatrixChainOrderHelper(int p[], int i, int j) {

        if (i == j) {
            return 0;
        }
        int minimum = INT_MAX;

        // For an array, we can image it below:
        //     A   B   C   D   E
        // 10  30  50  30  10  40
        //     i       k       j
        // which means A=10x30, B=30x50, etc, and i,j points to array A and
        // E (more specifically, to the second dimension of A and E).
        // Therefore, by passing MatrixChainOrderHelper(p, i, k) we mean, find
        // least operations involving A,B,C; by passing (p, k+1, j), we mean,
        // find the least operations involving C,D,E.
        for (int k = i; k < j; k++) {
            int operations = MatrixChainOrderHelper(p, i, k) +
                MatrixChainOrderHelper(p, k + 1, j) +
                p[i-1] * p[k] * p[j];
            if (operations < minimum) {
                minimum = operations;
            }
        }

        return minimum;
    }
};


// Driver program to test above function
int main() {

    MySolution solution;
    int arr[] = {1, 2, 3, 4, 3};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Minimum number of multiplications is %d\n",
           MatrixChainOrder(arr, 1, n-1));
    printf("Minimum number of multiplications is %d\n",
           MatrixChainOrderDP(arr, n));
    printf("Minimum number of multiplications is %d\n",
           solution.MatrixChainOrder(arr, n));
    printf("Minimum number of multiplications is %d\n",
           solution.MatrixChainOrderDP(arr, n));

    return 0;
}
