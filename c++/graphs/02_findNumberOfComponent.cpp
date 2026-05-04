#include <iostream>
#include <vector>
#include <queue>
using namespace std;



// [[0, 1], [1, 2], [2, 3], [4, 5]]

// 0 
//     1
//         2
//             3
// 4
//     5

// 6

// [0] = [1]
// [1] = [0,2]
// [2] = [1,3]
// [3] = [2]
// [4] = [5]
// [5] = [4]
// [6] = []

// for 0..V
//     bfs()
//         q
//         q.push
//         visited
//             while q.empty

//         components++



int findNumberOfComponent(int V, vector<vector<int>> &edges) {
    vector<int> adj[V];
    vector<int> visited(V, 0);

    for(auto edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    int components = 0;

    for(int i=0; i<V; i++) {
        // bfs
        if(!visited[i]) {
            queue<int> q;
            q.push(i);
            visited[i] = 1;

            while(!q.empty()) {
                int node = q.front();
                q.pop();

                for(auto child : adj[node]) {
                    if(!visited[child]) {
                        visited[child] = 1;
                        q.push(child);
                    }
                }
            }
            
            components++;            
        }
    }
    return components;
}


int main() {

    int V = 7;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {4, 5}};

    cout << findNumberOfComponent(V, edges) << endl;

    V = 4;
    edges = {{0,1}, {1,2}};
    cout << findNumberOfComponent(V, edges) << endl;

    return 0;
}