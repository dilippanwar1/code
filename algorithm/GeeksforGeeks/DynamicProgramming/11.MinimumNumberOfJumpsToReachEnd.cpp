// http://www.geeksforgeeks.org/minimum-number-of-jumps-to-reach-end-of-a-given-array/

// Given an array of integers where each element represents the max number of
// steps that can be made forward from that element. Write a function to return
// the minimum number of jumps to reach the end of the array (starting from the
// first element). If an element is 0, then cannot move through that element.

// Example:

// Input: arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9}
// Output: 4 ( 1 -> 3 -> 8 ->9 )
// First element is 1, so can only go to 3. Second element is 3, so can make at
// most 3 steps eg to 5 or 8 or 9.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
using namespace std;


// Returns minimum number of jumps to reach arr[h] from arr[l]
int minJumps(int arr[], int l, int h)
{
    // Base case: when source and destination are same
    if (h == l)
        return 0;

    // When nothing is reachable from the given source
    if (arr[l] == 0)
        return INT_MAX;

    // Traverse through all the points reachable from arr[l]. Recursively
    // get the minimum number of jumps needed to reach arr[h] from these
    // reachable points.
    int min = INT_MAX;
    for (int i = l+1; i <= h && i <= l + arr[l]; i++)
    {
        int jumps = minJumps(arr, i, h);
        if(jumps != INT_MAX && jumps + 1 < min)
            min = jumps + 1;
    }

    return min;
}


// Returns minimum number of jumps to reach arr[n-1] from arr[0]
int minJumpsDP(int arr[], int n)
{
    int *jumps = new int[n];  // jumps[n-1] will hold the result
    int i, j;

    if (n == 0 || arr[0] == 0)
        return INT_MAX;

    jumps[0] = 0;

    // Find the minimum number of jumps to reach arr[i]
    // from arr[0], and assign this value to jumps[i]
    for (i = 1; i < n; i++)
    {
        jumps[i] = INT_MAX;
        for (j = 0; j < i; j++)
        {
            if (i <= j + arr[j] && jumps[j] != INT_MAX)
            {
                jumps[i] = jumps[j] + 1;
                break;
            }
        }
    }
    return jumps[n-1];
}


class MySolution {
public:
    // Returns minimum number of jumps to reach arr[h] from arr[l]
    int minJumps(int arr[], int l, int h) {

        // Base case, when src and dst are the same
        if (l == h)
            return 0;

        int min_sofar = INT_MAX;
        // We need to use i>=l instead of i>l to hit base case
        for (int i = h-1; i >= l; i--) {
            if (h - i <= arr[i]) { // we can reach arr[h] by arr[i]
                int m = minJumps(arr, l, i);
                if (m + 1 < min_sofar) {
                    min_sofar = m + 1;
                }
            }
        }

        return min_sofar;
    }

    int minJumpsDP(int arr[], int l, int h) {

        // start from 0
        int table[h-l+1];

        // initialize table array
        table[0] = 0;           // first element should be 0
        for (int i = 1; i <= h-l; i++) {
            table[i] = INT_MAX - 100; // set to max
        }

        // bottom up
        for (int i = l + 1; i <= h; i++) {
            for (int j = l; j < i; j++) {
                // if ith element can be reached and steps are less, update
                if (j + arr[j] >= i && table[j-l] + 1 < table[i-l]) {
                    table[i-l] = table[j-l] + 1;
                }
            }
        }

        return table[h-l];
    }
};


// Driver program to test above function
int main() {

    MySolution solution;
    int arr[] = {1, 3, 6, 3, 2, 3, 6, 1, 2, 5, 3, 4, 5, 1, 4, 9, 3};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Minimum number of jumps is %d\n", solution.minJumps(arr, 0, n-1));
    printf("Minimum number of jumps is %d\n", solution.minJumpsDP(arr, 0, n-1));
    printf("Minimum number of jumps is %d\n", minJumpsDP(arr, n));

    return 0;
}
