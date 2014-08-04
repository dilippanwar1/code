// There are two sorted arrays A and B of size m and n respectively. Find the
// median of the two sorted arrays. The overall run time complexity should be
// O(log(m+n)).

// First, we choose Ai and Bj (the middle elements of A and B) where i and j
// are defined as m/2 and n/2. We made an observation that if Ai <= Bj, then
// the median must be somewhere between Ai and Bj (inclusive). Therefore, we
// could dispose a total of i elements from left of Ai and a total of n-j-1
// elements to the right of Bj. Please take extra caution not to dispose Ai
// or Bj, as we might need two middle values to calculate the median (it might
// also be possible that the two middle values are both in the same array).
// The case where Ai > Bj is similar.

// The main idea illustrated above is mostly right, however there is one more
// important invariant we have to maintain. It is entirely possible that the
// number of elements being disposed from each array is different. An important
// invariant we have to maintain is: The number of elements being disposed from
// each array must be the same. Following is the formula to throw elements,
// basically, it means throw away the min # of elements to left of A and to
// right of B.
//    k = min(i-1, n-j-1) when Ai <= Bj and m is even.
//    k = min(i, n-j-1)   when Ai <= Bj and m is odd.
//    k = min(m-i-1, j-1) when Ai > Bj  and n is even.
//    k = min(m-i-1, j)   when Ai > Bj  and n is odd.

// For example: A = {4, 7, 21, 40, 47} and B = {6, 10, 18, 30, 48, 50, 52}
// then median of A is 21 and median of B is 30, then we can throw away {4, 7}
// in A and {50, 52} in B. The reason of the observation is that since Ai <= Bj,
// we know that in the sorted array of A and B, it will be like this generally:
// x x x x 21 x x x x x x 31 x x x x x, therefore we can safely throw them away.
// Note here for B, we cannot dispose 48 since the median of the subproblem will
// change.

// Second, base case. It is obvious that when m=1 or n=1, you must treat it
// as a special base case, or else it would end up in an infinite loop. The
// hard part is reasoning why m=2 or n=2 requires special case handling as
// well. For example, if A = {3, 10}, B = {1, 4, 10, 12, 15}. Then median of
// A is 3 and median of B is 10; in this case we need to discard elements
// to the left of A, which has nothing, so we end up in an infinite loop.

// Finally, implementing the above idea turns out to be an extremely tricky
// coding exercise. Before looking at the solution below, try to challenge
// yourself by coding the algorithm.

#include <iostream>
#include <stdlib.h>
using namespace std;


class Solution {
public:
    // when one of the array has only one element, find the median of the
    // two arrays. In this case, we need to know the relationship between
    // the single array element `med` and median of array C.
    double findMedianBaseCase(int med, int C[], int n) {

        if (n == 1)
            return (med+C[0])/2.0;

        if (n % 2 == 0) {
            int a = C[n/2 - 1], b = C[n/2];
            if (med <= a)
                return a;
            else if (med <= b)
                return med;
            else /* med > b */
                return b;
        } else {
            int a = C[n/2 - 1], b = C[n/2], c = C[n/2 + 1];
            if (med <= a)
                return (a+b) / 2.0;
            else if (med <= c)
                return (med+b) / 2.0;
            else /* med > c */
                return (b+c) / 2.0;
        }
    }

    // when one of the array has two elements, find the median of the two
    // arrays.
    double findMedianBaseCase2(int med1, int med2, int C[], int n) {

        if (n % 2 == 0) {
            int a = (((n/2-2) >= 0) ? C[n/2 - 2] : INT_MIN);
            int b = C[n/2 - 1], c = C[n/2];
            int d = (((n/2 + 1) <= n-1) ? C[n/2 + 1] : INT_MAX);
            if (med2 <= b)
                return (b+max(med2,a)) / 2.0;
            else if (med1 <= b)
                return (b+min(med2,c)) / 2.0;
            else if (med1 >= c)
                return (c+min(med1,d)) / 2.0;
            else if (med2 >= c)
                return (c+max(med1,b)) / 2.0;
            else  /* a < med1 <= med2 < b */
                return (med1+med2) / 2.0;
        } else {
            int a = C[n/2 - 1], b = C[n/2], c = C[n/2 + 1];
            if (med1 >= b)
                return min(med1, c);
            else if (med2 <= b)
                return max(med2, a);
            else  /* med1 < b < med2 */
                return b;
        }
    }

    // return median of a single array
    double findMedianSingleArray(int A[], int n) {
        return ((n%2 == 1) ? A[n/2] : (A[n/2-1]+A[n/2])/2.0);
    }


    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        if (m == 0)
            return findMedianSingleArray(B, n);
        else if (n == 0)
            return findMedianSingleArray(A, m);
        else if (m == 1)
            return findMedianBaseCase(A[0], B, n);
        else if (n == 1)
            return findMedianBaseCase(B[0], A, m);
        else if (m == 2)
            return findMedianBaseCase2(A[0], A[1], B, n);
        else if (n == 2)
            return findMedianBaseCase2(B[0], B[1], A, m);

        int i = m/2, j = n/2, k;
        if (A[i] <= B[j]) {
            k = ((m%2 == 0) ? min(i-1, n-j-1) : min(i, n-j-1));
            return findMedianSortedArrays(A+k, m-k, B, n-k);
        } else {
            k = ((n%2 == 0) ? min(m-i-1, j-1) : min(m-i-1, j));
            return findMedianSortedArrays(A, m-k, B+k, n-k);
        }
    }

};


int main(void) {

    int A[5] = {1,3,5,7,9};
    int B[5] = {2,4,6,8,10};
    Solution solution;

    cout << solution.findMedianSortedArrays(A, 5, B, 5) << endl;
}
