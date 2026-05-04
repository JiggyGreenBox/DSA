#include <istream>
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