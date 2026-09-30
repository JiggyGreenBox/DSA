#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;


/*
Path with minimum effort
    [https://takeuforward.org/practice/dsa/path-with-minimum-effort?category=shortest-path-algorithms&source=strivers-a2z-dsa-sheet]
    
A hiker is preparing for an upcoming hike. Given heights, a 2D array 
of size rows x columns, where heights[row][col] represents the height 
of the cell (row, col). The hiker is situated in the top-left cell, 
(0, 0), and hopes to travel to the bottom-right cell, (rows-1, 
columns-1) (i.e.,0-indexed). He can move up, down, left, or right. He 
wishes to find a route that requires the minimum effort.

A route's effort is the maximum absolute difference in heights 
between two consecutive cells of the route.


Example 1:
    Input: heights = [[1,2,2],[3,8,2],[5,3,5]]

    Output: 2

    Explanation: The route of [1,3,5,3,5] has a maximum absolute 
    difference of 2 in consecutive cells. This is better than the route 
    of [1,2,2,2,5], where the maximum absolute difference is 3.

Example 2:
    Input: heights = [[1,2,3],[3,8,4],[5,3,5]]

    Output: 1

    Explanation: The route of [1,2,3,4,5] has a maximum absolute 
    difference of 1 in consecutive cells, which is better than route 
    [1,3,5,3,5].



*/

/*
we have to track the greatest step ever taken from [0,0] to [m-1,n-1]
    max_step = max ( max_step , abs(dist[old] - dist[new]) )

*/

int MinimumEffort(vector<vector<int>> &heights) {
    // we dont need paths
    // just the minimum distance at [max-r,max-c]    

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

        // stale entry
        if (effort != dist[x][y])
            continue;

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

/*
Minimum Effort Path
        ↓
path cost = maximum edge difference along path
        ↓
minimize that maximum
        ↓
Dijkstra / minimax Dijkstra
*/