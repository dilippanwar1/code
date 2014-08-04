/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode *root) {

        int cur_max = INT_MIN, all_max = INT_MIN;
        maxPathSumHelper(root, cur_max, all_max);
        return all_max;
    }

    void maxPathSumHelper(TreeNode *root, int &cur_max, int &all_max) {

        if (root == NULL) {
            cur_max = 0;
            return;
        }

        int left_max = 0, right_max = 0;
        maxPathSumHelper(root->left, left_max, all_max);
        maxPathSumHelper(root->right, right_max, all_max);

        cur_max = max(max(left_max + root->val, right_max + root->val), root->val);
        all_max = max(max(cur_max, left_max + root->val + right_max), all_max);
    }
};
