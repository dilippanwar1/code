// Implement regular expression matching with support for '.' and '*'.

// '.' Matches any single character.
// '*' Matches zero or more of the preceding element.

// The matching should cover the entire input string (not partial).

// The function prototype should be:
//    bool isMatch(const char *s, const char *p)

// Some examples:
// isMatch("aa","a") ? false
// isMatch("aa","aa") ? true
// isMatch("aaa","aa") ? false
// isMatch("aa", "a*") ? true
// isMatch("aa", ".*") ? true
// isMatch("ab", ".*") ? true
// isMatch("aab", "c*a*b") ? true

#include <iostream>
using namespace std;


// http://discuss.leetcode.com/questions/175/regular-expression-matching
bool isMatch(const char *s, const char *p) {

    if (*p == '\0') return *s == '\0';

    // next char is not '*': must match current character
    if (*(p+1) != '*') {
        return ((*p == *s) || (*p == '.' && *s != '\0')) && isMatch(s+1, p+1);
    }

    // next char is '*'
    while ((*p == *s) || (*p == '.' && *s != '\0')) {
        if (isMatch(s, p+2)) return true;
        s++;
    }
    return isMatch(s, p+2);
}


class Solution {
public:
    bool isMatch(const char *s, const char *p) {

        if (*p == '\0')
            return *s == '\0';

        // next char is not '*'; then we must match current txt char. This
        // match can be either two chars equal or patter is '.', but for .
        // we need to check *s != '\0', e.g. ("ab", ".*c")
        if (*(p+1) != '*') {
            if (*s == *p || (*p == '.' && *s != '\0')) {
                return isMatch(s+1, p+1);
            } else {
                return false;
            }
        } else {
            while (*s == *p || (*p == '.' && *s != '\0')) {
                if (isMatch(s, p+2)) {
                    return true;
                } else {
                    s++;
                }
            }
            return isMatch(s, p+2); // next pattern
        }
    }
};


int main(void) {

    Solution solution;

    // cout << solution.isMatch("aa","a") << endl;
    // cout << solution.isMatch("aa","aa") << endl;
    // cout << solution.isMatch("aaa","aa") << endl;
    // cout << solution.isMatch("aa", "a*") << endl;
    // cout << solution.isMatch("aa", ".*") << endl;
    // cout << solution.isMatch("ab", ".*") << endl;
    // cout << solution.isMatch("aab", "c*a*b") << endl;
    // cout << solution.isMatch("aa", "a*") << endl;
    cout << solution.isMatch("ab", ".*c") << endl;
}
