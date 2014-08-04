// http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/

// We have discussed Overlapping Subproblems and Optimal Substructure properties
// in Set 1 and Set 2 respectively.

// Let us discuss Longest Increasing Subsequence (LIS) problem as an example
// problem that can be solved using Dynamic Programming.

// The longest Increasing Subsequence (LIS) problem is to find the length of the
// longest subsequence of a given sequence such that all elements of the
// subsequence are sorted in increasing order. For example, length of LIS for
// { 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is {10, 22, 33, 50, 60, 80}.

// Optimal Substructure:
// Let arr[0..n-1] be the input array and L(i) be the length of the LIS till index
// i such that arr[i] is part of LIS and arr[i] is the last element in LIS, then
// L(i) can be recursively written as.
// L(i) = { 1 + Max ( L(j) ) } where j < i and arr[j] < arr[i] and if there is no
// such j then L(i) = 1. To get LIS of a given array, we need to return max(L(i))
// where 0 < i < n. So the LIS problem has optimal substructure property as the main
// problem can be solved using solutions to subproblems.

// Overlapping Subproblems:
// Following is simple recursive implementation of the LIS problem. The
// implementation simply follows the recursive structure mentioned above. The value
// of lis ending with every element is returned using max_ending_here. The overall
// lis is returned using pointer to a variable max.


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


/* A Naive recursive implementation of LIS problem
   To make use of recursive calls, this function must return two things:
   1) Length of LIS ending with element arr[n-1]. We use max_ending_here
      for this purpose
   2) Overall maximum as the LIS may end with an element before arr[n-1]
      max_ref is used this purpose.
   The value of LIS of full array of size n is stored in *max_ref which
   is our final result
*/
int _lis( int arr[], int n, int *max_ref)
{
    /* Base case */
    if(n == 1)
        return 1;

    int res, max_ending_here = 1; // length of LIS ending with arr[n-1]

    /* Recursively get all LIS ending with arr[0], arr[1] ... ar[n-2]. If
       arr[i-1] is smaller than arr[n-1], and max ending with arr[n-1] needs
       to be updated, then update it */
    for(int i = 1; i < n; i++)
    {
        res = _lis(arr, i, max_ref);
        if (arr[i-1] < arr[n-1] && res + 1 > max_ending_here)
            max_ending_here = res + 1;
    }

    // Compare max_ending_here with the overall max. And update the
    // overall max if needed
    if (*max_ref < max_ending_here)
       *max_ref = max_ending_here;

    // Return length of LIS ending with arr[n-1]
    return max_ending_here;
}

// The wrapper function for _lis()
int lis(int arr[], int n)
{
    // The max variable holds the result
    int max = 1;

    // The function _lis() stores its result in max
    _lis( arr, n, &max );

    // returns max
    return max;
}


class MySolution {
public:
    int lis(int arr[], int n) {

        // L[i] means the LIS which end with arr[i]
        int L[n];
        int max = 0;

        for (int i = 0; i < n; i++) {
            L[i] = 1;
        }

        // Dynamicly find the LIS
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[i] > arr[j] && L[i] < L[j] + 1) {
                    L[i] = L[j] + 1;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (max < L[i]) {
                max = L[i];
            }
        }

        printLIS(arr, L, n-1, max);
        return max;
    }

private:
    void printLIS(int arr[], int L[], int i, int max) {

        if (max == 1) {
            cout << arr[i] << " ";
            return;
        }

        if (L[i] == max) {
            printLIS(arr, L, i-1, max-1);
            cout << arr[i] << " ";
        } else {
            printLIS(arr, L, i-1, max);
        }
    }
};


/* Driver program to test above function */
int main()
{
    MySolution solution;
    int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60, 80 };
    int n = sizeof(arr)/sizeof(arr[0]);

    // printf("Length of LIS is %d\n",  lis( arr, n ));
    printf("\nLength of LIS is %d\n",  solution.lis( arr, n ));

    return 0;
}
