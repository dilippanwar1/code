#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s.length() == 0)
            return 0;

        int max_len = 0, cur_len = 0;
        int chs[256];

        for (int i = 0; i < 256; i++)
            chs[i] = -1;

        for (int i = 0; i < s.length(); i++) {
            if (chs[s[i]] == -1 || chs[s[i]] < i-cur_len) {
                cur_len++;
                chs[s[i]] = i;
            } else {
                max_len = max(max_len, cur_len);
                cur_len = i - chs[s[i]];
                chs[s[i]] = i;
            }
        }

        max_len = max(max_len, cur_len);
        return max_len;
    }
};


int main(void) {

    Solution solution;

    cout << solution.lengthOfLongestSubstring("wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco") << endl;
    cout << solution.lengthOfLongestSubstring("abcba") << endl;
    cout << solution.lengthOfLongestSubstring("qopubjguxhxdipfzwswybgfylqvjzhar") << endl;
    return 0;
}
