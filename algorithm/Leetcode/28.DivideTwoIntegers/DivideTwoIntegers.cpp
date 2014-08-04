// Divide two integers without using multiplication, division and mod operator.

#include <iostream>
using namespace std;


class Solution {
public:
    int divide(int dividend, int divisor) {

        long long a = abs(dividend);;
        long long b = abs(divisor);

        long long ret = 0;
        while (a >= b) {
            long long c = b;
            for (int i = 0; a >= c; c <<= 1, i++) {
                a -= c;
                ret += 1 << i;
            }
        }

        // return positive/negtive result according to signs
        return ((dividend^divisor)>>31) ? (-ret) : (ret);
    }

    int divide2(int dividend, int divisor) {

        // handle signess
        int sign = (dividend < 0 ? -1 : 1) * (divisor  < 0 ? -1 : 1);
        unsigned long long temp1 = abs((long long)dividend);
        unsigned long long temp2 = abs((long long)divisor);
        unsigned long numOfDivisor = 1;

        while (temp1 > temp2) {
            temp2 <<= 1;
            numOfDivisor <<= 1;
        }

        int result = 0;
        while (temp1 >= abs((long long)divisor)) {

            while (temp1 >= temp2) {
                result += numOfDivisor;
                temp1 -= temp2;
            }

            numOfDivisor >>= 1;
            temp2 >>= 1;
        }

        return sign > 0 ? result : -result;
    }

    // divide(8, 3) = 2
    int divideTooSlow(int dividend, int divisor) {

        int sign;
        if (dividend < 0 && divisor < 0) {
            dividend = -dividend;
            divisor = -divisor;
            sign = 1;
        } else if (dividend < 0) {
            dividend = -dividend;
            sign = -1;
        } else if (divisor < 0) {
            divisor = -divisor;
            sign = -1;
        }


        int res = 0;
        while (dividend >= divisor) {
            res += 1;
            dividend -= divisor;
        }

        return sign > 0 ? res : -res;
    }
};


int main(void) {
    Solution solution;
    printf("%d\n", solution.divide(2147483647,2));
    printf("%d\n", solution.divide2(2147483647,2));
    printf("%d\n", solution.divide(1033759895,2147483647));
    printf("%d\n", solution.divide2(1033759895,2147483647));
}
