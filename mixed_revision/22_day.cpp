/*
============================================
oct 5
    last sep 25
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
Session 1 — Easy → Medium
============================================

Problem 1
You are given an undirected graph with n vertices numbered 0 ... n-1 
and a list of edges.
Return the number of connected components in the graph.
Example:
    n = 5
    edges = [[0,1], [1,2], [3,4]]

    answer = 2

Nodes:
    nodes are [0,n-1]
Edges:
    edges are given as [n1,n2]
Graph:
    0
     \
      1 - 2

    3 - 4

What are we trying to find:
    number of components
Algorithm:
    int numComponents(int n, vector<vector<int>> edges) {

        // make adj list
        vector<vector<int>> adj(n);

        // O(V+E) time/space
        for(auto &e : edges) {
            // undirected
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> vis(n, 0); // O(V) space

        int components = 0;

        for(int i=0; i<n; i++) {
            if(vis[i])
                continue;

            queue<int> q;
            vis[i] = 1;
            q.push(i);
            

            while(!q.empty()) {
                int node = q.front();
                q.pop();

                for(int nei : adj[node]) {
                    if(!vis[nei]) {
                        vis[nei] = 1;
                        q.push(nei);
                    }
                }
            }
            components++;
        }

        return components;
    }


Complexity:
    time: O(V+E) adj
          O(V+E) bfs
        O(V+E)
    space 
        O(V+E) adj
        O(V) vis
        O(V) bfs

        O(V+E)

============================================

Problem 2
You are given a 2D binary matrix where:
- 1 = land
- 0 = water
Two land cells belong to the same island if they are connected up, 
down, left, or right.
Return the number of islands.
Example:
    1 1 0 0
    1 0 0 1
    0 0 1 1

    3

Nodes:
    each 1 is a land node
    0 is a water node
        if in four directions we find land from another land node
        then it is considered to be the same land aka island
Edges:
    every step in any direction of the grid is an edge
Graph:
    this is an island
    1 1
    1


What are we trying to find:
    number of islands connected without water inbetween
Algorithm:

    int numIslands(vector<vector<int>> grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> vis(n, vector<int>(m, 0)); // O(nm) space

        int dx[] = {1,-1, 0, 0};
        int dy[] = {0, 0, 1,-1};

        int islands = 0;

        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(grid[i][j] == 1) { // land

                    if(vis[i][j])
                        continue;

                    queue<pair<int,int>> q;
                    vis[i][j] = 1;
                    q.push({i,j});

                    while(!q.empty()) {
                        auto &[x,y] = q.front();
                        q.pop();

                        for(int k=0; k<4; k++) {
                            int nx = x + dx[k];
                            int ny = y + dy[k];

                            if( nx>=0 && nx<n && 
                                ny>=0 && ny<m && 
                                grid[nx][ny] == 1 && 
                                !vis[nx][ny]) {
                                
                                vis[nx][ny] = 1;
                                q.push({nx,ny});
                            }
                        }
                    }
                    
                    islands++;
                }
            }
        }
        return islands;
    }

Complexity:

    time:
    O(nm) 

    space
    O(nm) vis
    queue(nm)

    total O(nm)


============================================
Problem 3
You are given a directed graph with n nodes and edges.
Determine whether the graph contains a cycle.
Example:

    0 → 1 → 2
    ↑   |
    └───┘

Nodes:
    nodes are numbers [0,n-1]
Edges:
    given as a list,
    they are directed
Graph:
What are we trying to find:
    if there is a cycle
Algorithm:
    bool dfs(int node, vector<vector<int>> &adj, vector<int> &vis, vector<int> &path_vis) {

        vis[node] = 1;
        path_vis[node] = 1;

        for(int nei : adj[node]) {
            if(!vis[nei]) {
                if(dfs(nei, adj, vis, path_vis))
                    return true;
            }
            else if(path_vis[nei]) {
                return true;
            }
        }

        path_vis[node] = 0;
        return false;
    }

    bool isCycle(int n, vector<vector<int>> edges) {

        vector<vector<int>> adj(n);

        for(auto &e : edges) {
            adj[e[0]].push_back(e[1]);
        }

        vector<int> vis(n, 0);
        vector<int> path_vis(n, 0);

        for(int i=0; i<n; i++) {
            if(vis[i])
                continue;
            
            if(dfs(i, adj, vis, path_vis))
                return true;
        }
        return false;
    }

Complexity
    time
        to visit whole graph
        O(V+E)
    space
        adj (V+E)
        vis O(V)
        pathvis O(V)
        stack O(v)
        total O(V+E)

============================================
Session 2 — Medium.
============================================

Problem 1
There are n courses numbered 0 ... n-1.
You are given prerequisites:
    [a, b]
        b before a

Return whether it is possible to finish all courses.
    n = 4

    prerequisites:
    [1,0]
    [2,1]
    [3,2]

    true
    ---
    n = 3

    prerequisites:
    [1,0]
    [2,1]
    [0,2]

    false

Nodes:
    this is a directed graph
        c1 depends on c2 being finished

    courses are nodes
Edges:
    b->a
    can complete a only after b
Graph:
    0-1-2-3
What are we trying to find:
    if the graph has no dependency cycles
Algorithm:

    bool allCourses(int n, vector<vector<int>> prereqs) {
        // kahns toposort

        vector<int> indegree(n);

        // adj
        vector<vector<int>> adj(n);
        for(auto &c : prereqs) {
            adj[c[1]].push_back(c[0]);
            indegree[c[0]]++;
        }

        queue<int> q;

        for(int i=0; i<n; i++) {
            if(indegree[i] == 0)
                q.push(i);
        }

        vector<int> topo;

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            topo.push_back(node);

            for(int nei : adj[node]) {
                indegree[nei]--;
                if(indegree[nei] == 0)
                    q.push(nei);
            }
        }

        return topo.size() == n;
    }

Why this algorithm:
    we use topo sort
    topo sort allows dependencies to modelled as directed graphs

    then if we can find a topological sorting order
    and the order is of the same size as the graph
    then we can take all courses


Complexity: 
    time
        adj O(V+E)
        bfs O(V)

    Space
        adj(V+E)
        bfs O(V)
        in O(V)
        topo O(V)

============================================

Session 2 — Problem 2
Now let's move away from dependency graphs.
You have an n × m grid containing:
0 = empty
1 = fresh orange
2 = rotten orange

Every minute, a rotten orange causes its up/down/left/right 
neighboring fresh oranges to become rotten.
Return the minimum number of minutes required for all oranges to 
become rotten.
If some fresh orange can never become rotten, return -1.
Example:
2 1 1
1 1 0
0 1 1

Nodes:
    the grid itself is the graph
    we start with oranges that are rotten (==2)
    then move in all 4 directions looking for fresh oranges
Edges:
Graph:
What are we trying to find:
Algorithm:

    int rottenOranges(vector<vector<int>> crate) {

        int n = crate.size();
        int m = crate[0].size();
        int fresh = 0;

        queue<pair<int,int>> q;

        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(crate[i][j] == 2) {
                    q.push({i,j});
                }
                else if(crate[i][j] == 1) {
                    fresh++;
                }
            }
        }

        if(fresh == 0)
            return 0; // no fresh oranges

        int dx[] = { 1,-1, 0, 0};
        int dy[] = { 0, 0,-1, 1};

        int time = 0;
        
        while(!q.empty()) {
            int sz = q.size();

            while(sz--) {
                auto &[x,y] = q.front();
                q.pop();

                for(int k=0; k<4; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];

                    if(nx>=0 && nx<n && ny>=0 && ny<m && crate[nx][ny] == 1) {
                        crate[nx][ny] = 2;
                        q.push({nx, ny});
                        fresh--;
                    } 
                }
            }

            if(!q.empty()) {
                time++;
            }
        }

        return fresh == 0 ? time : -1;
    }
Why this algorithm:


complexity:
    time
    O(nm) find oranges

    bfs 
        O(4nm)

    nm total

    space 
        queue
            nm

============================================

Problem 3
Last one for this session.
You are given a weighted undirected graph with n nodes. Each edge is:
    [u, v, w]

where w > 0 is the travel time between u and v.
Given a source node src, return the shortest distance from src to 
every other node.

0 --4-- 1
|       |
1       2
|       |
2 --5-- 3

0 → 1 → 3 = 4 + 2 = 6


Nodes:
    nodes are [o,n-1]
Edges:
    connections between 2 vertices with a given weight
Graph:
What are we trying to find:
    shortest distance of each node from src
Algorithm:
Why this algorithm:
    we use a priority queue to process the smallest weights first

Complexity:
    time
        adj (V+2E)

        pq
        O((V+E) log(V))

    space
        adj (V+2E)
        pq (V+2E)
        dist(V)


*/
#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;


