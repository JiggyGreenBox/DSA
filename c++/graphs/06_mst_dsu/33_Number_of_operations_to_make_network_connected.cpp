#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {
public:
    vector<int> parent, size;
public:
    DisjointSet(int n) {
        parent.resize(n+1);
        size.resize(n+1, 1);
        for(int i=0; i<n+1; i++) {
            parent[i] = i;
        }
    }

    int leader(int n) {
        if(parent[n] != n) {
            parent[n] = leader(parent[n]);
        }
        return parent[n];
    }

    bool find(int u, int v) {
        return leader(u) == leader(v);
    }

    void unionBySize(int u, int v) {
        u = leader(u);
        v = leader(v);
        if(u == v) return;
        if(size[u] < size[v]) {
            parent[u] = v;
            size[v] += size[u];
        }
        else {
            parent[v] = u;
            size[u] += size[v];
        }
    }
};

int solve(int n, vector<vector<int>> &Edge) {

    // One edge can be removed from anywhere and added between any two vertices in one operation
    // this line means that there should be n-1 edges already in the graph
    int size = Edge.size();
    if(size < n-1) 
        return -1;

    // Edge[i] = [a, b]

    DisjointSet ds(n);

    // store connected edges in DS
    for(auto &e : Edge) {
        ds.unionBySize(e[0], e[1]);
    }

    // find number of components and return count-1
    int count = 0;
    for(int i=0; i<n; i++) {
        if(ds.leader(i) == i) 
            count++;
    }
    return count-1;
}


int makeConnected(int n, vector<vector<int>>& connections) {

    DisjointSet ds(n);

    int extraEdges = 0;

    for (auto &e : connections) {

        int u = e[0];
        int v = e[1];

        if (ds.leader(u) == ds.leader(v))
            extraEdges++;
        else
            ds.unionBySize(u, v);
    }

    int components = 0;

    for (int i = 0; i < n; i++) {
        if (ds.leader(i) == i)
            components++;
    }

    if (extraEdges >= components - 1)
        return components - 1;

    return -1;
}

int main() {
    return 0;
}

/*
to connect all nodes in a graph
we need n-1 connections
we if we dont have these impossible

if we have 3 diff components
we need 2 edges to connect them
k comps require k-1 edges
*/