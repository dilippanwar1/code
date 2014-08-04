// Determine whether an integer is a palindrome. Do this without extra space.

#include <iostream>
using namespace std;


class Solution {
public:

    // reverse `x` may overflow
    bool isPalindrome(int x) {

        if (x < 0)
            return false;

        int reverse = 0;        // register value
        int number = x;
        while (number != 0) {
            reverse = reverse * 10 + number % 10;
            number = number / 10;
        }

        return (x == reverse);
    }


    bool isPalindrome2(int x) {

        if (x < 0)
            return false;

        int div = 1;
        while (x / div >= 10)
            div *= 10;

        while (x != 0) {
            int l = x / div;
            int r = x % 10;
            if (l != r)
                return false;
            x = (x % div) / 10;
            div /= 100;
        }

        return true;
    }
};


int main(void) {

    Solution solution;
    cout << solution.isPalindrome(23442) << endl;
    cout << solution.isPalindrome(-11) << endl;
}
