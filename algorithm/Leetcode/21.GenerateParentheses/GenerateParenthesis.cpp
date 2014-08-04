// Given n pairs of parentheses, write a function to generate all combinations
// of well-formed parentheses.

// For example, given n = 3, a solution set is:
//    "((()))", "(()())", "(())()", "()(())", "()()()"

#include <vector>
#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<string> generateParenthesis(int n) {

        string path(n*2, '\0');
        vector<string> result;

        generateParenthesisHelper(n, 0, n, n, path, result);

        return result;
    }

    void generateParenthesisHelper(int n, int index, int left, int right,
                                   string &path, vector<string> &result) {
        // if both left parenthesis and right parenthesis are 0, we have
        // a valid parenthesis combination
        if (left == 0 && right == 0) {
            result.push_back(path);
            return;
        } else if (left < 0 || right < 0 || left > right) {
            return;             // invalid case
        }

        path[index] = '(';
        generateParenthesisHelper(n, index+1, left-1, right, path, result);
        path[index] = ')';
        generateParenthesisHelper(n, index+1, left, right-1, path, result);
    }
};


int main(void) {

    Solution solution;

    vector<string> result = solution.generateParenthesis(2);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

}
