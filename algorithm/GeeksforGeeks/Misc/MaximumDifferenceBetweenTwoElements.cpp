// http://www.geeksforgeeks.org/maximum-difference-between-two-elements/

// Given an array arr[] of integers, find out the difference between any two
// elements such that larger element appears after the smaller number in arr[].

// Examples: If array is [2, 3, 10, 6, 4, 8, 1] then returned value should be
// 8 (Diff between 10 and 2). If array is [ 7, 9, 5, 6, 3, 2 ] then returned
// value should be 2 (Diff between 7 and 9)


#include <stdio.h>
#include <iostream>
using namespace std;


int maxDiff(int arr[], int size) {

    if (size == 0 || size == 1)
        return 0;

    int maxDiff_val = arr[1] - arr[0], min_sofar = arr[0];
    for (int i = 1; i < size; i++) {
        maxDiff_val = max(maxDiff_val, arr[i] - min_sofar);
        min_sofar = min(min_sofar, arr[i]);
    }

    return maxDiff_val;
}


/* Driver program to test above function */
int main()
{
    //int arr[] = {1, 2, 6, 80, 100};
    //int arr[] = {2, 3, 10, 6, 4, 8, 1};
    int arr[] = {8, 2, 6, 3, 100};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Maximum difference is %d\n",  maxDiff(arr, size));
    return 0;
}
