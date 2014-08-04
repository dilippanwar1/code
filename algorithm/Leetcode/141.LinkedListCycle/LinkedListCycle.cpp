// Given a linked list, determine if it has a cycle in it.

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
    bool hasCycle(ListNode *head) {

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
            return false;
        } else {
            return true;
        }
    }
};


int main(void) {
    return 0;
}
