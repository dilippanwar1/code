// http://www.geeksforgeeks.org/dynamic-programming-set-18-partition-problem/

// Partition problem is to determine whether a given set can be partitioned
// into two subsets such that the sum of elements in both subsets is same.

// Examples
// arr[] = {1, 5, 11, 5}
// Output: true
// The array can be partitioned as {1, 5, 5} and {11}

// arr[] = {1, 5, 3}
// Output: false
// The array cannot be partitioned into equal sum sets.


#include <stdio.h>

// Returns true if arr[] can be partitioned in two subsets of
// equal sum, otherwise false
bool findPartition(int arr[], int n)
{
    int sum = 0;
    int i, j;

    // Caculcate sun of all elements
    for (i = 0; i < n; i++)
        sum += arr[i];

    if (sum%2 != 0)
        return false;

    bool part[sum/2+1][n+1];

    // initialize top row as true
    for (i = 0; i <= n; i++)
        part[0][i] = true;

    // initialize leftmost column, except part[0][0], as 0
    for (i = 1; i <= sum/2; i++)
        part[i][0] = false;

    // Fill the partition table in botton up manner
    for (i = 1; i <= sum/2; i++)
    {
        for (j = 1; j <= n; j++)
        {
            part[i][j] = part[i][j-1];
            if (i >= arr[j-1])
                part[i][j] = part[i][j] || part[i - arr[j-1]][j-1];
        }
    }

    // uncomment this part to print table
    // for (i = 0; i <= sum/2; i++)
    // {
    //     for (j = 0; j <= n; j++)
    //         printf ("%4d", part[i][j]);
    //     printf("\n");
    // }

    return part[sum/2][n];
}


class MySolution {
public:
    bool findPartition(int arr[], int n) {

        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
        }

        // suppose on subset sum is x, the other subset sum is y, then:
        //    x = y, x + y = sum => x = sum/2, y = sum/2;
        if (sum % 2 == 1) {
            return false;
        }

        // find two subsets, both sum to sum/2
        return isSubsetSum(arr, n-1, sum/2);
    }

    // restrictions, sum is small, no negtive
    bool findPartitionDP(int arr[], int n) {

        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
        }

        if (sum % 2 == 1) {
            return false;
        }

        // table[i][j] means for arr[0...j], is there a subset to i
        bool table[sum/2+1][n+1];

        // all false
        for (int i = 0; i <= sum/2; i++) {
            for (int j = 0; j <= n; j++) {
                table[i][j] = false;
            }
        }

        // sum = 0 is true, it's the base case
        for (int i = 0; i <= n; i++) {
            table[0][i] = true;
        }

        for (int i = 1; i <= sum/2; i++) {
            for (int j = 1; j <= n; j++) {
                table[i][j] = table[i][j-1] ||
                    (i-arr[j-1] >= 0 && table[i-arr[j-1]][j-1]);
            }
        }

        return table[sum/2][n];
    }
private:
    bool isSubsetSum(int arr[], int end, int sum) {

        // find subset sum using arr[0...end]
        if (end == 0) {
            if (sum == arr[0]) {
                return true;
            } else {
                return false;
            }
        }

        if (sum == 0) {
            return true;
        }

        // if arr[end] > sum, we have to give up current value
        if (arr[end] > sum) {
            return isSubsetSum(arr, end-1, sum);
        }

        // two choices: use current value and do not use it
        return isSubsetSum(arr, end-1, sum) ||
            isSubsetSum(arr, end-1, sum-arr[end]);
    }
};


// Driver program to test above funtion
int main()
{
    MySolution solution;
    int arr[] = {3, 1, 1, 2, 2, 3,1,3,4,2,43,45,34,5};
    int n = sizeof(arr)/sizeof(arr[0]);

    if (findPartition(arr, n) == true) {
        printf("Can be divided into two subsets of equal sum\n");
    } else {
        printf("Can not be divided into two subsets of equal sum\n");
    }

    if (solution.findPartition(arr, n) == true) {
        printf("Can be divided into two subsets of equal sum\n");
    } else {
        printf("Can not be divided into two subsets of equal sum\n");
    }

    if (solution.findPartitionDP(arr, n) == true) {
        printf("Can be divided into two subsets of equal sum\n");
    } else {
        printf("Can not be divided into two subsets of equal sum\n");
    }

    return 0;
}
