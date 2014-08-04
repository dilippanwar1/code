// Given an array of strings, return all groups of strings that are anagrams.

// Note: All inputs will be in lower-case.

#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


class Solution {
public:

    vector<string> anagrams(vector<string> &strs) {

        vector<string> result;
        map<string, vector<string> > maps;
        // iterator
        vector<string>::iterator it;
        map<string, vector<string> >::iterator probe;

        for (it = strs.begin(); it != strs.end(); it++) {
            string temp = *it;
            sort(temp.begin(), temp.end()); // sort current string
            maps[temp].push_back(*it);
        }

        for (probe = maps.begin(); probe != maps.end(); probe++) {
            if (probe->second.size() > 1) {
                for (int i = 0; i < probe->second.size(); i++) {
                    result.push_back(probe->second[i]);
                }
            }
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    vector<string> inputs;
    inputs.push_back("abc");
    inputs.push_back("cab");
    inputs.push_back("cba");
    inputs.push_back("tty");
    inputs.push_back("ytt");
    inputs.push_back("yttt");
    inputs.push_back("ttt");

    vector<string> result = solution.anagrams(inputs);
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << endl;

    return 0;
}
