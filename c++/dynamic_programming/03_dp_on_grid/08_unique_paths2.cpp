#include <iostream>
#include <vector>
using namespace std;

/*
[0 0 0]
[0 1 0]
[0 0 0]

[1 1 1]
[1 2 0]
[0 0 0]


[0, 0, 0]
[0, 0, 1]
[0, 1, 0]
*/
// ==============================================================
// rec
int helper_rec(int x, int y, vector<vector<int>>& matrix) {
    if(x < 0 || y < 0) return 0; // guard
    if(matrix[x][y] == 1) return 0; // obstacle
    if(x == 0 && y == 0) return 1; // reached destination

    int up   = helper_rec(x-1, y, matrix);
    int left = helper_rec(x, y-1, matrix);
    return up + left;
}
int uniquePathsWithObstacles1(vector<vector<int>>& matrix) {    
    int m = matrix.size();
    int n = matrix[0].size();
    return helper_rec(m-1, n-1, matrix);
}
// ==============================================================
// dp
int helper_dp(int x, int y, vector<vector<int>> &matrix, vector<vector<int>> &dp) {
    if(x < 0 || y < 0)    return 0; // guard
    if(matrix[x][y] == 1) return 0; // obstacle
    if(x == 0 && y == 0)  return 1; // reached!

    if(dp[x][y] != -1) return dp[x][y];

    int up   = helper_dp(x-1, y, matrix, dp);
    int left = helper_dp(x, y-1, matrix, dp);
    return dp[x][y] = up + left;
}
int uniquePathsWithObstacles2(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return helper_dp(m-1, n-1, matrix, dp);
}
// ==============================================================
// tabulation
int uniquePathsWithObstacles3(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int> (n, 0));

    if(matrix[0][0] == 1 || matrix[m-1][n-1] == 1) return 0;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(i==0 && j == 0) {
                dp[i][j] = 1;
                continue;
            }

            if(matrix[i][j] == 1) {
                dp[i][j] = 0;
                continue;   
            }

            int up = 0, left = 0;
            if(i>0) up = dp[i-1][j];
            if(j>0) left = dp[i][j-1];
            dp[i][j] = up + left;
        }
    }
    return dp[m-1][n-1];
}
int uniquePathsWithObstacles4(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    if(matrix[0][0] == 1 || matrix[m-1][n-1] == 1) return 0;

    // i dont think we can do i=1, j=1 optimization for this problem
    // we dont know if there are any matrix 1's in the first row and col

    vector<int> prev(n, 0);
    // prev[0] = 1;
    for(int i=0; i<m; i++) {
        vector<int> curr(n, 0);
        for(int j=0; j<n; j++) {

            if(i==0 && j==0){
                curr[j] = 1;
                continue;
            } 
            
            if(matrix[i][j] == 1) {
                curr[j] = 0;
                continue;
            }

            int up = 0, left = 0;
            if(i>0) up = prev[j];
            if(j>0) left = curr[j-1];
            curr[j] = up + left;
        }
        prev = curr;
    }

    return prev[n-1];
}

int main() {
    vector<vector<int>> matrix = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};

    cout << uniquePathsWithObstacles1(matrix) << endl;
    cout << uniquePathsWithObstacles2(matrix) << endl;
    cout << uniquePathsWithObstacles3(matrix) << endl;
    cout << uniquePathsWithObstacles4(matrix) << endl;

    matrix = {{0, 0, 0},
              {0, 0, 1},
              {0, 1, 0}};

    cout << uniquePathsWithObstacles1(matrix) << endl;
    cout << uniquePathsWithObstacles2(matrix) << endl;
    cout << uniquePathsWithObstacles3(matrix) << endl;
    cout << uniquePathsWithObstacles4(matrix) << endl;
    // cout << "working" << endl;
    return 0;
}
