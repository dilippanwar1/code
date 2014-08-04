// You are given two linked lists representing two non-negative numbers.
// The digits are stored in reverse order and each of their nodes contain
// a single digit. Add the two numbers and return it as a linked list.
// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8


class ListNode {

    public int val;
    public ListNode next;

    public ListNode(int x) {
        val = x;
        next = null;
    }
}

public class AddTwoNumbers {

    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {

        int carry = 0;
        ListNode sum = new ListNode(0);
        ListNode prev = sum;

        while (l1 != null && l2 != null) {
            ListNode node = new ListNode((l1.val+l2.val+carry) % 10);
            carry = (l1.val + l2.val + carry) / 10;
            prev.next = node;
            prev = node;
            l1 = l1.next;
            l2 = l2.next;
        }

        while (l1 != null) {
            ListNode node = new ListNode((l1.val+carry) % 10);
            carry = (l1.val + carry) / 10;
            prev.next = node;
            prev = node;
            l1 = l1.next;
        }

        while (l2 != null) {
            ListNode node = new ListNode((l2.val+carry) % 10);
            carry = (l2.val + carry) / 10;
            prev.next = node;
            prev = node;
            l2 = l2.next;
        }

        if (carry != 0) {
            ListNode node = new ListNode(carry);
            prev.next = node;
        }

        return sum.next;
    }


    public static void main(String[] args) {

        AddTwoNumbers solution = new AddTwoNumbers();

        ListNode l1 = new ListNode(1);
        l1.next = new ListNode(8);
        // l1.next.next = new ListNode(9);

        ListNode l2 = new ListNode(0);
        //l2.next = new ListNode(8);
        //l2.next.next = new ListNode(4);

        ListNode sum = solution.addTwoNumbers(l1, l2);

        while (sum != null) {
            System.out.println(sum.val);
            sum = sum.next;
        }
    }
}

