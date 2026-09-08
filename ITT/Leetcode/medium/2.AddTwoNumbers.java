/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        // Create a dummy node to act as the anchor for our result list
        ListNode dummyHead = new ListNode(0);
        ListNode current = dummyHead;
        int carry = 0;
        
        // Loop runs as long as there is data to process in l1, l2, or a remaining carry
        while (l1 != null || l2 != null || carry != 0) {
            // Get values; if a list is empty, default its value to 0
            int val1 = (l1 != null) ? l1.val : 0;
            int val2 = (l2 != null) ? l2.val : 0;
            
            // Calculate sum and update carry
            int currentSum = val1 + val2 + carry;
            carry = currentSum / 10;
            
            // Create a new node with the single digit value
            current.next = new ListNode(currentSum % 10);
            current = current.next;
            
            // Advance the list pointers if they are not null
            if (l1 != null) l1 = l1.next;
            if (l2 != null) l2 = l2.next;
        }
        
        // The real head of our resulting list is right after the dummy head
        return dummyHead.next;
    }
}
