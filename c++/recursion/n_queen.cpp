#include <bits/stdc++.h>
using namespace std;

void printBoard(const vector<vector<int>>& results) {
    for(auto row : results) {
        cout << "[ ";
        for(auto x : row) cout << x << " ";
        cout << "]\n";
    }
    cout << "\n";
}

void printResults(const vector<vector<string>>& results) {
    for(auto row : results) {
        cout << "[ ";
        for(auto x : row) cout << x << " ";
        cout << "]\n";
    }
}

void markQueen(int i, int j, vector<vector<int>>& board, int val){
    int m = board.size(), n = board[0].size();
    // up
    for(int x=i; x>=0; x--){
        board[x][j] = val;
    }

    // down
    for(int x=i; x<m; x++){
        board[x][j] = val;
    }

    // right 
    for(int x=i; x<m; x++){
        board[i][x] = val;
    }

    // left
    for(int x=i; x>=0; x--){
        board[i][x] = val;
    }

    // diagonals
    // diagonal 1
    int x=i;
    int y=j;
    while(x<m && y<n){
        board[x++][y++] = val;
    }

    // diagonal 2
    x=i;
    y=j;
    while(x>=0 && y>=0){
        board[x--][y--] = val;       
    }

    // diagonal 3
    x=i;
    y=j;
    while(x>=0 && y<n){
        board[x--][y++] = val;       
    }

    // diagonal 4
    x=i;
    y=j;
    while(x<m && y>=0){
        board[x++][y--] = val;
    }

    board[i][j] = 2;
}

void dfs(   int i, 
            int j, 
            int queens,
            vector<vector<int>>& board)
{
    
    int n = board.size();
    queens++;
    cout << "placed queen at " << i <<"," <<j << " c:"<<  queens << endl;
    markQueen(i, j, board, 1);    
    printBoard(board);


    // n queens were placed
    if(queens == n) {
        cout << "n queens done: " << queens << endl;
        return;
    }

    cout << "find next 0 slot " << endl;
    for(int x=0; x<n; x++){
        for(int y=0; y<n; y++){
            if(board[x][y] == 0){
                dfs(x, y, queens, board);
            }
        }
    }
    cout << " no slots found" << endl;
    cout << "total queens" << queens << endl;
}

vector<vector<string>> solveNQueens(int n) {
    // construct a n-board?
    // mark the board when a piece is placed
    // dfs again
    // unmark the board
    // add to results if pieces_placed==n
    
    vector<vector<int>> board(n, vector<int>(n,0));
    vector<vector<string>> results;
    // markQueen(2,3,board, 1);
    // markQueen(0,3,board, 0);
    // printBoard(board);


    dfs(0, 2, 0, board);    

    return results;
}



void clearQueen(int i, int j, vector<vector<int>>& board){

}


int main() {
    

    printResults(solveNQueens(4));
    return 0;
}