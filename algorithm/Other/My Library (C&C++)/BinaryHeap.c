// BinaryHeap.c
// Note two properties of binary heap:
// 1. Binary heap is a complete tree (Top to buttom, left to right)
// 2. Root element is smaller than its children (Recursively true).
// Note three properties of complete tree: (i start from 1)
// 1. If parent node is at position i, then left child is at position 2i;
// 1. If parent node is at position i, then right child is at position 2i+1;
// 1. The parent node of a child is at position i/2.
#include <stdio.h>
#include <stdlib.h>


//***************************************************************************
// Public Declaration
int bheap_init(int size);
int bheap_insert(int item);
int bheap_findMin();
int bheap_removeMin();
int bheap_update(int index, int item);
int bheap_isEmpty();
void bheap_free();
//***************************************************************************





//============================================================================
// Static variable used in binary heap
static int heap_size = 0;
static int current_size = 0;
static int* array;


//============================================================================
// Initialize binary heap.
// @param `size`: the size of binary heap
// @return -1 if initialization fails, 0 if succeeds.
int bheap_init(int size) {

    // Initialize module variables, note we don't use `array[0]` in order to
    // use tree properties, so allocate one more space.
    if ((array = (int *) malloc(size + 1)) == NULL)
	return -1;

    heap_size = size;
    current_size = 0;
    return 0;
}

//============================================================================
// @param 'item': the item to be inserted
// @return -1 if insert fails (full), 0 if succeeds.
// Insert an element into binary heap.
int bheap_insert(int item) {
    if (current_size > heap_size) return -1;

    // At first, the place to insert new element (the `hole`) is at the last
    // position of the array. We need to "Percolate Up" to find the position.
    int hole = ++current_size;
    for (; hole > 1 && item < array[hole/2] ; hole /= 2)
	// If `item` is less than its parent, then percolate up; otherwise,
	// we have found the position to insert, so stop. Note we do not use
	// array[0], so condition should be `hole>1` other than `hole>0`.
	array[hole] = array[hole/2];
    
    array[hole] = item;
    return 0;
}

//============================================================================
// @return the minial element, do not delete.
int bheap_findMin() {
    return array[1]; /* return array[1] according to binary heap property */
}

//============================================================================
// @return the minial element, and delete. If there is no more element to be
//	removed, then return Integer MIN.
int bheap_removeMin() {

    if (bheap_isEmpty()) return ~(1<<31);
    
    int hole, child, min = array[1]; /* back up minimal element */

    // Now array[1] is no longer valid, we leave it as a hole, and copy the
    // last element in the heap into the hole. Our next step is to find the
    // appropriate place for the last element (which is now array[1]), this
    // is done by "Percolate Down". array[0] is used as a temp variable.
    array[0] = array[1] = array[current_size--];

    // Start percolate down
    for (hole = 1; 2 * hole <= current_size; hole = child) {
	child = hole * 2;	/* let the child be left child at first */

	// Make sure there is right child; then compare their value
	if (child != current_size && array[child] > array[child+1])
	    child++;

	// After found the min child, decide whether we need to continue
	// percolate down.
	if (array[0] > array[child])
	    array[hole] = array[child];
	else
	    break;
    }
    array[hole] = array[0];

    return min;
}

//============================================================================
// Check if binary heap is empty or not
// @return 1 if binary heap is empty, otherwise 0.
int bheap_isEmpty() {
    return current_size == 0;
}

//============================================================================
// Free binary heap
void bheap_free() {
    free(array);
}

//============================================================================
// Update heap content at a specified index. More useful implementation should
// use <key, value> pair to update binary heap, here to simplify, we update
// heap array at specified array index. Note index start from 1.
// @param `index`: the index of array to update
// @param `item`: the value to the array entry
// @return 0 if update successfully, otherwise -1
int bheap_update(int index, int new_item) {

    if (index < 1 || index > current_size) return -1;
    
    if (new_item < array[index]) { /* need percolate up */
	array[index] = new_item;
	
	int hole;
	for (hole = index; hole > 1 && new_item < array[hole/2] ; hole /= 2)
	    array[hole] = array[hole/2];
	array[hole] = new_item;

    } else {			/* need percolate down */
	int child, hole;
	array[0] = array[index] = new_item;

	for (hole = index; 2 * hole <= current_size; hole = child) {
	    child = hole * 2;	/* let the child be left child at first */

	    // Make sure there is right child; then compare their value
	    if (child != current_size && array[child] > array[child+1])
		child++;

	    // After found the min child, decide whether we need to continue
	    // percolate down.
	    if (array[0] > array[child])
		array[hole] = array[child];
	    else
		break;
	}
	array[hole] = array[0];
    }
}

//============================================================================
// Print the contents of binary heap.
void bheap_print() {
    int i;
    for (i = 1; i <= heap_size; i++)
	printf("%d ", array[i]);
    printf("\n");
}


// Binary heap small test and usages.
#define LENGTH 10
int main(void) {

    bheap_init(LENGTH);		/* Init heap by providing size */

    bheap_insert(8);
    bheap_insert(13);
    bheap_insert(3);
    bheap_insert(12);
    bheap_insert(31);
    bheap_insert(38);
    bheap_insert(51);
    bheap_insert(76);
    bheap_insert(11);
    bheap_insert(11);		/* Insert to heap */
    bheap_print();

    /* bheap_update(5, 1); */
    /* bheap_print(); */

    /* bheap_update(1, 30); */
    /* bheap_print(); */

    int i = 0;
    for (; i < LENGTH; i++)	/* call removeMin() directly */
	printf("%d\n", bheap_removeMin());

    bheap_free(); /* call to bheap_free() after calling bheap_init() */
}
