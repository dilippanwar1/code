// Given a binary tree, return the inorder traversal of its nodes' values.

// For example:
// Given binary tree {1,#,2,3},
//    1
//     \
//      2
//     /
//    3
// return [1,3,2].

// Note: Recursive solution is trivial, could you do it iteratively?
// g++-4.8 BinaryTreeInorderTraversal.cpp -o BinaryTreeInorderTraversal -std=c++11

#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:

    // Trivial recursive version
    vector<int> inorderTraversal(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> result;
        inorderTraversalHelper(root, result);
        return result;
    }

    // Iterative version using stack
    vector<int> inorderTraversalIterative(TreeNode *root) {

        vector<int> result;
        stack<TreeNode*> stk;
        unordered_map<TreeNode*, bool> visited;

        if (root == NULL)
            return result;

        stk.push(root);
        while (!stk.empty()) {
            TreeNode *cur = stk.top();
            if (visited[cur] == true) {
                result.push_back(cur->val);
                stk.pop();
                if (cur->right != NULL)
                    stk.push(cur->right);
            } else {
                visited[cur] = true;
                if (cur->left != NULL) {
                    stk.push(cur->left);
                }
            }
        }
    }

    // Do not need to use `visited` map
    vector<int> inorderTraversalBetter(TreeNode *root) {

        vector<int> result;
        stack<TreeNode*> s;
        TreeNode *current = root;

        while (!s.empty() || current) {
            if (current) {
                s.push(current);
                current = current->left;
            } else {
                current = s.top(); s.pop();
                result.push_back(current->val);
                current = current->right;
            }
        }
        return result;
    }

private:
    void inorderTraversalHelper(TreeNode *root, vector<int> &result) {
        if (root == NULL)
            return;

        inorderTraversalHelper(root->left, result);
        result.push_back(root->val);
        inorderTraversalHelper(root->right, result);
    }
};


int main(void) {

    Solution solution;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(8);

    //vector<int> result = solution.inorderTraversalIterative(root);
    vector<int> result = solution.inorderTraversalBetter(root);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
