// http://www.geeksforgeeks.org/dynamic-programming-set-14-maximum-sum-increasing-subsequence/

// Given an array of n positive integers. Write a program to find the sum of
// maximum sum subsequence of the given array such that the intgers in the
// subsequence are sorted in increasing order. For example, if input is
// {1, 101, 2, 3, 100, 4, 5}, then output should be 106 (1 + 2 + 3 + 100), if
// the input array is {3, 4, 5, 10}, then output should be 22 (3 + 4 + 5 + 10)
// and if the input array is {10, 5, 4, 3}, then output should be 10.

#include <iostream>
using namespace std;


class MySolution {
public:

    int maxSumIS(int arr[], int n) {

        int max_sum = INT_MIN;
        int table[n];

        table[0] = arr[0];
        for (int i = 1; i < n; i++) {
            table[i] = INT_MIN;
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[i] > arr[j]) {
                    table[i] = max(table[i], table[j] + arr[i]);
                }
            }
            if (table[i] > max_sum) {
                max_sum = table[i];
            }
        }

        return max_sum;
    }

private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
};


/* Driver program to test above function */
int main() {

    MySolution solution;
    int arr[] = {2, 3, 100, 4, 5, 10};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Sum of maximum sum increasing subsequence is %d\n",
           solution.maxSumIS(arr, n));

    return 0;
}
