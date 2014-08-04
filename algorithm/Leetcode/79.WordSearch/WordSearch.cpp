// Given a 2D board and a word, find if the word exists in the grid.

// The word can be constructed from letters of sequentially adjacent cell,
// where "adjacent" cells are those horizontally or vertically neighboring.
// The same letter cell may not be used more than once.

// For example,
// Given board =
// [
//   ["ABCE"],
//   ["SFCS"],
//   ["ADEE"]
// ]
// word = "ABCCED", -> returns true,
// word = "SEE", -> returns true,
// word = "ABCB", -> returns false.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {

        if (board.size() == 0)
            return false;
        if (word.length() == 0)
            return true;

        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    if (existHelper(board, i, j, word, 0)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool existHelper(vector<vector<char> > &board, int i, int j,
                     string word, int p) {

        if (board[i][j] == word[p] && p == word.length()-1)
            return true;
        if (board[i][j] != word[p])
            return false;

        // if we can move up
        if (i > 0 && board[i-1][j] != 'x') {
            int tmp = board[i][j];
            board[i][j] = 'x';  // block, same as visited
            if (existHelper(board, i-1, j, word, p+1)) {
                return true;
            }
            board[i][j] = tmp;
        }

        // if we can move down
        if (i < board.size()-1 && board[i+1][j] != 'x') {
            int tmp = board[i][j];
            board[i][j] = 'x';  // block, same as visited
            if (existHelper(board, i+1, j, word, p+1)) {
                return true;
            }
            board[i][j] = tmp;
        }

        // if we can move left
        if (j > 0 && board[i][j-1] != 'x') {
            int tmp = board[i][j];
            board[i][j] = 'x';  // block, same as visited
            if (existHelper(board, i, j-1, word, p+1)) {
                return true;
            }
            board[i][j] = tmp;
        }

        // if we can move right
        if (j < board[0].size()-1 && board[i][j+1] != 'x') {
            int tmp = board[i][j];
            board[i][j] = 'x';  // block, same as visited
            if (existHelper(board, i, j+1, word, p+1)) {
                return true;
            }
            board[i][j] = tmp;
        }

        return false;
    }
};


#define  ROW    3
#define  COL    4
int main(void) {

    Solution solution;
    vector<vector<char> > matrix(ROW, vector<char>(COL));
    int a[ROW][COL] = {{'A','B','C','E'}, {'S','F','C','S'}, {'A','D','E','E'}};

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            matrix[i][j] = a[i][j];
        }
    }

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }

    cout << solution.exist(matrix, "AG") << endl;
    return 0;
}
