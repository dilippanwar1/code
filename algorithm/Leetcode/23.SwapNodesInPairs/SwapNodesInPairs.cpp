// Given a linked list, swap every two adjacent nodes and return its head.

// For example,
//    Given 1->2->3->4, you should return the list as 2->1->4->3.

// Your algorithm should use only constant space. You may not modify the values
// in the list, only nodes itself can be changed.

#include <stdio.h>
#include <stdlib.h>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *swapPairs(ListNode *head) {

        // Corner cases
        if (head == NULL || head->next == NULL) {
            return head;
        }

        ListNode *res = head->next; // bookkeeping, we need to return head->next
        ListNode *first = head, *second = head->next;
        ListNode *prev = NULL;  // previous node of current swaping pair

        while (first != NULL && second != NULL) {

            // swap pair as well as update next field of previous pair
            first->next = second->next;
            second->next = first;
            if (prev != NULL)   // avoid first time update
                prev->next = second;

            // proceed to next pair
            prev = first;
            first = first->next;
            if (first == NULL)  // even number of nodes
                break;
            second = first->next;
        }

        return res;
    }

    ListNode *swapPairs2(ListNode *head) {

        // Corner cases
        if (head == NULL || head->next == NULL) {
            return head;
        }

        ListNode *res = head->next; // bookkeeping, we need to return head->next
        ListNode *first = head, *second = head->next;

        while (second != NULL) {
            // swap pair as well as update next field of previous pair
            ListNode *tmp = second->next;
            second->next = first;
            if (tmp == NULL)
                first->next = NULL;
            else if (tmp->next == NULL)
                first->next = tmp;
            else
                first->next = tmp->next;

            first = tmp;
            if (tmp == NULL)
                break;
            second = tmp->next;
        }

        return res;
    }
};


int main(void) {

    Solution solution;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    // head->next->next->next = new ListNode(4);
    // head->next->next->next->next = new ListNode(5);
    //head->next->next->next->next->next = new ListNode(6);

    head = solution.swapPairs2(head);

    printf("%d", head->val);
    ListNode* temp = head->next;
    while (temp != NULL) {
        printf("->%d", temp->val);
        temp = temp->next;
    }
    printf("\n");
}
