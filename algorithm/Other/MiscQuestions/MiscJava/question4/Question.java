package question4;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Find length of longest increasing sequence of an array. E.g. for the array
 * shown below: {1, 4, 7, 2, 3, 6, 9, 7, 4, 5, 3}, there are three longest
 * increasing sequence in total: [1,2,3,6,9]; [1,2,3,6,7]; [1,2,3,4,5], so
 * longest increasing sequence length is 5. Idea is to let every index number
 * as starting number, build LIS recursively.
 */
public class Question {

	public static int longestIncreasingSequence(int[] array) {
		HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
		int longest = 0;

		for (int i = 0; i < array.length; i++) {	// let every index be first
			int new_longest = longestIncreasingSequenceHelper(array, i, map);
			if (new_longest > longest ) longest = new_longest;
		}

		return longest;
	}

	private static int longestIncreasingSequenceHelper(
        int[] array, int start, HashMap<Integer, Integer> cache) {

		if (cache.containsKey(start)) return cache.get(start);

		int longest = 0;

		// We try to find the longest increasing sequence starting from `start`
		for (int i = start + 1; i < array.length; i++) {
            // only if "array[start] < array[i]" will our recursion be valid
			if (array[start] < array[i]) {
				int new_longest = longestIncreasingSequenceHelper(array, i, cache);
				if (new_longest > longest) longest = new_longest;
			}
		}

		longest++;	// include current element into longest sequence
		cache.put(start, longest);

		return longest;
	}




	/**
	 * Find one of the longest increasing sequence of an array.
	 */
	public static ArrayList<Integer> longestIncreasingSequence1(int[] array) {

		ArrayList<Integer> longest = new ArrayList<Integer>();
		HashMap<Integer, ArrayList<Integer>> cache =
            new HashMap<Integer, ArrayList<Integer>>();

		for (int i = 0; i < array.length; i++) {
			ArrayList<Integer> new_longest =
                longestIncreasingSequence1Helper(array, i, cache);
			if (new_longest.size() > longest.size()) longest = new_longest;
		}

		return longest;
	}

	@SuppressWarnings("unchecked")
	private static ArrayList<Integer> longestIncreasingSequence1Helper(
        int[] array, int start, HashMap<Integer, ArrayList<Integer>> cache) {

		if (cache.containsKey(start)) return cache.get(start);

		ArrayList<Integer> longest = new ArrayList<Integer>();

		// We try to find the longest increasing sequence starting from `start`
		for (int i = start + 1; i < array.length; i++) {
            // only if "array[start] < array[i]" will our recursion be valid
			if (array[start] < array[i]) {
				ArrayList<Integer> new_longest =
                    longestIncreasingSequence1Helper(array, i, cache);
				if (new_longest.size() > longest.size()) longest = new_longest;
			}
		}

        // include current element into longest sequence
		longest.add(0, array[start]);
		//cache.put(start, longest);

		return (ArrayList<Integer>) longest.clone();
	}




	public static void main(String[] args) {
		System.out.println(longestIncreasingSequence(
                               new int[] {8, 4, 7, 2, 3, 6, 9, 7, 4, 5, 3}));
		for (int i : longestIncreasingSequence1(
                 new int[] {8, 4, 7, 2, 3, 6, 9, 7, 4, 5, 3}))
			System.out.print(i + " ");
	}
}
