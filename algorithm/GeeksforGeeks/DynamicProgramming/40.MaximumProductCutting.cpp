#include <stdlib.h>
#include <iostream>
using namespace std;

int max(int a, int b) { return (a > b)? a : b;}
int max(int a, int b, int c) { return max(a, max(b, c));}

// The main function that returns maximum product obtainable
// from a rope of length n
int maxProd(int n)
{
    // Base cases
    if (n == 0 || n == 1) return 0;

    // Make a cut at different places and take the maximum of all
    int max_val = 0;
    for (int i = 1; i < n; i++)
        max_val = max(max_val, i*(n-i), maxProd(n-i)*i);

    // Return the maximum of all values
    return max_val;
}


class MySolution {
public:
    int maxProd(int n) {

        if (n == 1 || n == 2)
            return n;

        int max_p = -1;
        for (int i = 1; i < n; i++) {
            int left = maxProd(i);
            int right = maxProd(n-i);
            max_p = max(left * right, max_p); // left & right max
            max_p = max(left * (n-i), max_p); // left whole and right cut
            max_p = max(i * right, max_p);    // left cut and right whole
        }

        return max_p;
    }

    int maxProd2(int n) {

        int cache[n+1];
        for (int i = 0; i <= n; i++)
            cache[i] = -1;
        cache[0] = 1;
        cache[1] = 1;
        cache[2] = 2;

        return maxProd2Helper(n, cache);
    }

    int maxProd2Helper(int n, int cache[]) {

        if (cache[n] != -1)
            return cache[n];

        if (n == 1 || n == 2)
            return n;

        int max_p = -1;
        for (int i = 1; i < n; i++) {
            max_p = max(max_p, i * (n-i));
            max_p = max(max_p, maxProd2Helper(n-i, cache) * i);
        }

        cache[n] = max_p;
        return max_p;
    }
};


/* Driver program to test above function */
int main() {

    MySolution solution;
    int input = 10;
    cout << solution.maxProd2(20) << endl;
    cout << maxProd(20) << endl;
    return 0;
}
