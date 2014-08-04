// http://www.geeksforgeeks.org/length-of-the-longest-arithmatic-progression-in-a-sorted-array/

// Given a set of numbers, find the Length of the Longest Arithmetic Progression
// (LLAP) in it.

// Examples:

// set[] = {1, 7, 10, 15, 27, 29}
// output = 3
// The longest arithmetic progression is {1, 15, 29}

// set[] = {5, 10, 15, 20, 25, 30}
// output = 6
// The whole set is in AP

// For simplicity, we have assumed that the given set is sorted. We can always
// add a pre-processing step to first sort the set and then apply the below
// algorithms.

#include <iostream>
#include <string.h>
using namespace std;


// Returns length of the longest AP subset in a given set
int lengthOfLongestAP(int set[], int n)
{
    if (n <= 2)  return n;

    // Create a table and initialize all values as 2. The value of
    // L[i][j] stores LLAP with set[i] and set[j] as first two
    // elements of AP. Only valid entries are the entries where j>i
    int L[n][n];
    int llap = 2;  // Initialize the result

    // Fill entries in last column as 2. There will always be
    // two elements in AP with last number of set as second
    // element in AP
    for (int i = 0; i < n; i++)
        L[i][n-1] = 2;

    // Consider every element as second element of AP
    for (int j=n-2; j>=1; j--)
    {
        // Search for i and k for j
        int i = j-1, k = j+1;
        while (i >= 0 && k <= n-1)
        {
            if (set[i] + set[k] < 2*set[j])
                k++;

            // Before changing i, set L[i][j] as 2
            else if (set[i] + set[k] > 2*set[j])
            {   L[i][j] = 2, i--;   }

            else
            {
                // Found i and k for j, LLAP with i and j as first two
                // elements is equal to LLAP with j and k as first two
                // elements plus 1. L[j][k] must have been filled
                // before as we run the loop from right side
                L[i][j] = L[j][k] + 1;

                // Update overall LLAP, if needed
                llap = max(llap, L[i][j]);

                // Change i and k to fill more L[i][j] values for
                // current j
                i--; k++;
            }
        }

        // If the loop was stopped due to k becoming more than
        // n-1, set the remaining entties in column j as 2
        while (i >= 0)
        {
            L[i][j] = 2;
            i--;
        }
    }
    return llap;
}


class MySolution {
public:
    int lengthOfLongestAP(int set[], int n) {

        int max_len = 0;
        for (int i = 0; i < n; i++) {
            int new_len = lengthOfLongestAPHelper(set, i, -1) + 1;
            if (new_len > max_len) {
                max_len = new_len;
            }
        }

        return max_len;
    }

    int lengthOfLongestAPDP(int set[], int n) {

        int max_val = set[n-1], min_val = set[0];
        int max_len = 1;
        // table[i][j] means for array set[0...i], max length for difference j
        int table[n][max_val-min_val];

        memset(table, 0, sizeof(table));
        for (int i = 0; i < max_val-min_val; i++) {
            table[0][i] = 1;
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                table[i][set[i]-set[j]] = table[j][set[i]-set[j]] + 1;
                if (table[i][set[i]-set[j]] > max_len) {
                    max_len = table[i][set[i]-set[j]];
                }
            }
        }

        return max_len;
    }
private:
    int lengthOfLongestAPHelper(int set[], int n, int diff) {

        if (n == 0) {
            return 0;
        }

        int max_len = 0;
        for (int i = 0; i < n; i++) {
            if (set[n] - set[i] == diff || diff == -1) {
                int new_len = lengthOfLongestAPHelper(
                    set, i, set[n] - set[i]) + 1;
                if (new_len > max_len) {
                    max_len = new_len;
                }
            }
        }

        return max_len;
    }
};



/* Drier program to test above function*/
int main()
{
    MySolution solution;

    int set1[] = {1, 7, 10, 13, 14, 19};
    int n1 = sizeof(set1)/sizeof(set1[0]);
    cout << solution.lengthOfLongestAP(set1, n1) << endl;
    cout << solution.lengthOfLongestAPDP(set1, n1) << endl;
    cout << lengthOfLongestAP(set1, n1) << endl;
    cout << endl;

    int set2[] = {1, 7, 10, 15, 27, 29};
    int n2 = sizeof(set2)/sizeof(set2[0]);
    cout << solution.lengthOfLongestAP(set2, n2) << endl;
    cout << solution.lengthOfLongestAPDP(set2, n2) << endl;
    cout << lengthOfLongestAP(set2, n2) << endl;
    cout << endl;

    int set3[] = {2, 4, 6, 8, 10};
    int n3 = sizeof(set3)/sizeof(set3[0]);
    cout << solution.lengthOfLongestAP(set3, n3) << endl;
    cout << solution.lengthOfLongestAPDP(set3, n3) << endl;
    cout << lengthOfLongestAP(set3, n3) << endl;
    cout << endl;

    int set4[] = {-3, 0, 3, 6, 9, 12, 1500};
    int n4 = sizeof(set4)/sizeof(set4[0]);
    cout << solution.lengthOfLongestAP(set4, n4) << endl;
    cout << solution.lengthOfLongestAPDP(set4, n4) << endl;
    cout << lengthOfLongestAP(set4, n4) << endl;
    cout << endl;

    // int set5[1000];
    // for (int i = 0; i < 1000; i++) {
    //     set5[i] = i * 2 + 1;
    // }
    // int n5 = sizeof(set5)/sizeof(set5[0]);
    // cout << solution.lengthOfLongestAP(set5, n5) << endl;
    // cout << lengthOfLongestAP(set5, n5) << endl;

    return 0;
}
