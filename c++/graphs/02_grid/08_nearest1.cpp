#include <iostream>
#include <vector>
#include <queue>
using namespace std;


vector<vector<int>> nearest(vector<vector<int>> grid) {
    int m = grid.size();
    int n = grid[0].size();

    // visited + result
    vector<vector<int>> dist(m, vector<int>(n, -1));

    queue<pair<int, int>> q;    

    // collect 1's
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(grid[i][j] == 1) {
                q.push({i, j});
                dist[i][j] = 0;
            }
        }
    }

    int dx[] = {0, 0, 1,-1};
    int dy[] = {1,-1, 0, 0};
    
    while(!q.empty()) {
        
        auto [x, y] = q.front();
        q.pop();

        for(int k=0; k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            
            if(nx>=0 && nx<m && ny>=0 && ny<n && dist[nx][ny] == -1) 
            {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }        
    }

    return dist;
}

void print(const vector<vector<int>>& grid) {
    // cout << "[ ";
    for(auto& row : grid) {
        cout << "[ ";
        for(int cell : row) cout << cell << " ";
        cout << "]\n";
    }
    cout << "\n";
}

int main() {
    vector<vector<int>> grid = { {1, 0, 1}, {1, 1, 0}, {1, 0, 0}};
    print(grid);
    print(nearest(grid));

    cout << "\n\n";

    grid = {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 1, 1}};
    print(grid);
    print(nearest(grid));

    return 0;
}

