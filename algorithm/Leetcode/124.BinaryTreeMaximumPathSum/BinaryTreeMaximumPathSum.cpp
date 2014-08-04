// Given a binary tree, find the maximum path sum.

// The path may start and end at any node in the tree.

// For example:
//    Given the below binary tree,
//        1
//       / \
//      2   3
//    Return 6.

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
    // One needs to handle three cases:
    //    Left tree path plus the current root.
    //    Right tree path plus the current root.
    //    The path passes through the root and hence one needs to consider the
    //        left path + current root + right path.
    // In addition compare with the max path so far and update accordingly.
    int maxPathSum(TreeNode *root) {

        int csum;
        int maxsum = INT_MIN;
        maxPathSumHelper(root, csum, maxsum);
        return maxsum;

    }

    // `csum` means the straight sum along one path of a subtree
    void maxPathSumHelper(TreeNode *node, int &csum, int &maxsum) {

        if (node == NULL) {
            csum = 0;
            return;
        }

        int lsum = 0, rsum = 0;
        maxPathSumHelper(node->left, lsum, maxsum);
        maxPathSumHelper(node->right, rsum, maxsum);
        csum = max(node->val, max(node->val + lsum, node->val + rsum));
        maxsum = max(maxsum, max(csum, node->val + lsum + rsum));
    }

private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
};


int main(void) {

    Solution solution;

    TreeNode *root = new TreeNode(8);
    root->left = new TreeNode(3);
    root->right = new TreeNode(-2);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(7);
    root->right->right = new TreeNode(2);

    cout << solution.maxPathSum(root) << endl;

    return 0;
}
