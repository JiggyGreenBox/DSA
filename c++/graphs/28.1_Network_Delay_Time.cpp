#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;


/*
Network Delay Time
    [https://leetcode.com/problems/network-delay-time/description/]


You are given a network of n nodes, labeled from 1 to n. You are also 
given times, a list of travel times as directed edges times[i] = (ui, 
vi, wi), where ui is the source node, vi is the target node, and wi 
is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. Return the minimum time it 
takes for all the n nodes to receive the signal. If it is impossible 
for all the n nodes to receive the signal, return -1.

Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
Example 2:

Input: times = [[1,2,1]], n = 2, k = 1
Output: 1
Example 3:

Input: times = [[1,2,1]], n = 2, k = 2
Output: -1

*/

/*
graph is directed and weighted
when signal is sent from k
it is not certain that all nodes will receive a signal
then return -1

nodes are 1 indexed
    we can have a dist vector
    default value is INT_MIN
    later if any value is INT_MIN
        return -1

    return dist[n]

build adj vector
dist(n+1, INT_MIN)

we use a priority queue to reach the min distance as fast as possilbe
    later only update dist if a better option is found
*/


int networkDelayTime(vector<vector<int>>& times, int n, int k) {

    using P = pair<int, int>;
    vector<vector<pair<int,int>>> adj(n+1);

    for(auto &f : times) {
        adj[f[0]].push_back({f[1], f[2]});
    }

    vector<int> dist(n+1, INT_MAX);

    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, k});
    dist[k] = 0;

    while(!pq.empty()) {
        auto [time, node] = pq.top();
        pq.pop();

        if(time > dist[node])
            continue;

        for(auto [nei, t] : adj[node]) {
            int newTime = time + t;
            if(newTime < dist[nei]) {
                dist[nei] = newTime;
                pq.push({newTime, nei});
            }
        }
    }

    int ans = 0;

    for(int i=1; i<=n; i++) {
        if(dist[i] == INT_MAX)
            return -1;

        ans = max(ans, dist[i]);
    }
    return ans;
}

int main() {

    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    int n = 4;
    int k = 2;
    cout << networkDelayTime(times, n, k) << endl;

    times = {{1,2,1}}; n = 2; k = 1;
    cout << networkDelayTime(times, n, k) << endl;

    times = {{1,2,1}}; n = 2; k = 2;
    cout << networkDelayTime(times, n, k) << endl;


    return 0;
}