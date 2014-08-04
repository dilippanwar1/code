// Given two words (start and end), and a dictionary, find all shortest
// transformation sequence(s) from start to end, such that:
//    Only one letter can be changed at a time
//    Each intermediate word must exist in the dictionary

// For example,
// Given:
//    start = "hit"
//    end = "cog"
//    dict = ["hot","dot","dog","lot","log"]

// Return
//    [
//      ["hit","hot","dot","dog","cog"],
//      ["hit","hot","lot","log","cog"]
//    ]

// Note:
// All words have the same length.
// All words contain only lowercase alphabetic characters.


#include <list>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;


// The first time I tried DFS, it works pretty well for small test. However, it
// exceeded time limits for large test. So I switched to BFS. Because we want
// to find all the minimum results, and avoid searching all possible solutions,
// when we do BFS, we need to record the parent step of each child step.
// However, we may find that there should be some steps which may have multi
// parent steps. So in this case, I use my own node structure to record them and
// use a hashmap to trace those node. Another thing we should be careful is that
// we should make sure that the parent's layer should be less that the child's
// layer, in order to avoiding generate longer result which isn't the minimum
// solution.

// 1. Using BFS to search the end word and at the same time adding parent to each
//    child
// 2. After we find all the solutions, using DFS to generate the result.


class Solution {
public:

    struct Node {
        vector<string> parent;
        int layer;
    };

    vector<vector<string> > findLadders(string start, string end,
                                        unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        unordered_map<string, Node> checkmap;
        vector<vector<string> > result;
        list<string> layer;
        checkmap[start].layer = 1;
        checkmap[start].parent.push_back(start);
        layer.push_back(start);

        bool hasfind = false;
        string layerend = start;
        string last;

        while (!layer.empty()) {

            string s = layer.front(); layer.pop_front();
            int currentlayer = checkmap[s].layer;

            for (int i = 0; i < s.size(); i++) {
                string temp = s;
                for (int j = 0; j < 26; j++) {
                    temp[i] = j + 'a';
                    if (temp == end) {
                        checkmap[temp].parent.push_back(s);
                        checkmap[temp].layer = checkmap[s].layer+1;
                        hasfind = true;
                    }
                    else if (dict.count(temp) && s != temp) {
                        if (checkmap.count(temp) == 0) {
                            checkmap[temp].parent.push_back(s);
                            checkmap[temp].layer = checkmap[s].layer+1;
                            layer.push_back(temp);
                            last = temp;
                        } else if (checkmap[s].layer < checkmap[temp].layer) {
                            checkmap[temp].parent.push_back(s);
                        }
                    }
                }
            }

            if (s == layerend) {
                layerend = last;
                if (hasfind) {
                    list<string> r;
                    buildResult(result, r, start, end, checkmap);
                    break;      // stop searching
                }
            }
        }

        return result;
    }

    void buildResult(vector<vector<string> > &result, list<string> &r,
                     string start, string end,
                     unordered_map<string, Node> &checkmap) {
        r.push_front(end);
        if (end == start) {
            vector<string> oneresult(r.begin(), r.end());
            result.push_back(oneresult);
        }
        else {
            for (const string &s : checkmap[end].parent) {
                buildResult(result, r, start, s, checkmap);
            }
        }
        r.pop_front();
    }
};


int main(int argc, char *argv[]) {

    Solution solution;
    unordered_set<string> dict;
    dict.insert("hot");
    dict.insert("dot");
    dict.insert("dog");
    dict.insert("log");
    dict.insert("lot");

    vector<vector<string> > result = solution.findLadders("hit", "cog", dict);

    for (int i = 0; i < result.size(); i++) {
        cout << "[ ";
        vector<string> res = result[i];
        for (int j = 0; j < res.size(); j++) {
            cout << res[j] << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
