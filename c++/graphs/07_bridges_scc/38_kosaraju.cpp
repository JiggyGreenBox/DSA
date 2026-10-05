#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    void dfs(int node, vector<int> adj[], vector<int> &vis, stack<int> &st) {
        vis[node] = 1;

        for (int nei : adj[node]) {
            if (!vis[nei])
                dfs(nei, adj, vis, st);
        }

        st.push(node);
    }

    void dfsRev(int node, vector<int> revAdj[], vector<int> &vis) {
        vis[node] = 1;

        for (int nei : revAdj[node]) {
            if (!vis[nei])
                dfsRev(nei, revAdj, vis);
        }
    }

    int kosaraju(vector<vector<int>> &adj) {

        int V = adj.size();

        stack<int> st;
        vector<int> vis(V, 0);

        // First DFS
        for (int i = 0; i < V; i++) {
            if (!vis[i])
                dfs(i, adj.data(), vis, st);
        }

        // Reverse graph
        vector<vector<int>> rev(V);

        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                rev[v].push_back(u);
            }
        }

        fill(vis.begin(), vis.end(), 0);

        int scc = 0;

        // Second DFS
        while (!st.empty()) {

            int node = st.top();
            st.pop();

            if (!vis[node]) {
                dfsRev(node, rev.data(), vis);
                scc++;
            }
        }

        return scc;
    }
};

/*
===============================================
SCC = Strongly Connected Components
===============================================
Two main algorithms:
    1. Kosaraju
    2. Tarjan

===============================================
1. KOSARAJU
===============================================
First DFS on original graph:
    - visited[]
    - DFS
    - push node AFTER DFS finishes
    - gives finishing order

Reverse graph.

Reset visited[].

Second DFS on reversed graph:
    - take nodes from finishing-order stack
    - if node is unvisited:
        DFS
        scc_count++

Each DFS in second pass = one SCC.

===============================================

so the first pass for dfs is to establish the finishing order
or ancestor list [oldest->newest]

then on graph reversal
we try go backwards
    Inside an SCC, reversing the edges doesn't affect reachability.

we try go backwards
    loops will allow dfs to continue
    on return of a dfs pass
    this is an ssc

    we try from the stack for the next

SCC1 → SCC2
    within SSC1 reversal still allows reachablility
    but so from SSC2 we can reach SSC1 with the finishing stack
*/