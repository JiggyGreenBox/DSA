/*
Swim in Rising Water
    [https://leetcode.com/problems/swim-in-rising-water/description/]

You are given an n x n integer matrix grid where each value 
grid[i][j] represents the elevation at that point (i, j).

It starts raining, and water gradually rises over time. At time t, 
the water level is t, meaning any cell with elevation less than equal 
to t is submerged or reachable.

You can swim from a square to another 4-directionally adjacent square 
if and only if the elevation of both squares individually are at most 
t. You can swim infinite distances in zero time. Of course, you must 
stay within the boundaries of the grid during your swim.

Return the minimum time until you can reach the bottom right square 
(n - 1, n - 1) if you start at the top left square (0, 0).

*/

/*
we might have to wait if theres no way ahead,
look at these 2 examples

we have a path like [0 1 2 3 4 5 6], time take is 6
we have another path [0 1 11 7 8 7 1 2], time taken is 11

we want the min time taken
we have a dist matrix with INT_MAX

then from each square we can have dist = max(curr, grid[nx][ny])

    we use min-heap
        to process the lowest first

    relax by looking for a smaller answer
    and rejecting larger answers
answer is dist[n-1][n-1]
*/

/*
if the surrounding squares are less than currvalue
    we can travel there

if surrounding is greater, then we have to wait till t=greater

    we can have dist matrix[][] = INT_MAX

    then for all 4 dirs
        time = max(curr, cell)
        if(time < dist[cell])
            update

    return dist[n-1][n-1]
*/

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

    using P = pair<int, pair<int,int>>; // <cellval, <x, y>>
    priority_queue<P, vector<P>, greater<P>> pq; // process lowest cellval first


    pq.push({grid[0][0], {0,0}});
    dist[0][0] = grid[0][0];

    int dx[] = {1,-1, 0, 0};
    int dy[] = {0, 0, 1,-1};

    while(!pq.empty()) {
        auto [d, coords] = pq.top();
        pq.pop();

        auto [x,y] = coords;

        if(d != dist[x][y])
            continue; // stale entry

        for(int k=0; k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];            

            if(nx>=0 && nx<n && ny>=0 && ny<n) {
                int new_dist = max(dist[x][y], grid[nx][ny]);

                if(new_dist < dist[nx][ny]) {
                    dist[nx][ny] = new_dist;
                    pq.push({new_dist, {nx, ny}});
                }
            }
        }
    }

    return dist[n-1][n-1];
}

int main() {
    vector<vector<int>> grid = {{0,2},{1,3}};
    auto x = swimInWater(grid);

    grid = {{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}};
    x = swimInWater(grid);

    return 0;
}

/*
TIME
    V = n²
    cells

    each cell has 4 neighbours
    E = O(n²)

    Dijkstras
    O(ElogV)

    O(n^2log(n^2))

    O(n^2log(n))

SPACE
    dist → O(n²)
    pq   → O(n²) worst case
*/