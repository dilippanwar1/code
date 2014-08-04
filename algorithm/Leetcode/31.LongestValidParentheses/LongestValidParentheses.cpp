// Given a string containing just the characters '(' and ')', find the length
// of the longest valid (well-formed) parentheses substring.

// For "(()", the longest valid parentheses substring is "()", which has
// length = 2.

// Another example is ")()())", where the longest valid parentheses substring
// is "()()", which has length = 4.

#include <stack>
#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    // Use a stack to keep track of the positions of non-matching '('s.
    // Also need to keep track of the position of the last ')'.
    int longestValidParentheses(string s) {

        stack<int> stk;
        int max_len = 0, last = -1;

        if (s.length() == 0 || s.length() == 1)
            return 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') { // if we get '(', push index into stack
                stk.push(i);
            } else {
                if (stk.empty()) { // nothing in stk, cannot match
                    last = i;
                } else {
                    stk.pop();  // find a match
                    if (stk.empty()) {
                        max_len = max(max_len, i - last);
                    } else {
                        max_len = max(max_len, i - stk.top());
                    }
                }
            }
        }

        return max_len;
    }
};


int main(void) {

    Solution solution;

    cout << solution.longestValidParentheses(")()())") << endl;
    cout << solution.longestValidParentheses("()") << endl;
}
