// Given a sorted linked list, delete all nodes that have duplicate numbers,
// leaving only distinct numbers from the original list.

// For example,
//    Given 1->2->3->3->4->4->5, return 1->2->5.
//    Given 1->1->1->2->3, return 2->3.


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

        ListNode *dummy = new ListNode(INT_MIN);
        dummy->next = head;
        head = dummy;

        ListNode *preA = head, *pre = preA->next, *cur = pre->next;

        bool found = false;
        while (cur != NULL) {
            if (pre->val == cur->val) {
                found = true;
                pre = cur;
                cur = cur->next;
            } else {
                if (found == true) {
                    found = false;
                    preA->next = cur; // do not update preA here
                } else {
                    preA = pre;
                }
                pre = cur;
                cur = cur->next;
            }
        }

        // remember to check `found`, which means we have duplicates
        // at last
        if (found == true) {
            preA->next = cur;
        }

        delete dummy;
        return head->next;
    }
};


int main(void) {

    Solution solution;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(3);
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
