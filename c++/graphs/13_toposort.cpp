#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

void dfs(int node, vector<int>& visited, vector<int> adj[], vector<int>& ans) {
    visited[node] = 1;

    for(auto child : adj[node]) {
        if(!visited[child]) {
            dfs(child, visited, adj, ans);
        }
    }
    ans.push_back(node); // after children processed
}

vector<int> topoSort(int V, vector<int> adj[]) {
    vector<int> visited(V, 0);
    vector<int> ans;
    for(int i=0; i<V; i++) {
        if(!visited[i]) {
            dfs(i, visited, adj, ans);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

void print(const vector<int>& v) {
    cout << "[ ";
    for(int i : v) cout << i << " ";
    cout << "]\n";
}


vector<int> kahn_toposort(int V, vector<int> adj[]) {
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
    return topo;
}

int main() {
    int V = 6;
    vector<int> adj[V] = {
         {}, 
         {}, 
         {3}, 
         {1}, 
         {0,1}, 
         {0,2}
    };
    auto x = topoSort(V, adj);
    print(x);

    auto y = kahn_toposort(V, adj);
    print(y);
    return 0;
}