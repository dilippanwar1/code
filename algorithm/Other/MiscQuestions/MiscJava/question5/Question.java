package question5;

import java.util.ArrayList;

import CtCILibrary.AssortedMethods;

public class Question {

	/**
	 * Print all sequences of an array which sums to a given value
	 */
	public static ArrayList<ArrayList<Integer>> arrayFindSum(int[] array, int sum) {
		ArrayList<ArrayList<Integer>> rtn = new ArrayList<ArrayList<Integer>>();
		arrayFindSumHelper(array, new boolean[array.length], sum, 0, rtn);
		return rtn;
	}

	private static void arrayFindSumHelper(

        int[] array, boolean[] flags, int sum, int pos,
        ArrayList<ArrayList<Integer>> rtn) {

		// First three "if"s are base cases. Note here compare `sum`
		// should appear before compare `pos`
		if (sum < 0) {
			return;
		} else if (sum == 0) {
			ArrayList<Integer> newlist = new ArrayList<Integer>();
			for (int i = 0; i < array.length; i++)	// print out path
				if (flags[i]) newlist.add(array[i]);
			rtn.add(newlist);
		} else if (pos >= array.length) {
			return;
		} else {
			// Do not use current element.
			arrayFindSumHelper(array, flags, sum, pos + 1, rtn);
			// Use current element, be careful to clear flag.
			flags[pos] = true;
			arrayFindSumHelper(array, flags, sum - array[pos], pos + 1, rtn);
			flags[pos] = false;
		}
	}


	public static void main(String[] args) {
		int[] array = AssortedMethods.randomArray(200, 0, 200);
		ArrayList<ArrayList<Integer>> rtn = arrayFindSum(array, 100);

		for (ArrayList<Integer> list : rtn) {
			for (int val : list)
				System.out.print(val + " ");
			System.out.println();
		}
	}
}
