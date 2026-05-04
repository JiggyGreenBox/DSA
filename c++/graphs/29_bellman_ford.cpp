#include <iostream>
#include <vector>
using namespace std;

vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
    // 1. dist
    vector<int> dist(V, 1e9);
    dist[S] = 0;

    for(int i=0; i<V-1; i++) {
        for(auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int wt = e[2];
            if(dist[u] != 1e9 && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // one last check for cycles
    // if any relaxation happens, cycle detected
    for(auto &e : edges) {
        int u = e[0];
        int v = e[1];
        int wt = e[2];
        if(dist[u] != 1e9 && dist[u] + wt < dist[v]) {
            return {-1};
        }
    }
    return dist;
}

int main() {
    return 0;
}