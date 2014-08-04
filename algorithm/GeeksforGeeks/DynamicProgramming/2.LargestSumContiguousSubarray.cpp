// http://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
// http://en.wikipedia.org/wiki/Kadane%27s_Algorithm

// Largest Sum Contiguous Subarray
// Write an efficient C program to find the sum of contiguous subarray within
// a one-dimensional array of numbers which has the largest sum.

// Kadane’s Algorithm:
// Initialize:
//    max_so_far = 0
//    max_ending_here = 0
// Loop for each element of the array
//    (a) max_ending_here = max_ending_here + a[i]
//    (b) if (max_ending_here < 0)
//            max_ending_here = 0
//    (c) if (max_so_far < max_ending_here)
//            max_so_far = max_ending_here
// return max_so_far

// Explanation:
// Simple idea of the Kadane's algorithm is to look for all positive contiguous
// segments of the array (max_ending_here is used for this). And keep track of
// maximum sum contiguous segment among all positive segments (max_so_far is used
// for this). Each time we get a positive sum compare it with max_so_far and
// update max_so_far if it is greater than max_so_far.

// Time Complexity: O(n)
// Algorithmic Paradigm: Dynamic Programming

// Try below question
// Given an array of integers (possibly some of the elements negative), write
// a C program to find out the *maximum product* possible by adding 'n'
// consecutive integers in the array, n <= ARRAY_SIZE. Also give where in the
// array this sequence of n integers starts.

// Program:
#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int a[], int size) {

    int max_so_far = 0, max_ending_here = 0;
    int i;

    for (i = 0; i < size; i++) {
        max_ending_here = max_ending_here + a[i];
        if (max_ending_here < 0) {
            max_ending_here = 0;
        }
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
        }
    }

    return max_so_far;
}

// Notes:
// Algorithm doesn't work for all negative numbers. It simply returns 0 if all
// numbers are negative. For handling this we can add an extra phase before
// actual implementation. The phase will look if all numbers are negative, if
// they are it will return maximum of them (or smallest in terms of absolute
// value). There may be other ways to handle it though.


// Following is another simple implementation suggested by Mohit Kumar.
// The implementation handles the case when all numbers in array are negative.
int max(int x, int y) {
    return (y > x)? y : x;
}

int maxSubArraySum2(int a[], int size) {

    int max_so_far = a[0], i;
    int curr_max = a[0];

    for (i = 1; i < size; i++) {
        curr_max = max(a[i], curr_max+a[i]);
        max_so_far = max(max_so_far, curr_max);
    }

    return max_so_far;
}


class MySolution {
public:
    int maxSubArraySum(int arr[], int size) {

        int max_so_far = 0;
        int max_ending_here = 0;

        for (int i = 0; i < size; i++) {
            max_ending_here += arr[i];

            if (max_ending_here < 0) {
                /* set to 0, subarray will always start from positive number */
                max_ending_here = 0;
            } else if (max_so_far < max_ending_here) {
                max_so_far = max_ending_here;
            }
        }

        return max_so_far;
    }

    int maxSubArraySumEnhanced(int arr[], int size, int &start, int &end) {

        int max_so_far = 0;
        int max_ending_here = 0;
        int local_start = 0;

        end = -1;
        for (int i = 0; i < size; i++) {

            max_ending_here += arr[i];
            if (max_ending_here < 0) {
                /* set to 0, subarray will always start from positive number */
                max_ending_here = 0;
                local_start = i + 1;
            } else if (max_so_far < max_ending_here) {
                max_so_far = max_ending_here;
                start = local_start;
                end = i;
            }
        }

        max_so_far = INT_MIN;
        if (end == -1) {        // all negative
            for (int i = 0; i < size; i++) {
                if (arr[i] > max_so_far) {
                    max_so_far = arr[i];
                    start = i;
                    end = i;
                }
            }
        }

        return max_so_far;
    }
};

/* Driver program to test maxSubArraySum */
int main(void) {

    //int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int a[] = {-2, -3, -1, -2, -1, -5, -3};
    int n = sizeof(a)/sizeof(a[0]);
    MySolution solution;

    int max_sum = solution.maxSubArraySum(a, n);
    printf("Maximum contiguous sum is %d\n", max_sum);

    int start, end;
    printf("Maximum contiguous sum is %d\n",
           solution.maxSubArraySumEnhanced(a, n, start, end));
    printf("%d, %d\n", start, end);
    return 0;
}
