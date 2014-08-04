// Given two binary strings, return their sum (also a binary string).

// For example,
//    a = "11"
//    b = "1"
//    Return "100".

#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    string addBinary(string a, string b) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int m = a.length(), n = b.length();
        if (m == 0 && n == 0)
            return a;
        if (m == 0)
            return b;
        if (n == 0)
            return a;
        m--; n--;               // use index instead of length

        string result;
        char carry = 0;
        while (m >= 0 || n >= 0 || carry) {
            char sum = carry;
            sum += (m >= 0) ? a[m] - '0' : 0;
            sum += (n >= 0) ? b[n] - '0' : 0;
            if (sum == 2) {
                carry = 1;
                result.insert(0, 1, '0');
            } else if (sum == 3) {
                carry = 1;
                result.insert(0, 1, '1');
            } else {
                carry = 0;
                result.insert(0, 1, sum + '0');
            }
            m--; n--;
        }
        return result;
    }
};


int main(void) {

    Solution solution;

    cout << solution.addBinary("11", "110") << endl;
    return 0;
}
