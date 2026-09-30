#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// this problem needs the shortest path
// dfs is not suitable
// level order traversal is more suitable
void dfs(int i, int parent, vector<int> adj[], vector<int> &dist) {

    dist[i] = 1 + dist[parent];

    for(int nei : adj[i]) {
        if(dist[nei] == -1) {
            dfs(nei, i, adj, dist);
        }
    }
}


// this ca
vector<int> shortestPath(vector<vector<int>>& edges, int N,int M) {

    // 1. build the adjacency list
    vector<int> adj[N]; // each node can be connected

    for(auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];

        // undirected
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 2. iterate through all components
    vector<int> dist(N, -1); // can we use dist as visited vector    

    for(int i=0; i<N; i++) {
        if(dist[i] == -1) {
            queue<int> q;

            q.push(i);
            dist[i] = 0; // first node picked up, dist=0
            // ACTUALLY THIS IS A BUG
            // we are only calculating from node 0
            
            while(!q.empty()) {
                auto node = q.front();
                q.pop();
                
                // calculate when u know a node has children
                for(int nei : adj[node]) {
                    if(dist[nei] == -1) {
                        dist[nei] = 1 + dist[node];
                        q.push(nei);
                    }
                }
            }
        }
    }

    

    return dist;
}


vector<int> shortestPath_fixed(vector<vector<int>>& edges, int N,int M) {
     // 1. build the adjacency list
    vector<int> adj[N]; // each node can be connected

    for(auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];

        // undirected
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 2. iterate through all components, connected to 0
    vector<int> dist(N, -1); // can we use dist as visited vector    
    
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    
    while(!q.empty()) {
        auto node = q.front();
        q.pop();
        
        // calculate when u know a node has children
        for(int nei : adj[node]) {
            if(dist[nei] == -1) {
                dist[nei] = 1 + dist[node];
                q.push(nei);
            }
        }
    }

    return dist;
}

int main() {

    int N = 9, M = 10;
    vector<vector<int>> edges = {
        {0,1}, {0,3}, {3,4}, 
        {4,5}, {5,6}, {1,2}, 
        {2,6}, {6,7}, {7,8}, {6,8}
    };

    // N = 8; M = 10;
    // edges = {{1,0},{2,1},{0,3},{3,7},{3,4},{7,4},{7,6},{4,5},{4,6},{6,5}};

    auto x  = shortestPath(edges, N, M);
    for(int i : x) cout << i << " ";
    cout << endl;

    return 0;
}
