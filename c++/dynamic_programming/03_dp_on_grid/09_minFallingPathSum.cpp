#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
[1,   2,  10,  4]
[100, 3,  2,   1]
[1,   1,  20,  2]
[1,   2,  2,   1]


[1, 4,  3,  1]
[2, 3, -1, -1]
[1, 1, -1,  8]

backtracking with global state
    try all possibilities
    carry min_sum
    return min_sum


dp [r][c] solution

    // out of rows
    if(i<0) return 0;

    [r][c] should be ignored in min call
    if(j<0 || j>m) return INT_MAX

    dp[i][j] = a[i][j] + min(dp[i-1][j-1], dp[i-1][j], dp[i-1][j+1])
*/
// ===================================================================================
void backtrack(int &min_sum, int cur_sum, int r, int c, vector<vector<int>> &matrix) {

    int rows = matrix.size();
    int cols = matrix[0].size();

    if(r == rows) {
        min_sum = min(min_sum, cur_sum);
        return;
    }

    if(c < 0 || c == cols) return;
    
    // check 3 possible spots
    backtrack(min_sum, cur_sum + matrix[r][c], r+1, c-1, matrix);
    backtrack(min_sum, cur_sum + matrix[r][c], r+1, c, matrix);
    backtrack(min_sum, cur_sum + matrix[r][c], r+1, c+1, matrix);
}

int minFallingPathSum1(vector<vector<int>>& matrix) {
    int min_sum = INT_MAX;
    int cols = matrix[0].size();
    for(int c=0; c<cols; c++) {
        backtrack(min_sum, 0, 0, c, matrix);
    }
    return min_sum;
}

// ===================================================================================
// dp style with no memoization
int helper_no_memo(int i, int j, vector<vector<int>>& matrix) {

    if(i>=matrix.size()) return 0;
    if(j<0 || j >= matrix[0].size()) return INT_MAX;

    int bot       = helper_no_memo(i+1, j, matrix);
    int bot_left  = helper_no_memo(i+1, j-1, matrix);
    int bot_right = helper_no_memo(i+1, j+1, matrix);

    return matrix[i][j] + min({bot, bot_left, bot_right});
}
int minFallingPathSum2(vector<vector<int>>& matrix) {
    int min_sum = INT_MAX;

    int r = matrix.size();
    int c = matrix[0].size();
    for(int j=0; j<c; j++) {
        int sum = helper_no_memo(0, j, matrix);
        min_sum = min(min_sum, sum);
    }
    return min_sum;
}
// ===================================================================================
int helper(int i, int j, vector<vector<int>> &matrix, vector<vector<int>> &dp) {
    int r = matrix.size();
    int c = matrix[0].size();

    if(i>=r) return 0;

    if(j<0 || j>=c) return INT_MAX;

    if(dp[i][j] != 1e9) return dp[i][j];

    int bot       = helper(i+1, j,   matrix, dp);
    int bot_left  = helper(i+1, j-1, matrix, dp);
    int bot_right = helper(i+1, j+1, matrix, dp);

    return dp[i][j] = matrix[i][j] + min({bot, bot_left, bot_right});    
}
int minFallingPathSum3(vector<vector<int>>& matrix) {
    int r = matrix.size();
    int c = matrix[0].size();
    // The answer will not exceed 109
    vector<vector<int>> dp(r, vector<int>(c, 1e9));

    int min_sum = INT_MAX;
    for(int j=0; j<c; j++) {
        min_sum = min(min_sum, helper(0, j, matrix, dp));
    }
    return min_sum;
}
// ===================================================================================
// [1,   2,  10,  4]
// [100, 3,  2,   1]
// [1,   1,  20,  2]
// [1,   2,  2,   1]
// tabulation iterative
int minFallingPathSum4(vector<vector<int>>& matrix) {
    int r = matrix.size();
    int c = matrix[0].size();

    vector<vector<int>> dp(r, vector<int>(c, 1e9)); // The answer will not exceed 10^9

    // last row
    for(int j=0; j<c; j++) {
        dp[r-1][j] = matrix[r-1][j];
    } 

    for(int i=r-2; i>=0; i--) { // start from the second-last row
        for(int j=0; j<c; j++) {

            int b1 = (j-1 >= 0) ? dp[i+1][j-1] : 1e9;
            int b2 = dp[i+1][j];
            int b3 = (j+1 < c) ? dp[i+1][j+1] : 1e9;

            dp[i][j] = matrix[i][j] + min({b1, b2, b3});
        }
    }

    int ans = 1e9;
    for(int j=0; j<c; j++) {
        ans = min(ans, dp[0][j]);
    }
    return ans;
}
// ===================================================================================
int minFallingPathSum5(vector<vector<int>>& matrix) {
    // we only need 2 arrays
    // prev and curr
    int r = matrix.size();
    int c = matrix[0].size();
    vector<int> prev = matrix[r-1];

    for(int i=r-2; i>=0; i--) {
        vector<int> curr(c, 1e9);
        for(int j=0; j<c; j++) {
            int b1 = (j-1 >= 0) ? prev[j-1] : 1e9;
            int b2 = prev[j];
            int b3 = (j+1 < c) ? prev[j+1] : 1e9;
            curr[j] = matrix[i][j] + min({b1, b2, b3});
        }
        prev = curr;
    }

    int ans = 1e9;
    for(int j=0; j<c; j++) {
        ans = min(ans, prev[j]);
    }
    return ans;
}


int main() {


    vector<vector<int>> matrix = {{1, 2, 10, 4}, {100, 3, 2, 1}, {1, 1, 20, 2}, {1, 2, 2, 1}};
    cout << minFallingPathSum1(matrix) << endl;
    cout << minFallingPathSum2(matrix) << endl;
    cout << minFallingPathSum3(matrix) << endl;
    cout << minFallingPathSum4(matrix) << endl;
    cout << minFallingPathSum5(matrix) << endl;
    

    matrix = {{1, 4, 3, 1}, {2, 3, -1, -1}, {1, 1, -1, 8}};
    cout << minFallingPathSum1(matrix) << endl;
    cout << minFallingPathSum2(matrix) << endl;
    cout << minFallingPathSum3(matrix) << endl;
    cout << minFallingPathSum4(matrix) << endl;
    cout << minFallingPathSum5(matrix) << endl;

    return 0;
}