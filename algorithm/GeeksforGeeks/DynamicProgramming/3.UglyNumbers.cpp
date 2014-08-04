// http://www.geeksforgeeks.org/ugly-numbers/

// Ugly numbers are numbers whose only prime factors are 2, 3 or 5. The sequence
// 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, ... shows the first 11 ugly numbers. By
// convention, 1 is included.
// Write a program to find and print the 150'th ugly number.

// METHOD 1 (Simple)
// Algorithm:
// Loop for all positive integers until ugly number count is smaller than n, if
// an integer is ugly then increment ugly number count.
// To check if a number is ugly, divide the number by greatest divisible powers
// of 2, 3 and 5, if the number becomes 1 then it is an ugly number otherwise not.
// For example, let us see how to check for 300 is ugly or not. Greatest divisible
// power of 2 is 4, after dividing 300 by 4 we get 75. Greatest divisible power
// of 3 is 3, after dividing 75 by 3 we get 25. Greatest divisible power of 5 is
// 25, after dividing 25 by 25 we get 1. Since we get 1 finally, 300 is ugly number.
// This method is not time efficient as it checks for all integers until ugly
// number count becomes n, but space complexity of this method is O(1)

// METHOD 2 (Use Dynamic Programming)
// Intuition:
// Each number needs to be multiplied by 2, 3, 5. But we don't know which one
// is smaller: The smaller number multiplied by 5 or the largest number multiplied
// by 2? You'll have no idea unless you actually try it out, which is exactly what
// you're doing. However, for each of 2, 3 and 5 you advance to the next trial
// only if you're sure that there is no smaller ugly number that can be formed by
// multiplying the other two with the existing ugly number.

#include <stdio.h>
#include <stdlib.h>
#define bool int

/* Function to find minimum of 3 numbers */
unsigned min(unsigned , unsigned , unsigned );

/* This function divides a by greatest divisible power of b */
int maxDivide(int a, int b)
{
    while (a%b == 0)
        a = a/b;
    return a;
}

/* Function to check if a number is ugly or not */
int isUgly(int no)
{
    no = maxDivide(no, 2);
    no = maxDivide(no, 3);
    no = maxDivide(no, 5);

    return (no == 1)? 1 : 0;
}

/* Function to get the nth ugly number*/
int getNthUglyNo(int n)
{
    int i = 1;
    int count = 1;   /* ugly number count */

    /* Check for all integers untill ugly count becomes n */
    while (n > count) {
        i++;
        if (isUgly(i))
            count++;
    }
    return i;
}

/* Function to get the nth ugly number*/
unsigned getNthUglyNo2(unsigned n) {

    unsigned *ugly = (unsigned *)(malloc (sizeof(unsigned)*n));
    unsigned i2 = 0, i3 = 0, i5 = 0;
    unsigned i;
    unsigned next_multiple_of_2 = 2;
    unsigned next_multiple_of_3 = 3;
    unsigned next_multiple_of_5 = 5;
    unsigned next_ugly_no = 1;
    *(ugly+0) = 1;

    for (i=1; i<n; i++) {
        next_ugly_no = min(next_multiple_of_2,
                           next_multiple_of_3,
                           next_multiple_of_5);
        *(ugly+i) = next_ugly_no;
        if (next_ugly_no == next_multiple_of_2) {
            i2 = i2+1;
            next_multiple_of_2 = *(ugly+i2)*2;
        }
        if (next_ugly_no == next_multiple_of_3) {
            i3 = i3+1;
            next_multiple_of_3 = *(ugly+i3)*3;
        }
        if (next_ugly_no == next_multiple_of_5) {
            i5 = i5+1;
            next_multiple_of_5 = *(ugly+i5)*5;
        }
    } /* End of for loop (i=1; i<n; i++) */

    return next_ugly_no;
}

/* Function to find minimum of 3 numbers */
unsigned min(unsigned a, unsigned b, unsigned c) {

    if (a <= b) {
        if (a <= c)
            return a;
        else
            return c;
    }

    if (b <= c)
        return b;
    else
        return c;
}


class MySolution {
public:
    /* Function to get the nth ugly number */
    int getNthUglyNo1(int n) {

        int cur = 1, count = 0;

        while (1) {
            if (isUglyNo(cur)) {
                if (++count == n)
                    return cur;
            }
            cur++;
        }
    }

    int getNthUglyNo2(int n) {

        int array[n];

        // base case
        int next_2_index = 0;
        int next_3_index = 0;
        int next_5_index = 0;
        int next_2 = 2;         // next number which is multiple of 2
        int next_3 = 3;
        int next_5 = 5;
        array[0] = 1;

        for (int i = 1; i < n; i++) {
            array[i] = min(next_2, next_3, next_5);
            // we need to use three if instead of else if, since there
            // are duplicate, e.g. 6 is multiple of 2 and 3.
            if (array[i] == next_2) { // compute next multiple of 2
                next_2_index++;
                next_2 = array[next_2_index] * 2;
            }
            if (array[i] == next_3) { // compute next multiple of 3
                next_3_index++;
                next_3 = array[next_3_index] * 3;
            }
            if (array[i] == next_5 ){ // compute next multiple of 5
                next_5_index++;
                next_5 = array[next_5_index] * 5;
            }
        }

        return array[n-1];
    }

private:
    int isUglyNo(int no) {

        if (no == 1) {
            return 1;
        }

        // test if a number can be divided to 1 with only 2,3,5
        int temp = 0;
        temp = modeall(no, 2);
        temp = modeall(temp, 3);
        temp = modeall(temp, 5);

        return temp == 1 ? 1 : 0;
    }

    int modeall(int x, int b) {
        while (x % b == 0)
            x = x / b;
        return x;
    }

    int min(int a, int b, int c) {

        if (a <= b) {
            if (a <= c)
                return a;
            else
                return c;
        }

        if (b <= c)
            return b;
        else
            return c;
    }
};


/* Driver program to test above functions */
int main() {

    MySolution solution;

    // unsigned int no1 = solution.getNthUglyNo1(150);
    // printf("150th ugly no. is %d\n", no1);

    unsigned int no2 = solution.getNthUglyNo2(150);
    printf("150th ugly no. is %d\n", no2);

    // unsigned int nono = getNthUglyNo(150);
    // printf("150th ugly no. is %d\n", nono);

    return 0;
}
