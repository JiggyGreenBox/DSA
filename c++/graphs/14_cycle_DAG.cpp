#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, vector<int> adj[], vector<int>& visited, vector<int>& pathVisited) {
    visited[node] = 1;
    pathVisited[node] = 1;

    for(int nei : adj[node]) {
        if(!visited[nei]) {
            if(dfs(nei, adj, visited, pathVisited)) return true;
        }
        else if(pathVisited[nei]) return true;
    }

    pathVisited[node] = 0;
    return false;
}

bool isCyclic_dfs(int V, vector<int> adj[]) {
    vector<int> visited(V, 0);
    vector<int> pathVisited(V, 0);
    
    for(int i=0; i<V; i++) {
        if(!visited[i]) {
            if(dfs(i, adj, visited, pathVisited)) return true;
        }
    }
    return false;
}

int main() {
    int V = 6;
    vector<int> adj[V] = {
        {1}, 
        {2, 5}, 
        {3}, 
        {4}, 
        {1},
        {} 
    };

    if(isCyclic_dfs(V, adj)) {
        cout << "has cycle" << endl;
    }
    else cout << "no cycle" << endl;

    return 0;
}