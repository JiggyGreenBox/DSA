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