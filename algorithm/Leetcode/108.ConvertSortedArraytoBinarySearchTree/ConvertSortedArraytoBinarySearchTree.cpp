// Given an array where elements are sorted in ascending order, convert it
// to a height balanced BST.

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
    TreeNode *sortedArrayToBST(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (num.size() == 0)
            return NULL;

        return sortedArrayToBSTHelper(num, 0, num.size()-1);
    }

    TreeNode *sortedArrayToBSTHelper(vector<int> &num, int left, int right) {

        if (left == right)
            return new TreeNode(num[left]);
        else if (left > right)
            return NULL;

        int mid = (left + right) / 2;
        TreeNode *root = new TreeNode(num[mid]);
        root->left = sortedArrayToBSTHelper(num, left, mid-1);
        root->right = sortedArrayToBSTHelper(num, mid+1, right);

        return root;
    }
};


int main(void) {
    return 0;
}
