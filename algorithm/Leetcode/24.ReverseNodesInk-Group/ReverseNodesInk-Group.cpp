// Given a linked list, reverse the nodes of a linked list k at a time and
// return its modified list.

// If the number of nodes is not a multiple of k then left-out nodes in the
// end should remain as it is.

// You may not alter the values in the nodes, only nodes itself may be changed.
// Only constant memory is allowed.

// For example,
//    Given this linked list: 1->2->3->4->5
//    For k = 2, you should return: 2->1->4->3->5
//    For k = 3, you should return: 3->2->1->4->5


#include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {

        if (k == 1 || head == NULL || head->next == NULL)
            return head;

        ListNode *p_head = NULL;
        ListNode *c_head = head;
        ListNode *ret = head;
        ListNode *tmp;
        ListNode *p = head, *q = head->next;

        while (c_head != NULL) {

            // Test if there are enough nodes to reverse
            ListNode *test = p;
            int tst = k-1;
            while (test != NULL && tst-- > 0) {
                test = test->next;
            }
            if (test == NULL) {
                // point previous head to start of current list
                if (p_head != NULL)
                    p_head->next = p;
                return ret;
            }

            int t = k - 1;
            while (t-- > 0) {   // reverse t times for current
                tmp = q->next;
                q->next = p;
                p = q;
                q = tmp;
            }
            // update return value for the first time
            if (ret == head)
                ret = p;
            // if previous head is NULL, we are reversing the first list segment
            if (p_head != NULL) {
                p_head->next = p;
            }

            // update information for reversing next list segment
            p_head = c_head;
            c_head->next = NULL;
            c_head = tmp;
            p = tmp;
            if (p == NULL)      // even case
                break;
            q = p->next;
        }

        return ret;
    }


    // Elegent solution from web
    ListNode *reverseKGroupWeb(ListNode *head, int k) {

        if (!head || k <= 1)
            return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode *pre = &dummy;

        int i = 0;
        while (head) {
            i++;
            if (i % k == 0) {   // time to reverse
                pre = reverse(pre, head->next);
                head = pre->next;
            } else {
                head = head->next;
            }
        }

        return dummy.next;
    }

    // reverse between node `pre` and node `next`, exclusive. also make
    // sure that pre->next point to the right element. E.g.
    // x -> 1 -> 2 -> 3 -> NULL  (pre = x, next = NULL)
    // After return
    // x -> 3 -> 2 -> 1 -> NULL  (return last point to NULL, here is "1")
    ListNode *reverse(ListNode *pre, ListNode *next) {

        ListNode *last = pre->next;
        ListNode *cur = last->next;

        while (cur != next) {

            last->next = cur->next;
            cur->next = pre->next;
            pre->next = cur;

            cur = last->next;
        }

        return last;
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
    head->next->next->next->next->next->next->next = new ListNode(8);
    head->next->next->next->next->next->next->next->next = new ListNode(9);
    head->next->next->next->next->next->next->next->next->next = new ListNode(10);

    ListNode *probe = head;
    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    probe = solution.reverseKGroupWeb(head, 3);

    while (probe != NULL) {
        cout << probe->val << " ";
        probe = probe->next;
    }
    cout << endl;

    return 0;
}
