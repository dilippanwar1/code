// Given a binary tree, check whether it is a mirror of itself (ie, symmetric
// around its center).

// For example, this binary tree is symmetric:
//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3

// But the following is not:
//     1
//    / \
//   2   2
//    \   \
//    3    3

// Note:
// Bonus points if you could solve it both recursively and iteratively.

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
    bool isSymmetric(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        if (root == NULL)
            return true;
        if (root->left == NULL && root->right == NULL)
            return true;

        return isSymmetricHelper(root->left, root->right);
    }

    bool isSymmetricHelper(TreeNode *p, TreeNode *q) {

        if ((p == NULL && q != NULL) || (p != NULL && q == NULL)) {
            return false;
        } else if (p == NULL && q == NULL) {
            return true;
        } else if (p->val != q->val) {
            return false;
        }

        return isSymmetricHelper(p->left, q->right) &&
            isSymmetricHelper(p->right, q->left);
    }
};


int main(void) {

    Solution solution;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(8);

    cout << solution.isSymmetric(root) << endl;
    return 0;
}
