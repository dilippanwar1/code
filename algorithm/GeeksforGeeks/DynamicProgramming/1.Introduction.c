// http://www.geeksforgeeks.org/dynamic-programming-set-1/
// http://www.geeksforgeeks.org/dynamic-programming-set-2 \
// -optimal-substructure-property/

// Introduction - 1
// Dynamic Programming is an algorithmic paradigm that solves a given complex
// problem by breaking it into subproblems and stores the results of subproblems
// to avoid computing the same results again. Following are the two main
// properties of a problem that suggest that the given problem can be solved
// using Dynamic programming.
//   1) Overlapping Subproblems
//   2) Optimal Substructure

// 1) Overlapping Subproblems:
// Like Divide and Conquer, Dynamic Programming combines solutions to sub-problems.
// Dynamic Programming is mainly used when solutions of same subproblems are
// needed again and again. In dynamic programming, computed solutions to subproblems
// are stored in a table so that these don't have to recomputed. So Dynamic
// Programming is not useful when there are no common (overlapping_subproblems
// because there is no point storing the solutions if they are not needed again.
// For example, Binary Search doesn't have common subproblems. If we take example
// of following recursive program for Fibonacci Numbers, there are many subproblems
// which are solved again and again.

// simple recursive program for Fibonacci numbers
int fib(int n)
{
   if ( n <= 1 )
      return n;
   return fib(n-1) + fib(n-2);
}

// Recursion tree for execution of fib(5)
                         fib(5)
                     /             \
               fib(4)                fib(3)
             /      \                /     \
         fib(3)      fib(2)         fib(2)    fib(1)
        /     \        /    \       /    \
  fib(2)   fib(1)  fib(1) fib(0) fib(1) fib(0)
  /    \
fib(1) fib(0)
                         ;
// We can see that the function f(3) is being called 2 times. If we would have
// stored the value of f(3), then instead of computing it again, we would have
// reused the old stored value. There are following two different ways to store
// the values so that these values can be reused.

// a) Memoization (Top Down):
// b) Tabulation (Bottom Up):

// a) Memoization (Top Down): The memoized program for a problem is similar to
//    the recursive version with a small modification that it looks into a lookup
//    table before computing solutions. We initialize a lookup array with all
//    initial values as NIL. Whenever we need solution to a subproblem, we first
//    look into the lookup table. If the precomputed value is there then we return
//    that value, otherwise we calculate the value and put the result in lookup
//    table so that it can be reused later.
// Following is the memoized version for nth Fibonacci Number.

/* Memoized version for nth Fibonacci number */
#include <stdio.h>

#define NIL -1
#define MAX 100

int lookup[MAX];

/* Function to initialize NIL values in lookup table */
void _initialize()
{
    int i;
    for (i = 0; i < MAX; i++)
        lookup[i] = NIL;
}

/* function for nth Fibonacci number */
int fib(int n)
{
    if (lookup[n] == NIL) {
        if ( n <= 1 )
            lookup[n] = n;
        else
            lookup[n] = fib(n-1) + fib(n-2);
    }

    return lookup[n];
}

int main ()
{
    int n = 40;
    _initialize();
    printf("Fibonacci number is %d ", fib(n));
    getchar();
    return 0;
}


// b) Tabulation (Bottom Up): The tabulated program for a given problem builds
//    a table in bottom up fashion and returns the last entry from table.

/* tabulated version */
#include <stdio.h>

int fib(int n)
{
    int f[n+1];
    int i;
    f[0] = 0; f[1] = 1;

    for (i = 2; i <= n; i++)
        f[i] = f[i-1] + f[i-2];

    return f[n];
}

int main ()
{
    int n = 9;
    printf("Fibonacci number is %d ", fib(n));
    getchar();
    return 0;
}


// Both tabulated and Memoized store the solutions of subproblems. In Memoized
// version, table is filled on demand while in tabulated version, starting from
// the first entry, all entries are filled one by one. Unlike the tabulated
// version, all entries of the lookup table are not necessarily filled in memoized
// version. For example, memoized solution of LCS problem doesn't necessarily
// fill all entries. (LCS = longest common subsequence)

// To see the optimization achieved by memoized and tabulated versions over the
// basic recursive version, see the time taken by following runs for 40th Fibonacci
// number.
// Simple recursive program
// Memoized version
// tabulated version

// Also see method 2 of Ugly Number post for one more simple example where we
// have overlapping subproblems and we store the results of subproblems.

// We will be covering Optimal Substructure Property and some more example problems
// in future posts on Dynamic Programming.

// Try following questions as an exercise of this post.
// 1) Write a memoized version for LCS problem. Note that the tabular version
//    is given in the CLRS book.
// 2) How would you choose between Memoization and Tabulation?

// References:
// http://www.cs.uiuc.edu/class/fa08/cs573/lectures/05-dynprog.pdf
// http://web.iiit.ac.in/~avidullu/pdfs/dynprg/Dynamic%20Programming%20Lesson.pdf
// http://www.youtube.com/watch?v=V5hZoJ6uK-s




// Introduction - 2
// As we discussed in Set 1, following are the two main properties of a problem
// that suggest that the given problem can be solved using Dynamic programming.
//   1) Overlapping Subproblems
//   2) Optimal Substructure
// We have already discussed Overlapping Subproblem property in the Set 1. Let
// us discuss Optimal Substructure property here.

// 2) Optimal Substructure:
// A given problems has Optimal Substructure Property if optimal solution of the
// given problem can be obtained by using optimal solutions of its subproblems.

// For example the shortest path problem has following optimal substructure
// property: If a node x lies in the shortest path from a source node u to
// destination node v then the shortest path from u to v is combination of
// shortest path from u to x and shortest path from x to v. The standard All
// Pair Shortest Path algorithms like Floyd-Warshall and Bellman-Ford are typical
// examples of Dynamic Programming.

// On the other hand the Longest path problem doesn't have the Optimal Substructure
// property. Here by Longest Path we mean longest simple path (path without cycle)
// between two nodes. Consider the following unweighted graph given in the CLRS
// book. There are two longest paths from q to t: q -> r ->t and q ->s->t. Unlike
// shortest paths, these longest paths do not have the optimal substructure property.
// For example, the longest path q->r->t is not a combination of longest path from
// q to r and longest path from r to t, because the longest path from q to r is
// q->s->t->r. ()

// References:
// http://en.wikipedia.org/wiki/Optimal_substructure
// CLRS book
