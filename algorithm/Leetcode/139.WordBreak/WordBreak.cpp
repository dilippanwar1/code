// Given a string s and a dictionary of words dict, determine if s can be
// segmented into a space-separated sequence of one or more dictionary words.

// For example, given
// s = "leetcode",
// dict = ["leet", "code"].

// Return true because "leetcode" can be segmented as "leet code".

#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;


class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {

        unordered_map<string, bool> cache;
        unordered_set<string>::iterator every;

        // set every word in dict as true
        for (every = dict.begin(); every != dict.end(); every++)
            cache[*every] = true;

        return wordBreakHelper(s, dict, cache);
    }

    bool wordBreakHelper(string s, unordered_set<string> &dict,
                         unordered_map<string, bool> &cache) {

        if (cache.find(s) != cache.end()) {
            return cache[s];
        }

        for (int i = 1; i < s.length(); i++) {
            if (dict.find(s.substr(0, i)) != dict.end()) {
                if (wordBreakHelper(s.substr(i), dict, cache)) {
                    cache[s] = true;
                    return true;
                }
            }
        }

        cache[s] = false;
        return false;
    }

    // solution from web
    bool wordBreak2(string s, unordered_set<string> &dict) {

        // wordB[i] means whether s[0...i-1] can be broken into sentence
        vector<bool> wordB(s.length() + 1, false);
        wordB[0] = true;        // we can break empty string

        for (int i = 1; i < s.length() + 1; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (wordB[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
                    wordB[i] = true;
                    break;
                }
            }
        }
        return wordB[s.length()];
    }
};


int main(void) {

    Solution solution;
    string s = "leetcode";

    return 0;
}
