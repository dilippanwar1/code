// Given a singly linked list where elements are sorted in ascending order,
// convert it to a height balanced BST.

#include <vector>
#include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:

    TreeNode *sortedListToBST(ListNode *head) {

        int size = 0;

        if (head == NULL)
            return NULL;

        ListNode *tmp = head;
        while (tmp != NULL) {
            size++;
            tmp = tmp->next;
        }

        return sortedListToBSTHelper(head, 0, size-1);
    }

    TreeNode *sortedListToBSTHelper(ListNode *&head, int left, int right) {

        if (left > right)
            return NULL;

        int mid = left + (right - left) / 2;
        TreeNode *leftChild = sortedListToBSTHelper(head, left, mid-1);
        TreeNode *root = new TreeNode(head->val);
        root->left = leftChild;
        head = head->next;
        root->right = sortedListToBSTHelper(head, mid+1, right);

        return root;
    }

    // Convert list to array then build binary tree
    TreeNode *sortedListToBST2(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        if (head == NULL)
            return NULL;

        vector<int> num;
        while (head != NULL) {
            num.push_back(head->val);
            head = head->next;
        }

        return sortedArrayToBST(num);
    }

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

    Solution solution;
    ListNode *head = new ListNode(0);

    solution.sortedListToBST(head);
}
