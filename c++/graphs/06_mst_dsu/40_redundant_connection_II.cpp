/*
Redundant Connection II               LC 685

    [https://leetcode.com/problems/redundant-connection-ii/description/]

Redundant Connection I
        ↓
Undirected
        ↓
Only care about cycles
        ↓
DSU directly solves it


Redundant Connection II
        ↓
Directed rooted tree
        ↓
Need to handle:
    1. cycle
    2. node with 2 parents
        ↓
Indegree + DSU





a node cant have 2 parents
    indegree

we cant have a cycle
    dsu


brute force
    for each edge
        skip 1
            build a dsu
            maintain indegree
                if loop
                    break;
                
                if indegree > 1
                    break;

for (int skip = 0; skip < n; skip++) {

    DSU ds(n + 1);
    vector<int> indegree(n + 1, 0);

    bool valid = true;

    for (int i = 0; i < n; i++) {

        if (i == skip)
            continue;

        int u = edges[i][0];
        int v = edges[i][1];

        // v would have two parents
        if (indegree[v] == 1) {
            valid = false;
            break;
        }

        // cycle
        if (ds.find(u) == ds.find(v)) {
            valid = false;
            break;
        }

        indegree[v]++;
        ds.unite(u, v);
    }

    if (valid)
        return edges[skip];
}
*/

#include <vector>
using namespace std;

class DSU {
private:
    vector<int> parent, size;
public:
    DSU(int n) {
        parent.resize(n+1);
        size.resize(n+1, 1);
        for(int i=0; i<=n; i++) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if(parent[node] == node) return node;

        return parent[node] = find(parent[node]);
    }    

    void unite(int u, int v) {
        int u = find(u);
        int v = find(v);

        if(u == v) 
            return;

        if(size[u] < size[v])
            swap(u,v);

        parent[v] = u;
        size[u] += size[v];
    }
};

class Solution {
public:

    vector<int> findRedundantDirectedConnection(
        vector<vector<int>>& edges) {

        int n = edges.size();

        /*
            A valid rooted tree has:

                - exactly one parent for every node except root
                - no cycles

            Therefore there are two possible problems:

                1. A node has TWO parents
                2. There is a CYCLE
        */


        // parent[v] = edge that currently gives v its parent
        vector<int> parent(n + 1, 0);

        // Two candidate edges if some node has two parents
        vector<int> first;
        vector<int> second;


        /*
            Find a node with two parents.

            Example:

                1 -> 3
                2 -> 3

            Then:

                first  = [1,3]
                second = [2,3]

            Only these two edges can possibly be
            the answer.
        */

        for (auto &edge : edges) {

            int u = edge[0];
            int v = edge[1];

            if (parent[v] == 0) {

                // First parent of v
                parent[v] = u;

            } else {

                // v already has a parent

                first = {parent[v], v};
                second = {u, v};

                break;
            }
        }


        /*
            Now we know:

                first  = earlier parent edge
                second = later parent edge

            If there was no node with two parents,
            both vectors remain empty.

            In that case this reduces to
            normal Redundant Connection.
        */


        DSU ds(n + 1);

        for (auto &edge : edges) {

            /*
                If there is a node with two parents,
                temporarily ignore the SECOND parent edge.

                We want to see whether the remaining
                graph forms a tree.
            */

            if (!second.empty() &&
                edge[0] == second[0] &&
                edge[1] == second[1]) {

                continue;
            }


            int u = edge[0];
            int v = edge[1];


            /*
                If u and v are already connected,
                this edge creates a cycle.
            */

            if (ds.find(u) == ds.find(v)) {

                /*
                    We found a cycle.

                    If there was a two-parent situation,
                    skipping 'second' wasn't enough.

                    Therefore 'first' must be the edge
                    that should be removed.
                */

                if (!second.empty())
                    return first;

                /*
                    No two-parent situation.

                    This is simply Redundant Connection I.
                */

                return edge;
            }


            ds.unite(u, v);
        }


        /*
            If we reached here without finding a cycle,
            then skipping 'second' produced a valid tree.

            Therefore 'second' is the redundant edge.
        */

        if (!second.empty())
            return second;


        return {};
    }
};