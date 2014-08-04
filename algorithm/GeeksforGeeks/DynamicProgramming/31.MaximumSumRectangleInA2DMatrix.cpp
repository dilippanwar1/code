// http://www.geeksforgeeks.org/dynamic-programming-set-27-max-sum-rectangle-in-a-2d-matrix/
// Given a 2D array, find the maximum sum subarray in it.

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <iostream>
using namespace std;

#define  ROW    4
#define  COL    5


class MySolution {
public:
    void findMaxSum(int matrx[ROW][COL]) {

        int temp[COL];
        int max_sum = INT_MIN, c_start, c_end, r_start, r_end;
        int start, end;

        for (int i = 0; i < ROW; i++) {
            memset(temp, 0, sizeof(temp));
            for (int j = i; j < ROW; j++) {
                // sum r_end
                for (int k = 0; k < COL; k++) {
                    temp[k] += matrx[j][k];
                }

                int sum = findArrayMaxSum(temp, COL, start, end);
                if (sum > max_sum) {
                    max_sum = sum;
                    c_start = start;
                    c_end = end;
                    r_start = i;
                    r_end =j;
                }
            }
        }

        // Print final values
        printf("(Top-Left) (%d, %d)\n", r_start, c_start);
        printf("(Bottom-Right) (%d, %d)\n", r_end, c_end);
        printf("Max sum is: %d\n", max_sum);
    }

    // Given array of size COL, return max sum and it's range. O(n)
    int findArrayMaxSum(int array[], int n, int &start, int &end) {

        int max_sum = 0;
        int max_sofar = 0;
        int reset_start = 0;

        end = -1;
        // find max sum when at least one positive number
        for (int k = 0; k < n; k++) {
            max_sofar += array[k];
            if (max_sofar < 0) {
                max_sofar = 0;
                reset_start = k + 1;
            } else if (max_sofar > max_sum) {
                max_sum = max_sofar;
                start = reset_start;
                end = k;
            }
        }

        // handle all negative case
        if (end == -1) {
            max_sum = array[0];
            start = end = 0;
            // find the maximum element in array
            for (int i = 1; i < n; i++) {
                if (array[i] > max_sum) {
                    max_sum = array[i];
                    start = end = i;
                }
            }
        }

        return max_sum;
    }
};

// Driver program to test above functions
int main()
{
    MySolution solution;
    int matrx[ROW][COL] = {{1, 2, -1, -4, -20},
                           {-8, -3, 4, 2, 1},
                           {3, 8, 10, 1, 3},
                           {-4, -1, 1, 7, -6}};

    solution.findMaxSum(matrx);

    return 0;
}
