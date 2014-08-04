#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (board.size() == 0 || board[0].size() == 0) {
            return false;
        }

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == word[0]) {
                    if (exist_helper(board, i, j, word, 0)) {
                        return true;
                    }
                }
            }
        }
    }

    bool exist_helper(vector<vector<char> > &board, int i, int j,
                      string word, int index) {

        if (index == word.length() - 1 && board[i][j] == word[index])
            return true;
        if (board[i][j] != word[index])
            return false;

        // going up
        if (i > 0 && board[i-1][j] != '#') {
            char tmp = board[i][j];
            board[i][j] = '#';
            if (exist_helper(board, i-1, j, word, index+1)) {
                return true;
            }
            board[i][j] = tmp;
        }

        // going down
        if (i < board.size()-1 && board[i+1][j] != '#') {
            char tmp = board[i][j];
            board[i][j] = '#';
            if (exist_helper(board, i+1, j, word, index+1)) {
                return true;
            }
            board[i][j] = tmp;
        }

        // going left
        if (j > 0 && board[i][j-1] != '#') {
            char tmp = board[i][j];
            board[i][j] = '#';
            if (exist_helper(board, i, j-1, word, index+1)) {
                return true;
            }
            board[i][j] = tmp;
        }

        // going right
        if (j < board[0].size()-1 && board[i][j+1] != '#') {
            char tmp = board[i][j];
            board[i][j] = '#';
            if (exist_helper(board, i, j+1, word, index+1)) {
                return true;
            }
            board[i][j] = tmp;
        }

        return false;
    }
};


int main() {

}
