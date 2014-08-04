// Given preorder and inorder traversal of a tree, construct the binary tree.

// Note:
// You may assume that duplicates do not exist in the tree.

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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (inorder.size() != preorder.size())
            return NULL;
        if (inorder.size() == 0)
            return NULL;

        unordered_map<int, int> map;
        for (int i = 0; i < inorder.size(); i++) {
            map[inorder[i]] = i;
        }

        return buildTreeHelper(preorder, 0, preorder.size() - 1,
                               inorder, 0, inorder.size() - 1, map);
    }

    TreeNode *buildTreeHelper(vector<int> &preorder, int pre_left, int pre_right,
                              vector<int> &inorder, int in_left, int in_right,
                              unordered_map<int, int> &map) {
        if (in_left > in_right)
            return NULL;
        if (in_left == in_right)
            return new TreeNode(preorder[pre_left]);

        int root_val = preorder[pre_left];
        int index = map[root_val];
        int left_size = index - in_left;   // left subtree size
        int right_size = in_right - index; // right subtree size
        TreeNode *root = new TreeNode(root_val);
        root->left = buildTreeHelper(preorder, pre_left+1, pre_left+left_size,
                                     inorder, in_left, index-1,
                                     map);
        root->right = buildTreeHelper(preorder, pre_right-right_size+1, pre_right,
                                      inorder, index+1, in_right,
                                      map);

        return root;
    }
};


int main(void) {

    Solution solution;
    int a[] = {3,9,20,15,7};
    int b[] = {9,3,15,20,7};
    vector<int> inorder(a, a+sizeof(a)/sizeof(a[0]));
    vector<int> ptorder(b, b+sizeof(b)/sizeof(b[0]));

    TreeNode *root = solution.buildTree(inorder, ptorder);
    //cout << root->right->val << endl;
    return 0;
}
