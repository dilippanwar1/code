// You are given two linked lists representing two non-negative numbers. The
// digits are stored in reverse order and each of their nodes contain a single
// digit. Add the two numbers and return it as a linked list.

// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8

#include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {

        ListNode *head = new ListNode(-1);
        ListNode *p = head;
        int carry = 0;

        while (l1 != NULL || l2 != NULL || carry != 0) {

            int sum = 0;
            if (l1 != NULL) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                sum += l2->val;
                l2 = l2->next;
            }
            if (carry != 0) {
                sum += carry;
                carry = 0;
            }

            if (sum > 9) {
                carry = 1;
                sum = sum % 10;
            }

            p->next = new ListNode(sum);
            p = p->next;
        }

        p = head->next;
        delete head;
        return p;
    }
};


int main(void) {

    Solution solution;

    ListNode *head = new ListNode(2);
    head->next = new ListNode(3);
    head->next->next = new ListNode(4);

    ListNode *tail = new ListNode(6);
    tail->next = new ListNode(4);


    ListNode *probe = solution.addTwoNumbers(head, tail);

    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    return 0;
}
