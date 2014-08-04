// http://www.geeksforgeeks.org/divide-and-conquer-maximum-sum-subarray/
// Also see DynamicProgramming/LargestSumContiguousSubarray.c

// You are given a one dimensional array that may contain both positive and
// negative integers, find the sum of contiguous subarray of numbers which has
// the largest sum.

// For example, if the given array is {-2, -5, 6, -2, -3, 1, 5, -6}, then the
// maximum subarray sum is 7 (6, -2, -3, 1, 5)

// The naive method is to run two loops. The outer loop picks the beginning
// element, the inner loop finds the maximum possible sum with first element
// picked by outer loop and compares this maximum with the overall maximum.
// Finally return the overall maximum. The time complexity of the Naive method
// is O(n^2).

// Using Divide and Conquer approach, we can find the maximum subarray sum
// in O(nLogn) time. Following is the Divide and Conquer algorithm.

// 1) Divide the given array in two halves
// 2) Return the maximum of following three
// ....a) Maximum subarray sum in left half (Make a recursive call)
// ....b) Maximum subarray sum in right half (Make a recursive call)
// ....c) Maximum subarray sum such that the subarray crosses the midpoint

// The lines 2.a and 2.b are simple recursive calls. How to find maximum
// subarray sum such that the subarray crosses the midpoint? We can easily
// find the crossing sum in linear time. The idea is simple, find the maximum
// sum starting from mid point and ending at some point on left of mid, then
// find the maximum sum starting from mid + 1 and ending with sum point on
// right of mid + 1. Finally, combine the two and return.

// Time Complexity: maxSubArraySum() is a recursive method and time complexity
// can be expressed as following recurrence relation.
//     T(n) = 2T(n/2) + \Theta(n)
// The above recurrence is similar to Merge Sort and can be solved either using
// Recurrence Tree method or Master method. It falls in case II of Master Method
// and solution of the recurrence is \Theta(nLogn).

// The Kadane's Algorithm for this problem takes O(n) time. Therefore the Kadane's
// algorithm is better than the Divide and Conquer approach, but this problem can
// be considered as a good example to show power of Divide and Conquer. The above
// simple approach where we divide the array in two halves, reduces the time
// complexity from O(n^2) to O(nLogn).

// A Divide and Conquer based program for maximum subarray sum problem
#include <stdio.h>
#include <limits.h>


//====================================================================
// Solution from web
// A utility funtion to find maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }

// A utility funtion to find maximum of three integers
int max(int a, int b, int c) { return max(max(a, b), c); }

// Find the maximum possible sum in arr[] such that arr[m] is part of it
int maxCrossingSum(int arr[], int l, int m, int h) {

    // Include elements on left of mid.
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; i--)
    {
        sum = sum + arr[i];
        if (sum > left_sum)
            left_sum = sum;
    }

    // Include elements on right of mid
    sum = 0;
    int right_sum = INT_MIN;
    for (int i = m+1; i <= h; i++)
    {
        sum = sum + arr[i];
        if (sum > right_sum)
            right_sum = sum;
    }

    // Return sum of elements on left and right of mid
    return left_sum + right_sum;
}

// Returns sum of maxium sum subarray in aa[l..h]
int maxSubArraySum(int arr[], int l, int h) {

    // Base Case: Only one element
    if (l == h)
        return arr[l];

    // Find middle point
    int m = (l + h)/2;

    /* Return maximum of following three possible cases
       a) Maximum subarray sum in left half
       b) Maximum subarray sum in right half
       c) Maximum subarray sum such that the subarray crosses the midpoint */
    return max(maxSubArraySum(arr, l, m),
               maxSubArraySum(arr, m+1, h),
               maxCrossingSum(arr, l, m, h));
}


class MySolution {
public:
    int maxSubArraySum(int arr[], int left, int right) {

        if (left >= right)
            return arr[left];

        int middle = (left + right) / 2;

        /* recurse on left and right part */
        int left_max  = maxSubArraySum(arr, left, middle);
        int right_max = maxSubArraySum(arr, middle + 1, right);

        /* compute max sum across middle point */
        int sum = 0;
        int temp_left_max = INT_MIN;
        for (int i = middle; i >= left; i--) {
            sum += arr[i];
            if (sum > temp_left_max)
                temp_left_max = sum;
        }

        sum = 0;
        int temp_right_max = INT_MIN;
        for (int i = middle+1; i <= right; i++) {
            sum += arr[i];
            if (sum > temp_right_max)
                temp_right_max = sum;
        }

        return max(left_max, right_max, temp_left_max+temp_right_max);
    }
private:
    // A utility funtion to find maximum of two integers
    int max(int a, int b) { return (a > b)? a : b; }

    // A utility funtion to find maximum of three integers
    int max(int a, int b, int c) { return max(max(a, b), c); }
};

/* Driver program to test maxSubArraySum */
int main() {

    // int arr[] = {2, 3, 4, 5, 7};
    int arr[] = {-2, -5, 6, -2, -3, 1, 5, -6};
    int n = sizeof(arr)/sizeof(arr[0]);
    MySolution solution;

    int max_sum = solution.maxSubArraySum(arr, 0, n-1);
    printf("Maximum contiguous sum is %d\n", max_sum);

    return 0;
}
