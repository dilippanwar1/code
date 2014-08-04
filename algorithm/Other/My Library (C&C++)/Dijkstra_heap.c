// Dijkstra_heap.c
// Note: 1. For apps, vertex starts from 0. But inside dijkstra, we add 1 to
//          input because binary heap do not use array[0].
//       2. The heap implementation provides dijkstra algorithm an illusion
//          that the vertices are numbered properly, while in heap, an array
//          is used to keep position of each vertex.
//       3. Graph is represented as adjacent matrix.
//       4. Can be used to both direct and indirect graph.
#include <stdio.h>
#include <stdlib.h>


//***************************************************************************
// Public Declaration
// Max possible distance betwenn two vertex
#define DIST_MAX 30000
// Representation of a vertex
typedef struct {	      /* Representation of a vertex */
    int v_num;		      /* vertex number, starts from 1 */
    int known;		      /* mark each node as known or unknown */
    int dist;		      /* shortest path to specified vertex */
} Vertex;
int dijkstra(Vertex *v, int *g_array, int size, int s);
//***************************************************************************
// Private Declaration
static int bheap_init(int size);
static void bheap_free();
static void bheap_removeMin(int* min_dist, int* min_vnum);
static void bheap_update_dist(int v_num, int new_dist);
static void inline bheap_update_known(int v_num, int known);
static int inline bheap_isEmpty();
static int inline bheap_get_known(int v_num);
static int inline bheap_get_dist(int v_num);
//***************************************************************************





//============================================================================
// Static variable used in binary heap
static int heap_size = 0;
static int current_size = 0;
static int* array_index;
static Vertex* array;

//============================================================================
// Implementation of dijkstra shortest path algorithm. Graph is represented
// as adjacent matrix. Vertex is numbered from 0 to size-1 (inclusive). Use
// binary heap to choose shortest greedy path from unexplored vertices. The
// binary heap keeps all vertices.
// @param `v`: an array of vertices. v[0] is the shortest path from node s to
//	node 0, etc.
// @param `g`: Adjacent matrix of a graph.
// @param `size`: Size of the graph, ie. the adjacent matrix is size * size.
// @param 's': Source vertex, the param must between 0 to size-1.
// @return -1 if fails, otherwise 0.
int dijkstra(Vertex *v, int *g_array, int size, int s) {

    if (s < 0 || s >= size) return -1; /* make sure vertex is valid */
    else s++;			       /* internally, vertex starts from 1 */

    int i, j;
    bheap_init(size); /* initialize heap, all vertices are added into heap */

    bheap_update_dist(s, 0);	/* Update source vertex, dist = 0 */
    
    for (i = 1; i <= size; i++) {
	int min_dist, min_vnum;

	// Find the shortest gready shortest path from the vertices which
	// haven't been explored. Using binary heap.
	bheap_removeMin(&min_dist, &min_vnum);
	v[min_vnum - 1].dist = min_dist;
	
	// Mark the node as explored.
	bheap_update_known(min_vnum, 1);

	// For every ajacent vertices of the above vertex, update their greedy
	// shortest path. (Only update when their greedy shortest path can be
	// smaller after adding vertex min_index.)
	for (j = 1; j <= size; j++) {
	    int j_index = j - 1;
	    int min_index = min_vnum - 1;
	    int temp_dist = min_dist + *(g_array + (min_index*size+j_index));
	    if (bheap_get_known(j) == 0 && temp_dist < bheap_get_dist(j))
		bheap_update_dist(j, temp_dist);
	}
    }

    bheap_free();
    return 0;
}


//============================================================================
// Initialize binary heap.
// @param `size`: the size of binary heap (number of vertices).
// @return -1 if initialization fails, 0 if succeeds.
static int bheap_init(int size) {

    int i;
    // Initialize module variables, note we don't use `array[0]` in order to
    // utilize tree properties, so allocate one more space.
    if ((array = (Vertex *) malloc(sizeof(Vertex) * (size + 1))) == NULL)
	return -1;
    // `array_index` is used keep the position of vertex, ie, mapping between
    // v_num and its position in array. E.g. array_index[2] = 1 means vertex
    // number 2 is located at array[1].
    if ((array_index = (int *) malloc(sizeof(int) * (size + 1))) == NULL)
	return -1;

    // All nodes are unknown and shortest path is max.
    for (i = 1; i <= size; i++) {
	array[i].v_num = i;
	array[i].known = 0;
	array[i].dist = DIST_MAX;
    }

    // Upon initialization, all vertices have not been swapped.
    for (i = 1; i <= size; i++) {
	array_index[i] = i;
    }

    heap_size = size;
    current_size = size;	/* all vertices have benn added */
    return 0;
}

