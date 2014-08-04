// Dijkstra.c
// Note: 1. Vertex number starts from 0.
//       2. Graph is represented as adjacent matrix.
//       3. Can be used to both direct and indirect graph.
#include <stdio.h>
#include <stdlib.h>


//***************************************************************************
// Public Declaration
// Max possible distance betwenn two vertex
#define DIST_MAX 30000
// Representation of a vertex
typedef struct {
    int known;		      /* mark each node as known or unknown */
    int dist;		      /* shortest path to specified vertex */
} Vertex;
int dijkstra(Vertex *v, int *g, int size, int s);
//***************************************************************************


//============================================================================
// Implementation of dijkstra shortest path algorithm. Graph is represented
// as adjacent matrix. Vertex is numbered from 0 to size-1 (inclusive).
// @param `v`: an array of vertices. v[0] is the shortest path from node s to
//	node 0, etc.
// @param `g`: Adjacent matrix of a graph.
// @param `size`: Size of the graph, ie. the adjacent matrix is size * size.
// @param 's': Source vertex, the param must between 0 to size-1.
// @return -1 if fails, otherwise 0.
int dijkstra(Vertex *v, int *g, int size, int s) {

    if (s < 0 || s >= size) return -1; /* make sure vertex is valid */

    int i, j;

    // At first, only vertex `s` is known and shortest path is 0, all other
    // nodes are unknown and shortest path is max.
    for (i = 0; i < size; i++) {
        v[i].known = 0;
        v[i].dist = DIST_MAX;
    }
    v[s].dist = 0;

    for (i = 0; i < size; i++) {

        int min_dist = DIST_MAX, min_index = 0;

        // Find the shortest gready shortest path from the vertices which
        // haven't been explored.
        for (j = 0; j < size; j++) {
            if (v[j].known == 0 && v[j].dist < min_dist) {
                min_dist = v[j].dist;
                min_index = j;
            }
        }

        // Mark the node as explored.
        v[min_index].known = 1;

        // For every ajacent vertex of the above vertex, update their greedy
        // shortest path. (Only update when their greedy shortest path can be
        // smaller after adding vertex min_index.)
        for (j = 0; j < size; j++) {
            int temp_dist = min_dist + *(g + (min_index*size+j));
            if (v[j].known == 0 && temp_dist < v[j].dist)
                v[j].dist = temp_dist;
        }
    }

    return 0;
}



// Dijkstra shortest path small test and usage
#define SIZE 7
int main() {
    /* Construct graph, more rigous test can read from file */
    int i;
    int g[SIZE][SIZE] = {{ 0,2,DIST_MAX,1,DIST_MAX,DIST_MAX,DIST_MAX },
                         { DIST_MAX,0,DIST_MAX,3,10,DIST_MAX,DIST_MAX },
                         { 4,DIST_MAX,0,DIST_MAX,DIST_MAX,5,DIST_MAX},
                         { DIST_MAX,DIST_MAX,2,0,2,8,4 },
                         { DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,0,DIST_MAX,6 },
                         { DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,0,DIST_MAX},
                         { DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,1,0}};

    /* Dijkstra */
    Vertex* v = (Vertex*) malloc(sizeof(Vertex) * SIZE);
    dijkstra(v, (int*)g, SIZE, 0);
    for (i = 0; i < SIZE; i++)
        printf("%d ", v[i].dist);
    printf("\n");
    free(v);
}
