// http://www.geeksforgeeks.org/dynamic-programming-set-11-egg-dropping-puzzle/

// The following is a description of the instance of this famous puzzle
// involving n=2 eggs and a building with k=36 floors.

// Suppose that we wish to know which stories in a 36-story building are
// safe to drop eggs from, and which will cause the eggs to break on landing.
// We make a few assumptions:

// ...An egg that survives a fall can be used again.
// ...A broken egg must be discarded.
// ...The effect of a fall is the same for all eggs.
// ...If an egg breaks when dropped, then it would break if dropped from a
//    higher floor.
// ...If an egg survives a fall then it would survive a shorter fall.
// ...It is not ruled out that the first-floor windows break eggs, nor is it
//    ruled out that the 36th-floor do not cause an egg to break.

// If only one egg is available and we wish to be sure of obtaining the right
// result, the experiment can be carried out in only one way. Drop the egg from
// the first-floor window; if it survives, drop it from the second floor window.
// Continue upward until it breaks. In the worst case, this method may require
// 36 droppings. Suppose 2 eggs are available. What is the least number of
// egg-droppings that is guaranteed to work in all cases?

// The problem is not actually to find the critical floor, but merely to decide
// floors from which eggs should be dropped so that total number of trials are
// minimized.

// 1) Optimal Substructure:
//    When we drop an egg from a floor x, there can be two cases (1) The egg
//    breaks; (2) The egg doesn’t break.
//    1) If the egg breaks after dropping from xth floor, then we only need to
//       check for floors lower than x with remaining eggs; so the problem reduces
//       to x-1 floors and n-1 eggs
//    2) If the egg doesn’t break after dropping from the xth floor, then we
//       only need to check for floors higher than x; so the problem reduces to
//       k-x floors and n eggs.
//    Since we need to minimize the number of trials in worst case, we take the
//    maximum of two cases. We consider the max of above two cases for every floor
//    and choose the floor which yields minimum number of trials.

# include <stdio.h>
# include <limits.h>


// A utility function to get maximum of two integers
int max(int a, int b) { return (a > b)? a: b; }


/* Function to get minimum number of trails needed in worst
 * case with n eggs and k floors */
int eggDrop(int n, int k) {

    // If there are no floors, then no trials needed. OR if there is
    // one floor, one trial needed.
    if (k == 1 || k == 0)
        return k;

    // We need k trials for one egg and k floors
    if (n == 1)
        return k;

    int min = INT_MAX, x, res;

    // Consider all droppings from 1st floor to kth floor and
    // return the minimum of these values plus 1.
    for (x = 1; x <= k; x++)
    {
        res = max(eggDrop(n-1, x-1), eggDrop(n, k-x));
        if (res < min)
            min = res;
    }

    return min + 1;
}


/* Function to get minimum number of trails needed in worst
  case with n eggs and k floors */
int eggDropDP(int n, int k)
{
    /* A 2D table where entery eggFloor[i][j] will represent minimum
       number of trials needed for i eggs and j floors. */
    int eggFloor[n+1][k+1];
    int res;
    int i, j, x;

    // We need one trial for one floor and0 trials for 0 floors
    for (i = 1; i <= n; i++)
    {
        eggFloor[i][1] = 1;
        eggFloor[i][0] = 0;
    }

    // We always need j trials for one egg and j floors.
    for (j = 1; j <= k; j++)
        eggFloor[1][j] = j;

    // Fill rest of the entries in table using optimal substructure
    // property
    for (i = 2; i <= n; i++)
    {
        for (j = 2; j <= k; j++)
        {
            eggFloor[i][j] = INT_MAX;
            for (x = 1; x <= j; x++)
            {
                res = 1 + max(eggFloor[i-1][x-1], eggFloor[i][j-x]);
                if (res < eggFloor[i][j])
                    eggFloor[i][j] = res;
            }
        }
    }

    // eggFloor[n][k] holds the result
    return eggFloor[n][k];
}


class MySolution {
public:
    // Given `n` eggs and `k` floors, find the min number of trials in the
    // worst case, in order to find the critical floor
    int eggDrop(int n, int k) {

        // if we have only 1 egg, we have to try all floors in the worst case,
        // i.e. try first floor, second floor, ..., until kth floor.
        if (n == 1) {
            return k;
        }

        // if we have only one floor, try one once; or 0 if no floor
        if (k == 1 || k == 0)
            return k;

        int min = INT_MAX;
        for (int i = 1; i <= k; i++) {
            // worst case of egg break and egg doesn't break
            // if egg break, then we have n-1 eggs, and we have i-1 floors to
            // try; if egg doesn't break, then we still have n eggs, and we
            // have k-i floors to try.
            int res = max(eggDrop(n-1, i-1), eggDrop(n, k-i));
            if (res < min) {
                min = res;
            }
        }

        return min + 1;
    }


    int eggDropDP(int n, int k) {

        int table[n+1][k+1];

        for (int i = 0; i <= k; i++) {
            table[0][i] = 0;
            table[1][i] = i;    // only one egg
        }

        for (int i = 0; i <= n; i++) {
            table[i][0] = 0;    // floor 0
            table[i][1] = 1;    // floor 1
        }

        for (int i = 2; i <= n; i++) { // for different # of egg
            for (int j = 2; j <= k; j++) { // for different floor
                table[i][j] = INT_MAX;
                for (int x = 1; x < j; x++) {
                    int res = 1 + max(table[i-1][x-1], table[i][j-x]);
                    if (res < table[i][j]) {
                        table[i][j] = res;
                    }
                }
            }
        }

        return table[n][k];
    }

private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
};


/* Driver program to test to pront printDups*/
int main() {

    MySolution solution;
    int n = 2, k = 10;

    printf("Minimum number of trials in worst case with %d eggs and "
             "%d floors is %d \n", n, k, solution.eggDrop(n, k));
    printf("Minimum number of trials in worst case with %d eggs and "
             "%d floors is %d \n", n, k, solution.eggDropDP(n, k));
    return 0;
}
