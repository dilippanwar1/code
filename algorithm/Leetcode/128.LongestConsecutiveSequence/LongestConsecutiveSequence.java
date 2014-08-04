// Given an unsorted array of integers, find the length of the longest
// consecutive elements sequence.

// For example,
//    Given [100, 4, 200, 1, 3, 2],
//    The longest consecutive elements sequence is [1, 2, 3, 4].
//    Return its length: 4.

// Your algorithm should run in O(n) complexity.

import java.util.HashMap;


public class LongestConsecutiveSequence {

    public int longestConsecutive(int[] num) {

        int max = 0;
        // a map between number and its length (e.g. 2,3,4,5, the length for
        // 2 and 5 is 4, we don't care length of 3 and 4)
        HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();

        // use hash map, check left and right element. remember to update
        // leftmost and rightmost length when updating.
        for (int i = 0; i < num.length; i++) {

            int left_len = 0, right_len = 0;
            if (map.containsKey(num[i])) { // duplicate
                continue;
            }

            if (map.containsKey(num[i]-1)) {
                left_len = map.get(num[i]-1);
            }
            if (map.containsKey(num[i]+1)) {
                right_len =  map.get(num[i]+1);
            }

            map.put(num[i], 1 + left_len + right_len);
            max = Math.max(max, 1 + left_len + right_len);
            if (left_len != 0) {
                map.put(num[i] - left_len, 1 + left_len + right_len);
            }
            if (right_len != 0) {
                map.put(num[i] + right_len, 1 + left_len + right_len);
            }
        }

        return max;
    }

    public static void main(String[] args) {
        LongestConsecutiveSequence lcs = new LongestConsecutiveSequence();
        int[] array = {1};
        System.out.println(lcs.longestConsecutive(array));
    }
}
