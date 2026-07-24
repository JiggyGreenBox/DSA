#include <istream>
#include <queue>
#include <vector>
using namespace std;

class Solution{
private:
    bool dfs(int node, int parent, int visited[], vector<int> adj[]) {
        visited[node] = 1;

        for(int child : adj[node]) {
            if(!visited[child]) {
                if(dfs(child, node, visited, adj)) return true;
            }
            else if(parent != child) {
                return true;
            }
        }
        return false;        
    }

public:
    bool isCycle(int V, vector<int> adj[]) {
        int visited[V] = {0};
        for(int i=0; i<V; i++) {
            if(!visited[i]){
                if(dfs(i, -1, visited, adj)) return true;
            }            
        }
        return false;
    }
};

bool hasCycle(int V, vector<vector<int>>& adj) {

    vector<int> vis(V, 0);

    for (int start = 0; start < V; start++) {

        if (vis[start]) continue;

        queue<pair<int,int>> q;
        q.push({start, -1});
        vis[start] = 1;

        while (!q.empty()) {

            auto [node, parent] = q.front();
            q.pop();

            for (int neigh : adj[node]) {

                if (!vis[neigh]) {

                    vis[neigh] = 1;
                    q.push({neigh, node});

                }
                else if (neigh != parent) {

                    return true;
                }
            }
        }
    }

    return false;
}



int main() {

    int V = 6;
    vector<int> adj[V] = {
        {1, 3}, 
        {0, 2, 4}, 
        {1, 5}, 
        {0, 4}, 
        {1, 3, 5}, 
        {2, 4}
    };

    

    

    return 0;
}