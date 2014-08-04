// Given n, how many structurally unique BST's (binary search trees) that store
// values 1...n?

// For example,
// Given n = 3, there are a total of 5 unique BST's.
//    1         3     3      2      1
//     \       /     /      / \      \
//      3     2     1      1   3      2
//     /     /       \                 \
//    2     1         2                 3

#include <iostream>
#include <unordered_map>
using namespace std;


class Solution {
public:
    int numTrees(int n) {
        unordered_map<int, int> cache;
        return numTreesHelper(n, cache);
    }

    int numTreesDP(int n) {

        int nums[n+1];

        for (int i = 0; i <= n; i++)
            nums[i] = 0;
        nums[0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                nums[i] += nums[j] * nums[i-j-1];
            }
        }

        return nums[n];
    }

private:
    int numTreesHelper(int n, unordered_map<int, int> cache) {

        if (cache[n] != 0)
            return cache[n];

        if (n == 0)
            return 1;

        int sum = 0;
        for (int i = 0; i < n; i++) {
            int left = numTrees(i);
            int right = numTrees(n - i - 1);
            sum += left * right;
        }

        cache[n] = sum;
        return sum;

    }
};


int main(void) {

    Solution solution;

    cout << solution.numTrees(12) << endl;
    cout << solution.numTreesDP(12) << endl;
}
