// Implement pow(x, n).

#include <iostream>
using namespace std;


class Solution {
public:
    double pow(double x, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n == 0)
            return 1;
        if (n == 1)
            return x;
        if (n == -1)
            return 1/x;

        if (n % 2 == 0) {
            double tmp = pow(x, n/2);
            return tmp * tmp;
        } else if (n % 2 == 1) {
            double tmp = pow(x, (n-1)/2);
            return tmp * tmp * x;
        } else if (n % 2 == -1) { // remainder is negative one
            double tmp = pow(x, (n+1)/2);
            return tmp * tmp / x;
        }
    }
};


int main(void) {

    Solution solution;
    cout << solution.pow(2, -3) << endl;

    return 0;
}
