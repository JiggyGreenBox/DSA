#include <bits/stdc++.h>
using namespace std;

void printBoard(const vector<vector<char> >& board){
    for(const auto& row : board){
        cout << "[ ";
        for(char c : row) cout << c << " ";
        cout << "]\n";
    }
}

void fill_used_vecs(vector<vector<char>>& board,
                    vector<vector<bool>>& used_sector,
                    vector<vector<bool>>& used_col,
                    vector<vector<bool>>& used_row )
{
    int n = board.size(), m = board[0].size();

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {

            int  used_idx = ((i/3)*3) + j/3;
            

            if(board[i][j] != '.') {                                                
                int num = board[i][j] - '0';
                // cout << num << " sector num[" << used_idx << "][" << num-1 << "];"<< endl;
                used_sector[used_idx][num-1]   = true; // 3x3 grid
                used_col[j][num-1]            = true; // used in column
                used_row[i][num-1]            = true; // used in row
            }
        }
    }
}



bool solve( vector<vector<char>>& board,
            vector<vector<bool>>& used_sector,
            vector<vector<bool>>& used_col,
            vector<vector<bool>>& used_row )
{    
    // look for a free spot
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            // cout << x << y << endl;
            
            if(board[i][j] == '.') {
                // iterate and choose a suitable option
                for(int num=0; num<9; num++){
                    // check row and col and sector
                    int sector_idx = ((i/3)*3) + j/3;                    
                    if(used_row[i][num] || used_col[j][num] || used_sector[sector_idx][num]) {
                        continue;
                    }
                    
                    // choose                     
                    board[i][j] = (num+1) + '0';
                    // cout << "num: " << char((num+1) + '0') << endl;
                    used_row[i][num] = true;
                    used_col[j][num] = true;
                    used_sector[sector_idx][num] = true;

                    if(solve(board, used_sector, used_col, used_row)){
                        return true;
                    }

                    // unchoose                    
                    board[i][j] = '.';
                    used_row[i][num] = false;
                    used_col[j][num] = false;
                    used_sector[sector_idx][num] = false;
                }
                return false; // no number fits
            }
        }
    }
    return true; // no empty cells found
}


void solveSudoku(vector<vector<char>>& board) {    
    vector<vector<bool>> used_sector = vector(9, vector<bool>(9, false));
    vector<vector<bool>> used_col = vector(9, vector<bool>(9, false));
    vector<vector<bool>> used_row = vector(9, vector<bool>(9, false));
    fill_used_vecs(board, used_sector, used_col, used_row);    

    solve(board, used_sector, used_col, used_row);
}

int main() {
    vector<vector<char>> board = { {'5', '3', '.', '.', '7', '.', '.', '.', '.'} , {'6', '.', '.', '1', '9', '5', '.', '.', '.'} , {'.', '9', '8', '.', '.', '.', '.', '6', '.'} , {'8', '.', '.', '.', '6', '.', '.', '.', '3'} , {'4', '.', '.', '8', '.', '3', '.', '.', '1'} , {'7', '.', '.', '.', '2', '.', '.', '.', '6'} , {'.', '6', '.', '.', '.', '.', '2', '8', '.'} , {'.', '.', '.', '4', '1', '9', '.', '.', '5'} , {'.', '.', '.', '.', '8', '.', '.', '7', '9'} };
    
    solveSudoku(board);
    printBoard(board);


    // cout << board[8][8] << endl;
    // [0..8] == 9
    // used[0][5] == true
    // used[9][9] vector
    // 0 1 2       3 4 5       6 7 8
    // 1
    // 2

    // i/3 == [0]  [1][1]
    // j/3 == [0]

    // [0,0][0,1][0,2]     [0,3][0,4][0,5]     [0,6][0,7][0,8]
    // [1,0][1,1][1,2]     [1,3][1,4][1,5]     [1,6][1,7][1,8]
    // [2,0][2,1][2,2]     [2,3][2,4][2,5]     [2,6][2,7][2,8]

    // i/3 = 0             i/3 = 0             i/3 = 0
    // j/3 = 0             j/3 = 1             j/3 = 2

    // [3,0][3,1][3,2]     [3,3][3,4][3,5]     [3,6][3,7][3,8]
    // [4,0][4,1][4,2]     [4,3][4,4][4,5]     [4,6][4,7][4,8]
    // [5,0][5,1][5,2]     [5,3][5,4][5,5]     [5,6][5,7][5,8]

    // i/3 = 1             i/3 = 1             i/3 = 1
    // j/3 = 0             j/3 = 1             j/3 = 2

    // [6,0][6,1][6,2]     [6,3][6,4][6,5]     [6,6][6,7][6,8]
    // [7,0][7,1][7,2]     [7,3][7,4][7,5]     [7,6][7,7][7,8]
    // [8,0][8,1][8,2]     [8,3][8,4][8,5]     [8,6][8,7][8,8]

    // i/3 = 2             i/3 = 2             i/3 = 2
    // j/3 = 0             j/3 = 1             j/3 = 2


    // vector[sector] = vector[1..9]
    // sector[i+(j/3)]


    return 0;
}