vector<int> shortestPath(int src, int n, vector<vector<int>> &edges) {
    vector<int> dist(n, INT_MAX);

    vector<vector<pair<int,int>>> adj(n);

    // adj
    for(auto &e : edges) {
        adj[e[0]].push_back({e[1], e[2]});
        adj[e[1]].push_back({e[0], e[2]});
    }

    
    using P = pair<int,int>;

    priority_queue<P, vector<P>, greater<P>> pq;

    pq.push({0, src}); // wt, node
    dist[src] = 0;

    while(!pq.empty()) {

        auto [d, node] = pq.top();
        pq.pop();

        if(d > dist[node])
            continue; // stale

        for(auto [nei, wt] : adj[node]) {
            int new_dist = d + wt;
            if(new_dist < dist[nei]) {
                dist[nei] = new_dist;
                pq.push({new_dist, nei});
            }
        }
    }

    for(auto &d : dist) {
        if(d == INT_MAX)
            d = -1;
    }

    return dist;
}


int main() {
    
// 0 --4-- 1
// |       |
// 1       2
// |       |
// 2 --5-- 3

    vector<vector<int>> edges = {{0, 1, 4},
                                {1, 3, 2},
                                {0, 2, 1},
                                {2, 3, 5}};

    auto x = shortestPath(0, 4, edges);

    return 0;
}


