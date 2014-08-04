package question1;


/**
 * Sort an array with only element 0,1,2. You can not use bucket sort.
 */
public class Question {

	// sort an array with only element 0,1,2
	public static void sort3Ele(int[] array) {
		//int left = 0, current = 0, right = array.length - 1;
	}


    public static void main(String[] args) {
		int[] array = new int[] {2,1,2,1,2,0,1,1,1,2,1,0,2,1,0};
		sort3Ele(array);

		for (int i = 0; i < array.length; i++)
			System.out.println(array[i]);
	}
}
