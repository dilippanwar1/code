// http://www.geeksforgeeks.org/dynamic-programming-set-18-word-wrap/

// Given a sequence of words, and a limit on the number of characters that
// can be put in one line (line width). Put line breaks in the given sequence
// such that the lines are printed neatly. Assume that the length of each word
// is smaller than the line width. The word processors like MS Word do task of
// placing line breaks. The idea is to have balanced lines. In other words, not
// have few lines with lots of extra spaces and some lines with small amount of
// extra spaces.

// The extra spaces includes spaces put at the end of every line except the
// last one. The problem is to minimize the following total cost.
// Cost of a line = (Number of extra spaces in the line) ^ 3
// Total Cost = Sum of costs for all lines

// For example, consider the following string and line width M = 15
//    "Geeks for Geeks presents word wrap problem"
// Following is the optimized arrangement of words in 3 lines
//    "Geeks for Geeks"
//    "presents word"
//    "wrap problem"
// The total extra spaces in line 1, line 2 and line 3 are 0, 2 and 3 respectively.
// So optimal value of total cost is 0 + 2*2 + 3*3 = 13
// Please note that the total cost function is not sum of extra spaces, but sum
// of cubes (or square is also used) of extra spaces. The idea behind this cost
// function is to balance the spaces among lines. For example, consider the
// following two arrangement of same set of words:

// 1) There are 3 lines. One line has 3 extra spaces and all other lines have 0
//    extra spaces. Total extra spaces = 3 + 0 + 0 = 3. Total cost = 3*3*3 +
//    0*0*0 + 0*0*0 = 27.
// 2) There are 3 lines. Each of the 3 lines has one extra space. Total extra
//    spaces = 1 + 1 + 1 = 3. Total cost = 1*1*1 + 1*1*1 + 1*1*1 = 3.
// Total extra spaces are 3 in both scenarios, but second arrangement should be
// preferred because extra spaces are balanced in all three lines. The cost
// function with cubic sum serves the purpose because the value of total cost
// in second scenario is less.

#include <stdio.h>

class MySolution {
public:
    // `l` is an array of integers, each represent a word's length
    // `n` is total number of integers
    // `M` is line length
    int solveWordWrap(int l[], int n, int M) {
        ?
    }
};


// Driver program to test above functions
int main()
{
    int l[] = {3, 2, 2, 5};
    int n = sizeof(l)/sizeof(l[0]);
    int M = 6;

    solveWordWrap(l, n, M);

    return 0;
}
