// The set [1,2,3,…,n] contains a total of n! unique permutations.

// By listing and labeling all of the permutations in order,
// We get the following sequence (ie, for n = 3):
// "123"
// "132"
// "213"
// "231"
// "312"
// "321"

// Given n and k, return the kth permutation sequence.
// Note: Given n will be between 1 and 9 inclusive.

#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    string getPermutation(int n, int k) {

        int factorial[n];
        string numbers;
        string result;

        // compute factorial from 0 to n-1, and numbers. e.g. n = 4 =>
        // compute f[0]=1, f[1]=1, f[2]=2, f[3]=6 and numbers = "1234"
        factorial[0] = 1;
        for (int i = 1; i < n; i++) {
            numbers += '0' + i;
            factorial[i] = factorial[i-1] * i;
        }
        numbers += '0' + n;

        k--;                    // convert to zero based
        for (int i = n - 1; i >= 0; i--) {
            int position = k / factorial[i];
            result += numbers[position];
            numbers.erase(position, 1); // important, erase
            k %= factorial[i];
        }

        return result;
    }
};


int main(void) {

    Solution solution;

    cout << solution.getPermutation(1, 1) << endl;
    return 0;
}
