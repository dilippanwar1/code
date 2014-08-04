// Given a binary tree, flatten it to a linked list in-place.

// For example,
// Given
//          1
//         / \
//        2   5
//       / \   \
//      3   4   6
// The flattened tree should look like:
//    1
//     \
//      2
//       \
//        3
//         \
//          4
//           \
//            5
//             \
//              6

#include <iostream>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct Result {
    TreeNode *head;
    TreeNode *tail;
    Result(TreeNode *h, TreeNode *t) : head(h), tail(t) {}
};


class Solution {
public:

    // Better version
    void flatten(TreeNode *root) {
        TreeNode *next = NULL;
        flattenHelper(root, next);
    }

    void flattenHelper(TreeNode *root, TreeNode *&next) {

        if (root == NULL)
            return;

        flattenHelper(root->right, next);
        flattenHelper(root->left, next);

        root->right = next;
        next = root;
        root->left = NULL;
    }

    // My version: left child  will return a linked list with head and tail,
    // root insert it between itself and its right child.
    void flatten2(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL)
            return;

        Result *tmp = flattenHelper(root);
        delete tmp;
    }

    Result* flattenHelper(TreeNode *root) {

        if (root->left == NULL && root->right == NULL)
            return new Result(root, root);

        Result *res_left, *res_right;

        if (root->left != NULL) {
            res_left = flattenHelper(root->left);
            res_left->tail->right = root->right;
            root->right = res_left->head;
        } else {
            res_left = new Result(root, root);
        }

        // if original root's right is not NULL
        if (res_left->tail->right != NULL) {
            res_right = flattenHelper(res_left->tail->right);
        } else {
            // create dummy node
            res_right = new Result(res_left->tail, res_left->tail);
        }

        TreeNode *tmp = res_right->tail;
        delete res_left;
        delete res_right;

        root->left = NULL;      // clear left pointer then return
        tmp->left = NULL;
        return new Result(root, tmp);
    }
};


int main(void) {

    Solution solution;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(8);
    root->right->right = new TreeNode(2);

    solution.flatten2(root);

    while (root != NULL) {
        cout << root->val << endl;
        root = root->right;
    }
}
