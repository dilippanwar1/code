// A non-empty zero-indexed array A consisting of N numbers is given. The array
// is sorted in non-decreasing order. The absolute distinct count of this array
// is the number of distinct absolute values among the elements of the array.

// For example, consider array A such that:
//   A[0] = -5
//   A[1] = -3
//   A[2] = -1
//   A[3] =  0
//   A[4] =  3
//   A[5] =  6
// The absolute distinct count of this array is 5, because there are 5 distinct
// absolute values among the elements of this array, namely 0, 1, 3, 5 and 6.


import java.util.*;
import java.math.*;


class Solution {

    public int solution(int[] A)
    {
        int count = 0;
        HashSet<Integer> set = new HashSet<Integer>();

        for (int i = 0; i < A.length; i++) {
            int number = Math.abs(A[i]);
            if (!set.contains(number)) {
                set.add(number);
                count++;
            }
        }

        return count;
    }
}
