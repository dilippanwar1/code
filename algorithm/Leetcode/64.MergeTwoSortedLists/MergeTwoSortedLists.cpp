// Merge two sorted linked lists and return it as a new list. The new list
// should be made by splicing together the nodes of the first two lists.


#include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {

        // make sure each list has at least one node
        if (l1 == NULL && l2 == NULL)
            return NULL;
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;

        // compute new head first to simplify logic below
        ListNode *new_head, *probe;
        if (l1->val < l2->val) {
            new_head = l1;
            l1 = l1->next;
        } else {
            new_head = l2;
            l2 = l2->next;
        }
        probe = new_head;

        while (l1 != NULL && l2 != NULL) {
            if (l1->val < l2->val) {
                probe->next = l1;
                l1 = l1->next;
                probe = probe->next;
            } else {
                probe->next = l2;
                l2 = l2->next;
                probe = probe->next;
            }
        }

        // handle remainning part
        if (l1 != NULL)
            probe->next = l1;
        else if (l2 != NULL)
            probe->next = l2;

        return new_head;
    }
};


int main(void) {

    Solution solution;
    ListNode *l1 = new ListNode(3);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(8);
    l1->next->next->next = new ListNode(9);
    l1->next->next->next->next = new ListNode(12);
    ListNode *probe = l1;
    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    ListNode *l2 = new ListNode(6);
    l2->next = new ListNode(10);
    l2->next->next = new ListNode(11);
    l2->next->next->next = new ListNode(13);
    l2->next->next->next->next = new ListNode(14);

    probe = l2;
    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;


    probe = solution.mergeTwoLists(l1, l2);

    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    return 0;
}
