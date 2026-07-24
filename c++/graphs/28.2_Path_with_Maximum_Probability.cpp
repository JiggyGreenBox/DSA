#include <iostream>
#include <queue>
#include <climits>
#include <vector>
using namespace std;

/*
graph is weighted
undirected
we will use a priority queue
with a dist vector
and relax the edges

we want max value
    dist(n, INT_MAX)


*/

double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {

    vector<vector<pair<int, double>>> adj(n);

    for(int i=0; i<edges.size(); i++) {

        int u = edges[i][0];
        int v = edges[i][1];
        double prob = succProb[i];

        adj[u].push_back({v, prob});
        adj[v].push_back({u, prob});
    }

    vector<double> dist(n, 0);
    dist[start_node] = 1;

    priority_queue<pair<double, int>> pq; // max-heap

    pq.push({1, start_node});

    while(!pq.empty()) {
        auto [prob, node] = pq.top();
        pq.pop();

        if(prob < dist[node])
            continue;

        for(auto [nei_node, nei_prob] : adj[node]) {
            double newProb = prob * nei_prob;
            if(newProb > dist[nei_node]) {
                dist[nei_node] = newProb;
                pq.push({newProb, nei_node});
            }
        }
    }
    return dist[end_node];    
}

int main() {

    int n = 3;
    vector<vector<int>> edges = {{0,1},{1,2},{0,2}};
    vector<double> succProb = {0.5,0.5,0.2};
    int start = 0;
    int end = 2;

    cout << maxProbability(n, edges, succProb, start, end) << endl;

    n = 3; edges = {{0,1},{1,2},{0,2}}; succProb = {0.5,0.5,0.3}; start = 0; end = 2;

    cout << maxProbability(n, edges, succProb, start, end) << endl;

    return 0;
}

/*
Maximum Probability

Weighted graph

↓

Need best path value

↓

Probability along path multiplies

↓

Keep highest probability

↓

Max Heap

dist[src] = 1

newProb = currProb * edgeProb

if(newProb > dist[v])

    update
*/