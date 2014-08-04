// http://www.geeksforgeeks.org/dynamic-programming-subset-sum-problem/

// Given a set of non-negative integers, and a value sum, determine if there
// is a subset of the given set with sum equal to given sum.

// Examples: set[] = {3, 34, 4, 12, 5, 2}, sum = 9
// Output: True  // There is a subset (4, 5) with sum 9.

#include <stdio.h>


class MySolution {
public:
    int isSubsetSum(int set[], int n, int sum) {

        if (n == 0) {
            if (set[0] == sum) {
                printf("%d ", set[0]);
                return true;
            } else {
                return false;
            }
        }

        if (sum < set[n-1]) {
            return isSubsetSum(set, n - 1, sum);
        }

        // do not use current number and use current number
        if (isSubsetSum(set, n - 1, sum) == true) {
            return true;
        } else if (isSubsetSum(set, n - 1, sum - set[n-1]) == true) {
            printf("%d ", set[n-1]);
            return true;
        } else {
            return false;
        }
    }

    int isSubsetSumDP(int set[], int n, int sum) {

        bool table[sum+1][n+1];

        // all false
        for (int i = 0; i <= sum; i++) {
            for (int j = 0; j <= n; j++) {
                table[i][j] = false;
            }
        }

        // sum = 0 is true, it's the base case
        for (int i = 0; i <= n; i++) {
            table[0][i] = true;
        }

        for (int i = 1; i <= sum; i++) {
            for (int j = 1; j <= n; j++) {
                table[i][j] = table[i][j-1] ||
                    (i - set[j-1] >= 0 && table[i - set[j-1]][j-1]);
            }
        }

        return table[sum][n];
    }

    // space efficient
    int isSubsetSumDP2(int set[], int n, int sum) {

        int isSum[sum+1];

        isSum[0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = sum - set[i]; j >= 0; j--) {
                // if sum=j is available, then sum=j+set[i] is also available
                if (isSum[j] == 1) {
                    isSum[j+set[i]] = 1;
                }
            }
            if (isSum[sum] == 1)
                return 1;
        }

        return 0;
    }
};


// Driver program to test above function
int main()
{
    MySolution solution;
    int set[] = {3, 34, 4, 12, 5, 2};
    int sum = 20;
    int n = sizeof(set)/sizeof(set[0]);

    if (solution.isSubsetSum(set, n, sum) == true) {
        printf("Found a subset with given sum\n");
    } else {
        printf("No subset with given sum\n");
    }

    if (solution.isSubsetSumDP(set, n, sum) == true) {
        printf("Found a subset with given sum\n");
    } else {
        printf("No subset with given sum\n");
    }
    return 0;
}
