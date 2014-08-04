// http://www.geeksforgeeks.org/dynamic-programming-set-34-assembly-line-scheduling/

// A car factory has two assembly lines, each with n stations. A station is
// denoted by S(i,j) where i is either 1 or 2 and indicates the assembly line
// the station is on, and j indicates the number of the station. The time taken
// per station is denoted by a(i,j). Each station is dedicated to some sort of
// work like engine fitting, body fitting, painting and so on. So, a car chassis
// must pass through each of the n stations in order before exiting the factory.
// The parallel stations of the two assembly lines perform the same task. After
// it passes through station S(i,j), it will continue to station S(i,j+1) unless
// it decides to transfer to the other line. Continuing on the same line incurs
// no extra cost, but transferring from line i at station j - 1 to station j on
// the other line takes time t(i,j). Each assembly line takes an entry time ei
// and exit time xi which may be different for the two lines. Give an algorithm
// for computing the minimum time it will take to build a car chassis.


#include <stdio.h>
#define NUM_LINE 2
#define NUM_STATION 10


// Utility function to find minimum of two numbers
int min(int a, int b) { return a < b ? a : b; }

int carAssembly(int a[][NUM_STATION], int t[][NUM_STATION], int *e, int *x)
{
    int T1[NUM_STATION], T2[NUM_STATION], i;

    T1[0] = e[0] + a[0][0]; // time taken to leave first station in line 1
    T2[0] = e[1] + a[1][0]; // time taken to leave first station in line 2

    // Fill tables T1[] and T2[] using the above given recursive relations
    for (i = 1; i < NUM_STATION; ++i)
    {
        T1[i] = min(T1[i-1] + a[0][i], T2[i-1] + t[1][i] + a[0][i]);
        T2[i] = min(T2[i-1] + a[1][i], T1[i-1] + t[0][i] + a[1][i]);
    }

    // Consider exit times and retutn minimum
    return min(T1[NUM_STATION-1] + x[0], T2[NUM_STATION-1] + x[1]);
}


class MySolution {
public:
    int carAssembly(int a[][NUM_STATION], int t[][NUM_STATION],
                    int e[], int x[]) {
        return min(carAssemblyHelper(a, t, e, x, 0, NUM_STATION-1) + x[0],
                   carAssemblyHelper(a, t, e, x, 1, NUM_STATION-1) + x[1]);
    }

    int carAssemblyDP(int a[][NUM_STATION], int t[][NUM_STATION],
                      int e[], int x[]) {
        int T1[NUM_STATION], T2[NUM_STATION];

        T1[0] = e[0] + a[0][0];
        T2[0] = e[1] + a[1][0];

        for (int i = 1; i < NUM_STATION; i++) {
            T1[i] = min(T1[i-1] + a[0][i], T2[i-1] + t[1][i] + a[0][i]);
            T2[i] = min(T2[i-1] + a[1][i], T1[i-1] + t[0][i] + a[1][i]);
        }

        return min(T1[NUM_STATION-1] + x[0], T2[NUM_STATION-1] + x[1]);
    }

private:
    int carAssemblyHelper(int a[][NUM_STATION], int t[][NUM_STATION],
                          int e[], int x[], int line, int station) {

        if (station == 0) {
            return a[line][station] + e[line];
        }

        int use_line0 = carAssemblyHelper(a, t, e, x, 0, station-1);
        use_line0 += a[line][station];
        if (line == 1) {
            use_line0 += t[0][station-1];
        }
        int use_line1 = carAssemblyHelper(a, t, e, x, 1, station-1);
        use_line1 += a[line][station];
        if (line == 0) {
            use_line1 += t[1][station-1];
        }

        return min(use_line0, use_line1);
    }

    int min(int a, int b) {
        return a < b ? a : b;
    }
};


int main()
{
    MySolution solution;
    int a[][NUM_STATION] = {{4, 5, 3, 4, 1, 9, 2, 4, 4, 4},
                            {2, 10, 1, 4, 8, 6, 9, 2, 6, 6}};
    int t[][NUM_STATION] = {{0, 7, 4, 9, 3, 4, 3, 3, 8, 3},
                            {0, 9, 2, 2, 8, 8, 1, 7, 8, 6}};
    int e[] = {10, 12}, x[] = {18, 7};

    printf("%d\n", carAssembly(a, t, e, x));
    printf("%d\n", solution.carAssembly(a, t, e, x));
    printf("%d\n", solution.carAssemblyDP(a, t, e, x));

    return 0;
}
