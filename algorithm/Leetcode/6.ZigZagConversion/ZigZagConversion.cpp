// The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
// of rows like this: (you may want to display this pattern in a fixed font for
// better legibility)
//    P   A   H   N
//    A P L S I I G
//    Y   I   R
// And then read line by line: "PAHNAPLSIIGYIR"
// Write the code that will take a string and make this conversion given a
// number of rows:
//    string convert(string text, int nRows);
//    convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".


#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Solution {
public:

    // elegent solution from web
    string convert(string s, int nRows) {

        if (nRows == 1)
            return s;

        string buf(s.length(), '0');
        int diff = nRows + nRows - 2;
        int position = 0;
        for (int i = 0; i < nRows; i++) {
            int index = i;
            while (index < s.length()) {
                buf[position++] = s[index];
                index += diff;
                if (i != 0 && i != nRows - 1 && index - i - i < s.length()) {
                    buf[position++] = s[index-i-i];
                }
            }
        }

        return buf;
    }

    string convert2(string s, int nRows) {

        // return original string if only one row
        if (nRows == 1) {
            return s;
        }

        // if we conbine the zigzag string, there are two types of columns, one
        // long and one short, e.g:
        // for nRows = 4, s.length = 17
        //   0     6     12
        //   1  5  7  11 13
        //   2  4  8  10 14 16
        //   3     9     15
        // for the above input, long_leader is {0, 6, 12} and short_leader is
        // {4, 10, 16}. Note that last column is not complete.
        int long_col = nRows, short_col = nRows - 2;
        vector<int> long_leader;
        vector<int> short_leader;

        // compute leaders for long and short column
        int turn = 1, num = 0;
        while (num < s.length()) {
            if (turn == 1) {    // compute long col leader
                long_leader.push_back(num);
                num += long_col;
                turn = 0;
            } else {            // compute short col leader
                short_leader.push_back(num);
                num += short_col;
                turn = 1;
            }
        }

        // compute output according to leaders
        int index = 0;
        char array[s.length() + 1];
        for (int i = 0; i < nRows; i++) {
            // if i equals 0 or nRows-1, we only use long column
            if (i == 0 || i == nRows - 1) {
                for (int j = 0; j < long_leader.size(); j++) {
                    if (long_leader[j] + i < s.length()) {
                        array[index++] = s[long_leader[j] + i];
                    }
                }
            } else {
                int start = index;
                for (int j = 0; j < long_leader.size(); j++) {
                    if (long_leader[j] + i < s.length()) {
                        array[start + j*2] = s[long_leader[j] + i];
                        index++;
                    }
                }
                for (int j = 0; j < short_leader.size(); j++) {
                    // short column is in reverse direction
                    if (short_leader[j] + nRows - 2 - i < s.length()) {
                        array[start + j*2 + 1] = s[short_leader[j] + nRows - 2 - i];
                        index++;
                    }
                }
            }
        }
        array[s.length()] = '\0';

        string a(array);
        return a;
    }
};


int main(void) {

    Solution solution;
    string a("PAYPALISHIRING");

    cout << solution.convert(a, 3) << endl;
    cout << solution.convert2(a, 3) << endl;
}
