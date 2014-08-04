// http://www.geeksforgeeks.org/dynamic-programming-set-16-floyd-warshall-algorithm/

// The Floyd Warshall Algorithm is for solving the All Pairs Shortest Path
// problem. The problem is to find shortest distances between every pair of
// vertices in a given edge weighted directed Graph.

// Example:
// Input:
//        graph[][] = { {0,   5,  INF, 10},
//                     {INF,  0,  3,  INF},
//                     {INF, INF, 0,   1},
//                     {INF, INF, INF, 0} }
// which represents the following graph
//              10
//        (0)------->(3)
//         |         /|\
//       5 |          |
//         |          | 1
//        \|/         |
//        (1)------->(2)
//             3
// Note that the value of graph[i][j] is 0 if i is equal to j
// And graph[i][j] is INF (infinite) if there is no edge from vertex i to j.

// Output:
// Shortest distance matrix
//       0      5      8      9
//     INF      0      3      4
//     INF    INF      0      1
//     INF    INF    INF      0

#include <stdio.h>

#define  V    4
#define  INF  99999


// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshell (int graph[][V])
{
    /* dist[][] will be the output matrix that will finally have the shortest
      distances between every pair of vertices */
    int dist[V][V], i, j, k;

    /* Initialize the solution matrix same as input graph matrix. Or
       we can say the initial values of shortest distances are based
       on shortest paths considering no intermediate vertex. */
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    /* Add all vertices one by one to the set of intermediate vertices.
      ---> Before start of a iteration, we have shortest distances between all
      pairs of vertices such that the shortest distances consider only the
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
      ----> After the end of a iteration, vertex no. k is added to the set of
      intermediate vertices and the set becomes {0, 1, 2, .. k} */
    for (k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist);
}

/* A utility function to print solution */
void printSolution(int dist[][V])
{
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}


class MySolution {
public:
    void floydWarshell(int graph[][V]) {

        int dist[V][V];

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = graph[i][j];
            }
        }

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                for (int k = 0; k < V; k++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        printSolution(dist);
    }


private:
    /* A utility function to print solution */
    void printSolution(int dist[][V]) {

        printf ("Following matrix shows the shortest distances"
                " between every pair of vertices \n");
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][j] == INF)
                    printf("%7s", "INF");
                else
                    printf ("%7d", dist[i][j]);
            }
            printf("\n");
        }
    }
};


// driver program to test above function
int main()
{
    /* Let us create the following weighted graph
       10
       (0)------->(3)
       |         /|\
       5 |          |
       |          | 1
       \|/         |
       (1)------->(2)
       3           */
    MySolution solution;
    int graph[V][V] = { {0,   5,  INF, 10},
                        {INF, 0,   3, INF},
                        {INF, INF, 0,   1},
                        {INF, INF, INF, 0}
    };

    // Print the solution
    solution.floydWarshell(graph);
    return 0;
}
