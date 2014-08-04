package question3;


/**
 * A sorted array has elements, each appears at least twice, e.g. [2,2,3,3,3,4,4].
 * Find the last position of an element, e.g. find2(3) = 4. If not found, return -1.
 */
public class Question {

	public static int find2(int[] array, int key) {

		int lower = 0;
		int upper = array.length;

		while (lower < upper) {
			int mid = (upper - lower) / 2 + lower;

			if (key >= array[mid]) {
				lower = mid + 1;
			} else {
				upper = mid;	// `upper` can not be mid-1
            }
		}

		if (lower >= 1 && array[lower-1] == key) {
			return lower - 1;
		} else {
			return -1;
        }
    }


	public static void main(String[] args) {
		System.out.println(find2(new int[] {-2,-2,3,3,4,4,5,5,6,6,6}, -5));
	}
}
