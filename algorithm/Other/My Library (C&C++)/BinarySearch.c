#include <stdio.h>
#include <limits.h>


//***************************************************************************
// Public Declaration
int binary_search(int a[], int size, int value);
//***************************************************************************



//============================================================================
// Implementation of binary search.
// @param `a`: sorted array of int
// @param `size`: size of array
// @param `value`: value to search
int binary_search(int a[], int size, int value) {

    int left = 0, right = size - 1;
    
    while (left <= right) {
	int center = (left + right) / 2;

	if (a[center] > value) {
	    right = center - 1;
	} else if (a[center] < value) {
	    left = center + 1;
	} else {
	    return a[center];
	}
    }

    return INT_MIN;
}



// Binary search small test and usage.
#define LENGTH 15
int main() {

    int b[LENGTH] = {13,24,31,45,65,86,117,131,149,210,331,422,513,618,625};

    printf("%d\n", binary_search(b, LENGTH, 13));
}
