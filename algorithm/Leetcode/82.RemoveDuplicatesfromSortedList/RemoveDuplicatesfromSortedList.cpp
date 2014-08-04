// Given a sorted linked list, delete all duplicates such that each element
// appear only once.

// For example,
//    Given 1->1->2, return 1->2.
//    Given 1->1->2->3->3, return 1->2->3.


#include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {

        if (head == NULL || head->next == NULL)
            return head;

        ListNode *pre = head, *cur = pre->next;

        while (cur != NULL) {
            if (pre->val == cur->val) {
                // delete cur, we can free it using a tmp value
                cur = cur->next;
            } else {
                pre->next = cur;
                pre = cur;
                cur = cur->next;
            }
        }
        pre->next = NULL;

        return head;
    }
};


int main(void) {

    Solution solution;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(7);
    head->next->next->next->next->next->next = new ListNode(7);

    ListNode *probe = head;
    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    probe = solution.deleteDuplicates(head);

    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    return 0;
}
