// Given a binary tree, return the preorder traversal of its nodes' values.

// For example:
// Given binary tree {1,#,2,3},
//    1
//     \
//      2
//     /
//    3
// return [1,2,3].

// Note: Recursive solution is trivial, could you do it iteratively?

#include <stack>
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

    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> stk;

        if (root == NULL)
            return result;

        stk.push(root);
        while (!stk.empty()) {
            TreeNode *current = stk.top(); stk.pop();
            result.push_back(current->val);
            if (current->right)
                stk.push(current->right);
            if (current->left)
                stk.push(current->left);
        }

        return result;
    }

    vector<int> preorderTraversal1(TreeNode *root)
    {
        vector<int> result;
        preorderTraversalHelper(root, result);
        return result;
    }

    void preorderTraversalHelper(TreeNode *root, vector<int> &result)
    {
        if (root == NULL)
            return;

        result.push_back(root->val);
        preorderTraversalHelper(root->left, result);
        preorderTraversalHelper(root->right, result);
    }
};


int main(void)
{
    Solution solution;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(4);

    vector<int> result = solution.preorderTraversal(root);

    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    cout << endl;

    return 0;
}
