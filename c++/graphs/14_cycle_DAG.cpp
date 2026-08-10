#include <iostream>
#include <vector>
#include <queue>
#include "../common/printer.h"
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

bool isCyclic_kahn(int V, vector<int> adj[]) {
    vector<int> indegree(V,0);
    for(int i=0; i<V; i++) {
        for(int nei : adj[i]) {
            indegree[nei]++;
        }        
    }

    // 2. push all nodeswith indegree of 0
    queue<int> q;
    for(int i=0; i<V; i++) {
        if(indegree[i] == 0) {
            q.push(i);            
        }
    }

    // 3. bfs
    vector<int> topo;
    while(!q.empty()) {
        int node = q.front();
        q.pop();

        topo.push_back(node);

        for(int nei : adj[node]) {
            indegree[nei]--; // node is removed
            if(indegree[nei] == 0) q.push(nei);
        }
    }
    return topo.size() != V; // true is cycle, false is no cycle
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
    
    print(isCyclic_kahn(V, adj));

    return 0;
}

/*
0 → 1 → 2
↓       ↑
↘ → → → ↗

we have 2 paths from 0 to 2 [0,1,2] [0,2]
if we use visited then 2 will come twice


0 → 1 → 2
↑       ↓
↖ ← ← ← ↙

here a cycle exists
    [0,1,2,0]
    if we start from 0 we reach 0 again in the same run
    we need another DS for this
        think of it as the current run or current stack

    so visited and pathvisited
        visited to make sure we only process each node once
        pathvisited is the current run or current stack

how to use:
    before processing nei
    add to path visited
        pV[node] = 1
    after
    remove
        pV[node] = 0

        during process:
            if pV[nei] == 1
                cycle detected
*/