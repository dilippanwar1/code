// Given an absolute path for a file (Unix-style), simplify it.

// For example,
//    path = "/home/", => "/home"
//    path = "/a/./b/../../c/", => "/c"

// Corner Cases:
//    Did you consider the case where path = "/../"?
//    In this case, you should return "/".
//    Another corner case is the path might contain multiple slashes '/'
//    together, such as "/home//foo/".
//    In this case, you should ignore redundant slashes and return "/home/foo".


#include <stack>
#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    string simplifyPath(string path) {

        // because we need to fall back, stack is suitable for this problem
        stack<char> stk;
        for (int i = 0; i < path.size(); i++) { // iterate all characters
            if (path[i] == '/') {
                // if we reach '/', check if top is '/' since we do not want
                // duplicate. note that stack can be empty.
                if (stk.size() == 0 || stk.top() != '/') {
                    stk.push('/');
                }
            } else if (path[i] == '.') {
                // if we reach '.', and it's the last one, e.g. "/a/.", simply
                // pop out last '/'
                if (i + 1 == path.size()) {
                    stk.pop();
                } else if (path[i+1] == '.') {
                    // '/a/b/../c' case, pop out first '/'
                    stk.pop();
                    i++;        // skip next '.'
                    while (stk.size() != 0 && stk.top() != '/')
                        stk.pop(); // pop to upper level dir
                } else if (path[i+1] == '/') {
                    // '/a/b/./c
                    stk.pop();
                } else {        // other cases, '/.hidden'
                    stk.push('.');
                }
            } else {
                stk.push(path[i]);
            }
        }

        if (stk.size() == 0)    // size can be 0 here
            stk.push('/');
        else if (stk.top() == '/' && stk.size() != 1) // delete trailing '/'
            stk.pop();

        // construct string
        string result(stk.size(), '0');
        for (int i = stk.size() - 1; i >= 0; i--) {
            result[i] = stk.top();
            stk.pop();
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    cout << solution.simplifyPath("/a/./b/../..///c/") << endl;
    cout << solution.simplifyPath("/home/") << endl;
    cout << solution.simplifyPath("/a/..") << endl;
    cout << solution.simplifyPath("/../") << endl;
    cout << solution.simplifyPath("/.hidden") << endl;
    cout << solution.simplifyPath("/.") << endl;
}
