/*
path_with_maximum_gold
    [https://leetcode.com/problems/path-with-maximum-gold/description/]

In a gold mine grid of size m x n, each cell in this mine has an 
integer representing the amount of gold in that cell, 0 if it is 
empty.

Return the maximum amount of gold you can collect under the 
conditions:

Every time you are located in a cell you will collect all the gold in 
that cell.
From your position, you can walk one step to the left, right, up, or 
down.
You can't visit the same cell more than once.
Never visit a cell with 0 gold.
You can start and stop collecting gold from any position in the grid 
that has some gold.
 

Example 1:

Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
Output: 24
Explanation:
[[0,6,0],
 [5,8,7],
 [0,9,0]]
Path to get the maximum gold, 9 -> 8 -> 7.
Example 2:

Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
Output: 28
Explanation:
[[1,0,7],
 [2,0,6],
 [3,4,5],
 [0,3,0],
 [9,0,20]]
Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.


*/


#include <vector>
using namespace std;

int dfs(int x, int y,
        vector<vector<int>>& grid,
        vector<vector<bool>>& vis) {

    int n = grid.size();
    int m = grid[0].size();

    vis[x][y] = true;

    int best = 0;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx >= 0 && nx < n &&
            ny >= 0 && ny < m &&
            !vis[nx][ny] &&
            grid[nx][ny] > 0) {

            best = max(best,
                       dfs(nx, ny, grid, vis));
        }
    }

    vis[x][y] = false;

    return grid[x][y] + best;
}

int getMaximumGold(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<bool>> vis(n, vector<bool>(m, false));

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            if (grid[i][j] > 0) {
                ans = max(ans, dfs(i, j, grid, vis));
            }
        }
    }

    return ans;
}

// ==================================

void dfs(int x, int y,
         vector<vector<int>>& grid,
         vector<vector<bool>>& vis,
         int current_gold,
         int& ans) {

    int n = grid.size();
    int m = grid[0].size();

    current_gold += grid[x][y];
    ans = max(ans, current_gold);

    vis[x][y] = true;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx >= 0 && nx < n &&
            ny >= 0 && ny < m &&
            !vis[nx][ny] &&
            grid[nx][ny] > 0) {

            dfs(nx, ny, grid, vis, current_gold, ans);
        }
    }

    vis[x][y] = false;
}

int getMaximumGold(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<bool>> vis(n, vector<bool>(m, false));

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] > 0) {
                dfs(i, j, grid, vis, 0, ans);
            }
        }
    }

    return ans;
}