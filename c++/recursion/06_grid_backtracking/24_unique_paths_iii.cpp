/*
Unique Paths III
    [https://leetcode.com/problems/unique-paths-iii/description/]

You are given an m x n integer array grid where grid[i][j] could be:

1 representing the starting square. There is exactly one starting 
square.
2 representing the ending square. There is exactly one ending square.
0 representing empty squares we can walk over.
-1 representing obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to 
the ending square, that walk over every non-obstacle square exactly 
once.
*/

#include <vector>
using namespace std;

int dfs(int x, int y,        
        vector<vector<int>> &vis,
        vector<vector<int>> &grid,
        int remaining
){
    if(grid[x][y] == 2) {
        return remaining == 0;
    }

    int n = grid.size();
    int m = grid[0].size();

    int count = 0;

    vis[x][y] = 1;

    int dx[] = { 1,-1, 0, 0};
    int dy[] = { 0, 0,-1, 1};

    for(int i=0; i<4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx<0 || nx>=n || ny<0 || ny>=m)
            continue;        

        if(!vis[nx][ny] && grid[nx][ny] != -1) {
            count += dfs(nx,ny, vis, grid, remaining - 1);
        }
    }

    vis[x][y] = 0;
    return count;
}

int uniquePathsIII(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> vis(n, vector<int>(m, 0));

    int sx, sy;
    int remaining = 0;

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(grid[i][j] != -1)
                remaining++;

            if(grid[i][j] == 1) {
                sx = i;
                sy = j;
            }
        }
    }

    vis[sx][sy] = 1;
    remaining--; // start is already visited
    return dfs(sx, sy, vis, grid, remaining);
}

int main() {
    vector<vector<int>> grid = {{1,0,0,0},{0,0,0,0},{0,0,2,-1}};
    // grid = {{0,1},{2,0}};

    grid = {{1,0,0,0},{0,0,0,0},{0,0,0,2}};
    auto x = uniquePathsIII(grid);
    return 0;
}