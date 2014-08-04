// Given a binary tree, determine if it is a valid binary search tree (BST).

// Assume a BST is defined as follows:
//    The left subtree of a node contains only nodes with keys less than the
//        node's key.
//    The right subtree of a node contains only nodes with keys greater than
//        the node's key.
//    Both the left and right subtrees must also be binary search trees.

// The serialization of a binary tree follows a level order traversal, where
// '#' signifies a path terminator where no node exists below.

// Here's an example:
//    1
//   / \
//  2   3
//     /
//    4
//     \
//      5
// The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".

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

    bool isValidBST(TreeNode *root) {
        int pre = INT_MIN;
        return another(root, pre);
    }

    bool another(TreeNode *root, int &pre) {

        if (root == NULL)
            return true;

        if (another(root->left, pre) == false)
            return false;
        if (root->val <= pre) return false;
        pre = root->val;
        if (another(root->right, pre) == false)
            return false;

        return true;
    }

    bool isValidBST2(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int min = INT_MAX, max = INT_MIN;
        return isValidBSTHelper(root, min, max);
    }

    bool isValidBSTHelper(TreeNode *root, int &min, int &max) {

        if (root == NULL) {
            min = INT_MAX;
            max = INT_MIN;
            return true;
        }

        int left_min, left_max, right_min, right_max;
        if (isValidBSTHelper(root->left, left_min, left_max) == false)
            return false;
        if (isValidBSTHelper(root->right, right_min, right_max) == false)
            return false;

        if (root->val <= left_max || root->val >= right_min) {
            return false;
        } else {
            min = left_min < right_min ? left_min : right_min;
            min = min < root->val ? min : root->val;
            max = left_max > right_max ? left_max : right_max;
            max = max > root->val ? max : root->val;
            return true;
        }
    }
};


int main(void) {
    Solution solution;
    TreeNode *root = new TreeNode(8);
    root->left = new TreeNode(3);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(1);
    //root->left->right = new TreeNode(9);

    cout << solution.isValidBST(root) << endl;
    cout << solution.isValidBST2(root) << endl;
}
