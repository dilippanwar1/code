// Given a linked list, remove the nth node from the end of list and return its head.

// For example,
//    Given linked list: 1->2->3->4->5, and n = 2.
//    After removing the second node from the end, the linked list becomes 1->2->3->5.
// Note:
//    Given n will always be valid.
//    Try to do this in one pass.

#include <stdio.h>
#include <stdlib.h>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {

        int forward = n;
        ListNode *fast = head, *slow = head, *pre_slow = head;

        while (forward != 0) {
            fast = fast->next;
            forward--;
        }

        while (fast != NULL) {
            pre_slow = slow;
            fast = fast->next;
            slow = slow->next;
        }

        // if slow pointer hasn't moved at all, corner case "n = length"
        if (slow == pre_slow) {
            return head->next;
        } else {
            pre_slow->next = slow->next;
            return head;
        }
    }
};

int main(void) {
    Solution solution;
    ListNode *head = new ListNode(10);

    solution.removeNthFromEnd(head, 1);
    return 0;
}
