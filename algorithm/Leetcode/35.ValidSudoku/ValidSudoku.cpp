// Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

// The Sudoku board could be partially filled, where empty cells are filled
// with the character '.'.

#include <vector>
using namespace std;


class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {

        vector<vector<bool> > rows(9, vector<bool>(9, false));
        vector<vector<bool> > cols(9, vector<bool>(9, false));
        vector<vector<bool> > blocks(9, vector<bool>(9, false));

        // i - i%3 + j/3 will convert to block number
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char ch = board[i][j] - '1';
                if (board[i][j] == '.') continue;
                if (rows[i][ch] || cols[j][ch] || blocks[i - i%3 + j/3][ch]) {
                    return false;
                } else {
                    rows[i][ch] = true;
                    cols[j][ch] = true;
                    blocks[i - i%3 + j/3][ch] = true;
                }
            }
        }

        return true;
    }
};


int main(void) {
    return 0;
}
