// The gray code is a binary numeral system where two successive values differ
// in only one bit.

// Given a non-negative integer n representing the total number of bits in the
// code, print the sequence of gray code. A gray code sequence must begin with 0.

// For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
//    00 - 0
//    01 - 1
//    11 - 3
//    10 - 2

// Note:
//    For a given n, a gray code sequence is not uniquely defined.
//    For example, [0,2,3,1] is also a valid gray code sequence according to
//        the above definition.
//    For now, the judge is able to judge based on one instance of gray code
//        sequence. Sorry about that.

#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;


class Solution {
public:
    vector<int> grayCode(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<int> stk;
        vector<int> result;
        unordered_map<int, bool> visited;

        if (n < 0)
            return result;
        int size = 1 << n;

        stk.push(0);
        visited[0] = true;

        while (!stk.empty()) {
            // get the top element (which is adjcent number of previous number)
            // push it into stack and mark it as visited
            int top = stk.top(); stk.pop();
            result.push_back(top);
            visited[top] = true;
            // we must return immediately when size is full
            if (result.size() == size)
                return result;
            // check all adjcent numbers, push to stack if we haven't visited
            // if there is no unvisited adjcent number, then we are done!
            // (it's the same condition with result.size() == size, both are ok).
            for (int i = n-1; i >= 0; i--) {
                int flip = top ^ (1 << i);
                if (visited[flip] == false) {
                    stk.push(flip);
                }
            }
        }

        return result;
    }


    vector<int> grayCode2(int n) {

        vector<int> result;
        result.push_back(0);

        // n = i can be derived by n = i-1 (reverse and prepend 1)
        for (int i = 1; i <= n; i++) {
            int size = result.size();
            int k = 1 << (i-1);
            for (int j = size - 1; j >= 0; j--) {
                result.push_back(result[j] | k);
            }
        }

        return result;
    }


    // elegant solution from web (math)
    vector<int> grayCodeWeb(int n) {

        vector<int> ret;
        int count = 1 << n;

        for (int i = 0 ; i < count; ++i) {
            ret.push_back(i ^ (i>>1));
        }

        return ret;
    }
};


int main(void) {

    Solution solution;
    vector<int> result = solution.grayCode2(3);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
