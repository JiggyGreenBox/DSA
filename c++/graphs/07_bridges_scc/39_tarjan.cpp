#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
    private:

        int timer = 0;
        int ssc = 0;

        void dfs(int u,
                vector<vector<int>> &adj,
                vector<int> &disc,
                vector<int> &low,
                vector<bool> &onStack,
                stack<int> &st ) {
        
            // 1. discover
            disc[u] = low[u] = timer++;

            st.push(u);
            onStack[u] = true;

            // 2. Explore neighbors
            for(int v : adj[u]) {

                // v has not been visited
                if(disc[v] == -1) {
                    dfs(v, adj, disc, low, onStack, st);

                    // v's subtree may have reached an earlier node
                    // check if child can reach backwards, then curr can too
                    low[u] = min(low[u], low[v]);
                }

                // v is already visited AND still belongs to
                // the active DFS stack
                // back edge, edge to the back
                else if(onStack[v]) {
                    low[u] = min(low[u], low[v]);
                }
            }

            // 3. u is the root of the ssc
            if(disc[u] == low[u]) {

                while(true) {
                    int v = st.top();
                    st.pop();

                    onStack[v] = false;

                    if(u == v)
                        break;
                }

                ssc++;
            }
        }

    public:
        int tarjan(int n, vector<vector<int>> &adj) {
            vector<int> disc(n,-1);
            vector<int> low(n);

            vector<bool> onStack(n, false);

            stack<int> st;

            for(int i=0; i<n; i++) {
                if(disc[i] == -1)
                    dfs(i, adj, disc, low, onStack, st);
            }
            return ssc;
        }
};

int main() {
    
    int V=8; vector<vector<int>> adj={{1},{2},{0,3},{4},{5,7},{6},{4,7},{}}; // 4

    Solution sol;
    auto x = sol.tarjan(V, adj);

    return 0;
}

/*
===============================================
SCC = Strongly Connected Components
===============================================
Two main algorithms:
    1. Kosaraju
    2. Tarjan

===============================================
1. KOSARAJU
===============================================
First DFS on original graph:
    - visited[]
    - DFS
    - push node AFTER DFS finishes
    - gives finishing order

Reverse graph.

Reset visited[].

Second DFS on reversed graph:
    - take nodes from finishing-order stack
    - if node is unvisited:
        DFS
        scc_count++

Each DFS in second pass = one SCC.

===============================================
2. TARJAN
===============================================

One DFS.

Track:

    disc[u] = discovery time of u

    low[u] = earliest active ancestor
             reachable from u's DFS subtree

    stack = nodes whose SCC hasn't been finalized

    onStack[u] = whether u is currently on stack


DFS(u):

    disc[u] = low[u] = timer++

    push u onto stack
    onStack[u] = true

    for each neighbor v:

        if disc[v] == -1:
            dfs(v)

            low[u] = min(low[u], low[v])

        else if onStack[v]:
            low[u] = min(low[u], disc[v])


    if low[u] == disc[u]:

        u is root of an SCC

        pop stack until u
        set onStack[v] = false

        scc_count++


Initialize:
    disc[] = -1
    low[]
    timer = 0
    scc_count = 0
    stack
    onStack[] = false

For every node:
    if disc[u] == -1:
        dfs(u)

Return scc_count.

===============================================
dry run of the low vector
===============================================

graph
    0 → 1 → 2
    ↑       ↓
    └───────┘

edges
    0 → 1
    1 → 2
    2 → 0

Start DFS at 0
    disc[0] = low[0] = 0

    Stack:
        [0]

Then go to 1:
    disc[1] = low[1] = 1

    Stack:
        [0, 1]

Then go to 2:
    disc[2] = low[2] = 2

    Stack:
        [0, 1, 2]

Now 2 sees edge to 0
    2 → 0

    0 is already visited, disc vector

    so
        low[2] = min(low[2], disc[0]);

    disc:  0  1  2
    low:   0  1  0

DFS(2) returns to 1
    low[1] = min(low[1], low[2]);

    disc:  0  1  2
    low:   0  0  0

DFS(1) returns to 0
    low[0] = min(low[0], low[1]);


Finally
    At node 0:

    if (low[0] == disc[0])
        0 is the root of the ssc
        pop the stack
            2
            1
            0

    scc-count++


so there are 2 ways to update the low vector (ancestor)
    in a cycle directly
        if vis and on stack

    return
        my child subtree was able to reach my ancestor

*/