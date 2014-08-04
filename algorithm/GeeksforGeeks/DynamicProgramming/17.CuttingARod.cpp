// http://www.geeksforgeeks.org/dynamic-programming-set-13-cutting-a-rod/

// Given a rod of length n inches and an array of prices that contains prices
// of all pieces of size smaller than n. Determine the maximum value obtainable
// by cutting up the rod and selling the pieces. For example, if length of the
// rod is 8 and the values of different pieces are given as following, then the
// maximum obtainable value is 22 (by cutting in two pieces of lengths 2 and 6)
// length   | 1   2   3   4   5   6   7   8
// --------------------------------------------
// price    | 1   5   8   9  10  17  17  20

// And if the prices are as following, then the maximum obtainable value is 24
// (by cutting in eight pieces of length 1)
// length   | 1   2   3   4   5   6   7   8
// --------------------------------------------
// price    | 3   5   8   9  10  17  17  20

#include <stdio.h>
#include <limits.h>


// A utility function to get the maximum of two integers
int max(int a, int b) { return (a > b)? a : b;}

/* Returns the best obtainable price for a rod of length n and
   price[] as prices of different pieces */
int cutRod(int price[], int n)
{
   if (n <= 0)
     return 0;
   int max_val = INT_MIN;

   // Recursively cut the rod in different pieces and compare different
   // configurations
   for (int i = 0; i<n; i++)
         max_val = max(max_val, price[i] + cutRod(price, n-i-1));

   return max_val;
}



class MySolution {
public:
    // `n` is the size of rod; array is the value of each pieces
    int cutRod(int price[], int n) {

        if (n <= 0) {
            return 0;
        } else if (n == 1) {
            return price[0];
        }

        int max_val = -1;
        // when total size is `n`, cut to size `i` and `n-i`, and we get
        // the value of size `i`, continuing cut `n-i` part
        for (int i = 1; i <= n; i++) {
            int res = cutRod(price, n-i) + price[i-1];
            if (res > max_val) {
                max_val = res;
            }
        }

        return max_val;
    }

    int cutRodDP(int price[], int n) {

        int table[n+1];      // table[i] means best value for length i

        table[0] = 0;           // rod length 0 => 0
        table[1] = price[0];    // rod length 1 => price[0]

        for (int i = 2; i <= n; i++) { // all rod length
            table[i] = price[i-1];
            for (int j = 1; j < i; j++) { // different cut point
                table[i] = max(table[i], table[i-j] + table[j]);
            }
        }

        return table[n];
    }

private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
};



/* Driver program to test above functions */
int main() {

    MySolution solution;
    int arr[] = {1, 5, 8, 9, 10, 17, 17, 20, 22, 24, 28};
    int size = sizeof(arr)/sizeof(arr[0]);

    printf("Maximum Obtainable Value is %d\n", cutRod(arr, size));
    printf("Maximum Obtainable Value is %d\n", solution.cutRod(arr, size));
    printf("Maximum Obtainable Value is %d\n", solution.cutRodDP(arr, size));
    return 0;
}
