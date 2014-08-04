// Given n, generate all structurally unique BST's (binary search trees) that
// store values 1...n.

// For example,
// Given n = 3, your program should return all 5 unique BST's shown below.

//    1         3     3      2      1
//     \       /     /      / \      \
//      3     2     1      1   3      2
//     /     /       \                 \
//    2     1         2                 3

#include <vector>
#include <iostream>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    vector<TreeNode *> generateTrees(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return generateTreesHelper(1, n);
    }

private:
    vector<TreeNode *> generateTreesHelper(int start, int end) {

        vector<TreeNode *> result;

        if (start > end) {
            result.push_back(NULL);
            return result;
        } else if (start == end) {
            TreeNode *root = new TreeNode(start);
            result.push_back(root);
            return result;
        }

        for (int i = start; i <= end; i++) { // choose i as root
            vector<TreeNode *> left = generateTreesHelper(start, i-1);
            vector<TreeNode *> right = generateTreesHelper(i+1, end);
            for (int p = 0; p < left.size(); p++) {
                for (int q = 0; q < right.size(); q++) {
                    TreeNode *root = new TreeNode(i);
                    root->left = left[p];
                    root->right = right[q];
                    result.push_back(root);
                }
            }
        }

        return result;
    }
};


int main(void) {

    Solution solution;

    vector<TreeNode *> result = solution.generateTrees(3);
    cout << result.size();
    return 0;
}
