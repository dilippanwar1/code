package question8;

import java.util.Comparator;

public class PersonComparator implements Comparator<Person> {

	public int compare(Person arg0, Person arg1) {

		if (arg0.weight < arg1.weight) return -1;
		else if (arg0.weight > arg1.weight) return 1;
		else {
			if (arg0.height < arg1.height) return -1;
			else if (arg0.height > arg1.height) return 1;
		}
		
		return 0;
	}
}
