package question6;

import java.util.ArrayList;
import java.util.Arrays;


/**
 * Find all pairs of integers within an array which sum to a specified value
 */
public class Question {

	public static ArrayList<Pair> findPair(int[] array, int sum) {
		int left = 0, right = array.length - 1;
		ArrayList<Pair> rtn = new ArrayList<Pair>();

		Arrays.sort(array);
		while (left < right) {
			if (array[left] + array[right] == sum) {
				rtn.add(new Pair(array[left], array[right]));
				left++; right--;
			} else if (array[left] + array[right] < sum) {
				left++;
			} else {
				right--;
			}
		}

		return rtn;
	}

	public static void main(String[] args) {
		int[] test = {9, 3, 6, 5, 7, -1, 13, 14, -2, 12, 0, 18, -6};
		ArrayList<Pair> pairs = findPair(test, 12);

		if (pairs.isEmpty())
			System.out.println("No pair!");
		else
			for (Pair pair : pairs)
				pair.print();
	}
}


class Pair {
	private int val1;
	private int val2;

	public Pair(int val1, int val2) {
		this.val1 = val1;
		this.val2 = val2;
	}

	public void print() {
		System.out.println("(" + val1 + ", " + val2 + ")");
	}
}
