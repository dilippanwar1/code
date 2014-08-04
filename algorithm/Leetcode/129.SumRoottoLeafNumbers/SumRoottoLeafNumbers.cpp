// Given a binary tree containing digits from 0-9 only, each root-to-leaf path
// could represent a number.

// An example is the root-to-leaf path 1->2->3 which represents the number 123.

// Find the total sum of all root-to-leaf numbers.

// For example,

//     1
//    / \
//   2   3
// The root-to-leaf path 1->2 represents the number 12.
// The root-to-leaf path 1->3 represents the number 13.

// Return the sum = 12 + 13 = 25.

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
    int sumNumbers(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL)
            return 0;

        int sum = 0;
        sumNumbersHelper(root, &sum);
        return sum;
    }

private:
    void sumNumbersHelper(TreeNode *root, int *leafSum) {

        // must init to 0 in case root has only one child
        int sumToLeft = 0, sumToRight = 0;

        // `root` is not NULL for sure here

        // if root is leaf, update leaf sum
        if (root->left == NULL && root->right == NULL) {
            *leafSum = *leafSum * 10 + root->val;
            return;
        }

        // if root is not leaf, pass current sum to children
        if (root->left != NULL) {
            sumToLeft = *leafSum * 10 + root->val;
            sumNumbersHelper(root->left, &sumToLeft);
        }
        if (root->right != NULL) {
            sumToRight = *leafSum * 10 + root->val;
            sumNumbersHelper(root->right, &sumToRight);
        }

        *leafSum = sumToLeft + sumToRight;
    }
};


int main(void) {

    Solution solution;
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    // root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(3);
    root->left->right->right = new TreeNode(2);

    cout << solution.sumNumbers(root) << endl;
    return 0;
}
