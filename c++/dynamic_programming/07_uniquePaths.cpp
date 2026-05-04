#include <iostream>
#include <vector>
using namespace std;

// ===============================================================
// i think we can skip a visited array
// because we cant go back to where we started from
void backtrack(int x, int y, int m, int n, int& count) {
    if(x == m-1 && y==n-1) {
        count++;
        return;
    }
    int dx[] = {1,0};
    int dy[] = {0,1};

    // try right and down
    for(int k=0; k<2; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if(nx>=0 && nx<m && ny>=0 && ny<n) {
            backtrack(nx, ny, m, n, count);
        }
    }
}
int uniquePaths1_bt(int m, int n) {
    int count = 0;
    backtrack(0, 0, m, n, count);
    return count;
}
// ===============================================================
/*
need to convert the problem into
dp[row][col] = count of ways till [0][0] or [m-1][n-1]


[0 0 0]
[0 0 0]
[0 0 0]

dp[r][c] += dp[up] + dp[left] 
dp[r][c] += dp[down] + dp[right]
*/
int helper_no_memo(int x, int y) {
    if(x == 0 && y == 0) return 1;

    if(y<0 || x<0) return 0; // guard

    // go up and left
    return helper_no_memo(x, y-1) + helper_no_memo(x-1, y);
    
}
int uniquePaths2_dp_no_memo(int m, int n) {
    return helper_no_memo(m-1, n-1);
}
// ===============================================================
int helper_memo(int x, int y, vector<vector<int>> &dp) {
    if(x == 0 && y == 0) return 1;

    if(x<0 || y<0) return 0; // guard

    if(dp[x][y] != -1) return dp[x][y];

    // try up and left
    return dp[x][y] = helper_memo(x-1, y, dp) + helper_memo(x, y-1, dp);
}
int uniquePaths3_memo(int m, int n) {
    vector<vector<int>> dp(m, vector(n, -1));
    return helper_memo(m-1, n-1, dp);
}
// ===============================================================
/*
for tabulation at each step we count possible choices?
[1 1 1]
[1 2 3]
[1 3 6]
*/
int uniquePaths4_tab1(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, -1));
    dp[0][0] = 1;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(i == 0 && j == 0) continue;

            // add up and left
            int up = 0, left = 0;
            if(i>0) up = dp[i-1][j];
            if(j>0) left = dp[i][j-1];
            dp[i][j] = up + left;
        }
    }
    return dp[m-1][n-1];
}

int uniquePaths4_tab2(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));

    for(int i=1; i<m; i++) {
        for(int j=1; j<n; j++) {                        
            int up   = dp[i-1][j];
            int left = dp[i][j-1];
            dp[i][j] = up + left;
        }
    }
    return dp[m-1][n-1];
}

int uniquePaths4_tab3(int m, int n) {
    // we only need 2 rows
    vector<int> prev(n, 1);

    for(int i=1; i<m; i++) {
        vector<int> curr(n, 1);
        for(int j=1; j<n; j++) {
            curr[j] = curr[j-1] + prev[j];
        }
        prev = curr;
    }
    return prev[n-1];
}


int main() {
    int m = 3;
    int n = 2;
    cout << uniquePaths1_bt(m, n) << endl;
    cout << uniquePaths2_dp_no_memo(m, n) << endl;    
    cout << uniquePaths3_memo(m, n) << endl;
    cout << uniquePaths4_tab1(m, n) << endl;
    cout << uniquePaths4_tab2(m, n) << endl;
    cout << uniquePaths4_tab3(m, n) << endl;
    
    
    
    m = 2;
    n = 4;
    cout << uniquePaths1_bt(m, n) << endl;
    cout << uniquePaths2_dp_no_memo(m, n) << endl;
    cout << uniquePaths3_memo(m, n) << endl;
    cout << uniquePaths4_tab1(m, n) << endl;
    cout << uniquePaths4_tab2(m, n) << endl;
    cout << uniquePaths4_tab3(m, n) << endl;
    return 0;
}