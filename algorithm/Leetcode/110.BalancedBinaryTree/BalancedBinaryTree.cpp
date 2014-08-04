// Given a binary tree, determine if it is height-balanced.

// For this problem, a height-balanced binary tree is defined as a binary tree in
// which the depth of the two subtrees of every node never differ by more than 1.

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
    bool isBalanced(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int height;
        return isBalancedHelper(root, height);
    }

private:
    bool isBalancedHelper(TreeNode *root, int &height) {

        if (root == NULL) {
            height = 0;
            return true;
        }

        int left_h, right_h;
        if (isBalancedHelper(root->left, left_h) == false)
            return false;
        if (isBalancedHelper(root->right, right_h) == false)
            return false;

        if (abs(left_h - right_h) > 1) {
            return false;
        } else {
            height = max(left_h, right_h) + 1;
            return true;
        }
    }
};


int main(void) {

    Solution solution;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(8);

    cout << solution.isBalanced(root) << endl;
}
