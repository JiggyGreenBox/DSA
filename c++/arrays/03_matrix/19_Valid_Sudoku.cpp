/*
Valid Sudoku
    [https://leetcode.com/problems/valid-sudoku/description/]

Determine if a 9 x 9 Sudoku board is valid. Only the filled cells 
need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 
1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not 
necessarily solvable.
Only the filled cells need to be validated according to the mentioned 
rules.
*/

/*

need a row lookup
need a col lookup
need a grid lookup

    how many rows, cols and grids = 9
    we can either use a 9x10 mat or a 9x9 and -1 for lookup
        if [0][0] == 5
            then row[0][5] = 1
                 col[0][5] = 1

    for each blank spot
        for 1..9
            if not grid and not row and not col
                place


    place
        return true if could place
        else return false


    use recursive solution
        to simplify state tracking
            for a blank spot, if 1 didnt work
                try with 2

    tc 9^blank spots

*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;



bool isValidSudoku(vector<vector<char>>& board) {
    int n = board.size();

    vector<vector<int>> rowseen(9, vector<int>(10, 0));
    vector<vector<int>> colseen(9, vector<int>(10, 0));
    vector<vector<int>> gridseen(9, vector<int>(10, 0));

    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {

            if(board[i][j] == '.') 
                continue;

            int num = board[i][j] - '0';
            int grid_idx = (i/3) * 3 + (j/3); 

            if (rowseen[i][num] ||
                colseen[j][num] ||
                gridseen[grid_idx][num])
                return false;

            
            
            rowseen[i][num] = 1;
            colseen[j][num] = 1;
            gridseen[grid_idx][num] = 1;
        }
    }

    return true;
}

void print(bool b) {
    if(b) cout << "true" << endl;
    else cout << "false" << endl;
}

int main() {


    vector<vector<char>> board = {{'5','3','.','.','7','.','.','.','.'}
                            ,{'6','.','.','1','9','5','.','.','.'}
                            ,{'.','9','8','.','.','.','.','6','.'}
                            ,{'8','.','.','.','6','.','.','.','3'}
                            ,{'4','.','.','8','.','3','.','.','1'}
                            ,{'7','.','.','.','2','.','.','.','6'}
                            ,{'.','6','.','.','.','.','2','8','.'}
                            ,{'.','.','.','4','1','9','.','.','5'}
                            ,{'.','.','.','.','8','.','.','7','9'}};

    print(isValidSudoku(board)); // true;

    board = {{'8','3','.','.','7','.','.','.','.'}
            ,{'6','.','.','1','9','5','.','.','.'}
            ,{'.','9','8','.','.','.','.','6','.'}
            ,{'8','.','.','.','6','.','.','.','3'}
            ,{'4','.','.','8','.','3','.','.','1'}
            ,{'7','.','.','.','2','.','.','.','6'}
            ,{'.','6','.','.','.','.','2','8','.'}
            ,{'.','.','.','4','1','9','.','.','5'}
            ,{'.','.','.','.','8','.','.','7','9'}};

    print(isValidSudoku(board)); // false;
            

    return 0;
}




