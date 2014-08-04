// Follow up for problem "Populating Next Right Pointers in Each Node".

// What if the given tree could be any binary tree? Would your previous
// solution still work?

// Note:
//    You may only use constant extra space.

// For example,
// Given the following binary tree,
//          1
//        /  \
//       2    3
//      / \    \
//     4   5    7
// After calling your function, the tree should look like:
//          1 -> NULL
//        /  \
//       2 -> 3 -> NULL
//      / \    \
//     4-> 5 -> 7 -> NULL

#include <list>
#include <iostream>
using namespace std;


struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};


class Solution {
public:

    void connect(TreeLinkNode *root) {
        if (root == NULL)
            return;

        root->next = NULL;
        TreeLinkNode *level = root;

        // basic idea is to use previous level's linked list
        while (level != NULL) {
            TreeLinkNode *next_level = NULL;
            TreeLinkNode *next_level_head = NULL;
            for (; level != NULL; level = level->next) {
                if (next_level == NULL) {
                    next_level = level->left;
                    if (next_level == NULL) { // left child is NULL
                        next_level = level->right;
                        if (next_level != NULL)
                            next_level_head = next_level;
                    } else {
                        next_level_head = next_level;
                        if (level->right != NULL) {
                            next_level->next = level->right;
                            next_level = level->right;
                        }
                    }
                } else {
                    if (level->left != NULL) {
                        next_level->next = level->left;
                        next_level = level->left;
                    }
                    if (level->right != NULL) {
                        next_level->next = level->right;
                        next_level = level->right;
                    }
                }
            }
            if (next_level != NULL)
                next_level->next = NULL;
            level = next_level_head;
        }
    }

    // Not constant memory
    void connect2(TreeLinkNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL)
            return;

        int count = 1;
        list<TreeLinkNode*> layer;
        layer.push_back(root);

        while (count > 0) {
            while (count > 0) {
                TreeLinkNode *cur = layer.front(); layer.pop_front();
                if (count == 1) { // last element in this level
                    cur->next = NULL;
                } else {
                    cur->next = layer.front();
                }
                if (cur->left != NULL)
                    layer.push_back(cur->left);
                if (cur->right != NULL)
                    layer.push_back(cur->right);
                count--;
            }
            count = layer.size();
        }
    }
};


int main(void) {

    Solution solution;

    TreeLinkNode *root = new TreeLinkNode(1);
    root->left = new TreeLinkNode(2);
    root->right = new TreeLinkNode(3);
    root->left->left = new TreeLinkNode(4);
    root->left->right = new TreeLinkNode(5);
    //root->right->left = new TreeLinkNode(6);
    root->right->right = new TreeLinkNode(7);

    solution.connect(root);

    cout << root->left->right->next->val << endl;
}
