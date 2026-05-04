#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <queue>
using namespace std;


vector<int> shortestPath(int n, int m, vector<vector<int>> &edges) {
    using P = pair<int, int>;

    // 1. construct adjacency list
    vector<P> adj[n+1];
    for(auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    // 2. dijkstra
    vector<int> dist(n+1, INT_MAX);
    dist[1] = 0;

    // when we find the shortest dist
    // we will also store the parent when that happens
    // then we can track the path backwards from n..1
    vector<int> parent(n+1);
    for(int i=1; i<=n; i++) {
        parent[i] = i;
    }
    

    
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, 1});

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if(d > dist[node]) continue; // most likely revisiting from another node

        for(auto [nei, wt] : adj[node]) {
            if(d + wt < dist[nei]) {
                parent[nei] = node; // node was the parent with the shortest path/wt/dist
                dist[nei] = d + wt;
                pq.push({dist[nei], nei});
            }
        }
    }

    // n was not connected to the src node
    if(dist[n] == INT_MAX) return {-1};

    vector<int> path;

    int node = n;
    // parent[1] = 1, it was never changed    
    while(parent[node] != node) {        
        path.push_back(node);
        node = parent[node];
    }

    path.push_back(1);
    path.push_back(dist[n]); // for this problem, not in cannonical

    reverse(path.begin(), path.end());

    return path;
}

void print(const vector<int>& v) {
    cout << "[ ";
    for(auto x : v) cout << x << " ";
    cout << "]\n";
}

int main() {

    int n = 5;
    vector<vector<int>> edges = {{1,2,2}, {2,5,5}, {2,3,4}, {1,4,1},{4,3,3},{3,5,1}};
    print(shortestPath(n, edges.size(), edges));
    return 0;
}