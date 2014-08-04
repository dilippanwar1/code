// Given a binary tree, return the postorder traversal of its nodes' values.

// For example:
// Given binary tree {1,#,2,3},
//    1
//     \
//      2
//     /
//    3
// return [3,2,1].

// Note: Recursive solution is trivial, could you do it iteratively?


#include <stack>
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> stk;
        unordered_set<TreeNode *> set;

        if (root == NULL)
            return result;

        stk.push(root);
        while (!stk.empty()) {
            TreeNode *current = stk.top();
            if (set.find(current) == set.end()) {
                set.insert(current);
                if (current->right)
                    stk.push(current->right);
                if (current->left)
                    stk.push(current->left);
            } else {
                result.push_back(current->val);
                stk.pop();
            }
        }

        return result;
    }
};


int main(void)
{
    Solution solution;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(4);

    vector<int> result = solution.postorderTraversal(root);

    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    cout << endl;

    return 0;
}
