// Find the longest decreasing sequence in 2-D array. The sequence can move
// up, down, left and right.
// For example:
//   1   3   5   7   4
//   2   1   8   6   5
//   4   0  -1  -2   6
// The longest decreasing sequence is : 7, 5, 3, 1, 0, -1, -2, length = 7.

#include <vector>
#include <iostream>
using namespace std;


// Recursive search
class Solution1
{
public:
    int findLongestHelper(vector<vector<int> > &array, int i, int j,
                          vector<vector<bool> > &visited)
    {
        int current = 1;

        // try go up
        if (i - 1 >= 0 && visited[i-1][j] == false &&
            array[i][j] > array[i-1][j]) {
            visited[i-1][j] = true;
            current = max(current, 1 + findLongestHelper(array, i-1, j, visited));
            visited[i-1][j] = false;
        }

        // try go down
        if (i + 1 < array.size() && visited[i+1][j] == false &&
            array[i][j] > array[i+1][j]) {
            visited[i+1][j] = true;
            current = max(current, 1 + findLongestHelper(array, i+1, j, visited));
            visited[i+1][j] = false;
        }

        // try go left
        if (j - 1 >= 0 && visited[i][j-1] == false &&
            array[i][j] > array[i][j-1]) {
            visited[i][j-1] = true;
            current = max(current, 1 + findLongestHelper(array, i, j-1, visited));
            visited[i][j-1] = false;
        }

        // try go right
        if (j + 1 < array[0].size() && visited[i][j+1] == false &&
            array[i][j] > array[i][j+1]) {
            visited[i][j+1] = true;
            current = max(current, 1 + findLongestHelper(array, i, j+1, visited));
            visited[i][j+1] = false;
        }

        return current;
    }


    int findLongest(vector<vector<int> > &array)
    {
        int longest = INT_MIN;
        vector<vector<bool> > visited(array.size(), vector<bool>(array[0].size()));

        for (int i = 0; i < array.size(); i++) {
            for (int j = 0; j < array[0].size(); j++) {
                int current = findLongestHelper(array, i, j, visited);
                longest = max(longest, current);
            }
        }

        return longest;
    }
};


int main(void) {

// #define M  3
// #define N  5
    // int input[M][N] = {{1,3,5,7,4},
    //                    {2,1,8,6,5},
    //                    {4,0,-1,-2,6}};

#define M  5
#define N  5
	int input[M][N] = {{100,100,18,19,20},
                       {10,100,16,100,14},
                       {12,14,15,100,12},
                       {100,100,11,100,11},
                       {100,100,9,100,7}};

    vector<vector<int> > array(M, vector<int>(N));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            array[i][j] = input[i][j];

    Solution1 solution;
    cout << solution.findLongest(array) << endl;

    return 0;
}
