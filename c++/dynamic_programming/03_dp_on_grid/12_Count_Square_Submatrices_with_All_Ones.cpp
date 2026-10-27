/*

Count Square Submatrices with All Ones
    [https://takeuforward.org/practice/dsa/count-square-submatrices-with-all-one?category=dp-on-grids&source=strivers-a2z-dsa-sheet]

You are given a binary matrix matrix containing only 0s and 1s.

Your task is to find the total number of square submatrices that 
contain only 1s.

A square submatrix can have any valid size, such as 1 × 1, 2 × 2, 3 
× 3, and so on. Each square is counted separately based on its 
position in the matrix.

Return the total number of such square submatrices.

Example 1:
Input: matrix = [ [1, 1, 1], [1, 1, 1], [0, 1, 1] ]

Output: 11

Explanation:

There are:

8 squares of size 1 × 1
3 squares of size 2 × 2
0 squares of size 3 × 3
Therefore: 8+3 =11

Example 2:
Input: matrix = [ [1, 0, 1, 1], [1, 1, 1, 1], [1, 1, 1, 0] ]

Output: 13

Explanation:

There are 10 individual 1 × 1 squares.

There is also 3 square of size 2 × 2.

So total count is 13.

*/

/*
[1, 0, 1, 1] 
[1, 1, 1, 1] 
[1, 1, 1, 0]


[1, 0, 2, 1] 
[2, 2, 1, 1] 
[1, 1, 1, 0]

[1, 1, 1]       [2, 2, 1]
[1, 1, 1]       [1, 2, 1]
[0, 1, 1]       [0, 1, 1]


counting mechanism
    but how do we calculate
        brute:
            for any [x,y]
                bfs left,right,diagonal


rec(x,y, mat)
    if(x != 1 && y != 1)
        return

    int right = 
    int left = 
    int diag = 

    return mat[x][y] +  min(right,left,diag)


each [r][c] is checked
    3 choices at each rc
    3^rc
    rc stack space


*/

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int rec(int x, int y, vector<vector<int>>& matrix) {
    int r = matrix.size();
    int c = matrix[0].size();

    if(x < 0 || x >= r || y < 0 || y >= c)
        return 0;
        
    if(matrix[x][y] == 0)
        return 0;

    int right = rec(x, y+1, matrix);
    int bot = rec(x+1, y, matrix);
    int diag = rec(x+1, y+1, matrix);

    return matrix[x][y] + min({right, bot, diag});
}

// 
// r*c* 3^rc upper bound time
// rc stack space
int countSquares(vector<vector<int>>& matrix) {
    int total = 0;
    int r = matrix.size();
    int c = matrix[0].size();

    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            total += rec(i,j, matrix);
        }
    }
    return total;
}

int memo(int x, int y, vector<vector<int>> &matrix, vector<vector<int>> &dp) {

    int r = matrix.size();
    int c = matrix[0].size();

    if(x < 0 || x >= r || y < 0 || y >= c)
        return 0;

    if(dp[x][y] != -1)
        return dp[x][y];
        
    if(matrix[x][y] == 0)
        return dp[x][y] = 0;

    int right = memo(x, y+1, matrix, dp);
    int bot = memo(x+1, y, matrix, dp);
    int diag = memo(x+1, y+1, matrix, dp);

    return dp[x][y] = matrix[x][y] + min({right, bot, diag});
}

// r*c states
// 3rc time
// rc stack space
int countSquares2(vector<vector<int>>& matrix) {
    int total = 0;
    int r = matrix.size();
    int c = matrix[0].size();

    vector<vector<int>> dp(r, vector<int>(c, -1));

    
    for(int i=0;i<r; i++) {
        for(int j=0;j<c; j++) {            
            total += memo(i, j, matrix, dp);
        }
    }
    return total;
}



// tabulation
// start from bottom right
// we dont need a queue
// rc states
// rc time
// rc space
// 1 stack space
int countSquares3(vector<vector<int>>& matrix) {
    
    int r = matrix.size();
    int c = matrix[0].size();

    vector<vector<int>> dp(r, vector<int>(c, 0));    

    int total = 0;

    for(int i = r - 1; i >= 0; i--) {

        for(int j = c - 1; j >= 0; j--) {

            if(matrix[i][j] == 0) {
                dp[i][j] = 0;
                continue;    
            }
            
            int bot = (i < r-1) ? dp[i+1][j] : 0;
            int right = (j < c-1) ? dp[i][j+1] : 0;
            int diag = (i < r-1 && j < c-1) ? dp[i+1][j+1] : 0;

            int score = min({bot, right, diag});

            dp[i][j] = matrix[i][j] + score;
            total +=  dp[i][j];
        }
    }

    return total;
}

int countSquares4(vector<vector<int>>& matrix) {

    if (matrix.empty() || matrix[0].empty())
        return 0;
    
    int r = matrix.size();
    int c = matrix[0].size();

    vector<int> prev(c, 0);

    int total = 0;

    for(int i = r - 1; i >= 0; i--) {

        vector<int> curr(c, 0);

        for(int j = c - 1; j >= 0; j--) {

            if(matrix[i][j] == 1) {

                int bot     = (i < r-1) ? prev[j] : 0;
                int right   = (j < c-1) ? curr[j+1] : 0;
                int diag    = (i < r-1 && j < c-1) ? prev[j+1] : 0;
                
                curr[j] = 1 + min({bot, right, diag});
                total +=  curr[j];    
            }                        
        }

        prev = curr;
    }
    
    return total;
}

int main() {

    vector<vector<int>> matrix = { {1, 1, 1}, {1, 1, 1}, {0, 1, 1} };
    // vector<vector<int>> matrix = { 
    //     {0, 0, 0}, 
    //     {0, 1, 1}, 
    //     {0, 1, 1}
    // };
    auto x = countSquares(matrix);
    x = countSquares2(matrix);
    x = countSquares4(matrix);
    return 0;
}