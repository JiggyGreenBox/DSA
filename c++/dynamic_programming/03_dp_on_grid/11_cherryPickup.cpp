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




#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <algorithm>
using namespace std;


/*
Cherry pickup II

matrix

 [2, 1, 3]
 [4, 2, 5]
 [1, 6, 2]
 [7, 2, 8]

 2+4+6+7+3+5+2+8


 approach 1
    max_sum approach
    can we do 2 max sum runs
    where after we finish the run we mark visited cells as zero

    then the second robot
    will not pick up and may skip these cells?

approach 2
    process row by row
    since we have fixed starting points we start at thos spots

    take a max for both,
        how?
            bot, bot-l, bot-r


        1 0 1
        1 5 2

            we could choose 1+5+1+1 or 1+5+1+2

    rec(r, c1, c2)

        if(r == n)
            return 0
        
        int gain = mat[r][c1];
        if(c1 != c2)
            gain += mat[r][c2];


        int max_gain = 0;
        for each next col in c1
            for each next col in c2
                max_gain = ...

        return gain + max_gain;
*/


// r recursion stack space
// 3 choices for each robot
// 3^2 total 3 branches for 2 robots
// and r rows
// time r*3^2
// space r


// loop is checking 3x3 combinations at each step
// bracnhing factor is 9
// 9^r time
// r space stack
int rec(int r, int c1, int c2, vector<vector<int>> &matrix) {

    int n = matrix.size();
    int m = matrix[0].size();

    if(c1 < 0 || c2 < 0 || c1 >= m || c2 >= m)
        return 0;

    if(r == n)
        return 0;
    
    int gain = matrix[r][c1];
    if(c1 != c2)
        gain += matrix[r][c2];


    int max_gain = 0;
    for(int i=-1; i<2; i++) {        
        for(int j=-1; j<2; j++) {
            max_gain = max(max_gain, rec(r+1, c1 + i, c2 + j, matrix));
        }
    }                    

    return gain + max_gain;
}

int cherryPickup1(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    return rec(0, 0, m-1, matrix);
}


// [r][c1][c2]
// [0][0][0]
// [0][0][1]
// [0][]


// states are r*c*c
// time is r*c^2
// space is r*c^2
int memo(int r, int c1, int c2, 
    vector<vector<int>> &matrix,
    vector<vector<vector<int>>> &dp) {

    int n = matrix.size();
    int m = matrix[0].size();        

    if(dp[r][c1][c2] != -1)
        return dp[r][c1][c2];
    
    int gain = matrix[r][c1];
    if(c1 != c2)
        gain += matrix[r][c2];

    if(r == n-1)
        return gain;


    int max_gain = 0;
    for(int i=-1; i<2; i++) {        
        for(int j=-1; j<2; j++) {

            int nc1 = c1 + i;
            int nc2 = c2 + j;

            if(nc1 < 0 || nc2 < 0 || nc1 >= m || nc2 >= m)
                continue;

            max_gain = max(max_gain, memo(r+1, c1 + i, c2 + j, matrix, dp));
        }
    }                    

    return dp[r][c1][c2] = gain + max_gain;
}

int cherryPickup2(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m,-1)));
    return memo(0, 0, m-1, matrix, dp);
}

// total states r*c^2
// time r*c*c*3*3
// space r*c^2
// stack space 1
int cherryPickup3(vector<vector<int>>& matrix) {

    /*
    for tabulation we need the row above
    [5,4,3]
    [,+5,]    

    this explores all pairs
    we need the neg_inf to discard states we dont want
    */
    const int NEG_INF = -1e9;
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, NEG_INF)));
    
    // for row 0 only the first and last condition are allowed
    dp[0][0][m-1] = matrix[0][0] + matrix[0][m-1];    

    // choose from the best above options
    for(int r=1; r<n; r++) {
        
        for(int c1 = 0; c1 < m; c1++) {
            for(int c2 = 0; c2 < m; c2++) {

                int gain = matrix[r][c1];
                if(c1 != c2)
                    gain += matrix[r][c2];

                int max_gain = NEG_INF;

                // 9 choices for c1/c2
                for(int d1=-1; d1<2; d1++) {        
                    for(int d2=-1; d2<2; d2++) {

                        int nc1 = c1 + d1;
                        int nc2 = c2 + d2;

                        if(nc1 < 0 || nc2 < 0 || nc1 >= m || nc2 >= m)
                            continue;

                        max_gain = max(max_gain, dp[r-1][nc1][nc2]);
                    }
                }

                if(max_gain != NEG_INF) 
                    dp[r][c1][c2] = gain + max_gain;                
            }
        }
    }
    

    // get max
    int max_sum = NEG_INF;
    for(int c1 = 0; c1 < m; c1++) {
        for(int c2 = 0; c2 < m; c2++) {
            max_sum = max(max_sum, dp[n-1][c1][c2]);
        }
    }    
    return max_sum;
}

int main() {

    vector<vector<int>> matrix = {{2, 1, 3}, {4, 2, 5}, {1, 6, 2}, {7, 2, 8}};
    auto x = cherryPickup1(matrix);
    x = cherryPickup2(matrix);
    x = cherryPickup3(matrix);
    return 0;
}