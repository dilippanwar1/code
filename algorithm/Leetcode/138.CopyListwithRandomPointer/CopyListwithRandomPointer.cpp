// A linked list is given such that each node contains an additional random
// pointer which could point to any node in the list or null.

// Return a deep copy of the list.

#include <iostream>
using namespace std;


struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};


class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {

        if (head == NULL)
            return NULL;

        RandomListNode *probe = head;
        // insert new node after corresponding node in original list
        while (probe != NULL) {
            RandomListNode *clone = new RandomListNode(probe->label);
            clone->next = probe->next;
            probe->next = clone;
            probe = probe->next->next;
        }

        // deal with random pointer of cloned list
        probe = head;
        while (probe != NULL) {
            if (probe->random != NULL)
                probe->next->random = probe->random->next;
            probe = probe->next->next;
        }

        // separate original list and cloned list
        probe = head;
        RandomListNode *clone_head = probe->next;
        RandomListNode *clone_probe = clone_head;
        while (probe != NULL) {
            probe->next = clone_probe->next;
            if (probe->next != NULL) // make sure it's not the last one
                clone_probe->next = probe->next->next;
            probe = probe->next;
            clone_probe = clone_probe->next;
        }

        return clone_head;
    }
};


int main(void) {

    Solution solution;

    RandomListNode *head = new RandomListNode(-1);
    RandomListNode *clone = solution.copyRandomList(head);

    return 0;
}
