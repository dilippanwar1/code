// Given two words (start and end), and a dictionary, find all shortest
// transformation sequence(s) from start to end, such that:
//    Only one letter can be changed at a time
//    Each intermediate word must exist in the dictionary

// For example,
// Given:
//    start = "hit"
//    end = "cog"
//    dict = ["hot","dot","dog","lot","log"]

// Return
//    [
//      ["hit","hot","dot","dog","cog"],
//      ["hit","hot","lot","log","cog"]
//    ]

// Note:
// All words have the same length.
// All words contain only lowercase alphabetic characters.

// Doesn't work

import java.util.Queue;
import java.util.LinkedList;
import java.util.HashSet;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Set;


public class WordLadderII {

    public ArrayList<ArrayList<String>> findLadders(
        String start, String end, HashSet<String> dict) {
        // Start typing your Java solution below
        // DO NOT write main() function
        int count = 1;
        int distance = 1;
        boolean find = false;
        ArrayList<ArrayList<String>> result = new ArrayList<ArrayList<String>>();
        Set<String> visited = new HashSet<String>();
        Queue<String> queue = new LinkedList<String>();
        queue.offer(start);

        while (count > 0 && !find) {
            while (count > 0 && !find) {
                char[] curr = queue.poll().toCharArray();
                for (int i = 0; i < curr.length; i++) {
                    char tmp = curr[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == tmp)
                            continue;
                        curr[i] = c;
                        String str = new String(curr);
                        if (str.equals(end)) {
                            find = true;
                            break;
                        }
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

        if (find == false) {
            return result; // return empty arraylist if no word ladder exists
        } else {
            return findLaddersDFS(start, end, distance, dict,
                                  new HashMap<String, HashSet<String>>());
        }
    }

    private ArrayList<ArrayList<String>> findLaddersDFS(
        String start, String end, int distance,
        HashSet<String> dict, HashMap<String, HashSet<String>> parents) {

        ArrayList<ArrayList<String>> result = new ArrayList<ArrayList<String>>();
        if (distance == 1) {
            if (!start.equals(end)) {
                return result;
            } else {
                ArrayList<String> res = new ArrayList<String>();
                res.add(start);
                result.add(res);
                return result;
            }
        }

        char[] curr = start.toCharArray();
        for (int i = 0; i < curr.length; i++) {
            char tmp = curr[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == tmp)
                    continue;
                curr[i] = c;
                String str = new String(curr);
                if (dict.contains(str)) {
                    ArrayList<ArrayList<String>> res =
                        findLaddersDFS(str, end, distance-1, dict, parents);
                    for (ArrayList<String> item : res) {
                        item.add(0, start);
                    }
                    result.addAll(res);
                }
            }
            curr[i] = tmp;
        }

        return result;
    }


    public static void main(String[] args) {

        WordLadderII wl = new WordLadderII();
		String[] words = {"hot","dot","dog","lot","log"};
		HashSet<String> wordsHash = new HashSet<String>();
		for (String word : words) {
			wordsHash.add(word.toLowerCase());	// make sure all lower case
		}

        System.out.println(wl.findLadders("hit", "cog", wordsHash));
    }
}
