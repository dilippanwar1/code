// Write a function to find the longest common prefix string amongst an array
// of strings.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {

        if (strs.empty()) {
            return "";
        } else if (strs.size() == 1) {
            return strs[0];
        }

        int max_len = 0;
        while (true) {
            for (int i = 0; i < strs.size() - 1; i++) {
                if (strs[i].length() < max_len ||
                    strs[i+1].length() < max_len) {
                    return strs[0].substr(0, max_len);
                }
                if (strs[i][max_len] != strs[i+1][max_len]) {
                    return strs[0].substr(0, max_len);
                }
            }
            max_len++;
        }

        return strs[0].substr(0, max_len);
    }
};


int main(void) {

    Solution solution;
    vector<string> strs;
    strs.push_back("commonprefix");
    strs.push_back("commonsufix");
    strs.push_back("commoncommon");

    cout << solution.longestCommonPrefix(strs) << endl;
}
