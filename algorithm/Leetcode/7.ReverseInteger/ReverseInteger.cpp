// Reverse digits of an integer.

// Example1: x = 123, return 321
// Example2: x = -123, return -321

#include <iostream>
using namespace std;


class Solution {
public:
    int reverse(int x) {

        int result = 0;

        while (x != 0) {
            result = result * 10 + x % 10;
            x = x / 10;
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    int x;

    cin >> x;
    cout << solution.reverse(x) << endl;
}
