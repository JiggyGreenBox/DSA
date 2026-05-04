#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;


/*



Your code currently doesn't keep track of a dist[] or stops[] array to "prune"
(skip) paths. It will push every possible path into the pq as long as stops <=
K. In a dense graph, this could lead to a Time Limit Exceeded (TLE) error
because the same node could be pushed into the queue thousands of times with
slightly different prices and stop counts.
*/

// if flight_1 = node_0-> node_1 -> 1000xNodes
// if flight_2 = node_0-> node_1 -> 1000xNodes
//      without state tracking, we visit all 1000xNodes again
int CheapestFlight(int n, vector<vector<int>> &flights,
                       int src, int dst, int K) 
{
    // 1. build adjacency list
    vector<pair<int, int>> adj[n]; // node, wt
    for(auto &flight : flights){
        int u = flight[0];
        int v = flight[1];
        int price = flight[2];

        adj[u].push_back({v, price}); // directed Graph        
    }

    // 2. pq
    using T = tuple<int, int, int>; // price, k, node
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, 0, src});

    while(!pq.empty()) {
        auto [price, stops, node] = pq.top();
        pq.pop();

        // return condition
        if(node == dst) return price;

        // only check connected nodes if stops<=k
        if(stops <= K) {
            for(auto [nei, nei_price] : adj[node]) {
                pq.push({price + nei_price, stops+1, nei});
            }
        }
    }


    return -1;
}

// dijkstras with state tracking, cannonical solution
int CheapestFlight2(int n, vector<vector<int>> &flights,
                       int src, int dst, int K) 
{
    // 1. adjacency list
    vector<vector<pair<int,int>>> adj(n);
    for(auto& f : flights) {
        adj[f[0]].push_back({f[1], f[2]});
    }

    // 2. pq
    using T = tuple<int, int, int>; // cost, node, stops
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, src, 0});

    vector<int> stops(n, INT_MAX);

    while(!pq.empty()) {
        auto [cost, node, k] = pq.top();
        pq.pop();

        if(node == dst) return cost;

        // since we have ordered by price
        // if we come back to the same node with same stops
        // we will not visit
        if(k>K || k>stops[node]) continue;

        stops[node] = k;

        for(auto [nei, price] : adj[node]) {
            pq.push({cost+price, nei, k+1});
        }
    }
    return -1;
}


// normal BFS with queue, we use stops as the limiting factor
int CheapestFlight3(int n, vector<vector<int>> &flights,
                       int src, int dst, int K) 
{
    // 1. adj list
    vector<vector<pair<int,int>>> adj(n);
    for(auto &f : flights) {
        adj[f[0]].push_back({f[1], f[2]});
    }

    // 2. queue, dist[]
    queue<pair<int,int>> q; // node, cost
    q.push({src, 0});

    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    int stops = 0;

    while(!q.empty() && stops <= K) {
        int size = q.size();

        while (size--) {
            auto [node, cost] = q.front();
            q.pop();

            for(auto [nei, price] : adj[node]) {
                if(cost + price < dist[nei]) {
                    dist[nei] = cost + price;
                    q.push({nei, dist[nei]});
                }
            }
        }
        stops++;
    }

    return dist[dst] == INT_MAX ? -1 : dist[dst];
}

/*
BFS (normal queue)
    O(K * E)
        works because stops are limited

Dijkstra version
    O(E log V)
        handles larger graphs better
*/

int main() {
    int src = 0;
    int dst = 3;
    int K = 1;    
    int n = 4;
    vector<vector<int>> flights  = {{0,1,100},
                                    {1,2,100},
                                    {2,0,100},
                                    {1,3,600},
                                    {2,3,200}};
    cout << CheapestFlight2(n, flights, src, dst, K) << endl;
    cout << CheapestFlight3(n, flights, src, dst, K) << endl;

    src = 0;
    dst = 2;
    K = 1;    
    n = 3;    
    flights  = {{0,1,100},
                {1,2,100},
                {0,2,500}};
                                    
    cout << CheapestFlight2(n, flights, src, dst, K) << endl;
    cout << CheapestFlight3(n, flights, src, dst, K) << endl;

    return 0;
}