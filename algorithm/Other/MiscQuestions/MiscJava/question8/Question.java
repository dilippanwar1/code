package question8;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;


/**
 * Each person must be both shorter and lighter than the person below him or her.
 * Given some people, find the largest possible number of people with one stand
 * atop one anther's shoulders.
 * Solution @author deyuandeng
 */
public class Question {

	public static int highest(Person[] persons) {

		HashMap<Integer, Integer> cache = new HashMap<Integer, Integer>();
		int longest = 0;

		for (int i = 0; i < persons.length; i++) {
			int new_longest = highestHelper(persons, i, cache);
			if (new_longest > longest) longest = new_longest;
		}

		return longest;
	}

	private static int highestHelper(Person[] persons, int index,
                                     HashMap<Integer, Integer> cache) {

		if (cache.containsKey(index)) return cache.get(index);
		int longest = 0;

		for (int i = index + 1; i < persons.length; i++) {
			if (persons[i].height > persons[index].height) {
				int new_longest = highestHelper(persons, i, cache);
				if (new_longest > longest) longest = new_longest;
			}
		}

		longest++;

		return longest;
	}


	public static Person[] initialize() {
		ArrayList<Person> items = new ArrayList<Person>();

		Person item = new Person(65, 60);
		items.add(item);

		item = new Person(70, 150);
		items.add(item);

		item = new Person(56, 90);
		items.add(item);

		item = new Person(75, 190);
		items.add(item);

		item = new Person(60, 95);
		items.add(item);

		item = new Person(68, 110);
		items.add(item);

		item = new Person(35, 65);
		items.add(item);

		item = new Person(40, 62);
		items.add(item);

		item = new Person(45, 63);
		items.add(item);

		item = new Person(33, 25);
		items.add(item);

		item = new Person(66, 65);
		items.add(item);

		item = new Person(75, 61);
		items.add(item);

		Person[] persons = new Person[items.size()];
		for (int i = 0; i < items.size(); i++)
			persons[i] = items.get(i);

		return persons;
	}


	public static void main(String[] args) {
		Person[] persons = initialize();
		Arrays.sort(persons, new PersonComparator());

		System.out.println(highest(persons));
	}


}
