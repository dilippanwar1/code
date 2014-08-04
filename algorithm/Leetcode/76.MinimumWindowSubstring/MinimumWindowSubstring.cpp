// Given a string S and a string T, find the minimum window in S which will
// contain all the characters in T in complexity O(n).

// For example,
//    S = "ADOBECODEBANC"
//    T = "ABC"
//    Minimum window is "BANC".

// Note:
//    If there is no such window in S that covers all characters in T, return
//        the emtpy string "".
//    If there are multiple such windows, you are guaranteed that there will
//        always be only one unique minimum window in S.

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;


class Solution {
public:
    string minWindow(string s, string t) {

        if (t.size() == 0)
            return "";

        map<char, int> hist;
        for (char c : t) {      // use g++-4.8 -std=c++11
            hist[c] = 0;
        }

        for (char c : t) {
            hist[c]++;
        }

        int count = 0;
        int minstart = 0 ,minlen = s.size() + 1;
        int start = 0, end = 0;

        while (end < s.size()) {
            if (hist.find(s[end]) != hist.end()) {
                hist[s[end]]--;
                if (hist[s[end]] >= 0) count++;
                while (count == t.size()) {
                    if (end - start + 1 < minlen) {
                        minlen = end - start + 1;
                        minstart = start;
                    }
                    if (hist.find(s[start]) != hist.end()) {
                        hist[s[start]]++;
                        if (hist[s[start]] > 0) count --;
                    }
                    start++;
                }
            }
            end++;
        }

        if (minlen > s.size())
            return "";
        return s.substr(minstart, minlen);
    }
};


int main(void) {

    Solution solution;

    cout << solution.minWindow("ADOBECODEBANC", "ABC") << endl;
    return 0;
}
