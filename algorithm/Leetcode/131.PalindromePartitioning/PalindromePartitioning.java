// Given a string s, partition s such that every substring of the partition
// is a palindrome.

// Return all possible palindrome partitioning of s.

// For example, given s = "aab",
// Return
//   [
//     ["aa","b"],
//     ["a","a","b"]
//   ]

import java.util.*;


public class PalindromePartitioning {

    public ArrayList<ArrayList<String>> partition(String s) {

        if (s == null || s.length() == 0)
            return new ArrayList<ArrayList<String>>();

        boolean[][] isPalin = new boolean[s.length()][s.length()];

        // helper array to compute palindrome substring
        for (int cl = 1; cl <= s.length(); cl++) {
            for (int i = 0; i < s.length() - cl + 1; i ++) {
                int j = i + cl - 1;
                if (cl == 1) {
                    isPalin[i][i] = true;
                } else if (cl == 2) {
                    isPalin[i][j] = (s.charAt(i) == s.charAt(j));
                } else {
                    isPalin[i][j] = (s.charAt(i) == s.charAt(j)) &&
                        isPalin[i+1][j-1];
                }
            }
        }

        return partitionHelper(s, 0, isPalin);
    }

    private ArrayList<ArrayList<String>> partitionHelper(
        String s, int index, boolean[][] isPalin) {

        ArrayList<ArrayList<String>> new_pa = new ArrayList<ArrayList<String>>();

        // As of some typical DP problem, we can use a hashmap to store
        // sub-problem result using a hash map.

        // Base case, only one character. E.g. "aab" => [ ["a"] ]
        if (index == s.length()) {
            new_pa.add(new ArrayList<String>());
            return new_pa;
        }

        for (int i = index; i < s.length(); i++) {
            // if s[index ... i] is palindrome, then we form arraylist according
            // to s[i ... length]
            if (isPalin[index][i]) {
                for (ArrayList<String> subpa : partitionHelper(s, i+1, isPalin)) {
                    subpa.add(0, s.substring(index, i+1));
                    new_pa.add(subpa);
                }
            }
        }

        return new_pa;
    }

    public static void main(String[] args) {
        PalindromePartitioning palindromePartitioning = new
            PalindromePartitioning();
        System.out.println(palindromePartitioning.partition("dde"));
    }
}
