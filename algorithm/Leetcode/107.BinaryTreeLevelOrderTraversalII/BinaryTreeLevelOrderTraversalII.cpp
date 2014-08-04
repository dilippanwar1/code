// Given a binary tree, return the bottom-up level order traversal of its
// nodes' values. (ie, from left to right, level by level from leaf to root).

// For example:
// Given binary tree {3,9,20,#,#,15,7},
//     3
//    / \
//   9  20
//     /  \
//    15   7
// return its bottom-up level order traversal as:
// [
//   [15,7]
//   [9,20],
//   [3],
// ]

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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int height = maxDepth(root);
        vector<vector<int> > result(height);

        levelOrderBottomHelper(root, 0, height, result);
        return result;
    }

    void levelOrderBottomHelper(TreeNode *root, int level, int height,
                                vector<vector<int> > &result) {
        if (root == NULL)
            return;

        levelOrderBottomHelper(root->left, level+1, height, result);
        result[height-level-1].push_back(root->val);
        levelOrderBottomHelper(root->right, level+1, height, result);
    }

private:
    int maxDepth(TreeNode *root) {
        if (root == NULL)
            return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};


int main(void) {

    Solution solution;
    TreeNode *root = new TreeNode(3);
    // root->left = new TreeNode(9);
    // root->right = new TreeNode(20);
    // root->right->left = new TreeNode(15);
    // root->right->right = new TreeNode(7);

    vector<vector<int> > result = solution.levelOrderBottom(NULL);
    for (int i = 0; i < result.size(); i++) {
        cout << "[ ";
        vector<int> res = result[i];
        for (int j = 0; j < res.size(); j++) {
            cout << res[j] << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
