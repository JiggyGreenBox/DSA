/*
Set Matrix Zeroes
    [https://leetcode.com/problems/set-matrix-zeroes/description/]

Given an m x n integer matrix matrix, if an element is 0, set its 
entire row and column to 0's.

You must do it in place


Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]


matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]

*/

#include <iostream>
#include <vector>
using namespace std;

void setZeroes(vector<vector<int>>& matrix) {
    int r = matrix.size();
    int c = matrix[0].size();

    vector<bool> rowseen(r, false);
    vector<bool> colseen(c, false);

    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(matrix[i][j] == 0) {
                rowseen[i] = true;
                colseen[j] = true;
            }
        }
    }

    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(rowseen[i] || colseen[j])
                matrix[i][j] = 0;
        }
    }
}


/*
use the first row and first col as rowseen and colseen

0,0 is common
    so it may be set 

    [i][j]
        [i][0] = 0 anyzero in first row may set 0,0
        [0][j] = 0 anyzero in first col may set 0,0

    so we check before hand if it is zero   
        actually we just want to know if a zero is in first col
        or from first row
            first row if dont do anything
            first col , we need to mark the zeros
                with bool

    this is marking

    when writing

    if 0,0 is zero then make row 0

    if bool
        make first col zero
*/

void setZeroes2(vector<vector<int>>& matrix) {
    int r = matrix.size();
    int c = matrix[0].size();
    bool colZero = false;

    // marking
    for(int i=0; i<r; i++) {

        if(matrix[i][0] == 0)
            colZero = true;

        for(int j=1; j<c; j++) {
            if(matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    // writing
    for(int i=1; i<r; i++) {
        for(int j=1; j<c; j++) {
            if(matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;                
            }
        }
    }

    // first row
    if(matrix[0][0] == 0) {
        for(int j=1; j<c; j++) {
            matrix[0][j] = 0;
        }
    }

    // first row
    if(colZero) {
        for(int i=0; i<r; i++) {
            matrix[i][0] = 0;
        }
    }
}

    


int main() {
    vector<vector<int>> matrix = {{1,1,1},{1,0,1},{1,1,1}};
    setZeroes2(matrix);

    matrix = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    setZeroes2(matrix);
    return 0;
}

