// Given inorder and postorder traversal of a tree, construct the binary tree.

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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (inorder.size() != postorder.size())
            return NULL;
        if (inorder.size() == 0)
            return NULL;

        unordered_map<int, int> map;
        for (int i = 0; i < inorder.size(); i++) {
            map[inorder[i]] = i;
        }

        return buildTreeHelper(inorder, 0, inorder.size() - 1,
                               postorder, 0, postorder.size() - 1, map);
    }

    TreeNode *buildTreeHelper(vector<int> &inorder, int in_left, int in_right,
                              vector<int> &ptorder, int pt_left, int pt_right,
                              unordered_map<int, int> &map) {
        if (in_left > in_right)
            return NULL;
        if (in_left == in_right)
            return new TreeNode(ptorder[pt_right]);

        int root_val = ptorder[pt_right];
        int index = map[root_val];
        int left_size = index - in_left;   // left subtree size
        int right_size = in_right - index; // right subtree size
        TreeNode *root = new TreeNode(root_val);
        root->left = buildTreeHelper(inorder, in_left, index-1,
                                     ptorder, pt_left, pt_left+left_size-1,
                                     map);
        root->right = buildTreeHelper(inorder, index+1, in_right,
                                      ptorder, pt_right-right_size, pt_right-1,
                                      map);

        return root;
    }
};


int main(void) {

    Solution solution;
    int a[] = {3,15,20,7};
    int b[] = {15,7,20,3};
    vector<int> inorder(a, a+sizeof(a)/sizeof(a[0]));
    vector<int> ptorder(b, b+sizeof(b)/sizeof(b[0]));

    TreeNode *root = solution.buildTree(inorder, ptorder);
    //cout << root->right->val << endl;
    return 0;
}
