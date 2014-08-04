// Implement atoi to convert a string to an integer.

// Hint: Carefully consider all possible input cases. If you want a challenge,
// please do not see below and ask yourself what are the possible input cases.

// Notes: It is intended for this problem to be specified vaguely (ie, no given
// input specs). You are responsible to gather all the input requirements up front.


#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;


class Solution {
public:
    int atoi(const char *str) {

        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        const char *ptr_h = str; // point to
        char sign = 1;

        // remove leading whitespaces
        while (*ptr_h == ' ') {
            ptr_h++;
        }

        // handle sign
        if (*ptr_h == '-') {
            sign = -1;
            ptr_h++;
        } else if (*ptr_h == '+') {
            ptr_h++;
        }

        long long number = 0;
        while (*ptr_h != '\0') {
            if (!isdigit(*ptr_h)) {
                return sign * number; // return whatever we see so far
            }
            char digit = *ptr_h - '0';
            number = number * 10 + digit;
            if (sign == -1 && -number < INT_MIN) {
                return INT_MIN;
            } else if (sign == 1 && number > INT_MAX) {
                return INT_MAX;
            }
            ptr_h++;
        }

        return number * sign;
    }
};



int main(void) {

    Solution solution;
    cout << solution.atoi("2147483648") << endl;
}
