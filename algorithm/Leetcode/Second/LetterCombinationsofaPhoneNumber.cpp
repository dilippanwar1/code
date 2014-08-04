#include <vector>
#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<string> letterCombinations(string digits) {

        int len = digits.length();
        int steps[len];
        int total;
        string map[10] = {"","","abc","def","ghi","jkl","mno","qprs","tuv","wxyz"};
        int sizes[10] =  {0, 0, 3, 3, 3, 3, 3, 4, 3, 4}; // convenient array

        steps[len-1] = 1;
        for (int i = len - 2; i >= 0; i--) {
            steps[i] = steps[i + 1] * sizes[digits[i+1] - '0'];
        }
        total = steps[0] * sizes[digits[0] - '0'];

        vector<string> result(total, string(len, '0'));

        for (int i = 0; i < total; i++) {
            for (int j = 0; j < len; j++) {
                int index = digits[j] - '0';
                string number = map[index];
                result[i][j]  = number[(i/steps[j]) % sizes[index]];
            }
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    string input("");
    vector<string> result = solution.letterCombinations(input);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }

    return 0;
}
