// Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
// determine if the input string is valid.

// The brackets must close in the correct order, "()" and "()[]{}" are all valid
// but "(]" and "([)]" are not.

#include <stack>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


class Solution {
public:
    bool isValid(string s) {

        if (s.length() == 0) {
            return true;
        } else if (s.length() % 2 == 1) {
            return false;
        }

        // typical application of stack
        stack<char> stk;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                stk.push(s[i]);
            } else {
                if (stk.empty()) {
                    return false;
                } else {
                    switch (s[i]) {
                    case ')':
                        if (stk.top() != '(') {
                            return false;
                        }
                        break;
                    case ']':
                        if (stk.top() != '[') {
                            return false;
                        }
                        break;
                    case '}':
                        if (stk.top() != '{') {
                            return false;
                        }
                        break;
                    }
                    stk.pop();
                }
            }
        }

        if (stk.empty()) {
            return true;
        } else {
            return false;
        }
    }
};


int main(void) {
    Solution solution;
    printf("%d\n", solution.isValid("()()[{]"));
    return 0;
}
