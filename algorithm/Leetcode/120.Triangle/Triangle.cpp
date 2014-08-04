// Given a triangle, find the minimum path sum from top to bottom. Each step
// you may move to adjacent numbers on the row below.

// For example, given the following triangle
// [
//      [2],
//     [3,4],
//    [6,5,7],
//   [4,1,8,3]
// ]
// The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

// Note:
// Bonus point if you are able to do this using only O(n) extra space, where
// n is the total number of rows in the triangle.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    int minimumTotal(vector<vector<int> > &triangle) {

        if (triangle.size() == 0)
            return 0;

        vector<int> array(triangle[triangle.size()-1]);
        for (int i = triangle.size() - 2; i >= 0; i--) {
            int size = i + 1;
            for (int j = 0; j < size; j++) {
                array[j] = triangle[i][j] + min(array[j], array[j+1]);
            }
        }

        return array[0];
    }


    int minimumTotal2(vector<vector<int> > &triangle) {

        if (triangle.size() == 0)
            return 0;

        int n = triangle.size();
        int **cache = new int *[n];
        for (int i = 0; i < n; i++) {
            cache[i] = new int[n];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cache[i][j] = INT_MIN;
            }
        }
        return minimumTotalHelper(triangle, 0, 0, cache);
    }

    int minimumTotalHelper(vector<vector<int> > &triangle,
                           int level, int index, int **cache) {

        if (level == (triangle.size() - 1))
            return triangle[level][index];

        if (cache[level][index] != INT_MIN)
            return cache[level][index];

        cache[level][index] = min(
            minimumTotalHelper(triangle, level+1, index, cache),
            minimumTotalHelper(triangle, level+1, index+1, cache))
            + triangle[level][index];
        return cache[level][index];
    }
};


int main(void) {

    vector<int> v1;
    v1.push_back(-1);
    vector<int> v2;
    v2.push_back(2);
    v2.push_back(3);
    vector<int> v3;
    v3.push_back(1);
    v3.push_back(-1);
    v3.push_back(-3);
    vector<int> v4;
    v4.push_back(4);
    v4.push_back(1);
    v4.push_back(8);
    v4.push_back(3);
    vector<vector<int> > triangle;
    triangle.push_back(v1);
    triangle.push_back(v2);
    triangle.push_back(v3);
    triangle.push_back(v4);

    for (int i = 0; i < triangle.size(); i++) {
        cout << "[ ";
        vector<int> res = triangle[i];
        for (int j = 0; j < res.size(); j++) {
            cout << res[j] << " ";
        }
        cout << "]" << endl;
    }

    Solution solution;
    cout << solution.minimumTotal(triangle) << endl;
    return 0;
}
