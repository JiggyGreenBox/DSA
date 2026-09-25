/*
M-Coloring Problem
    [https://www.geeksforgeeks.org/problems/m-coloring-problem-1587115620/1]

You are given an undirected graph consisting of V vertices and E 
edges represented by a list edges[][], along with an integer m. Your 
task is to find if it is possible to color the graph using at most m 
different colors such that no two adjacent vertices share the same 
color. 

Note: The graph is indexed with 0-based indexing.

*/

#include <vector>

using namespace std;


/*
Observation
    the graph geometry and the number of colors
    decide if we can color nodes without adjacent nodes 
    having the same color

    we need to try color combinations
    either we color the node
        and then check if neighbours have that color
            end
    
    or we check neighbours
        for a usable color

    then choose color
        backtrack
            if true we can end early
    else unchoose color

*/

/*
Observation

    We need to assign one of m colors to every node such that
    adjacent nodes don't have the same color.

    We need to try different color assignments.

    Decision:
        For the current node:
            try each color 0..m-1

    State:
        node
        color[]     // colors assigned to previous/current nodes

    Why is color[] state?
        Whether a color is valid for the current node depends on
        the colors already assigned to its neighbours.

    For each candidate color:
        check whether any neighbour already has this color

        if safe:
            choose color
            recurse to next node

            if recursion succeeds:
                return true

            unchoose color

    Base case:
        all nodes colored
            → return true

    If no color works:
        return false
*/

bool dfs(int node, int v, vector<int> &colors, int m, vector<int> adj[]) {

    if(node == v)
        return true;
    
    // try all colors for this node
    for(int c=0; c<m; c++) {

        bool safe = true;

        for(int nei : adj[node]) {
            if(colors[nei] == c) {
                safe = false; // color already used for neighbour
                break;
            }                
        }

        if(!safe)
            continue; // try another color

        colors[node] = c; // pick

        if(dfs(node+1, v, colors, m, adj))
            return true;

        colors[node] = -1; // unpick
    }
    return false;
}

bool graphColoring(int v, vector<vector<int>> &edges, int m) {
    // adjacency list from edges
    vector<int> adj[v];

    for(auto &e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    
    vector<int> colors(v, -1); // store colors and visited in same vector

    return dfs(0, v, colors, m, adj);
}

int main() {
    int V = 4; 
    vector<vector<int>> edges = {{0, 1}, {1, 3}, {2, 3}, {3, 0}, {0, 2}};
    int m = 3;
    auto x = graphColoring(V, edges, m);


    V = 3; edges = {{0, 1}, {1, 2}, {0, 2}}; m = 2;
    x = graphColoring(V, edges, m);
    int xx = 5;

    return 0;
}