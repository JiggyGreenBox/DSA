#include <vector>
#include <queue>
using namespace std;

class Solution{
private:
    bool dfs(int node, int curr_color, vector<int>& colors, vector<int> adj[]) {        
        colors[node] = curr_color;

        for(int i : adj[node]) {
            if(colors[i] == -1) {
                if(!dfs(i, !curr_color, colors, adj)) return false;
            }
            else if(colors[i] == curr_color) return false;
        }
        return true;
    }
public:
    bool isBipartite(int V, vector<int> adj[])  {
       vector<int> colors(V, -1);       
       for(int i=0; i<V; i++) {
        if(colors[i] == -1){
            bool ans = dfs(i, 1, colors, adj);
            if(!ans) return false;
        }        
       }
       return true;
    }
};


bool isBipartite(int V, vector<int> adj[]) {
    vector<int> colors(V, -1);

    for(int i = 0; i < V; i++) {
        if(colors[i] == -1) {
            queue<int> q;
            q.push(i);
            colors[i] = 0;

            while(!q.empty()) {
                int node = q.front(); q.pop();

                for(int nei : adj[node]) {
                    if(colors[nei] == -1) {
                        colors[nei] = !colors[node];
                        q.push(nei);
                    }
                    else if(colors[nei] == colors[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}