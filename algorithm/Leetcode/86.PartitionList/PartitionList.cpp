// Given a linked list and a value x, partition it such that all nodes less
// than x come before nodes greater than or equal to x.

// You should preserve the original relative order of the nodes in each of
// the two partitions.

// For example,
//    Given 1->4->3->2->5->2 and x = 3,
//    return 1->2->2->4->3->5.

#include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head == NULL || head->next == NULL)
            return head;

        ListNode *before = NULL, *after = NULL;
        ListNode *before_head = NULL, *after_head = NULL;

        for (ListNode *p = head; p != NULL; p = p->next) {

            if (p->val >= x) {  // we should append to after list
                if (after == NULL) {
                    after = p;
                    after_head = p;
                } else {
                    after->next = p;
                    after = p;
                }
            } else {            // we should append to before list
                if (before == NULL) {
                    before = p;
                    before_head = p;
                } else {
                    before->next = p;
                    before = p;
                }
            }
        }

        if (after != NULL)      // if we have numbers bigger than x
            after->next = NULL; // clear last number to avoid circle

        if (before != NULL) {   // if we have numbers less than x
            before->next = after_head;
            return before_head;
        } else {                // all numbers all bigger than x
            return after_head;
        }
    }
};


int main(void) {

    Solution solution;
    ListNode *head = new ListNode(7);
    head->next = new ListNode(4);
    head->next->next = new ListNode(6);
    head->next->next->next = new ListNode(9);

    head = solution.partition(head, 13);

    while (head != NULL) {
        cout << head->val << endl;
        head = head->next;
    }

    return 0;
}
