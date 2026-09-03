/*
Game of Life
[https://leetcode.com/problems/game-of-life/description/]

According to Wikipedia's article: "The Game of Life, also known 
simply as Life, is a cellular automaton devised by the British 
mathematician John Horton Conway in 1970."

The board is made up of an m x n grid of cells, where each cell has 
an initial state: live (represented by a 1) or dead (represented by a 
0). Each cell interacts with its eight neighbors (horizontal, 
vertical, diagonal) using the following four rules (taken from the 
above Wikipedia article):

Any live cell with fewer than two live neighbors dies as if caused by 
under-population.
Any live cell with two or three live neighbors lives on to the next 
generation.
Any live cell with more than three live neighbors dies, as if by 
over-population.
Any dead cell with exactly three live neighbors becomes a live cell, 
as if by reproduction.
The next state of the board is determined by applying the above rules 
simultaneously to every cell in the current state of the m x n grid 
board. In this process, births and deaths occur simultaneously.

Given the current state of the board, update the board to reflect its 
next state.

Note that you do not need to return anything.

*/

/*
for each cell we can use:
    dx[] = 
    dy[] = 

    to find all eight dirs
    if if curr == 1 and count < 2
        die, make 0
    if curr == 1 and count == 2 or 3, no change

    if curr == 1 and count >3, die, make 0

    if curr == 0 and count == 3 make live, 1

    changes are not chained
        original condition is the deciding condition
        that means that we need a transition state 
            from 0 to 1
            and 1 to 0

        make 1 alive
        0 1 0 0
        1 1 0 0
        0 0 0 0

        1 1 0 0
        1 1 0 0
        0 0 0 0
            if we process cell by cell
                then we would kill all of these

       -1 1 0 0
        1 1 0 0
        0 0 0 0
            now we later update -1 to 1
            0 to 1 make -1
            1 to 0 make 2
            then check if count of >= 1
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int getCount(vector<vector<int>>& board, int x, int y) {

    int m = board.size();
    int n = board[0].size();

    int dx[] = {1,-1, 0, 0, 1, 1,-1,-1};
    int dy[] = {0, 0,-1, 1, 1,-1, 1,-1};

    int count = 0;

    for(int k=0; k<8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if(nx>=0 && nx<m && ny>=0 && ny<n) {
            if(board[nx][ny] >= 1)
                count++;
        }
    }
    return count;
}

void gameOfLife(vector<vector<int>>& board) {
    

    int m = board.size();
    int n = board[0].size();

    // marking
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            int count = getCount(board, i, j);

            if(board[i][j] == 1 && count < 2)
                board[i][j] = 2;

            if(board[i][j] == 1 && count > 3)
                board[i][j] = 2;

            if(board[i][j] == 0 && count == 3)
                board[i][j] = -1;
        }
    }

    // writing
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(board[i][j] == 2)
                board[i][j] = 0;

            if(board[i][j] == -1)
                board[i][j] = 1;
        }
    }
}

void printMat(const vector<vector<int>>& v) {    
    for(auto &r :v){
        cout << "[ ";
        for(auto x : r) cout << x << " ";        
        cout << "]" << endl;
    }   
    cout << endl; 
}

int main() {
    vector<vector<int>> board = {{0,1,0},{0,0,1},{1,1,1},{0,0,0}};

    printMat(board);
    gameOfLife(board);
    printMat(board);
    
    return 0;
}
