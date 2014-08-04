// Write a program to solve a Sudoku puzzle by filling the empty cells.

// Empty cells are indicated by the character '.'.

// You may assume that there will be only one unique solution.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    void solveSudoku(vector<vector<char> > &board)
    {
        solveSudokuHelper(board);
    }

    bool solveSudokuHelper(vector<vector<char> > &board)
    {
        int r, c;

        getNextEmpty(board, r, c);
        if (r == -1 && c == -1)
            return true;

        for (char ch = '1'; ch <= '9'; ch++) {
            board[r][c] = ch;
            if (isValidSudoku(board, r, c) &&solveSudokuHelper(board)) {
                return true;
            }
        }

        board[r][c] = '.';      // change back to empty and return false
        return false;
    }

    // get next empty position from board
    void getNextEmpty(vector<vector<char> > &board, int &r, int &c)
    {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    r = i; c = j;
                    return;
                }
            }
        }
        r = -1; c = -1;
    }

    // check if board is valid according to specific row and column
    bool isValidSudoku(vector<vector<char> >& board, int r, int c)
    {
        if (!isValid(board[r]))
            return false;

        vector<char> column(9);
        for (int i = 0; i < 9; ++i)
            column[i] = board[i][c];
        if (!isValid(column))
            return false;

        int block_row = r / 3;
        int block_col = c / 3;
        vector<char> block;
        for (int i = block_row * 3; i < block_row * 3 + 3; ++i)
            for (int j = block_col * 3; j < block_col * 3 + 3; ++j)
                block.push_back(board[i][j]);
        if (!isValid(block))
            return false;

        return true;
    }

    bool isValid(const vector<char>& vec)
    {
        vector<bool> occur(9, false);

        for (int i = 0; i < 9; ++i) {
            if (isdigit(vec[i])) {
                if (occur[vec[i]-'1']) return false;
                else occur[vec[i]-'1'] = true;
            }
        }

        return true;
    }
};


int main(void) {
    return 0;
}
