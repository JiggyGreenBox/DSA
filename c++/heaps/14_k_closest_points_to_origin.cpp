/*
K Closest Points to Origin
    [https://leetcode.com/problems/k-closest-points-to-origin/description/]


Given an array of points where points[i] = [xi, yi] represents a 
point on the X-Y plane and an integer k, return the k closest points 
to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean 
distance (i.e., √(x1 - x2)2 + (y1 - y2)2).

You may return the answer in any order. The answer is guaranteed to 
be unique (except for the order that it is in).

Example 1:
    Input: points = [[1,3],[-2,2]], k = 1
    Output: [[-2,2]]
    Explanation:
    The distance between (1, 3) and the origin is sqrt(10).
    The distance between (-2, 2) and the origin is sqrt(8).
    Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
    We only want the closest k = 1 points from the origin, so the answer 
    is just [[-2,2]].
Example 2:

    Input: points = [[3,3],[5,-1],[-2,4]], k = 2
    Output: [[3,3],[-2,4]]
    Explanation: The answer [[-2,4],[3,3]] would also be accepted.
*/

/*

K Closest Points to Origin
for each point
    we find dist to origin with a helper function
    
    we want k closest, so we want the k smallest

    we can insert all into a min-heap
    pop k times then return top

    of we can use a max-heap of size k

    for each
        push
        if  heap > k
            pop

    return top
*/
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {

    priority_queue<pair<int, int>> pq;

    for (int i = 0; i < points.size(); i++) {

        int x = points[i][0];
        int y = points[i][1];

        int dist = x * x + y * y;

        pq.push({dist, i});

        if (pq.size() > k)
            pq.pop();
    }

    vector<vector<int>> ans;

    while (!pq.empty()) {
        ans.push_back(points[pq.top().second]);
        pq.pop();
    }

    return ans;
}

/*
Want K closest points

        ↓

Score each point by distance from origin

        ↓

dist = x² + y²
(no need for sqrt)

        ↓

Want K smallest distances

        ↓

Use max heap of size K

        ↓

Root = farthest / worst point among current K

        ↓

For each point:
    push

    if size > K:
        pop worst

        ↓

Heap contains K closest points
*/