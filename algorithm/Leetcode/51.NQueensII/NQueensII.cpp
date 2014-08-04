// Follow up for N-Queens problem.

// Now, instead outputting board configurations, return the total number of
// distinct solutions.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    int totalNQueens(int n) {

        int result = 0;
        int rows[n];

        if (n == 0)
            return result;

        totalNQueensHelper(0, rows, n, result);
        return result;
    }


    void totalNQueensHelper(int rowIndex, int rows[], int n, int &result) {

        if (rowIndex == n) {
            result++;
            return;
        }

        for (int i = 0; i < n; i++) {
            rows[rowIndex] = i;
            if (validUntil(rows, rowIndex)) {
                totalNQueensHelper(rowIndex + 1, rows, n, result);
            }
        }
    }

    bool validUntil(int rows[], int rowIndex) {

        for (int i = 0; i < rowIndex; i++) {
            int diff = abs(rows[i] - rows[rowIndex]);
            if (diff == 0 || diff == (rowIndex - i)) {
                return false;
            }
        }
        return true;
    }


    // Bit manipulation solution
    // http://www.matrix67.com/blog/archives/266
    int cnt, upper;
    int totalNQueens2(int n) {
        cnt = 0, upper = (1<<n)-1 ;
        Queen(0,0,0);
        return cnt;
    }

    void Queen(int row, int ld, int rd) {

        int pos, p;

        if (row != upper) {
            pos = upper & (~(row | ld |rd));
            while (pos != 0) {
                p = pos & (-pos);
                pos = pos - p;
                Queen(row+p, (ld+p)<<1, (rd+p)>>1);
            }
        } else {
            cnt++;
        }
    }
};


int main(void) {

    Solution solution;

    cout << solution.totalNQueens(4) << endl;
    return 0;
}
