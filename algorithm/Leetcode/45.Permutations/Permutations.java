// Given a collection of numbers, return all possible permutations.

// For example,
//    [1,2,3] have the following permutations:
//    [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].

import java.util.*;


public class Permutations {

    public ArrayList<ArrayList<Integer>> permute(int[] num) {
        // Start typing your Java solution below
        // DO NOT write main() function
        return permuteHelper(num, 0);
    }

    private ArrayList<ArrayList<Integer>> permuteHelper(
        int[] num, int start) {

        if (start == num.length - 1) {
            ArrayList<ArrayList<Integer>> result =
                new ArrayList<ArrayList<Integer>>();
            ArrayList<Integer> res = new ArrayList<Integer>();
            res.add(num[start]);
            result.add(res);
            return result;
        }

        ArrayList<ArrayList<Integer>> prev = permuteHelper(num, start+1);
        ArrayList<ArrayList<Integer>> result =
            new ArrayList<ArrayList<Integer>>();
        for (ArrayList<Integer> item : prev) {
            for (int i = 0; i <= item.size(); i++) {
                ArrayList<Integer> cloned = (ArrayList<Integer>)item.clone();
                cloned.add(i, num[start]);
                result.add(cloned);
            }
        }

        return result;
    }

    public static void main(String[] args) {

        Permutations permutations = new Permutations();
        System.out.println(permutations.permute(new int[] {1,2,3}));
    }
}
