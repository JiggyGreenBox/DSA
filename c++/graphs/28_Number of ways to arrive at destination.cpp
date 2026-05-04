#include <vector>
#include <iostream>
#include <queue>
#include <climits>
using namespace std;

/*
Number of ways to arrive at destination

A city consists of n intersections numbered from 0 to n - 1 with
bi-directional roads between some intersections. The inputs are
generated such that one can reach any intersection from any other
intersection and that there is at most one road between any two
intersections.

Given an integer n and a 2D integer array ‘roads’ where roads[i] =
[ui, vi, timei] means that there is a road between intersections ui
and vi that takes timei minutes to travel. Determine the number of
ways to travel from intersection 0 to intersection n - 1 in the
shortest amount of time.

Since the answer may be large, return it modulo 109 + 7.
*/
int countPaths(int n, vector<vector<int>> &roads) {
    using P = pair<int,int>;

    // 1. adjacency list
    vector<vector<P>> adj(n);
    for(auto &r : roads) {
        adj[r[0]].push_back({r[1],r[2]});
        adj[r[1]].push_back({r[0],r[2]});
    }

    vector<int> dist(n, INT_MAX);
    dist[0] = 0;

    int mod = 1e9+7;

    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0,0}); // time, node

    int count = 0;
    while(!pq.empty()) {
        auto [t, node] = pq.top();
        pq.pop();

        for(auto [nei, time] : adj[node]) {
            int new_time = (time + t) % mod;
            if(new_time < dist[nei]) {
                dist[nei] = new_time;

                if(nei == n-1){
                    count = 1; // shortest time/dist updated
                }
                
                pq.push({dist[nei], nei});
            }
            else if(new_time == dist[nei]) {
                pq.push({dist[nei], nei});

                if(nei == n-1){
                    count++; // another shortest time/dist found
                }
            }
        }
    }
    
    return dist[n-1] == INT_MAX ? -1 : count;

}


// cannonical solution
// in the last solution we pushed equal weights into the queue
// this is inefficient
// instead we track ways / visits and propogate that forward

int countPaths2(int n, vector<vector<int>> &roads) {
    const long long MOD = 1e9 + 7;

    vector<vector<pair<int,int>>> adj(n);
    for(auto &f : roads) {
        adj[f[0]].push_back({f[1], f[2]});
        adj[f[1]].push_back({f[0], f[2]});
    }

    vector<long long> dist(n, LLONG_MAX);
    vector<long long> ways(n, 0);
    using P = pair<long long, int>; // dist, node
    priority_queue<P, vector<P>, greater<P>> pq;

    pq.push({0,0});

    dist[0] = 0;
    ways[0] = 1;

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        for(auto [nei, w] : adj[node]) {
            long long newDist = d + w;

            if(newDist < dist[nei]) {
                dist[nei] = newDist;
                ways[nei] = ways[node];
                pq.push({newDist, nei});
            }
            else if(newDist == dist[nei]) {
                ways[nei] = (ways[nei] + ways[node]) % MOD;
            }
        }
    }
    return ways[n-1] % MOD;
}

int main() {


    vector<vector<int>> roads = {{0,6,7},
                                {0,1,2},
                                {1,2,3},
                                {1,3,3},
                                {6,3,3},
                                {3,5,1},
                                {6,5,1},
                                {2,5,1},
                                {0,4,5},
                                {4,6,2}};
    int n = 7;
    cout << countPaths2(n, roads) << endl;

    roads ={
        {0,5,8},
        {0,2,2},
        {0,1,1},
        {1,3,3},
        {1,2,3},
        {2,5,6},
        {3,4,2},
        {4,5,2}};
    n = 6;
    cout << countPaths2(n, roads) << endl;

    return 0;
}