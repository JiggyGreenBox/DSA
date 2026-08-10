#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                     pair<int, int> destination) 
{
    int r = grid.size();
    int c = grid[0].size();

    // if(grid[source.first][source.second] == 0) return -1; // this didnt work for some edge cases

    vector<vector<int>> dist(r, vector<int>(c, INT_MAX));    

    // not sure if a priority queue is required here
    // queue should be sufficient
    using P = pair<int, int>;
    queue<P> q; // {dist, {r,c}}
    q.push(source);

    dist[source.first][source.second] = 0;

    int dx[] = {0, 0, 1,-1}; // R, L, D, U
    int dy[] = {1,-1, 0, 0};

    while(!q.empty()) {
        auto [x,y] = q.front();
        q.pop();        
        
        for(int k=0;k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            // valid, 1 and unvisited
            if(nx>=0 && nx<r && ny>=0 && ny<c && grid[nx][ny] == 1) {

                // update if a shorter dist is found, INT_MAX, so at least once
                if(dist[x][y] + 1 < dist[nx][ny]) {
                    
                    dist[nx][ny] = dist[x][y] + 1;

                    if(make_pair(nx,ny) == destination) return dist[nx][ny];

                    q.push({nx, ny});
                }
            }
        }        
    }
    return -1; // not reacheable
}


// Shortest Distance in a Binary Maze
int shortestPath2(vector<vector<int>> &grid, pair<int, int> source,
                     pair<int, int> destination) 
{
    int r = grid.size();
    int c = grid[0].size();

    vector<vector<bool>> vis(r, vector<bool>(c, false));

    
    queue< pair<pair<int,int>, int>> q;
    q.push({source, 0});
    vis[source.first][source.second] = true;

    int dx[] = {1,-1, 0, 0};
    int dy[] = {0, 0, 1,-1};

    while(!q.empty()) {
        auto [cell, dist] = q.front();
        q.pop();

        if(cell == destination)
            return dist;

        auto [x,y] = cell;

        

        for(int k=0; k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if(nx<0 || nx>=r || ny<0 || ny>=c)
                continue;

            if(grid[nx][ny] == 0)
                continue;
            
            if(vis[nx][ny])
                continue;
            
            vis[nx][ny] = true;
            q.push({{nx,ny}, dist+1});
        }
    }
    return -1;
}

int main() {
    // Input: grid = [[1, 1, 1, 1],[1, 1, 0, 1],[1, 1, 1, 1],[1, 1, 0, 0],[1, 0, 0, 1]], source = [0, 1], destination = [2, 2]
    vector<vector<int>> grid = {
                                {1, 1, 1, 1},
                                {1, 1, 0, 1},
                                {1, 1, 1, 1},
                                {1, 1, 0, 0},
                                {1, 0, 0, 1}};
    pair<int, int> source = {0,1};
    pair<int, int> dest = {2,2};

    cout << shortestPath(grid, source, dest) << endl;
    cout << shortestPath2(grid, source, dest) << endl;


    grid = {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 0},
            {1, 0, 1, 0, 1}};
    source = {0,0};
    dest = {3,4};
    cout << shortestPath(grid, source, dest) << endl;
    cout << shortestPath2(grid, source, dest) << endl;

    
    return 0;
}