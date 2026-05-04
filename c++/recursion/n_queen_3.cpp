#include <bits/stdc++.h>
using namespace std;


void printResults(const vector<vector<string>>& results) {
    for(auto row : results) {
        cout << "[ ";
        for(auto x : row) cout << x << " ";
        cout << "]\n";
    }
}



void dfs(int row,
         int n,
         vector<bool>& col_m,
         vector<bool>&  diag1,
         vector<bool>&  diag2,
         vector<string>& board,
         vector<vector<string>>& results) 
{
    // 1. base case, add to results
    if(row == n) {
        results.push_back(board);
        return;
    }


    // 2. check each col in given row    
    for(int col=0; col<n; col++){
                
        int d1 = row + col;         // '/d' 
        int d2 = row - col + n - 1; // '\d'

        // try to place a queen
        // if any of the dict lookups are true
        // queen cant be placed
        if(col_m[col] || diag1[d1] || diag2[d2]) {
            continue; // skip this col
        }

        // queen can be placed
        // pick
        col_m[col] = diag1[d1] = diag2[d2] = true;             
        board[row][col] = 'Q';            

        dfs(row+1, n, col_m, diag1, diag2, board, results);

        // unpick
        board[row][col] = '.';
        col_m[col] = diag1[d1] = diag2[d2] = false;
        
    }

    
}

void printBoard(const vector<string>& board){
    for(auto s : board) {
        cout << s << endl;
    }
}


vector<vector<string>> solveNQueens(int n) {
        
    
    vector<vector<string>> results;
    vector<string> board(n,string(n,'.'));
    printBoard(board);

    vector<bool> col(n, false);
    vector<bool> diag1(2*n-1, false);
    vector<bool> diag2(2*n-1, false);

    dfs(0, n, col, diag1, diag2, board, results);
    return results;
}

int main() {
    printResults(solveNQueens(6));
    return 0;
}


// LOGIC FOR QUICK WHETHER A QUEEN WOULD KILL ANOTHER QUEEN
// 1. by being in the same row or col
// 2. by being on the \ digonal or / diagonal
    // a. col
    // b. / diagonal
    // c. \ diagonal

/*
------------------------------------

For n==4 chessboard:

coords:
    (0,0) (0,1) (0,2) (0,3)
    (1,0) (1,1) (1,2) (1,3)
    (2,0) (2,1) (2,2) (2,3)
    (3,0) (3,1) (3,2) (3,3)
------------------------------------
a. col
------------------------------------
    for column lookup, we just store the column, index when places
    vector<bool> col(n);
        if (col[idx] == true) {} // col already in use

------------------------------------
b. / diagonal
------------------------------------
row + col:
    0 1 2 3
    1 2 3 4
    2 3 4 5
    3 4 5 6

    Every / diagonal has the same (row + col)

        This is always non-negative.
            (row + col) == (n-1 + n-1) == 2n-2
            zero was an answer so the range is [0..2n-1]
                vector<bool>diag2 = (2n-1, false);

                index = diag2[row + col]

------------------------------------
c. \ diagonal
------------------------------------
row - col:
    0 -1 -2 -3
    1  0 -1 -2
    2  1  0 -1
    3  2  1  0
    
    Every \ diagonal has the same (row - col)

        This is can be negative. cant store negative indices in an array in c++
        lets list the \ diagonals:

            (0,0)
            (0,1)(1,0)
            (0,2)(1,1)(2,0)
            (0,3)(1,2)(2,1)(3,0)
            (1,3)(2,2)(3,1)
            (2,3)(3,2)
            (3,3)
        
            7 diagonals, for n==4 thats 2n-1 == 7, so we can store 
            index[0..2n] in vec of size 2n-1
                
                0 -1 -2 -3      add n-1 (3) =  3  2  1  0
                1  0 -1 -2      add n-1 (3) =  4  3  2  1
                2  1  0 -1      add n-1 (3) =  5  4  3  2
                3  2  1  0      add n-1 (3) =  6  5  4  3

                now this allows us to be similar to the positive numbers 
                [min..max] -> [0..6] -> [0..2n-2] 
                2n-1 possible answers
                vector<bool> diag2 = (2n-1, false);
*/





