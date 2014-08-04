// Given a linked list, return the node where the cycle begins. If there is
// no cycle, return null.

// Follow up:
// Can you solve it without using extra space?


#include <iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *detectCycle(ListNode *head) {

        if (head == NULL)
            return false;

        ListNode *slow = head, *fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break;
            }
        }

        if (fast == NULL || fast->next == NULL) {
            return NULL;
        } else {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
};


int main(void) {
    return 0;
}
