// Given an integer n, generate a square matrix filled with elements from
// 1 to n2 in spiral order.

// For example,
// Given n = 3,

// You should return the following matrix:
// [
//  [ 1, 2, 3 ],
//  [ 8, 9, 4 ],
//  [ 7, 6, 5 ]
// ]

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {

        int index = 1;
        int left = -1, right = n - 1;
        int top = 0, bottom = n - 1;
        vector<vector<int> > result(n, vector<int>(n));

        while (index <= n * n) {
            for (int j = ++left; j <= right; j++) {
                result[top][j] = index++;
            }
            for (int i = ++top; i <= bottom; i++) {
                result[i][right] = index++;
            }
            for (int j = --right; j >= left; j--) {
                result[bottom][j] = index++;
            }
            for (int i = --bottom; i >= top; i--) {
                result[i][left] = index++;
            }
        }

        return result;
    }
};


int main(int argc, char *argv[])
{
    Solution solution;

    vector<vector<int> > result = solution.generateMatrix(4);

    for (int i = 0; i < result.size(); i++) {
        cout << "[ ";
        vector<int> res = result[i];
        for (int j = 0; j < res.size(); j++) {
            cout << res[j] << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