//============================================================================
// @param `min_dist`: minimal distance
// @param `min_vnum`: minimal distance vertex number
static void bheap_removeMin(int* min_dist, int* min_vnum) {

    if (bheap_isEmpty()) return;
    
    int hole, child;
    *min_dist = array[1].dist;	/* set up minimal element */
    *min_vnum = array[1].v_num;

    // Begin "Percolate Down", array[0] is used as a temp variable.
    // We must update indices first because array will be changed shortly.
    array_index[array[1].v_num] = current_size;
    array_index[array[current_size].v_num] = 1;
    array[0] = array[1] = array[current_size--];

    for (hole = 1; 2 * hole <= current_size; hole = child) {
	child = hole * 2;   /* let the child be left child at first */

	// Make sure there is right child; then compare their value
	if (child != current_size && array[child].dist > array[child+1].dist)
	    child++;

	// After found the min child, decide whether we need to continue
	// percolate down.
	if (array[0].dist > array[child].dist) {
	    array_index[array[child].v_num] = hole; /* keep index mapping */
	    array[hole] = array[child];
	}
	else
	    break;
    }
    array_index[array[0].v_num] = hole;
    array[hole] = array[0];
}


//============================================================================
// Update shortest distance of a vertex, note index start from 1.
// @param `v_num`: the number of a vertex.
// @param `new_dist`: the new shortest distance of a vertex.
static void bheap_update_dist(int v_num, int new_dist) {

    int child, hole;
    int index = array_index[v_num];
    Vertex old_vertex = array[index];
    
    if (new_dist < array[index].dist) { /* need percolate up */
	for (hole = index; hole > 1 && new_dist < array[hole/2].dist ; hole /= 2) {
	    array_index[array[hole/2].v_num] = hole; /* update mapping */	    
	    array[hole] = array[hole/2];
	}
	array_index[v_num] = hole;	
	array[hole] = old_vertex;
	array[hole].dist = new_dist;
    } else {			/* need percolate down */
	for (hole = index; 2 * hole <= current_size; hole = child) {
	    child = hole * 2;	/* let the child be left child at first */

	    // Make sure there is right child; then compare their value
	    if (child != current_size && array[child].dist > array[child+1].dist)
		child++;

	    // After found the min child, decide whether we need to continue
	    // percolate down.
	    if (new_dist > array[child].dist) {
		array_index[array[child].v_num] = hole;		
		array[hole] = array[child];
	    }
	    else
		break;
	}
	array_index[v_num] = hole;
	array[hole] = old_vertex;
	array[hole].dist = new_dist;
    }
}


//============================================================================
// Check if binary heap is empty or not
// @return 1 if binary heap is empty, otherwise 0.
int bheap_isEmpty() {
    return current_size == 0;
}

//============================================================================
// Update explore status of a vertex, note that index start from 1. 
// @param `v_num`: the number of a vertex.
// @param `known`: the new status of a vertex.
static void inline bheap_update_known(int v_num, int known) {
    array[array_index[v_num]].known = known;
}

//============================================================================
// @return known status of a given vertex
static int inline bheap_get_known(int v_num) {
    return array[array_index[v_num]].known;
}

//============================================================================
// @return distance status of a given vertex
static int inline bheap_get_dist(int v_num) {
    return array[array_index[v_num]].dist;
}

//============================================================================
// Free binary heap memory
static void bheap_free() {
    free(array);
    free(array_index);
}


// Dijkstra shortest path test
#define SIZE 7
int main() {
    /* Construct direct graph, more rigous test can read from file */
    int i, g_array[SIZE][SIZE] = {{ 0,2,DIST_MAX,1,DIST_MAX,DIST_MAX,DIST_MAX },
				  { DIST_MAX,0,DIST_MAX,3,10,DIST_MAX,DIST_MAX },
				  { 4,DIST_MAX,0,DIST_MAX,DIST_MAX,5,DIST_MAX},
				  { DIST_MAX,DIST_MAX,2,0,2,8,4 },
				  { DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,0,DIST_MAX,6 },
				  { DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,0,DIST_MAX},
				  { DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,1,0}};

    /* Dijkstra */
    Vertex v[SIZE];
    dijkstra(v, (int*)g_array, SIZE, 0);
    for (i = 0; i < SIZE; i++)
	printf("%d ", v[i].dist);
    printf("\n");
}
