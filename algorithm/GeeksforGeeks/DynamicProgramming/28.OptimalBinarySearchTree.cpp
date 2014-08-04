// http://www.geeksforgeeks.org/dynamic-programming-set-24-optimal-binary-search-tree/

// Given a sorted array keys[0.. n-1] of search keys and an array freq[0.. n-1]
// of frequency counts, where freq[i] is the number of searches to keys[i].
// Construct a binary search tree of all keys such that the total cost of all
// the searches is as small as possible.

// Let us first define the cost of a BST. The cost of a BST node is level of
// that node multiplied by its frequency. Level of root is 1.

// Example 1
// Input:  keys[] = {10, 12}, freq[] = {34, 50}
// There can be following two possible BSTs
//         10                       12
//           \                     /
//            12                 10
//         I                        II
// Frequency of searches of 10 and 12 are 34 and 50 respectively.
// The cost of tree I is 34*1 + 50*2 = 134
// The cost of tree II is 50*1 + 34*2 = 118

// Example 2
// Input:  keys[] = {10, 12, 20}, freq[] = {34, 8, 50}
// There can be following possible BSTs
//     10                12                 20         10              20
//       \             /    \              /             \            /
//       12          10     20           12               20         10
//         \                            /                 /           \
//          20                        10                12             12
//     I                 II               III          IV              V
// Among all possible BSTs, cost of the fifth BST is minimum.
// Cost of the fifth BST is 1*50 + 2*34 + 3*8 = 142

#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>


// A utility function to get sum of array elements freq[i] to freq[j]
int sum(int freq[], int i, int j);

// A recursive function to calculate cost of optimal binary search tree
int optCost(int freq[], int i, int j)
{
    // Base cases
    if (j < i)      // If there are no elements in this subarray
        return 0;
    if (j == i)     // If there is one element in this subarray
        return freq[i];

    // Get sum of freq[i], freq[i+1], ... freq[j]
    int fsum = sum(freq, i, j);

    // Initialize minimum value
    int min = INT_MAX;

    // One by one consider all elements as root and recursively find cost
    // of the BST, compare the cost with min and update min if needed
    for (int r = i; r <= j; ++r)
    {
        int cost = optCost(freq, i, r-1) + optCost(freq, r+1, j);
        if (cost < min)
            min = cost;
    }

    // Return minimum value
    return min + fsum;
}

// The main function that calculates minimum cost of a Binary Search Tree.
// It mainly uses optCost() to find the optimal cost.
int optimalSearchTree(int keys[], int freq[], int n)
{
    // Here array keys[] is assumed to be sorted in increasing order.
    // If keys[] is not sorted, then add code to sort keys, and rearrange
    // freq[] accordingly.
    return optCost(freq, 0, n-1);
}

/* A Dynamic Programming based function that calculates minimum cost of
   a Binary Search Tree. */
int optimalSearchTreeDP(int keys[], int freq[], int n)
{
    /* Create an auxiliary 2D matrix to store results of subproblems */
    int cost[n][n];

    /* cost[i][j] = Optimal cost of binary search tree that can be
       formed from keys[i] to keys[j].
       cost[0][n-1] will store the resultant cost */

    // For a single key, cost is equal to frequency of the key
    for (int i = 0; i < n; i++)
        cost[i][i] = freq[i];

    // Now we need to consider chains of length 2, 3, ... .
    // L is chain length.
    for (int L=2; L<=n; L++)
    {
        // i is row number in cost[][]
        for (int i=0; i<=n-L+1; i++)
        {
            // Get column number j from row number i and chain length L
            int j = i+L-1;
            cost[i][j] = INT_MAX;

            // Try making all keys in interval keys[i..j] as root
            for (int r=i; r<=j; r++)
            {
                // c = cost when keys[r] becomes root of this subtree
                int c = ((r > i)? cost[i][r-1]:0) +
                    ((r < j)? cost[r+1][j]:0) +
                    sum(freq, i, j);
                if (c < cost[i][j])
                    cost[i][j] = c;
            }
        }
    }
    return cost[0][n-1];
}


// A utility function to get sum of array elements freq[i] to freq[j]
int sum(int freq[], int i, int j)
{
    int s = 0;
    for (int k = i; k <=j; k++)
        s += freq[k];
    return s;
}


class MySolution
{
public:
    int optimalSearchTree(int keys[], int freq[], int n) {

        // create two auxiliary arrays
        int **cache = new int *[n];
        for (int i = 0; i < n; i++) {
            cache[i] = new int[n];
        }
        int **sums = new int *[n];
        for (int i = 0; i < n; i++) {
            sums[i] = new int[n];
        }

        // init the two arrays
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (i == j) {
                    sums[i][j] = freq[i];
                } else {
                    sums[i][j] = sums[i][j-1] + freq[j];
                }
                cache[i][j] = -1;
            }
        }
        return optimalSearchTreeHelper(freq, 0, n-1, cache, sums);
    }

    int optimalSearchTreeDP(int keys[], int freq[], int n) {
    }
private:
    int optimalSearchTreeHelper(int freq[], int left, int right,
                                int **cache, int **sums) {

        // base cases
        if (left > right) {     // no element in sub-tree
            return 0;
        } else if (left == right) { // one element in sub-tree
            return freq[left];
        }

        if (cache[left][right] != -1) {
            return cache[left][right];
        }

        int cost = INT_MAX;
        for (int i = left; i <= right; i++) {
            int iAsRootCost =
                optimalSearchTreeHelper(freq, left, i-1, cache, sums) +
                optimalSearchTreeHelper(freq, i+1, right, cache, sums);
            if (iAsRootCost < cost) {
                cost = iAsRootCost;
            }
        }

        // We should return cost + sum(freq, left, right). Actually, when we
        // compute iAsRootCost, we need to do like below:
        // int iAsRootCost = optimalSearchTreeHelper(freq, left, i-1) +
        //     sum(freq, left, i-1) +
        //     optimalSearchTreeHelper(freq, i+1, right) +
        //     sum(freq, i+1, rigth) +
        //     freq[i];
        // The two sums are due to the fact sub-tree are one more level than
        // now, the freq[i] is i's cost as root. Essentially, we divide sub-
        // problom as follow:
        // (a + 1) * x + (b + 1) * y = a * x + b * y + sum(x,y)
        cache[left][right] = cost + sums[left][right];
        return cache[left][right];
    }

    int sum(int freq[], int i, int j) {

        int total = 0;
        for (int k = i; k <= j; k++) {
            total += freq[k];
        }
        return total;
    }
};


// Driver program to test above functions
int main()
{
    MySolution solution;
    int keys[] = {10, 12, 20, 23, 24, 26};
    int freq[1000];// = {34, 8, 50, 34, 10, 40};
    int n = sizeof(freq)/sizeof(freq[0]);

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        freq[i] = rand() % n;
    }

    printf("Cost of Optimal BST is %d\n",
           solution.optimalSearchTree(keys, freq, n));
    // printf("Cost of Optimal BST is %d\n",
    //        optimalSearchTreeDP(keys, freq, n));
    return 0;
}
