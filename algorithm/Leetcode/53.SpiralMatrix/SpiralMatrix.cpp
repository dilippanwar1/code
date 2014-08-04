// Given a matrix of m x n elements (m rows, n columns), return all elements
// of the matrix in spiral order.

// For example,
// Given the following matrix:

// [
//  [ 1, 2, 3 ],
//  [ 4, 5, 6 ],
//  [ 7, 8, 9 ]
// ]
// You should return [1,2,3,6,9,8,7,4,5].

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &mat)
    {
        vector<int> ret;

        if (mat.empty() || mat[0].empty())
            return ret;

        int left = -1, right = mat[0].size()-1;
        int top = 0, bottom = mat.size()-1;

        while (left <= right && top <= bottom) {
            for (int j= ++left; top <= bottom && j <= right; j++)
                ret.push_back(mat[top][j]);
            for (int i= ++top; left <= right && i <= bottom; i++)
                ret.push_back(mat[i][right]);
            for (int j= --right; top <= bottom && j >= left; j--)
                ret.push_back(mat[bottom][j]);
            for (int i= --bottom; left <= right && i >= top; i--)
                ret.push_back(mat[i][left]);
        }

        return ret;
    }
};


int main(void) {
    return 0;
}
