#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include "../common/printer.h"
using namespace std;

/*

node is also a vertex


dfs(node)
    print(node)
    for each child
        dfs(child)



bfs(node)
    queue<node> q;
    push(node)

    while q
        node = q.front()
        q.pop()

        for each child
            q.push(child)

*/

class Solution {
private:
    void helper(int node, vector<int>& visited, vector<int> adj[], vector<int>& res) {
        res.push_back(node);
        visited[node] = 1;
        if(!adj[node].empty()) {
            for(auto child : adj[node]) {
                if(!visited[child]) {
                    helper(child, visited, adj, res);
                }                
            }
        }
    }
  public:
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        vector<int> res;
        vector<int> visited(V, 0); // Initialize all nodes as unvisited
        helper(0, visited, adj, res);
        return res;
    }
    
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        vector<int> visited(V, 0); // Initialize all nodes as unvisited
        vector<int> res;
        queue<int> q;
        q.push(0);  
        visited[0] = 1;  // ✅ mark here      
        

        while(!q.empty()) {
            int node = q.front();
            q.pop();
            
            res.push_back(node);

            if(!adj[node].empty()) {
                for(auto child : adj[node]) {
                    if(!visited[child]){
                        visited[child] = 1;
                        q.push(child);                    
                    } 
                }
            }
        }
        return res;
    }
};


// cannonical
vector<int> dfsOfGraph(int V, vector<int> adj[]) {
    vector<int> res;
    vector<int> visited(V, 0);

    function<void(int)> dfs = [&](int node) {
        visited[node] = 1;
        res.push_back(node);

        for (auto child : adj[node]) {
            if (!visited[child]) {
                dfs(child);
            }
        }
    };

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i);   // handles disconnected graph
        }
    }

    return res;
}

vector<int> bfsOfGraph(int V, vector<int> adj[]) {
    vector<int> res;
    vector<int> visited(V, 0);
    queue<int> q;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            q.push(i);
            visited[i] = 1;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                res.push_back(node);

                for (auto child : adj[node]) {
                    if (!visited[child]) {
                        visited[child] = 1;  // 🔥 critical line
                        q.push(child);
                    }
                }
            }
        }
    }

    return res;
}


int main() {
    

    int V = 5;
    vector<int> edges[] = {
        {0, 1},
        {0, 2},
        {0, 3},
        {2, 4}        
    };
    // only edges, no need to insert for each node
    // for a fully disconnected graph this can be empty
        // vector<int> edges[] = {}

    // this is the adjacency list built from edge vector above
    // int V = 5;
    vector<int> adj[] = {
        {1,2,3}, // i=0
        {0},     // i=1
        {0,4},   // i=2
        {0},     // i=3
        {2}      // i=4
    };
    // for a fully disconnected graph, adj list
        /*
        vector<int> adj[] = {
            {}, // i=0
            {}, // i=1
            {}, // i=2
            {}, // i=3
            {}  // i=4
        };
        */

    Solution sol;
    print(sol.bfsOfGraph(V, adj));

    print(sol.dfsOfGraph(V, edges));

    return 0;
}
/*
int V = 5;
vector<vector<int>> edges = {
    {0, 1},
    {0, 2},
    {0, 3},
    {2, 4}
};
*/