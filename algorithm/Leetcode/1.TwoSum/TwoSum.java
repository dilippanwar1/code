// Given an array of integers, find two numbers such that they add up
// to a specific target number. The function twoSum should return indices
// of the two numbers such that they add up to the target, where index1
// must be less than index2. Please note that your returned answers (both
// index1 and index2) are not zero-based.

// You may assume that each input would have exactly one solution.

// Input: numbers={2, 7, 11, 15}, target=9
// Output: index1=1, index2=2

import java.util.Arrays;
import java.util.HashMap;


public class TwoSum {

    public int[] twoSum(int[] numbers, int target) {

        int[] copy = (int[]) numbers.clone();
        int[] result = new int[2];

        Arrays.sort(copy);      // in-place sort array
        for (int i = 0, j = copy.length-1; i !=j; ) {
            if (copy[i] + copy[j] == target) {
                // if we find the element, use two O(n) loops to find the index
                // we need to use two for loops in case there are duplicates.
                // the overall running time is still O(n), since the inner loop
                // only execute once. (we can also build mapping between value
                // and index).
                for (int k = 0; k < copy.length; k++) {
                    if (copy[i] == numbers[k])
                        result[0] = k + 1;
                }
                for (int k = copy.length-1; k >= 0; k--) {
                    if (copy[j] == numbers[k])
                        result[1] = k + 1;
                }
                break;
            } else if (copy[i] + copy[j] >= target) {
                j--;
            } else {
                i++;
            }
        }

        // result[0] is always less than result[1]
        if (result[0] > result[1]) {
            int temp = result[1];
            result[1] = result[0];
            result[0] = temp;
        }

        return result;
    }


    public int[] twoSumHash(int[] numbers, int target) {

        HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
        int[] resultVal = new int[2];

        // iterate all numbers
        for (int i = 0; i < numbers.length; i++) {
            if (map.containsKey(numbers[i])) {
                int index = map.get(numbers[i]);
                if (index < i) {
                    resultVal[0] = index + 1;
                    resultVal[1] = i + 1;
                    break;
                }
            } else {
                // put the number we want to find into hash map
                map.put(target - numbers[i], i);
            }
        }

        return resultVal;
    }

    public static void main(String[] args) {

        TwoSum twoSum = new TwoSum();
        int[] array = {2,3,5,1,7,8,4};

        int[] result = twoSum.twoSum(array, 10);
        System.out.println(result[0] + " " + result[1]);

        int[] result2 = twoSum.twoSumHash(array, 10);
        System.out.println(result2[0] + " " + result2[1]);
    }
}
