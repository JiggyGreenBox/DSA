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