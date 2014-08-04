// Merge k sorted linked lists and return it as one sorted list.
// Analyze and describe its complexity.

import java.util.*;


class ListNode {
    int val;
    ListNode next;
    ListNode(int x) {
        val = x;
        next = null;
    }
}

public class MergekSortedLists {

    // From forum
    public ListNode mergeKLists(ArrayList<ListNode> lists) {

        if (lists == null || lists.isEmpty())
            return null;

        Comparator<ListNode> comparator = new Comparator<ListNode>() {
            @Override
            public int compare(ListNode n1, ListNode n2) {
                if (n1.val < n2.val)
                    return -1;
                else if (n1.val > n2.val)
                    return 1;
                else
                    return 0;
            }
        };

        PriorityQueue<ListNode> heap = new
            PriorityQueue<ListNode>(lists.size(), comparator);
        ListNode head = null;
        ListNode cur = null;

        for (int i = 0; i < lists.size(); i++) {
            // add first element of each list into heap
            ListNode node = lists.get(i);
            if (node != null)
                heap.add(lists.get(i));
        }

        // heap sort, e.g. smallest value must be the head of all sorted lists
        while (!heap.isEmpty()) {
            if (head == null) {
                head = heap.poll();
                cur = head;
                if (cur.next != null)
                    heap.add(cur.next);
            } else {
                ListNode newNode = heap.poll();
                cur.next = newNode;
                cur = newNode;
                if (cur.next != null)
                    heap.add(cur.next);
            }
        }

        return head;
    }
};
