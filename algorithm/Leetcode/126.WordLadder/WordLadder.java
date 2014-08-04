// Given two words (start and end), and a dictionary, find the length of
// shortest transformation sequence from start to end, such that:
//    Only one letter can be changed at a time
//    Each intermediate word must exist in the dictionary

// For example,
// Given:
//    start = "hit"
//    end = "cog"
//    dict = ["hot","dot","dog","lot","log"]
// As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
// return its length 5.

// Note:
// Return 0 if there is no such transformation sequence.
// All words have the same length.
// All words contain only lowercase alphabetic characters.

import java.util.Queue;
import java.util.LinkedList;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.Set;


public class WordLadder {

    // from forum, can pass large set (mine has the same logic, but time
    // exceeded, maybe due to the use of two queues and arraylist)
    public int ladderLength(String start, String end, HashSet<String> dict) {

        int count = 1;
        int distance = 1;
        Set<String> visited = new HashSet<String>();
        Queue<String> queue = new LinkedList<String>();

        queue.offer(start);
        visited.add(start);

        // using `count` to record how many nodes are in one level, thus
        // eliminate the needs of using two queues.
        while (count > 0) {
            while (count > 0) {
                char[] curr = queue.poll().toCharArray();
                for (int i = 0; i < curr.length; i++) {
                    char tmp = curr[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == tmp)
                            continue;
                        curr[i] = c;
                        String str = new String(curr);
                        if (str.equals(end))
                            return distance + 1;
                        if (dict.contains(str) && !visited.contains(str)) {
                            queue.offer(str);
                            visited.add(str);
                        }
                    }
                    curr[i] = tmp;
                }
                count--;
            }
            distance++;
            count = queue.size();
        }
        return 0;
    }

    public int ladderLength1(String start, String end, HashSet<String> dict) {
        // Start typing your Java solution below
        // DO NOT write main() function
		HashSet<String> visited = new HashSet<String>();
        Queue<String> queue1 = new LinkedList<String>();
        Queue<String> queue2 = new LinkedList<String>();
        int length = 1;

        queue1.offer(start);

        while (!queue1.isEmpty()) {

            while (!queue1.isEmpty()) {
                String current = queue1.poll();
                visited.add(current);
                for (String next : getAllNextWords(current, dict)) {
                    if (next.equals(end))
                        return length + 1;
                    if (!visited.contains(next))
                        queue2.offer(next);
                }
            }
            length++;

            while (!queue2.isEmpty()) {
                String current = queue2.poll();
                visited.add(current);
                for (String next : getAllNextWords(current, dict)) {
                    if (next.equals(end))
                        return length + 1;
                    if (!visited.contains(next))
                        queue1.offer(next);
                }
            }
            length++;
        }

        return 0;
    }

	private ArrayList<String> getAllNextWords(
        String word, HashSet<String> dict) {

		ArrayList<String> rtn = new ArrayList<String>();

		for (int i = 0; i < word.length(); i++) {
			for (char ch = 'a'; ch <= 'z'; ch++) {
				if (ch != word.charAt(i)) {
					char[] temp = word.toCharArray();
					temp[i] = ch;
					String newWord = new String(temp);
					if (dict.contains(newWord)) {
						rtn.add(newWord);
					}
				}
			}
		}

		return rtn;
	}

    public static void main(String[] args) {
        WordLadder wl = new WordLadder();
		String[] words = {"slit"};
		HashSet<String> wordsHash = new HashSet<String>();
		for (String word : words) {
			wordsHash.add(word.toLowerCase());	// make sure all lower case
		}

        System.out.println(wl.ladderLength("sand", "acne", wordsHash));
    }
}
