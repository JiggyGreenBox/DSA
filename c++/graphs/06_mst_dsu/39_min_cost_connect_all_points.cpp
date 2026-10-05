/*
Min Cost to Connect All Points        LC 1584


fn get_dist(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}



points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
for each point
    get dist to every other point

    for(int u=0...)
        for(v=0..)
            if(u == v)
                continue;

    u,v,dist

        push into pq

        if find(u) != find(v)
            dist += wt
            merge(u,v)

return dist

*/

#include <vector>
#include <cmath>
#include <queue>
using namespace std;

class DSU {
    vector<int> parent, size;

public:
    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        // Path compression
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        // Already connected → adding this edge creates a cycle
        if (a == b)
            return false;

        // Attach smaller component to larger
        if (size[a] < size[b])
            swap(a, b);

        parent[b] = a;
        size[a] += size[b];

        return true;
    }
};


class Solution {
public:

    int minCostConnectPoints(vector<vector<int>>& points) {

        int n = points.size();

        /*
            Graph:

            Each point = node

            Every pair of points can be connected.

            Edge weight =
                Manhattan distance

                |x1 - x2| + |y1 - y2|

            Since every pair is possible:

                E = n(n-1)/2
        */

        using Edge = tuple<int, int, int>;
        // {weight, u, v}

        priority_queue<
            Edge,
            vector<Edge>,
            greater<Edge>
        > pq;


        // Generate every undirected edge exactly once
        //
        // v starts at u + 1 so we don't generate both:
        //
        // (0,1) and (1,0)
        //
        // They are the same edge.

        for (int u = 0; u < n; u++) {

            for (int v = u + 1; v < n; v++) {

                int x1 = points[u][0];
                int y1 = points[u][1];

                int x2 = points[v][0];
                int y2 = points[v][1];

                int wt = abs(x1 - x2) + abs(y1 - y2);

                pq.push({wt, u, v});
            }
        }


        /*
            Kruskal:

            Take the smallest edge.

            If u and v are already connected:
                adding this edge creates a cycle
                → skip it.

            Otherwise:
                connect them
                → add its weight.
        */

        DSU ds(n);

        int cost = 0;
        int edgesUsed = 0;

        while (!pq.empty() && edgesUsed < n - 1) {

            auto [wt, u, v] = pq.top();
            pq.pop();

            if (!ds.unite(u, v))
                continue;

            cost += wt;
            edgesUsed++;
        }

        return cost;
    }
};