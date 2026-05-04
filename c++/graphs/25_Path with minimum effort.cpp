#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;


/*
we have to track the greatest step ever taken from [0,0] to [m-1,n-1]
    max_step = max ( max_step , abs(dist[old] - dist[new]) )

*/

int MinimumEffort(vector<vector<int>> &heights) {
    // we dont need paths
    // just the minimum distance at [max-r,max-c]
    // bfs with a normal queue

    int m = heights.size();
    int n = heights[0].size();

    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

    using P = pair<int, pair<int, int>>;
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[0][0] = 0;
    pq.push({0,{0,0}});

    int dx[4] = {0,0,1,-1};
    int dy[4] = {1,-1,0,0};
    
    while(!pq.empty()) {
        
        auto [effort, coords] = pq.top();
        pq.pop();
        

        auto [x, y] = coords;

        if(x==m-1 && y==n-1)
            return effort;

        for(int k=0; k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            // if valid traversal
            if(nx>=0 && nx<m && ny>=0 && ny<n) {

                // if this is a lower step, carry old
                // else this is the max-step
                int new_effort = max(effort, abs(heights[nx][ny] - heights[x][y]));

                // lower step is possible, default is INT_MAX
                // update if a lower is found on the second pass
                if(new_effort < dist[nx][ny]) {
                    dist[nx][ny] = new_effort;
                    pq.push({new_effort, {nx, ny}});
                }
            }
        }
    }

    return 0;
}

int main() {

    // [[1,2,2],[3,8,2],[5,3,5]]
    // [[1,2,3],[3,8,4],[5,3,5]]

    vector<vector<int>> heights =   {
                                        {1,2,2},
                                        {3,8,2},
                                        {5,3,5}
                                    };

    cout << MinimumEffort(heights) << endl;
    heights =   {
                    {1,2,3},
                    {3,8,4},
                    {5,3,5}
                };
    cout << MinimumEffort(heights) << endl;    
    return 0;
}