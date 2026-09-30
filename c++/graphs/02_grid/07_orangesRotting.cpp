#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int orangesRotting(vector<vector<int>> &grid) {

    int m = grid.size();
    int n = grid[0].size();

    // can use the grid for visited

    // use a queue to store all 2's before performing bfs
    queue<pair<int, int>> q;
    int fresh = 0;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(grid[i][j] == 2) q.push({i,j});
            if(grid[i][j] == 1) fresh++;            
        }
    }

    if(fresh == 0) return 0;

    int dx[] = {0, 0, 1,-1};
    int dy[] = {1,-1, 0, 0};

    // we need access to the q size, to increment time
    int time = -1;

    while(!q.empty()) {
        int size = q.size();

        time++;

        for(int i=0; i<size; i++) {
            auto [x, y] = q.front();
            q.pop();

            for(int k=0; k<4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];

                if(nx>=0 && nx<m && ny>=0 && ny<n && grid[nx][ny] == 1) {
                    // rot orange
                    grid[nx][ny] = 2;
                    fresh--;
                    q.push({nx, ny});
                }
            }
        }
    }

    // // still might be non-rotten oranges that were not reachable
    // for(int i=0; i<m; i++) {
    //     for(int j=0; j<n; j++) {
    //         if(grid[i][j] == 1) {
    //             return -1;
    //         }
    //     }
    // }
    // return time;
    return fresh == 0 ? max(0, time) : -1;
}

int main() {

    vector<vector<int>> grid = {{2, 1, 1} , {0, 1, 1} , {1, 0, 1}};
    // cout << orangesRotting(grid) << endl;

    grid = {{2, 1, 1} , {1, 1, 0} , {0, 1, 1}};
    cout << orangesRotting(grid) << endl;

    return 0;
}