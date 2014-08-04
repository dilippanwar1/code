#include <stdio.h>


//***************************************************************************
// Public Declaration
void selection_sort(int a[], int size);
//***************************************************************************
// Private Declaration
static void swap(int a[], int i, int j);
//***************************************************************************
    

//============================================================================
// Implementation of selection sort.
// @param `a` array of int
// @param `size` size of array
void selection_sort(int a[], int size) {
    int i, j;

    // First loop scans entire array
    for (i = 0; i < size; i++) {
	// Second loop finds minimal element from `i` to `size`, set the
	// minimal element at `i` at first.
	int min = i;
	for (j = i; j < size; j++)
	    if (a[min] > a[j])
		min = j;

	if (i != min)
	    swap(a, min, i);
    }
}

// Swap two elements in array
static void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}



// Selection sort small test and usage.
#define LENGTH 15
int main() {

    int a[LENGTH] = {3,2,1,4,3,2,5,7,2,0,3,4,3,4,3};
    int b[LENGTH] = {13,24,31,14,45,26,7,81,19,10,31,22,13,18,25};
    int i;


    // Provide array and its size, in place sort.
    selection_sort(a, LENGTH);
    for (i = 0; i < LENGTH; i++)
	printf("%d ", a[i]);
    printf("\n");


    selection_sort(b, LENGTH);    
    for (i = 0; i < LENGTH; i++)
	printf("%d ", b[i]);
    printf("\n");
}
