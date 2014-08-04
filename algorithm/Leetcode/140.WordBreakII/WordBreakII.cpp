// Given a string s and a dictionary of words dict, add spaces in s to construct
// a sentence where each word is a valid dictionary word.

// Return all such possible sentences.

// For example, given
// s = "catsanddog",
// dict = ["cat", "cats", "and", "sand", "dog"].

// A solution is ["cats and dog", "cat sand dog"].

#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;


class Solution {
public:

    // Solution from web, dp + dfs + prune
    vector<string> wordBreak(string s, unordered_set<string> &dict) {

        string sentence;
        vector<string> output;
        // whether s[i...end] can be broken
        vector<bool> breakable(s.length()+1, false);

        // mark each index point as true or false.
        breakable[s.size()] = true;
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if(dict.find(s.substr(i, j-i+1)) != dict.end() && breakable[j+1]) {
                    breakable[i] = true; // valid sentence from i to end.
                    break;
                }
            }
        }

        getSentence(s, 0, sentence, output, dict, breakable);
        return output;
    }

    void getSentence(string &s, int start, string sentence, vector<string> &output,
                     unordered_set<string> &dict, vector<bool> &breakable) {

        if (start == s.size()) {
            sentence.erase(sentence.end() -1); // remove last ' '
            output.push_back(sentence);
            return;
        }

        for (int i = start; i < s.size(); i++) {
            if (breakable[i+1] == false) // prune here
                continue;
            string tmp = s.substr(start, i-start+1);
            if (dict.find(tmp) != dict.end()) // if dict contains tmp
                getSentence(s, i+1, sentence + tmp + " ", output, dict, breakable);
        }
    }

    // Memory Limit Exceeded
    vector<string> wordBreak1(string s, unordered_set<string> &dict) {

        vector<string> empty(1, "");
        vector<bool> wordB(s.length() + 1, false);
        vector<vector<string> > wordC(s.length() + 1, vector<string>());
        wordB[0] = true;
        wordC[0] = empty;

        for (int i = 1; i <= s.length(); i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (wordB[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
                    wordB[i] = true;
                    for (int k = 0; k < wordC[j].size(); k++) {
                        wordC[i].push_back(wordC[j][k]);
                        if (wordC[i].back().length() == 0) {
                            wordC[i].back().append(s.substr(j, i-j));
                        } else {
                            wordC[i].back().append(" " + s.substr(j, i-j));
                        }
                    }
                }
            }
        }

        return wordC[s.length()];
    }


    // error if word in dict can be composed from other words in dict, e.g.
    // dict = {"aaaa", "aa"}. we need to take care of this when warm up cache
    vector<string> wordBreak2(string s, unordered_set<string> &dict) {

        unordered_set<string>::iterator every;
        unordered_map<string, vector<string> > cache;

        // set every word in dict as true
        for (every = dict.begin(); every != dict.end(); every++) {
            vector<string> temp;
            temp.push_back(*every);
            cache[*every] = temp;
        }

        vector<string> result = wordBreakHelper(s, dict, cache);

        // unordered_map<string, vector<string> >::iterator it;
        // for (it = cache.begin(); it != cache.end(); it++) {
        //     cout << it->first << ": " << endl;;
        //     for (int i = 0; i < it->second.size(); i++)
        //         cout << it->second[i] << endl;
        //     cout << endl;
        //     cout << endl;
        // }

        return result;
    }

    vector<string> wordBreakHelper(string s, unordered_set<string> &dict,
                                   unordered_map<string, vector<string> > &cache) {

        vector<string> result;

        if (cache.find(s) != cache.end()) {
            return cache[s];
        }
        if (s.length() == 0) {
            return result;
        }

        vector<string> temp_cache;
        cache[s] = temp_cache;

        for (int i = 1; i < s.length(); i++) {
            if (dict.find(s.substr(0, i)) != dict.end()) {
                vector<string> temp = wordBreakHelper(s.substr(i), dict, cache);
                for (int j = 0; j < temp.size(); j++) {
                    temp[j].insert(0, s.substr(0, i) + " ");
                    result.push_back(temp[j]);
                    cache[s].push_back(temp[j]);
                }
            }
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    unordered_set<string> dict ( {"cat", "cats", "and", "sand", "dog"} );
    //unordered_set<string> dict ( {"aaaa", "aa", "a"} );

    vector<string> result = solution.wordBreak("catsanddog", dict);
    //vector<string> result = solution.wordBreak("catsanddogcatsanddog", dict);
    //vector<string> result = solution.wordBreak("aaaaaaa", dict);
    for (int i = 0; i < result.size(); i++) {
        cout << "[" << result[i] << "] ";
    }
    cout << endl;

    return 0;
}
