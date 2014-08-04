// Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

// A region is captured by flipping all 'O's into 'X's in that surrounded region .

// For example,
//    X X X X
//    X O O X
//    X X O X
//    X O X X
// After running your function, the board should be:
//    X X X X
//    X X X X
//    X X X X
//    X O X X

import java.util.Queue;
import java.util.LinkedList;


public class SurroundedRegions {

    public void solve(char[][] board) {

        if (board == null || board.length == 0) {
            return;
        }

        int m = board.length;
        int n = board[0].length;

        // First scan four edges of the board, replace 'O' and its neighbors
        // to a temporary value 'T'. Observation is that the only case when a
        // 'O' can not be able to change to 'X' is due to its connection to
        // a 'O' at any one of the four edges.
        for (int i = 0; i < n; i++) { // top edge
            if (board[0][i] == 'O') {
                markBFS(board, 0, i);
            }
        }
        for (int i = 0; i < n; i++) { // bottom edge
            if (board[m-1][i] == 'O') {
                markBFS(board, m-1, i);
            }
        }
        for (int i = 0; i < m; i++) { // left edge
            if (board[i][0] == 'O') {
                markBFS(board, i, 0);
            }
        }
        for (int i = 0; i < m; i++) { // right edge
            if (board[i][n-1] == 'O') {
                markBFS(board, i, n-1);
            }
        }

        // Second scan change all 'O' to 'X', and 'T' to 'O'
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == 'T') {
                    board[i][j] = 'O';
                }
            }
        }
    }

    // maybe stackoverflow if board is too large
    private void markDFS(char[][] board, int i, int j) {

        board[i][j] = 'T';

        // check top neighbor
        if (i - 1 >= 0 && board[i-1][j] == 'O') {
            markDFS(board, i-1, j);
        }
        // check bottom neighbor
        if (i + 1 < board.length && board[i+1][j] == 'O') {
            markDFS(board, i+1, j);
        }
        // check left neighbor
        if (j - 1 >= 0 && board[i][j-1] == 'O') {
            markDFS(board, i, j-1);
        }
        // check right neighbor
        if (j + 1 < board[0].length && board[i][j+1] == 'O') {
            markDFS(board, i, j+1);
        }
    }

    private void markBFS(char[][] board, int t, int s) {

        Queue<Integer> q = new LinkedList<Integer>();
        int m = board.length;
        int n = board[0].length;

        board[t][s] = 'T';
        q.offer(t * m + s);

        while (!q.isEmpty()){
            int cur = q.poll();
            int i = cur / board[0].length;
            int j = cur % board[0].length;
            // check top neighbor
            if (i - 1 >= 0 && board[i-1][j] == 'O') {
                board[i-1][j] = 'T';
                q.offer((i-1) * m + j);
            }
            // check bottom neighbor
            if (i + 1 < board.length && board[i+1][j] == 'O') {
                board[i+1][j] = 'T';
                q.offer((i+1) * m + j);
            }
            // check left neighbor
            if (j - 1 >= 0 && board[i][j-1] == 'O') {
                board[i][j-1] = 'T';
                q.offer(i * m + j - 1);
            }
            // check right neighbor
            if (j + 1 < board[0].length && board[i][j+1] == 'O') {
                board[i][j+1] = 'T';
                q.offer(i * m + j + 1);
            }
        }
    }

    public static void main(String[] args) {
        SurroundedRegions surroundedRegions = new SurroundedRegions();
        // char[][] board = {{'X', 'O', 'X'},
        //                   {'O', 'X', 'O'},
        //                   {'X', 'O', 'X'}};
        char[][] board = {{'O', 'O'},
                          {'O', 'O'}};
        surroundedRegions.solve(board);
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                System.out.print(board[i][j] + " ");
            }
            System.out.println();
        }
    }
}
