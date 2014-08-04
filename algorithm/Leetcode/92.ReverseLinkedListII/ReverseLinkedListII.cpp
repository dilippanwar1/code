// Reverse a linked list from position m to n. Do it in-place and in one-pass.

// For example:
//    Given  1->2->3->4->5->NULL, m = 2 and n = 4,
//    Return 1->4->3->2->5->NULL.

// Note:
// Given m, n satisfy the following condition:
// 1 < m < n < length of list.

#include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {

        // we only check head as corner condition, since m, n satisfy
        // given conditions
        if (head == NULL || head->next == NULL)
            return head;

        // handle m == 1
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        head = dummy;
        m = m + 1;
        n = n + 1;

        ListNode *prev = head, *cur = head->next, *prevM;
        for (int i = 1; i < n; i++) {
            if (i >= m) { // in-place reverse, record next node before swap
                ListNode *tmp = cur->next;
                cur->next = prev;
                prev = cur;
                cur = tmp;
            } else {
                prevM = prev; // move forward and record previous node of m
                prev = cur;
                cur = cur->next;
            }
        }
        prevM->next->next = cur; // handle prevM
        prevM->next = prev;

        delete dummy;
        return head->next;
    }
};


int main(void) {

    Solution solution;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next->next = new ListNode(7);

    ListNode *probe = head;
    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    probe = solution.reverseBetween(head, 1, 7);

    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    return 0;
}
