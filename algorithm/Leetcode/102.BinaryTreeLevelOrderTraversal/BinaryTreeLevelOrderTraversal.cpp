// Given a binary tree, return the level order traversal of its nodes' values.
// (ie, from left to right, level by level).

// For example:
// Given binary tree {3,9,20,#,#,15,7},
//     3
//    / \
//   9  20
//     /  \
//    15   7
// return its level order traversal as:
// [
//   [3],
//   [9,20],
//   [15,7]
// ]

#include <list>
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
    vector<vector<int> > levelOrder(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        int count = 1;
        list<TreeNode*> lst;
        vector<int> level;
        vector<vector<int> > result;

        if (root == NULL)
            return result;

        lst.push_back(root);
        while (count > 0) {
            while (count > 0) {
                TreeNode *cur = lst.front(); lst.pop_front();
                level.push_back(cur->val);
                if (cur->left != NULL)
                    lst.push_back(cur->left);
                if (cur->right != NULL)
                    lst.push_back(cur->right);
                count--;
            }
            result.push_back(level);
            level.clear();
            count = lst.size();
        }

        return result;
    }
};


int main(void) {

    Solution solution;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(8);

    vector<vector<int> > result = solution.levelOrder(root);

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}
