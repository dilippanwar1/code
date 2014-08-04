// The count-and-say sequence is the sequence of integers beginning as follows:
// 1, 11, 21, 1211, 111221, ...

// 1 is read off as "one 1" or 11.
// 11 is read off as "two 1s" or 21.
// 21 is read off as "one 2, then one 1" or 1211.

// Given an integer n, generate the nth sequence.

// Note: The sequence of integers will be represented as a string.


#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    string countAndSay(int n) {

        if (n == 1) {
            return "1";
        }

        string sub_prob = countAndSay(n-1);
        vector<char> result;
        int count = 0, i = 0, j = 0;

        while (i != sub_prob.length()) {
            count = 0;
            while (sub_prob[i] == sub_prob[j]) {
                count++;
                j++;
            }
            result.push_back(count + '0');
            result.push_back(sub_prob[i]);
            i = j;
        }

        string ret(result.begin(), result.end());
        return ret;
    }
};


int main(void) {

    Solution solution;
    cout << solution.countAndSay(4) << endl;
    return 0;
}
