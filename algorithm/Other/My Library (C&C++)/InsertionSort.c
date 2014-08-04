#include <stdio.h>


//***************************************************************************
// Public Declaration
void insertion_sort(int a[], int size);
//***************************************************************************
// Private Declaration
static void swap(int a[], int i, int j);
//***************************************************************************


//============================================================================
// Implementation of insertion sort.
// @param `a` array of int
// @param `size` size of array
void insertion_sort(int a[], int size) {
    int i, j, tmp;

    // First loop scans entire array. Keep current position of the element to
    // insert in `tmp`. Second scan moves element backward until find the
    // position to insert a[i]. Elements to the left of position i are sorted.
    for (i = 0; i < size; i++) {
	tmp = a[i];
	// Note insertion sort is liner time when array is almost sorted, this
	// is because of the condition "tmp < a[j-1]".
	for (j = i; (j > 0) && (tmp < a[j-1]) ; j--)
	    a[j] = a[j-1];
	a[j] = tmp;
    }

    // Above code is an optimization of the following version:
    /* for (i = 0; i < size; i++) */
    /* 	for (j = i; (j > 0) && (a[j] < a[j-1]); j--) */
    /* 	    swap(a, j, j-1); */
}

// Swap two elements in array
static void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}



// Insertion sort small test and usage.
#define LENGTH 15
int main() {

    int a[LENGTH] = {3,2,1,4,3,2,5,7,2,0,3,4,3,4,3};
    int b[LENGTH] = {13,24,31,14,45,26,7,81,19,10,31,22,13,18,25};
    int i;


    // Provide array and its size, in place sort.
    insertion_sort(a, LENGTH);
    for (i = 0; i < LENGTH; i++)
	printf("%d ", a[i]);
    printf("\n");


    insertion_sort(b, LENGTH);    
    for (i = 0; i < LENGTH; i++)
	printf("%d ", b[i]);
    printf("\n");
}
