// Given a string, find the length of the longest substring without repeating
// characters. For example, the longest substring without repeating letters for
// "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring
// is "b", with the length of 1.

#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        int visited[256];
        int cur_len = 0;
        int max_len = 0;

        // all characters are not visited
        for (int i = 0; i < 256; i++) {
            visited[i] = -1;
        }

        for (int i = 0; i < s.length(); i++) {
            // if character hasn't been visited, or it is outside of
            // current longest length, increment cur_len by 1.
            if (visited[s[i]] == -1 || i - cur_len > visited[s[i]]) {
                cur_len++;
                visited[s[i]] = i;
            } else {            // update cur_len
                cur_len = i - visited[s[i]];
                visited[s[i]] = i;
            }

            if (cur_len > max_len) {
                max_len = cur_len;
            }
        }

        return max_len;
    }
};


int main(void) {

    Solution solution;
    string a("abcd efg");
    cout << solution.lengthOfLongestSubstring(a) << endl;
}
