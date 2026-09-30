#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
using namespace std;

int main() {
    return 0;
}

/*

Toposort orders by dependency
for a DAG this handles order well

if we complete toposort
we can then iterate thru each element
and update the distances as we go

allow for update of distance
if a smaller combination is found

1->2->3

[1-2, 5]
[2-3, 7]

dist[1] = 0
dist[2] = dist[1] + 5 = 5
dist[3] = dist[2] + 7 = 12

*/

class Solution {
    private:
    void topo(int i, vector<pair<int,int>> adj[], int vis[], stack<int>& st) {
        vis[i] = 1;

        for(auto it : adj[i]) {
            if(!vis[it.first]){
                topo(it.first, adj, vis, st);
            }
        }
        st.push(i);
    }
    public:
    vector<int> shortestPath(int N, int M, vector<vector<int>> & edges) {
        // 1. adj list
        vector<pair<int,int>> adj[N];
        for(auto edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            adj[u].push_back({v, wt});
        }

        // 2. toposort
        int vis[N] = {0};
        stack<int> st;
        for(int i=0; i<N; i++) {
            if(!vis[i]){
                topo(i, adj, vis, st);
            }
        }
        
        // 3. calculate distance
        vector<int> dist(N, INT_MAX);
        dist[0] = 0;
        while(!st.empty()) {
            int node = st.top();
            st.pop();

            if(dist[node] != INT_MAX){
                for(auto it : adj[node]) {
                    int v = it.first;
                    int wt = it.second;
                    if(dist[node] + wt < dist[v]) {
                        dist[v] = dist[node] + wt;
                    }
                }
            }
            
        }
        /* If a node is unreachable, 
        updating its distance to -1 */
        for (int i = 0; i < N; i++) {
            if (dist[i] == INT_MAX) 
                dist[i] = -1;
        }
        return dist;
    }
};