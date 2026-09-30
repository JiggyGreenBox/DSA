#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void dfs(int x, int y, int baseX, int baseY, vector<vector<int>>& grid, vector<vector<int>>& visited, string &island) {

    int m = grid.size();
    int n = grid[0].size();

    visited[x][y] = 1;
    int dx[] = {0,0,-1,1};
    int dy[] = {1,-1,0,0};

    island += to_string(x-baseX) + "," + to_string(y-baseY) + " ";

    for(int k=0; k<4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if(nx>=0 && nx<m && ny>=0 && ny<n && grid[nx][ny] == 1 && !visited[nx][ny]) {            
            dfs(nx, ny, baseX, baseY, grid, visited,  island);
        }
    }
}

int countDistinctIslands(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> visited(m, vector<int>(n, 0));
    unordered_set<string> shapes;


    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(grid[i][j] == 1 && !visited[i][j]) {
                // this is a fresh island
                string island = "";
                dfs(i,j, i,j, grid, visited, island);
                shapes.insert(island);
            }
        }
    }

    return shapes.size();
}

int main() {

    vector<vector<int>> grid = {{1, 1, 0, 1, 1}, {1, 0, 0, 0, 0}, {0, 0, 0, 0, 1},{1, 1, 0, 1, 1}}; 
    cout << countDistinctIslands(grid) << endl;

    grid = {{1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 0, 1, 1},{0, 0, 0, 1, 1}};
    cout << countDistinctIslands(grid) << endl;
    return 0;
}