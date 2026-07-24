#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;


/*
Time:  O(V³)
Space: O(V²)

So it is only practical when:
     V ≤ ~400

*/
void shortestDistance(vector<vector<int>>&matrix) {
    int V = matrix.size();
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX));

    for(int k=0; k<V; k++) {
        for(int i=0; i<V; i++) {
            for(int j=0; j<V; j++) {

                if(matrix[i][k] == INT_MAX || matrix[k][j] == INT_MAX)
                    continue;

                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
}

int main() {
    return 0;
}

class Solution {
public:
	void shortestDistance(vector<vector<int>>&matrix) {
        int n = matrix.size();
        for(int k=0; k<n; k++) {
            for(int i=0; i<n; i++) {
                for(int j=0; j<n; j++) {
                    if(matrix[i][k] == -1 || matrix[k][j] == -1) {
                        continue;                        
                    }

                    // first time
                    if(matrix[i][j] == -1) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                    // update time
                    else{
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }                    
                }
            }
        }
	}
};

/*
    One source?

    ↓

    Dijkstra
    Bellman-Ford

    -------------------

    Every pair?

    ↓

    Floyd-Warshall
*/

/*
Floyd-Warshall

    State

        dist[i][j]
        =
        shortest distance
        from i to j

    Idea

        Can vertex k improve
        path i→j ?

    Transition

        dist[i][j]
        =
        min(dist[i][j],
            dist[i][k]+dist[k][j])

    Loop order

        for(k)
            for(i)
                for(j)

    Time

        O(V³)

    Negative edges

        ✓

    Negative cycle

        dist[i][i] < 0
*/

/*

how to construct input:

    n = 4;

    edges = {
        {0,1,5},
        {0,2,9},
        {1,2,3},
        {2,3,2}
    };

    const int INF = 1e9;

    vector<vector<int>> dist(n, vector<int>(n, INF));
    INF INF INF INF
    INF INF INF INF
    INF INF INF INF
    INF INF INF INF


    Distance to yourself:
    for(int i = 0; i < n; i++)
        dist[i][i] = 0;


    for(auto &e : edges) {
        int u = e[0];
        int v = e[1];
        int w = e[2];

        dist[u][v] = w;
        if undirected
        dist[v][u] = w;
    }

*/