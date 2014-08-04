// Given a list, rotate the list to the right by k places, where k is
// non-negative.

// For example:
//    Given  1->2->3->4->5->NULL and k = 2,
//    Return 4->5->1->2->3->NULL.

#include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        if (head == NULL || head->next == NULL)
            return head;

        // handle k > list size
        int size = 0;
        for (ListNode *tmp = head; tmp != NULL; tmp = tmp->next)
            size++;
        k = k % size;
        if (k == 0)
            return head;

        ListNode *pre = head, *cur = pre->next, *last = head, *new_head;
        // move k steps forward
        while (k-- > 0) {
            last = last->next;
        }

        // find start and end of rotate part
        while (last->next != NULL) {
            pre = cur;
            cur = cur->next;
            last = last->next;
        }

        // do rotation
        new_head = cur;
        pre->next = NULL;
        last->next = head;

        return new_head;
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

    probe = solution.rotateRight(head, 8);

    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    return 0;
}

