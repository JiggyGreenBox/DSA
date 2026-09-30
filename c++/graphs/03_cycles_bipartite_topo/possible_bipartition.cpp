/*
886. Possible Bipartition

We want to split a group of n people (labeled from 1 to n) into two 
groups of any size. Each person may dislike some other people, and 
they should not go into the same group.

Given the integer n and the array dislikes where dislikes[i] = [ai, 
bi] indicates that the person labeled ai does not like the person 
labeled bi, return true if it is possible to split everyone into two 
groups in this way.

 

Example 1:

Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
Output: true
Explanation: The first group has [1,4], and the second group has 
[2,3].
Example 2:

Input: n = 3, dislikes = [[1,2],[1,3],[2,3]]
Output: false
Explanation: We need at least 3 groups to divide them. We cannot put 
them in two groups.
*/

/*
886. Possible Bipartition
this is like bipartite graph
    dislikes are adjacent nodes
        we need to make sure colors are opposite



n = 4, dislikes = [[1,2],[1,3],[2,4]]


1
3 2
   4

n = 3, dislikes = [[1,2],[1,3],[2,3]]

 1
3 2

we can use dfs to try to color the graph in opposite colors
    if we cant return false
*/

#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, int color, vector<int> &colors, vector<int> adj[]) {

    colors[node] = color;

    for(int nei : adj[node]) {
        if(colors[nei] == -1) {
            if(!dfs(nei, !color, colors, adj))
                return false;
        }
        else if(colors[nei] == color)
            return false;
    }
    return true;
}

bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
    vector<int> colors(n+1, -1);
    vector<int> adj[n+1];

    for(auto &d : dislikes) {
        adj[d[1]].push_back(d[0]);
        adj[d[0]].push_back(d[1]);
    }


    // handle disconnected graph
    for (int i = 1; i <= n; i++) {
        if (colors[i] == -1) {
            if (!dfs(i, 0, colors, adj))
                return false;
        }
    }
    
    return true;
}

int main() {
    int n = 4;
    vector<vector<int>> dislikes = {{1,2},{1,3},{2,4}};
    auto x = possibleBipartition(n, dislikes);

    n = 3; dislikes = {{1,2},{1,3},{2,3}};
    x = possibleBipartition(n, dislikes);
    return 0;
}