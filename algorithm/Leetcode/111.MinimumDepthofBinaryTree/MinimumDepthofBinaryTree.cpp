// Given a binary tree, find its minimum depth.

// The minimum depth is the number of nodes along the shortest path from the
// root node down to the nearest leaf node.

#include <list>
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
    int minDepth(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        if (root == NULL)
            return 0;

        list<TreeNode*> queue;
        int depth = 1;
        int count = 1;

        queue.push_back(root);
        while (count > 0) {
            while (count > 0) {
                TreeNode *cur = queue.front(); queue.pop_front();
                if (cur->left == NULL && cur->right == NULL)
                    return depth;
                if (cur->left != NULL)
                    queue.push_back(cur->left);
                if (cur->right != NULL)
                    queue.push_back(cur->right);
                count--;
            }
            depth++;
            count = queue.size();
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

    cout << solution.minDepth(root) << endl;

    return 0;
}
