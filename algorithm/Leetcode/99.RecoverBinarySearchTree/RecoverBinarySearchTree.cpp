// Two elements of a binary search tree (BST) are swapped by mistake.
// Recover the tree without changing its structure.

// Note:
// A solution using O(n) space is pretty straight forward. Could you devise a
// constant space solution?

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
private:
    vector<TreeNode*> inorder;

public:

    // O(1) space solution
    // http://fisherlei.blogspot.com/2012/12/leetcode-recover-binary-search-tree.html
    void recoverTree(TreeNode *root) {
    }


    // O(n) space solution
    void recoverTree1(TreeNode *root) {

        // inorder tranversal of the tree
        inorder.clear();        // for leetcode OJ
        recoverTreeInorder(root);

        if (root == NULL || (root->left == NULL && root->right == NULL))
            return;

        // find the first element that violate BST property
        int i, j;
        for (i = 0; i < inorder.size() - 1; i++) {
            if (inorder[i]->val > inorder[i+1]->val) {
                break;
            }
        }

        // find the last element that violate BST property
        bool find = false;
        for (j = i + 1; j < inorder.size() - 1; j++) {
            if (inorder[j]->val > inorder[j+1]->val) {
                j = j + 1;
                find = true;
                break;
            }
        }
        // handle the case where two adjacent elements got swapped
        if (find == false) {
            j = i + 1;
        }

        int tmp = inorder[i]->val;
        inorder[i]->val = inorder[j]->val;
        inorder[j]->val = tmp;
    }

    void recoverTreeInorder(TreeNode *root) {
        if (root == NULL)
            return;
        recoverTreeInorder(root->left);
        inorder.push_back(root);
        recoverTreeInorder(root->right);
    }


    // O(n), standard in-order traversal
    void recoverTree2(TreeNode *root) {

        TreeNode *prev = NULL, *first = NULL, *second = NULL;

        recoverTree2Helper(root, prev, first, second);

        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }

    void recoverTree2Helper(TreeNode *root, TreeNode *&prev,
                            TreeNode *&first, TreeNode *&second) {
        if (root == NULL)
            return;

        recoverTree2Helper(root->left, prev, first, second);
        if (prev && root->val < prev->val) {
            if (first == NULL) {
                first = prev;
            }
            // tricky, second should always set to root
            second = root;
        }
        prev = root;
        recoverTree2Helper(root->right, prev, first, second);
    }
};


int main(void) {

    Solution solution;

    TreeNode *root = new TreeNode(0);
    root->left = new TreeNode(1);
    //root->right = new TreeNode(1);

    solution.recoverTree2(root);
}
