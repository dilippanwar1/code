#include <stdio.h>


//***************************************************************************
// Public Declaration
void merge_sort(int a[], int size);
//***************************************************************************
// Private Declaration
static void merge_sort_helper(int a[], int tmp[], int left, int right);
//***************************************************************************



//============================================================================
// Wrapper of merge sort, the merge sort is in place.
// @param `a`: array of int
// @param `size`: size of array
void merge_sort(int a[], int size) {
    int tmp[size];	  /* a temp array to hold temporary data when merge */

    /* Start actual merge sort */
    merge_sort_helper(a, tmp, 0, size-1);
}


//============================================================================
// Implementation of merge sort.
// @param `a`: array of int
// @param `tmp`: array of int, temporary array
// @param `left`: left side of the array to be sort
// @param `right`: right side of the array to be sort
static void merge_sort_helper(int a[], int tmp[], int left, int right) {
    // Base case
    if (left >= right) return;

    // Separate current array into two parts with same size, note the 
    // second call to merge_sort_helper() should pass `center+1`
    int center = (left + right) / 2;
    merge_sort_helper(a, tmp, left, center);
    merge_sort_helper(a, tmp, center+1, right);

    // Start merge (Now left and right parts are sorted)
    int i = left, j = center + 1, k = left;

    while (i <= center && j <= right) {
	if (a[i] > a[j])
	    tmp[k++] = a[j++];
	else
	    tmp[k++] = a[i++];
    }

    // Handle tail of either left or right part
    while (i <= center)
	tmp[k++] = a[i++];
    while (j <= right)
	tmp[k++] = a[j++];

    // Copy data from `tmp` to `a`
    for (i = left; i <= right; i++)
	a[i] = tmp[i];
}



// Merge sort small test and usage.
#define LENGTH 15
int main() {

    int a[LENGTH] = {3,2,1,4,3,2,5,7,2,0,3,4,3,4,3};
    int b[LENGTH] = {13,24,31,14,45,26,7,81,19,10,31,22,13,18,25};
    int i;


    // Provide array and its size, in place sort.
    merge_sort(a, LENGTH);
    for (i = 0; i < LENGTH; i++)
	printf("%d ", a[i]);
    printf("\n");


    merge_sort(b, LENGTH);    
    for (i = 0; i < LENGTH; i++)
	printf("%d ", b[i]);
    printf("\n");
}
