
////////////////////////////////////////////////////////////////////
//              Knights shortest path                             //
////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////
void init(int b[12][12])
{
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if ((i > 1) && (j > 1) && (i < 10) && (j < 11)) {
                b[i][j] = 0;    // valid spot
            } else {
                b[i][j] = -1;   // invalid spot
            }
        }
    }
}

////////////////////////////////////////////////////////////////////
void findpath(int b[12][12], int startx, int starty,
              int endx, int endy, int &nsteps)
{
    int i;
    int j;
    int newb[12][12];

    b[startx][starty] = 1;
    // increate steps
    for (nsteps = 0; nsteps < 100; nsteps++) {
        // if we can reach end point now, return steps
        if (b[endx][endy] == 1)
            return;
        // create a temporary new board
        for (i = 2; i <= 9; i++)
            for (j = 2; j <= 9; j++)
                newb[i][j] = b[i][j];
        // for each reachable spot, we can try to jump
        for (i = 2; i <= 9; i++)
            for (j = 2; j <= 9; j++)
                if (b[i][j] == 1) {
                    newb[i + 1][j + 2] = 1;
                    newb[i + 1][j - 2] = 1;
                    newb[i - 1][j + 2] = 1;
                    newb[i - 1][j - 2] = 1;
                    newb[i + 2][j + 1] = 1;
                    newb[i + 2][j - 1] = 1;
                    newb[i - 2][j + 1] = 1;
                    newb[i - 2][j - 1] = 1;
                }
        // copy back temporary board
        for (i = 2; i <= 9; i++)
            for (j = 2; j <= 9; j++)
                b[i][j] = newb[i][j];
    }
    nsteps = 999;  // error indication
}


////////////////////////////////////////////////////////////////////
int main()
{
    int      endx;
    int      endy;
    ifstream inf;
    int      nsteps;
    ofstream outf;
    int      startx;
    int      starty;
    int      board[12][12];


    inf.open("knights.in");
    outf.open("knights.out");

    inf >> startx >> starty >> endx >> endy;

    init(board);
    findpath(board, startx+1, starty+1, endx+1, endy+1, nsteps);
    outf << "from " << startx << ", " << starty << " to ";
    outf << endx << ", " << endy << " takes ";

    if (nsteps != 1)
        outf << nsteps << " steps." << endl;
    else
        outf << nsteps << " step." << endl;

}

////////////////////////////////////////////////////////////////////
//              End Knights shortest path                         //
////////////////////////////////////////////////////////////////////
