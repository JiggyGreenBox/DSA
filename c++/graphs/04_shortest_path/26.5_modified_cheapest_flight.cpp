/*
Problem 1
You are given n cities numbered 0 ... n-1 and a list of directed 
flights:
flights[i] = {from, to, time}

You start at city src and want to reach dst.
Each flight takes time units.
However, you have a maximum of K intermediate cities you are allowed 
to pass through.
Additionally, you have one special coupon that can be used on at most 
one flight:
- If you use it on a flight costing time, that flight costs time / 2 
(integer division).
- You may choose not to use the coupon.
Return the minimum possible travel time from src to dst, or -1 if 
impossible.


nodes are cities
edges are flights
they have time

we can use k stops to get from src to dst

we need some information to store state
we could use a bfs approach
    take flights till k stops are used
        then, see what is dist[dst]


the coupon means we should minus half of the longest flight

0-2-3
0-1-3

    we want min cost for 1 stop
    we want max_cost so far
    then at 3, we take lowest cost, - max/2

  0 
 / \
2   1
 \ /
  3


we can carry state of cost, stops, max-cost
    if(stops > K)
        continue

    if node == dst
        cost - max-cost/2



complexity
    time
        adj
            V+E
        pq
            V+E logV
        
    space
        adj 
            V+E
        best V

        queue
            E


*/

#include <vector>
#include <queue>
#include <iostream>
#include <climits>
#include <unordered_set>
using namespace std;


int cheapestFlight(int n, vector<vector<int>> &flights, int src, int dst, int K) {

    // adj    
    vector<vector<pair<int,int>>> adj(n);

    for(auto &f : flights) {
        //  from             to,   time
        adj[f[0]].push_back({f[1], f[2]});
    }

    using T = tuple<int,int, bool, int>; // <total_time, flights_taken, coupon_used, node>
    priority_queue<T, vector<T>, greater<T>> pq;

    pq.push({0, 1, 0, src});    

    while(!pq.empty()) {
        auto [total, flights_taken, c_used, node] = pq.top();
        pq.pop();

        

        if(node == dst)
            return total;

        if(flights_taken > K + 1)
            continue;

        for(auto [nei, time] : adj[node]) {

            // if coupon not used, we can use it here
            if(!c_used)
                pq.push({total + time/2, flights_taken+1, true, nei});

            pq.push({total + time, flights_taken+1, c_used, nei});
        }
    }

    return -1;
}

int cheapestFlight(int n, vector<vector<int>>& flights,
                   int src, int dst, int K) {

    vector<vector<pair<int,int>>> adj(n);

    for (auto& f : flights) {
        adj[f[0]].push_back({f[1], f[2]});
    }

    // dist[node][flights_taken][coupon_used]
    vector<vector<vector<int>>> dist(
        n,
        vector<vector<int>>(K + 2, vector<int>(2, INT_MAX))
    );

    // {cost, flights_taken, coupon_used, node}
    using T = tuple<int, int, int, int>;

    priority_queue<T, vector<T>, greater<T>> pq;

    dist[src][0][0] = 0;
    pq.push({0, 0, 0, src});

    while (!pq.empty()) {

        auto [cost, flights_taken, coupon_used, node] = pq.top();
        pq.pop();

        // stale state
        if (cost != dist[node][flights_taken][coupon_used])
            continue;

        // First destination popped = minimum cost
        if (node == dst)
            return cost;

        // Can't take more than K+1 flights
        if (flights_taken == K + 1)
            continue;

        for (auto [nei, time] : adj[node]) {

            int next_flights = flights_taken + 1;

            // 1. Don't use coupon
            int new_cost = cost + time;

            if (new_cost < dist[nei][next_flights][coupon_used]) {
                dist[nei][next_flights][coupon_used] = new_cost;

                pq.push({
                    new_cost,
                    next_flights,
                    coupon_used,
                    nei
                });
            }

            // 2. Use coupon
            if (!coupon_used) {

                new_cost = cost + time / 2;

                if (new_cost < dist[nei][next_flights][1]) {
                    dist[nei][next_flights][1] = new_cost;

                    pq.push({
                        new_cost,
                        next_flights,
                        1,
                        nei
                    });
                }
            }
        }
    }

    return -1;
}

// Time: O(K E log(KV))
// Space: O(KV + E)


// why is the coupon part of the state?
// if we have a path of 100+200
// isnt it just 100 + max/2 = 100+100 = 200


/*

consider
    dist[A] = 100+100+100 = 300
        after coupon 200+50 = 250

    dist[A] = 300 + 1 = 301
        after coupon 150+1 = 151

    coupon needs to be part of the path while building it

*/