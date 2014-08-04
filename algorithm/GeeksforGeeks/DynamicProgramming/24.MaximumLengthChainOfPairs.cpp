// http://www.geeksforgeeks.org/dynamic-programming-set-20-maximum-length-chain-of-pairs/

// You are given n pairs of numbers. In every pair, the first number is always
// smaller than the second number. A pair (c, d) can follow another pair (a, b)
// if b < c. Chain of pairs can be formed in this fashion. Find the longest
// chain which can be formed from a given set of pairs.

// For example, if the given pairs are { {5, 24}, {39, 60}, {15, 28}, {27, 40},
// {50, 90} }, then the longest chain that can be formed is of length 3, and
// the chain is {{5, 24}, {27, 40}, {50, 90}}

// The given problem is also a variation of Activity Selection problem and can
// be solved in (nLogn) time. To solve it as a activity selection problem,
// consider the first element of a pair as start time in activity selection
// problem, and the second element of pair as end time.

#include <stdio.h>
#include <stdlib.h>


// Structure for a pair
struct pair {
    int a;
    int b;
};


// This function assumes that arr[] is sorted in increasing order
// according the first (or smaller) values in pairs.
int maxChainLength( struct pair arr[], int n)
{
    int i, j, max = 0;
    int *mcl = (int*) malloc ( sizeof( int ) * n );

    /* Initialize MCL (max chain length) values for all indexes */
    for ( i = 0; i < n; i++ )
        mcl[i] = 1;

    /* Compute optimized chain length values in bottom up manner */
    for ( i = 1; i < n; i++ )
        for ( j = 0; j < i; j++ )
            if ( arr[i].a > arr[j].b && mcl[i] < mcl[j] + 1)
                mcl[i] = mcl[j] + 1;

    // mcl[i] now stores the maximum chain length ending with pair i

    /* Pick maximum of all MCL values */
    for ( i = 0; i < n; i++ )
        if ( max < mcl[i] )
            max = mcl[i];

    /* Free memory to avoid memory leak */
    free( mcl );

    return max;
}


int compare(const void *obj1, const void * obj2) {
    return (*(pair*)obj1).b - (*(pair*)obj2).b;
}

class MySolution {
public:
    int maxChainLength(pair arr[], int n) {

        int table[n];
        int max = 1;

        table[0] = 1;
        for (int i = 1; i < n; i++) {
            table[i] = 1;
            for (int j = 0; j < i; j++) { // variation of LIS
                if (arr[j].b < arr[i].a && table[i] < table[j] + 1) {
                    table[i] = table[j] + 1;
                }
            }
            if (table[i] > max) {
                max = table[i];
            }
        }

        return max;
    }

    int maxChainLengthGD(pair arr[], int n) {

        // sort array based on its finishing time
        qsort(arr, n, sizeof(arr[0]), compare);

        int i = 0;
        int count = 0;
        for (int j = 1; j < n; j++) {
            if (arr[j].a > arr[i].b) {
                count++;
                i = j;
            }
        }

        return count;
    }

private:
    void printPair(pair arr[], int n) {
        for (int i = 0; i < n; i++) {
            printf("(%d, %d) ", arr[i].a, arr[i].b);
        }
        printf("\n");
    }
};


/* Driver program to test above function */
int main()
{
    struct pair arr[] = { {19, 24}, {15, 25},
                          {27, 40}, {50, 60},
                          {17, 20}, {25, 63},
                          {14, 18}, {53, 100},
                          {114, 118}, {153, 200},
                          {21, 42}, {59, 130} };
    int n = sizeof(arr)/sizeof(arr[0]);
    MySolution solution;

    printf("Length of maximum size chain is %d\n",
           maxChainLength(arr, n));
    printf("Length of maximum size chain is %d\n",
           solution.maxChainLength(arr, n));
    printf("Length of maximum size chain is %d\n",
           solution.maxChainLengthGD(arr, n));
    return 0;
}
