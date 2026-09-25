#include <bits/stdc++.h>
using namespace std;

/*
Rat in a Maze
    [https://www.geeksforgeeks.org/problems/rat-in-a-maze-problem/1]
start 0,0 end [n-1, n-1]
    
    can move in this order
    D,L,R,U lexigraphically
*/

void dfs(int x, int y, 
    vector<vector<int>> &maze, 
    string &curr,
    vector<vector<int>> &vis ,
    vector<string> &ans
){
    int n = maze.size();
    if(x == n-1 && y == n-1) {
        ans.push_back(curr);
        return;
    }

    vis[x][y] = 1;

    // lexigraphic order
    int dx[]    = { 1,  0,  0, -1};
    int dy[]    = { 0, -1,  1,  0};
    char chs[]  = {'D','L','R','U'}; 

    for(int i=0; i<4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx>=0 && nx<n &&
            ny >=0 && ny <n &&
            !vis[nx][ny] &&
            maze[nx][ny] == 1
        ) {
            curr.push_back(chs[i]);
            dfs(nx, ny, maze, curr, vis, ans);
            curr.pop_back();
        }
    }

    vis[x][y] = 0;
}

vector<string> ratInMaze(vector<vector<int>>& maze) {
    int n = maze.size();
    vector<vector<int>> vis(n, vector<int>(n, 0));
    vector<string> ans;
    string curr;
    dfs(0, 0, maze, curr, vis, ans);
    return ans;
}

int main() {

    vector<vector<int>> maze = {{1, 0, 0, 0}, {1, 1, 0, 1}, {1, 1, 0, 0}, {0, 1, 1, 1}};    
    auto x = ratInMaze(maze);
    return 0;
}