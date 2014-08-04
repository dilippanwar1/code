// Write a function to find the longest common prefix string amongst an array
// of strings.

public class LongestCommonPrefix {

    public String longestCommonPrefix(String[] strs) {

        if (strs.length == 0) {
            return new String();
        } else if (strs.length == 1) {
            return strs[0];
        }

        int max_len = 0;

        while (true) {
            for (int i = 0; i < strs.length-1; i++) {
                if (max_len >= strs[i].length() ||
                    max_len >= strs[i+1].length()) {
                    return strs[0].substring(0, max_len);
                }
                if (strs[i].charAt(max_len) != strs[i+1].charAt(max_len)) {
                    return strs[0].substring(0, max_len);
                }
            }
            max_len++;
        }
    }

    public static void main(String[] args) {
        LongestCommonPrefix lcp = new LongestCommonPrefix();
        String[] strs = new String[3];
        strs[0] = new String("acd");
        strs[1] = new String("ac3f");
        strs[2] = new String("acde");
        System.out.println(lcp.longestCommonPrefix(strs));
    }
}
