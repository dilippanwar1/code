// Given a binary tree, return the zigzag level order traversal of its nodes'
// values. (ie, from left to right, then right to left for the next level and
// alternate between).

// For example:
// Given binary tree {3,9,20,#,#,15,7},
//     3
//    / \
//   9  20
//     /  \
//    15   7
// return its zigzag level order traversal as:
// [
//   [3],
//   [20,9],
//   [15,7]
// ]

#include <list>
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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {

        vector<vector<int> > result;
        stack<TreeNode*> stk1, stk2;
        vector<int> current;

        if (root == NULL)
            return result;

        stk1.push(root);
        while (!stk1.empty() || !stk2.empty()) {
            while (!stk1.empty()) {
                TreeNode *node = stk1.top(); stk1.pop();
                current.push_back(node->val);
                if (node->left != NULL) stk2.push(node->left);
                if (node->right != NULL) stk2.push(node->right);
            }
            if (current.size() != 0) result.push_back(current);
            current.clear();
            while (!stk2.empty()) {
                TreeNode *node = stk2.top(); stk2.pop();
                current.push_back(node->val);
                if (node->right != NULL) stk1.push(node->right);
                if (node->left != NULL) stk1.push(node->left);
            }
            if (current.size() != 0) result.push_back(current);
            current.clear();
        }

        return result;
    }

    vector<vector<int> > zigzagLevelOrder2(TreeNode *root) {

        int count = 1;
        list<TreeNode*> lst;
        vector<int> level;
        vector<vector<int> > result;

        if (root == NULL)
            return result;

        lst.push_back(root);
        while (count > 0) {
            while (count > 0) {
                TreeNode *cur = lst.front(); lst.pop_front();
                level.push_back(cur->val);
                if (cur->left != NULL)
                    lst.push_back(cur->left);
                if (cur->right != NULL)
                    lst.push_back(cur->right);
                count--;
            }
            result.push_back(level);
            level.clear();
            count = lst.size();
        }

        // reverse
        for (int i = 1; i < result.size(); i += 2) {
            reverse(result[i]);
        }

        return result;
    }

private:
    void reverse(vector<int> &numbers) {

        int i = 0, j = numbers.size() - 1;

        while (i < j) {
            int tmp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = tmp;
            i++;
            j--;
        }
    }
};


int main(void) {

    Solution solution;

    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<vector<int> > result = solution.zigzagLevelOrder2(root);

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}
