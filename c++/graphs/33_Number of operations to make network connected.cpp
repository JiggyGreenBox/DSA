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
    if(size < n-1) return -1;

    // Edge[i] = [a, b]

    DisjointSet ds(n);

    // store connected edges in DS
    for(auto &e : Edge) {
        ds.unionBySize(e[0], e[1]);
    }

    // find number of components and return count-1
    int count = 0;
    for(int i=0; i<n; i++) {
        if(ds.parent[i] == i) count++;
    }
    return count-1;
}

int main() {
    return 0;
}