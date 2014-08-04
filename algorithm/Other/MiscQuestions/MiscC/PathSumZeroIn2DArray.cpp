// Find the path sum to zero in 2-D array. The sequence can move up, down,
// left and right.
// For example:
//   1   3   5   7   4
//   2   1   8   6   5
//   4   2  -1  -2   6
// The path is [1, 2, -1, -2]

#include <vector>
#include <iostream>
using namespace std;


// Recursive search
class Solution1
{
public:
    bool findPathHelper(vector<vector<int> > &array, int i, int j, vector<int> &path,
                        vector<vector<bool> > &visited, int sum)
    {
        path.push_back(array[i][j]);
        sum += array[i][j];

        if (sum == 0) {
            return true;
        }

        // try go up
        if (i - 1 >= 0 && visited[i-1][j] == false) {
            visited[i-1][j] = true;
            if (findPathHelper(array, i-1, j, path, visited, sum))
                return true;
            visited[i-1][j] = false;
        }

        // try go down
        if (i + 1 < array.size() && visited[i+1][j] == false) {
            visited[i+1][j] = true;
            if (findPathHelper(array, i+1, j, path, visited, sum))
                return true;
            visited[i+1][j] = false;
        }

        // try go left
        if (j - 1 >= 0 && visited[i][j-1] == false) {
            visited[i][j-1] = true;
            if (findPathHelper(array, i, j-1, path, visited, sum))
                return true;
            visited[i][j-1] = false;
        }

        // try go right
        if (j + 1 < array[0].size() && visited[i][j+1] == false) {
            visited[i][j+1] = true;
            if (findPathHelper(array, i, j+1, path, visited, sum))
                return true;
            visited[i][j+1] = false;
        }

        path.pop_back();
        return false;
    }


    vector<int> findPath(vector<vector<int> > &array)
    {
        vector<int> path;
        vector<vector<bool> > visited(array.size(), vector<bool>(array[0].size()));

        for (int i = 0; i < array.size(); i++) {
            for (int j = 0; j < array[0].size(); j++) {
                if (findPathHelper(array, i, j, path, visited, 0)) {
                    return path;
                }
            }
        }

        return path;
    }
};


int main(void) {

#define M  3
#define N  5
    int input[M][N] = {{1,3,5,7,4},
                       {2,1,8,6,5},
                       {4,2,-1,-2,6}};

    vector<vector<int> > array(M, vector<int>(N));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            array[i][j] = input[i][j];

    Solution1 solution;
    vector<int> result = solution.findPath(array);

    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    cout << endl;

    return 0;
}
