// http://www.geeksforgeeks.org/dynamic-programming-set-21-box-stacking-problem/

// You are given a set of n types of rectangular 3-D boxes, where the i^th box
// has height h(i), width w(i) and depth d(i) (all real numbers). You want to
// create a stack of boxes which is as tall as possible, but you can only stack
// a box on top of another box if the dimensions of the 2-D base of the lower
// box are each strictly larger than those of the 2-D base of the higher box.
// Of course, you can rotate a box so that any side functions as its base. It
// is also allowable to use multiple instances of the same type of box.

// Source: http://people.csail.mit.edu/bdean/6.046/dp/. The link also has video
// for explanation of solution.

// The Box Stacking problem is a variation of LIS problem. We need to build a
// maximum height stack.

// Following are the key points to note in the problem statement:
// 1) A box can be placed on top of another box only if both width and depth of
//    the upper placed box are smaller than width and depth of the lower box
//    respectively.
// 2) We can rotate boxes. For example, if there is a box with dimensions
//    {1x2x3} where 1 is height, 2×3 is base, then there can be three
//    possibilities, {1x2x3}, {2x1x3} and {3x1x2}.
// 3) We can use multiple instances of boxes. What it means is, we can have two
//    different rotations of a box as part of our maximum height stack.

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


/* Representation of a box */
struct Box
{
    // h -> height, w -> width, d -> depth
    int h, w, d;  // for simplicity of solution, always keep w <= d
};

// A utility function to get minimum of two intgers
int min (int x, int y)
{ return (x < y)? x : y; }

// A utility function to get maximum of two intgers
int max (int x, int y)
{ return (x > y)? x : y; }

/* Following function is needed for library function qsort(). We
   use qsort() to sort boxes in decreasing order of base area.
   Refer following link for help of qsort() and compare()
   http://www.cplusplus.com/reference/clibrary/cstdlib/qsort/ */
int compare (const void *a, const void * b)
{
    return ( (*(Box *)b).d * (*(Box *)b).w ) -
        ( (*(Box *)a).d * (*(Box *)a).w );
}

/* Returns the height of the tallest stack that can be formed with give
   type of boxes */
int maxStackHeight( Box arr[], int n )
{
    /* Create an array of all rotations of given boxes
       For example, for a box {1, 2, 3}, we consider three
       instances{{1, 2, 3}, {2, 1, 3}, {3, 1, 2}} */
    Box rot[3*n];
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        // Copy the original box
        rot[index] = arr[i];
        index++;

        // First rotation of box
        rot[index].h = arr[i].w;
        rot[index].d = max(arr[i].h, arr[i].d);
        rot[index].w = min(arr[i].h, arr[i].d);
        index++;

        // Second rotation of box
        rot[index].h = arr[i].d;
        rot[index].d = max(arr[i].h, arr[i].w);
        rot[index].w = min(arr[i].h, arr[i].w);
        index++;
    }

    // Now the number of boxes is 3n
    n = 3*n;

    /* Sort the array ‘rot[]‘ in decreasing order, using library
       function for quick sort */
    qsort (rot, n, sizeof(rot[0]), compare);

    // Uncomment following two lines to print all rotations
    // for (int i = 0; i < n; i++ )
    //    printf("%d x %d x %d\n", rot[i].h, rot[i].w, rot[i].d);

    /* Initialize msh values for all indexes
       msh[i] –> Maximum possible Stack Height with box i on top */
    int msh[n];
    for (int i = 0; i < n; i++ )
        msh[i] = rot[i].h;

    /* Compute optimized msh values in bottom up manner */
    for (int i = 1; i < n; i++ )
        for (int j = 0; j < i; j++ )
            if (rot[i].w < rot[j].w && rot[i].d < rot[j].d &&
                msh[i] < msh[j] + rot[i].h) {
                msh[i] = msh[j] + rot[i].h;
            }


    /* Pick maximum of all msh values */
    int max = -1;
    for ( int i = 0; i < n; i++ )
        if ( max < msh[i] )
            max = msh[i];

    return max;
}


class MySolution {
public:
    int maxStackHeight(Box arr[], int n) {

        // first generate all rotations of boxes
        int size = 3*n;
        Box boxes[size];

        // we need consider different height rotation. (here are three
        // cases, for simplicity)
        for (int i = 0; i < n; i++) {
            boxes[3*i] = arr[i];

            boxes[3*i + 1].h = arr[i].w;
            boxes[3*i + 1].d = max(arr[i].h, arr[i].d);
            boxes[3*i + 1].w = min(arr[i].h, arr[i].d);

            boxes[3*i + 2].h = arr[i].d;
            boxes[3*i + 2].d = max(arr[i].h, arr[i].w);
            boxes[3*i + 2].w = min(arr[i].h, arr[i].w);
        }

        return maxStackHeightHelper(boxes, size, NULL);
    }

private:
    int maxStackHeightHelper(Box boxes[], int size, Box *bottom) {

        int max_len = 0;

        for (int i = 0; i < size; i++) {
            // build stack based on different bottom
            if (canBeAbove(&boxes[i], bottom)) {
                int len = maxStackHeightHelper(boxes, size, &boxes[i]);
                if (len + boxes[i].h > max_len) {
                    max_len = len + boxes[i].h;
                }
            }
        }

        return max_len;
    }

    bool canBeAbove(Box *box1, Box *box2) {

        if (box2 == NULL) {
            return true;
        }
        if ((*box1).w < (*box2).w && (*box1).d < (*box2).d) {
            return true;
        }
        return false;
    }

    int max(int a, int b) {
        return a > b ? a : b;
    }

    int min(int a, int b) {
        return a < b ? a : b;
    }
};


/* Driver program to test above function */
int main()
{
    MySolution solution;
    Box arr[] = {{5,2,4},{1,2,4},{4,2,4}};
    // Box arr[] = { {4, 6, 7}, {4, 5, 6}, {6,3,6}, {36,75,21},
    //               {48, 68, 17}, {42, 15, 61}, {16,13,26}, {3,7,2} };
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("The maximum possible height of stack is %d\n",
           solution.maxStackHeight(arr, n));
    printf("The maximum possible height of stack is %d\n",
           maxStackHeight(arr, n));

    return 0;
}
