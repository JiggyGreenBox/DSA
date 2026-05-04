#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;


bool checkCycle(int node, vector<int> adj[], vector<int>& visited, vector<int>& pathVisited, vector<int>& check) {
    visited[node] = 1;
    pathVisited[node] = 1;
    check[node] = 0; // unsafe for now

    for(int nei : adj[node]) {
        if(!visited[nei]) {
            if(checkCycle(nei, adj, visited, pathVisited, check)) return true;
        }
        else if(pathVisited[nei]) return true;
    }

    pathVisited[node] = 0;
    check[node] = 1; // safe as no cycle found
    return false;
}

vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
    // detect if a node is the starting of a cycle
    vector<int> visited(V, 0);
    vector<int> pathVisited(V, 0);
    vector<int> check(V,0);

    for(int i=0; i<V; i++) {
        if(!visited[i]) {
            checkCycle(i, adj, visited, pathVisited, check);                
        }
    }
    vector<int> safe;
    for(int i=0; i<V ; i++) {
        if(check[i]) safe.push_back(i);
    }
    return safe;
}

void print(const vector<int>& v) {
    cout << "[";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}


/*
safe nodes are nodes that end at a terminal node(outgoing = 0)
&& dont have cycles

in toposort we are able to sort these nodes
using the concept of indegree (count of incoming nodes)

by reversing the nodes we convert the problem of outgoing to incoming
which allows us to use toposort

cycles are automatically handled as the incoming or outgoing nodes
does not allow it to enter the topo queue
*/
vector<int> eventualSafeNodes_topo(int V, vector<int> adj[]) {

    /*    
    int V = 7;
    vector<int> adj[V] = {
        {1,2},    // 0
        {2,3},    // 1
        {5},      // 2
        {0},      // 3
        {5},      // 4
        {},       // 5
        {}        // 6
    };

    reversed graph
    [0] = {3}
    [1] = {0};
    [2] = {0,1};
    [3] = {1};
    [4]
    [5] = {2,4}
    [6]
    */

    // 1. reverse the graph
    vector<int> revAdj[V];

    for(int i=0; i<V; i++) {
        for(int node : adj[i]) {
            revAdj[node].push_back(i);
        }
    }

    // 2. calculate no of incoming nodes for each node
    vector<int> indegree(V, 0);
    for(int i=0; i<V; i++) {
        for(int nei : revAdj[i]) {
            indegree[nei]++;
        }
    }


    // 3. toposort dem nodes
    vector<int> topo;    
    queue<int> q;
    for(int i=0; i<V; i++) {
        if(indegree[i] == 0) {
            q.push(i);            
        }
    }
    
    while(!q.empty()) {
        int node = q.front();
        q.pop();

        topo.push_back(node); // tis def safe

        for(int nei : revAdj[node]) {
            indegree[nei]--;
            if(indegree[nei] == 0) q.push(nei);
        }
    }

    sort(topo.begin(), topo.end());
    
    return topo;
}

int main() {
    // int V = 8;
    // vector<int> adj[V] = {
    //      {1,2},
    //      {2,3},
    //      {5},
    //      {0},
    //      {5},
    //      {},
    //      {},
    //      {2}
    // };

    // int V = 8;
    // vector<int> adj[V] = {
    //      {1,2},
    //      {2,3},
    //      {5},
    //      {0},
    //      {5},
    //      {},
    //      {},
    //      {1}
    // };
    int V = 7;
    vector<int> adj[V] = {
         {1,2},
         {2,3},
         {5},
         {0},
         {5},
         {},
         {}
    };

    // vector<int> ans = eventualSafeNodes(V, adj);
    vector<int> ans = eventualSafeNodes_topo(V, adj);
    print(ans);
    
    return 0;
}


/*

0 - 1 - 3 - 0
    visited[0,1,3]
    pathV[0,1,3]
    check[]
0 - 1 - 2 - 5

0 - 2 - 5


*/