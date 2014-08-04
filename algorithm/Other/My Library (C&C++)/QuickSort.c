#include <stdio.h>


//***************************************************************************
// Public Declaration
void quick_sort(int a[], int size);
//***************************************************************************
// Private Declaration
static void insertion_sort(int a[], int left, int right);
static void quick_sort_helper(int a[], int left, int right);
static void swap(int a[], int i, int j);
//***************************************************************************


//============================================================================
// Wrapper of quick sort, the quick sort is in place.
// @param `a`: array of int
// @param `size`: size of array
void quick_sort(int a[], int size) {
    quick_sort_helper(a, 0, size-1);
}


//============================================================================
// Implementation of quick sort, using median of three as pivot.
// @param `a`: array of int
// @param `left`: left side of the array to be sort
// @param `right`: right side of the array to be sort
static void quick_sort_helper(int a[], int left, int right) {
    // Base case.
    // When subarray is less than 10 elements, use insertion sort is more
    // effcient than quick sort. (Recursive call overhead)
    if (left + 10 >= right) {
        insertion_sort(a, left, right);
        return;
    }

    // Choose Pivot
    // Using the median of left, right, center element. Note that median
    // element is swapped to the left.
    int pivot, center = (left + right) / 2;
    if (a[left] > a[center])
        swap(a, left, center);
    if (a[left] > a[right])
        swap(a, left, right); /* now `left` points to the min element */
    if (a[center] > a[right])
        swap(a, center, right);	/* now `right` points to the max element */
    swap(a, center, left);	/* swap the median to left position */
    pivot = a[left];

    // Start partition.
    // The goal is that after partition, elements smaller than pivots will be
    // on the left side of `i`, and elements bigger than pivots will be on
    // the right side of `i` (include `i`).
    int i = left + 1, j = left + 1, tmp;
    for (; j <= right; j++) {
        if (a[j] < pivot) {
            swap(a, i++, j);
        }
    }

    // At the final step of partition, swap pivot to the middle.
    // Position i-1 is the pivot.
    swap(a, left, i-1);

    // Recursively solve the problem, note that i-1 is the pivot.
    quick_sort_helper(a, left, i-2);
    quick_sort_helper(a, i, right);
}


// Swap two elements in array
static void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}


// Modification of insertion sort.
static void insertion_sort(int a[], int left, int right) {
    int i, j;

    for (i = left; i <= right; i++) {
        for (j = i; (j > left) && (a[j] < a[j-1]) ; j--) {
            swap(a, j, j - 1);
        }
    }
}



// Quick sort small test and usage.
#define LENGTH 15
int main() {

    int a[LENGTH] = {3,2,1,4,3,2,5,7,2,0,3,4,3,4,3};
    int b[LENGTH] = {13,24,31,14,45,26,7,81,19,10,31,22,13,18,25};
    int i;


    // Provide array and its size, in place sort.
    quick_sort(a, LENGTH);
    for (i = 0; i < LENGTH; i++)
        printf("%d ", a[i]);
    printf("\n");


    quick_sort(b, LENGTH);
    for (i = 0; i < LENGTH; i++)
        printf("%d ", b[i]);
    printf("\n");
}
