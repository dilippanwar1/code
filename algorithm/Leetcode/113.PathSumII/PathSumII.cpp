// Given a binary tree and a sum, find all root-to-leaf paths where each
// path's sum equals the given sum.

// For example:
// Given the below binary tree and sum = 22,
//               5
//              / \
//             4   8
//            /   / \
//           11  13  4
//          /  \    / \
//         7    2  5   1
// return
// [
//    [5,4,11,2],
//    [5,8,4,5]
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
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> path;
        vector<vector<int> > result;

        pathSumHelper(root, sum, path, result);
        return result;
    }

private:
    void pathSumHelper(TreeNode *root, int sum, vector<int> path,
                       vector<vector<int> > &result) {
        if (root == NULL)
            return;

        if (root->left == NULL && root->right == NULL) {
            if (root->val == sum) {
                path.push_back(root->val);
                result.push_back(path);
                path.pop_back();
            }
        }

        path.push_back(root->val);
        pathSumHelper(root->left, sum-root->val, path, result);
        pathSumHelper(root->right, sum-root->val, path, result);
        path.pop_back();
    }
};


int main(void) {

    Solution solution;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(2);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(7);

    vector<vector<int> > result = solution.pathSum(root, 11);
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
