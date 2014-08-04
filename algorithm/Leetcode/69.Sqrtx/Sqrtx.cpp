// Implement int sqrt(int x).

// Compute and return the square root of x.

#include <iostream>
using namespace std;


class Solution {
public:
    int sqrt(int x) {

        if (x <= 0)
            return x;

        // binary search variation
        int left = 1, right = x;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int div = x / mid;
            if (div == mid) {
                return mid;
            } else if (div < mid) { // mid is too big
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // we need to return `right`, consider x = 6. When "left == right", we
        // get div = 6/2 =3, mid = 2. Even though 2 is then answer, the program
        // won't find it, instead, it increases left. But this violate whild
        // condition, and this time, `right` is the one we need. Therefore, we
        // can also return `left-1`.
        return right;
    }

    int sqrtSlow(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (x <= 0)
            return x;

        int n = 0;
        long y = x;
        while (x != 1) {
            x = x >> 1;
            n++;
        }

        if (n % 2 == 1) {
            n--;
        }

        long guess = 1 << n/2;
        cout << guess << endl;
        while (true) {
            if (guess * guess > y) {
                return guess - 1;
            }
            guess++;
        }

        return guess;
    }
};


int main(void) {

    Solution solution;

    cout << solution.sqrt(6) << endl;
    return 0;
}
