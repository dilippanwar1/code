package question2;


/**
 * Find all prime numbers from 0 through max.
 */
public class Question {

	public static int[] findPrimes(int max) {

        // indicate whether a number is prime or not
		boolean[] flags = new boolean[max+1];
		int count = 0;

		for (int i = 2; i < flags.length; i++)
			flags[i] = true;

		for (int prime = 2; prime <= max && prime != -1;) {
			count++;
            // cross off all numbers that can be divided by prime
			crossOff(flags, prime);
			prime = nextPrime(flags, prime);
		}

		int[] rtn = new int[count];
		for (int i = 0, j = 0; i <= max; i++)
			if (flags[i])
				rtn[j++] = i;

		return rtn;
	}

	private static void crossOff(boolean[] flags, int prime) {
		for (int i = prime + prime; i < flags.length; i += prime)
			flags[i] = false;
	}

	private static int nextPrime(boolean[] flags, int prime) {
		for (int i = prime + 1; i < flags.length; i++)
			if (flags[i] == true)
				return i;
		return -1;
	}


	public static void main(String[] args) {
		int[] primes = findPrimes(100);
		for (int i = 0; i < primes.length; i++) {
			System.out.println(primes[i]);
		}
	}

}
