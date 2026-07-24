#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {
private:
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n+1, 0);
        parent.resize(n+1);
        size.resize(n+1);
        for(int i=0; i<=n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int node) {
        if(parent[node] == node) return node;

        return parent[node] = find(parent[node]); // path compression        
    }
    /* path compression
        1           1
        ↓          ↙  ↘
        2         2    3        
        ↓
        3
    */

    /*
    what is rank?
        an estimate of the tree's height.

    a node starts with rank/height = 0

    Rank1 + Rank0
     1  + 3
    /
    2

    Rank1, stays same
     1
    / \
    2 3


    Rank1 + Rank1
     1  + 3
    /      \
    2       4

    = Rank2
     1
    / \
    2  3
        \
         4

        Why doesn't rank always equal the height?
            because of path compression
    */
    void unionByRank(int u, int v) {
        int pu = find(u);
        int pv = find(v);

        if(pu == pv) 
            return;

        if(rank[pu] < rank[pv]) {
            parent[pu] = pv;
        }
        else if(rank[pu] > rank[pv]) {
            parent[pv] = pu;
        }
        // only increase rank when both ranks are equal
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }

    /*
    use this in interviews
    more intutive and less code
    */
    void unionBySize(int u, int v) {
        int pu = find(u);
        int pv = find(v);

        if(pu == pv)
            return;

        // smallers parent becomes larger
        // larger size += smaller size
        // if(size[pu] < size[pv]) {
        //     parent[pu] = pv;
        //     size[pv] += size[pu];
        // }
        // else {
        //     parent[pv] = pu;
        //     size[pu] += size[pv];
        // }

        // make pu larger
        if(size[pu] < size[pv])
            swap(pu, pv);

        parent[pv] = pu;
        size[pu] += size[pv];
    }
};

/*
we attach smaller trees to larger trees
this makes the tree wider not taller
so when find(x) recursively looks for nodes
it will be faster
*/

// use either size or rank
// dont mix them
int main() {

    DisjointSet ds(7);
    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);

    if(ds.find(3) == ds.find(7)) cout << "same\n";
    else cout << " not same\n";

    ds.unionByRank(3, 7);

    if(ds.find(3) == ds.find(7)) cout << "same\n";
    else cout << " not same\n";

    cout << "\n\n";

    DisjointSet ds2(7);
    ds2.unionBySize(1, 2);
    ds2.unionBySize(2, 3);
    ds2.unionBySize(4, 5);
    ds2.unionBySize(6, 7);
    ds2.unionBySize(5, 6);

    if(ds2.find(3) == ds2.find(7)) cout << "same\n";
    else cout << " not same\n";

    ds2.unionBySize(3, 7);

    if(ds2.find(3) == ds2.find(7)) cout << "same\n";
    else cout << " not same\n";

    return 0;
}

/*
Kruskal

Goal:
Minimum Spanning Tree

Idea:

Sort edges by weight

↓

Take smallest edge

↓

If endpoints are in different components

    Take edge
    Union components

Else

    Skip (cycle)

Stop after V-1 edges

Time:
O(E log E)

Data Structure:
Disjoint Set Union (Union-Find)
*/

/*

    sort(edges.begin(), edges.end());

    DisjointSet ds(n);

    int mstWeight = 0;

    for(auto &edge : edges) {

        int wt = edge[0];
        int u  = edge[1];
        int v  = edge[2];

        if(ds.find(u) != ds.find(v)) {

            mstWeight += wt;

            ds.unionBySize(u, v);
        }
    }
*/

/*
Disjoint Set Union (DSU)

    Purpose:
    Maintain connected components efficiently.

    Operations:

    find(x)
        -> returns the representative (root) of x's component.

    union(u, v)
        -> merges the two components if they're different.

    Optimizations:
    - Path Compression
    - Union by Size (or Rank)

    Time:
    find/union ≈ O(1) amortized (O(α(N)))

    Applications:
    - Kruskal's MST
    - Dynamic connectivity
    - Detecting cycles in undirected graphs
    - Number of connected components
*/