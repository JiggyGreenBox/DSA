// LeetCode 1293 — Shortest Path in a Grid with Obstacles Elimination. 
// It is classified as Hard and the intended approach is BFS on the 
// expanded state (row, col, remaining eliminations). LeetCode
// Problem statement
// Given an m × n grid:
// - 0 = empty cell
// - 1 = obstacle
// - Start = (0,0)
// - Destination = (m-1,n-1)
// - You can move up/down/left/right.
// - You may eliminate at most k obstacles.

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        if (m == 1 && n == 1)
            return 0;

        // state = (row, col, remaining eliminations)
        queue<tuple<int, int, int>> q;
        q.push({0, 0, k});

        vector<vector<vector<bool>>> visited(
            m,
            vector<vector<bool>>(n, vector<bool>(k + 1, false))
        );

        visited[0][0][k] = true;

        int steps = 0;

        int dirs[4][2] = {
            {-1, 0},
            {1, 0},
            {0, -1},
            {0, 1}
        };

        while (!q.empty()) {

            int size = q.size();

            while (size--) {

                auto [r, c, remaining] = q.front();
                q.pop();

                if (r == m - 1 && c == n - 1)
                    return steps;

                for (auto& [dr, dc] : dirs) {

                    int nr = r + dr;
                    int nc = c + dc;

                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;
                    
                    // this is fancy math
                    // if nextgrid == 1, then wall
                    // if breaks > 0 then breaks - 1
                    // is same as rem_breaks = curr - grid[next]
                    int next_remaining =
                        remaining - grid[nr][nc];

                    if (next_remaining < 0)
                        continue;

                    // dont revisit with longer path
                    if (visited[nr][nc][next_remaining])
                        continue;

                    visited[nr][nc][next_remaining] = true;

                    q.push({
                        nr,
                        nc,
                        next_remaining
                    });
                }
            }

            steps++;
        }

        return -1;
    }
};


// if k wallbreaks are allowed
//  k =3

//  then we have 
//     k=0
//     k=1
//     k=2
//     k=3 
// so k+1 possibel answers