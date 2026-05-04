#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;


void print(const vector<vector<string>>& v) {
    cout << "[ ";
    for(auto vv : v) {
        cout << "[ ";
        for(auto x : vv) cout << x << " ";
        cout << "], ";
    }    
    cout << "]\n";
}


void print(const vector<string>& v) {
    cout << "[ ";
    for(auto x : v) cout << x << " ";
    cout << "]\n";
}

bool isSafe(int node, vector<int> adj[], int c, vector<int> &colors) {
    for(int nei : adj[node]) {
        if(colors[nei] == c) return false;
    }
    return true;
}

bool dfs(int node, vector<int> adj[], int n, int m, vector<int>& colors) {

    if(node == n) return true; // everyone was placed

    // try every color for this node
    for(int c=0; c<m; c++) {

        if(isSafe(node, adj, c, colors)) {

            colors[node] = c;

            // for(int nei : adj[node]) {
                // if(dfs(nei, adj, n, m, colors)) return true;
            // }

            if(dfs(node + 1, adj, n, m, colors)) return true;

            colors[node] = -1;
        }        
    }
    return false;
}

bool graphColoring(vector<vector<int> >& edges, int m, int n) {

    vector<int> adj[n];
    for(auto &e : edges){
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    vector<int> colors(n, -1); // each node gets a color

    
    if(dfs(0, adj, n, m, colors)) return true;
    return false;
}


int main() {
    // vector<vector<int>> grid = {{1, 0, 0, 0},{1, 1, 0, 1},{1, 1, 0, 0},{0, 1, 1, 1}};    
    // vector<vector<int>> grid = {{1, 1, 0},{1, 1, 0}, {1,1,1}}; 
    // 1000
    // 1101   
    // 1100
    // 0111

    // 1 1 0
    // 1 1 0
    // 1 1 1
    vector<vector<int> > edges {{0,1}, {1, 2}, {0, 2} };
    int m = 2;
    int n = 3;
    if(graphColoring(edges, m, n)) cout << "true" << endl;
    else cout  << "false" << endl;

    edges  = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2}};
    m = 3;
    n = 4;
    if(graphColoring(edges, m, n)) cout << "true" << endl;
    else cout  << "false" << endl;
    return 0;
}




