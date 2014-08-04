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


/**
 * Mirror a tree
 */
class Solution {
public:
    TreeNode *mirror(TreeNode *root) {

        if (root == NULL)
            return NULL;

        TreeNode *node = new TreeNode(root->val);
        node->left = mirror(root->right);
        node->right = mirror(root->left);

        return node;
    }
};


int main(void) {

    Solution solution;

    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(9);
    root->right->right = new TreeNode(8);

    TreeNode* result = solution.mirror(root);
    cout << result->val << endl;
    cout << result->left->val << endl;
    cout << result->right->val << endl;
    cout << result->left->left->val << endl;
    cout << result->right->left->val << endl;

    return 0;
}
