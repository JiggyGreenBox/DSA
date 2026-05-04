#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Given a n x m 2d integer array called matrix where matrix[i][j] represents the
number of cherries you can pick up from the (i, j) cell. Given two robots that
can collect cherries, one is located at the top-leftmost (0, 0) cell and the
other at the top-rightmost (0, m-1) cell.


Return the maximum number of cherries that can be picked by the two robots in
total, following these rules:   

    Robots that are standing on (i, j) cell can
    only move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1), 
    if it exists in the matrix. 

    A robot will pick up all the cherries in a given cell when it
    passes through that cell.

    If both robots come to the same cell at the same
    time, only one robot takes the cherries.

    Both robots must reach the bottom row in matrix.
*/

// since we have starting points as [0,0] and [0, n-1]
// we start from there till the last row
// we need a method to prevent them from visiting the same 
// [r][c]
//      i propose a vec[] of size total-rows
//      each idx if the col-picked

// int helper_rec(int i, int j, vector<vector<int>> &matrix, vector<int> &picked) {
int helper_rec(int r, int c1, int c2, vector<vector<int>> &matrix) {
    int row_lim = matrix.size();
    int col_lim = matrix[0].size();

    if(c1 < 0 || c2 < 0 || c1 == col_lim || c2 == col_lim) return -1e9;

    if(c1 == c2) return -1e9;

    if(r == row_lim - 1) {
        return matrix[r][c1] + matrix[r][c2];
    }

    int max_sum = -1e9;
    for(int i=-1; i<2; i++) {
        for(int j=-1; j<2; j++) {
                               
            int sum = matrix[r][c1] + matrix[r][c2] + helper_rec(r+1, c1+i, c2+j, matrix);
            max_sum = max(max_sum, sum);
        }
    }
    return max_sum;    
}

/*
if we carry both robots in the same call i think it will be easier
1 1 1
2 2 2
3 3 3

return max_sum for row i, choosing c1 and c2
    such that c1 != c2


if i==last and c1 == c2
    return -1e9
if i==last
    return m[c1] + m[c2]

max_sum = -1e9
for x = -1,0,1
    for y = -1,0,1

    max_sum =  max(max_sum, helper(i+1, c1+x, c2+y))

return max_sum
*/

int cherryPickup(vector<vector<int>>& matrix) {
    int r = matrix.size();
    int c = matrix[0].size();
    return helper_rec(0, 0, c-1, matrix);    
}

int main() {
    vector<vector<int>> matrix = {{2, 1, 3}, {4, 2, 5}, {1, 6, 2}, {7, 2, 8}}; // 37 (19+18)
    cout << cherryPickup(matrix) << endl;

    matrix = {{1, 4, 4, 1}, {1, 2, 2, 1}, {5, 6, 10, 11}, {8, 1, 1, 1}}; // 32 (17+15)
    cout << cherryPickup(matrix) << endl;
    return 0;
}
