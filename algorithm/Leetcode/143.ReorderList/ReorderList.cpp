// Given a singly linked list L: L0->L1->...->Ln-1->Ln,
// reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->...

// You must do this in-place without altering the nodes' values.

// For example,
// Given {1,2,3,4}, reorder it to {1,4,2,3}.

#include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    void reorderList(ListNode *head)
    {
        ListNode *temp = head;

        if (head == NULL || head->next == NULL)
            return;

        reorderListHelper(temp, head);
    }

    bool reorderListHelper(ListNode *&head, ListNode *tail)
    {
        if (tail == NULL)
            return false;

        if (reorderListHelper(head, tail->next))
            return true;

        if (head->next == tail || head == tail) {
            tail->next = NULL;
            return true;
        } else {
            tail->next = head->next;
            head->next = tail;
            head = tail->next;
            return false;
        }
    }
};


int main(void)
{
    Solution solution;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);

    solution.reorderList(head);

    ListNode *probe = head;
    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    return 0;
}
