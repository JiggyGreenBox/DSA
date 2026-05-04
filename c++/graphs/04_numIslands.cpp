#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool valid(int x, int y, int x_lim, int y_lim) {
    // i+x >=0 
    // i+x < m
    // j+y >= 0
    // j+y < n
    return (x >=0 && x < x_lim && y >= 0 && y < y_lim);     
}

int numIslands(const vector<vector<char>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> visited(m, std::vector(n,0));

    int islands = 0;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(grid[i][j] == '1' && !visited[i][j]) {
                queue<pair<int, int>> q;
                q.push({i,j});
                visited[i][j] = 1;

                while(!q.empty()) {
                    auto p = q.front();
                    q.pop();

                    int x_vals[] = {-1,0,1};
                    int y_vals[] = {-1,0,1};
                    for(int x: x_vals) {
                        for(int y : y_vals) {
                            // validate bounds
                            // i+x >=0 
                            // i+x < m
                            // j+y >= 0
                            // j+y < n       
                            
                            int a = p.first;
                            int b = p.second;
                            
                            if(valid(a+x, b+y, m, n) && grid[a+x][b+y] == '1' && !visited[a+x][b+y]) {
                                visited[a+x][b+y] = 1;
                                q.push({a+x,b+y});
                            }
                        }
                    }
                }

                islands++;
            }
        }
    }

    return islands;
}

int main() {
    cout << numIslands({{'1', '0', '0', '0', '1'}, {'0', '1', '0', '1', '0'}, {'0', '0', '1', '0', '0'}, {'0', '1', '0', '1', '0'}}) << endl;
    // cout << numIslands({{'1', '1', '1', '0', '1'}, {'1', '0', '0', '0', '0'}, {'1', '1', '1', '0', '1'}, {'0', '0', '0', '1', '1'}}) << endl;
    
    return 0;
}

int numIslands(const vector<vector<char>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> visited(m, vector<int>(n, 0));
    int islands = 0;

    int dx[] = {-1,-1,-1,0,0,1,1,1};
    int dy[] = {-1,0,1,-1,1,-1,0,1};

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {

            if(grid[i][j] == '1' && !visited[i][j]) {
                queue<pair<int,int>> q;
                q.push({i,j});
                visited[i][j] = 1;

                while(!q.empty()) {
                    auto p = q.front();
                    q.pop();

                    int x = p.first;
                    int y = p.second;

                    for(int k = 0; k < 8; k++) {
                        int nx = x + dx[k];
                        int ny = y + dy[k];

                        if(nx >= 0 && nx < m && ny >= 0 && ny < n &&
                           grid[nx][ny] == '1' && !visited[nx][ny]) {

                            visited[nx][ny] = 1;
                            q.push({nx, ny});
                        }
                    }
                }

                islands++;
            }
        }
    }

    return islands;
}