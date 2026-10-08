/*
============================================
oct 6
    last oct 5
============================================

i want to perform our mixed revision, but for now i want to target specific topics.
this topic: graph
strategy topic wise 

Topic
  ↓
quick sheet reconnaissance
  ↓
Session 1: Easy → Medium
  ↓
Session 2: Medium
  ↓
Session 3: Medium+
  ↓
Session 4: Hard / transfer
  ↓
identify gaps
  ↓
targeted repair

============================================
Session 3 — Medium+
============================================

Problem 1 — Word Transformation

beginWord = "hit"
endWord   = "cog"

wordList = ["hot","dot","dog","lot","log","cog"]

Nodes:
    nodes are words
Edges:
    each edge is a 1 character change from the previous word
    to the next word
         hot
        /    \
      lot    hit
Graph:

    we build the graph dynamically,
        from the start word
        we generate words that are 1 char away, but present in our wordlist
        then bfs to the endword
        we will reach the endword in the least steps in this manner

What are we trying to find:
    least steps from start to end
Algorithm:

    int wordLadder(string &beginWord, string &endWord, vector<string> &wordList) {

        // for O(1) search
        // O(N) space
        unordered_set<string> dict(wordList.begin(), wordList.end());

        if(!dict.count(endWord))
            return 0; // not reachable

        // O(N) max space
        queue<pair<string, int>> q;
        q.push({beginWord, 1}); // word, level
        dict.erase(beginWord);

        while(!q.empty()) {
            auto [word, level] = q.front();
            q.pop();

            if(word == endWord)
                return level;

            // generate next word
            // O(26*L*N) to generate all words
            for(int i=0; i<word.size(); i++) {
                char og = word[i];

                for(char c='a'; c<='z'; c++) {

                    if(c == og)
                        continue;

                    word[i] = c;                

                    if(dict.count(word)) {
                        q.push({word, level+1});
                        dict.erase(word);
                    }
                }
                word[i] = og;
            }
        }
        return -1;
    }

Why this algorithm:


complexity:
    time
        O(26*L*N) to generate all words

    space
        O(N) dict
        O(NL) queue

============================================

Session 3 — Problem 2
Now let's make the graph even less obvious.
You have an array:
nums = [2, 3, 1, 1, 4]

You start at index 0.
At index i, nums[i] tells you the maximum number of positions you can 
move forward.
For example, from index 0:

0 → 1
0 → 2


because nums[0] = 2.
Return whether you can reach the final index.
Example:

[2,3,1,1,4] → true

[3,2,1,0,4] → false


Nodes:
    idx are nodes
Edges:
    each node has nums[idx] steps to take forward        
Graph:
        nums[2,3,1,1,4]
        idx [0,1,2,3,4]

         0
        / \
        1  2        
      / |\  \
      2 3 4  3
        |  ..
        4  

What are we trying to find:
    shortest path to last idx or beyond
Algorithm:
    there is a greedy solution
        as we can see that for each idx, we can move forward
            so track the furthest starting from 0

    but to model this as a graph
        we can construct the dependency, starting from node 0
            we bfs from all nodes
            we create neighbours using the given input
            push into queue

        then at earlier level where node >= last-idx
            return level / true

        if the queue ends and we cant reach the last-idx return false
Why this algorithm:

    bool canReach(vector<int> &nums) {

        int n = nums.size();
        vector<int> vis(n);

        queue<int> q; // idx
        q.push(0);

        while(!q.empty()) {
            int idx = q.front();
            q.pop();

            if(idx >= n-1)
                return true;

            for(int i=idx+1; i <= (nums[idx] + idx); i++) {

                if(i>=n)
                    continue;

                if(vis[i])
                    continue;

                vis[i] = 1;
                
                q.push(i);
            }
        }
        return false;
    }



complexity
    time
        at each idx we can take idx..n steps
            N^2 time worst case

    space
        O(n) vis
        O(n^2) queue


============================================
Cheapest Flights Within K Stops problem.
This one is particularly useful because it tests whether you 
recognize that the k stops constraint changes the usual shortest-path 
problem.

Input: n = 4, flights = 
[[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 
3, k = 1
Output: 700

Nodes:
    airports are nodes
Edges:
    flights between airports are edges
    weights are the flight cost
Graph:
    directed weighted graph
    
What are we trying to find:
    given a src and dst
    we need to bfs k steps to find if we can find the cheapest flight
Algorithm:

    int cheapestFlight(int n, vector<vector<int>> flights, int src, int dst, int k) {
        // build adj
        //flights[i] = [fromi, toi, pricei]

        vector<vector<pair<int,int>>> adj(n);

        for(auto &f : flights) {
            adj[f[0]].push_back({f[1], f[2]});
        }

        
        queue<pair<int, int>> q;    
        vector<int> dist(n, INT_MAX);

        q.push({src, 0});
        dist[src] = 0;

        int stops = 0;
        while(!q.empty() && stops <= k) {

            int sz = q.size();

            while(sz--) {
                auto [node, cost] = q.front();
                q.pop();

                for(auto [flight, price] : adj[node]) {
                    int new_cost = cost + price;

                    if(new_cost < dist[flight]) {
                        dist[flight] = new_cost;
                        q.push({flight, new_cost});
                    }
                }
            }

            stops++;
        }
        
        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }

Why this algorithm:

complexity:
    adj
        V+E

    pq
        V+E logV

        tota V+E logV
    space
        V+E adj
        queue
            E
        dist V

        total V+E

============================================
Session 4: Hard / Transfer
============================================

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


=========================================

Problem
You are given n cities and m undirected roads:
    roads[i] = {u, v, cost}

You want to connect all cities with roads.

However, there is a special rule:
You are allowed to choose at most one road and reduce its cost to 
half, using integer division.

Return the minimum total cost needed to connect all cities.
If it is impossible to connect all cities, return -1.

n = 4

roads = {
    {0, 1, 10},
    {1, 2, 10},
    {2, 3, 10},
    {0, 3, 100},
    {0, 2, 50}
}
    0 --10-- 1 --10-- 2 --10-- 3

    cost = 25

usually we use a priority queue
    then we choose the smallest edges
        unite
        till we cant

    but here one edge could be half


state
    dist[node][coupon]


What graph algorithm comes to mind?
    mst using dsu
How does the one-time coupon change the problem?
    we have an extra state variable
Do you actually need to keep coupon state like the previous problem?

Then give me your algorithm and complexity.




MST cost = C
largest MST edge = M

Using coupon on M:

    C - M/2


Consider a non-MST edge e.

Add e to MST → creates a cycle.
Remove some MST edge f.

Alternative tree:

    C - f + e

Use coupon on e:

    C - f + e/2


Because MST is minimum:

    e >= f

And because M is largest edge in the original MST:

    M >= f

Therefore:

    e/2 + M/2 >= f

So:

    -f >= -e/2 - M/2

Thus:

    C - f + e/2
        >= C - M/2



*/

#include <vector>
#include <queue>
#include <iostream>
#include <climits>
#include <unordered_set>
using namespace std;




int main() {



    return 0;
}