#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class DisJointSet {
private:
    vector<int> parent, rank;
public:
    DisJointSet(int n) {
        parent.resize(n+1);
        rank.resize(n+1, 1);
        for(int i=0; i<=n; i++) {
            parent[i] = i;
        }
    }

    int leader(int node) {
        if(parent[node] == node) return node;

        return parent[node] = leader(parent[node]);
    }

    bool find(int u, int v) {
        return leader(u) == leader(v);
    }

    void unionByRank(int u, int v) {
        int pu = leader(u);
        int pv = leader(v);

        if(pu == pv) return;

        if(rank[pu] < rank[pv]) {
            parent[pu] = pv;
        }
        else if(rank[pu] > rank[pv]) {
            parent[pv] = pu;
        }
        else{
            parent[pv] = pu;
            rank[pv]++;
        }
    }

};

// prims
int spanningTree(int V, vector<vector<int>> adj[]) {
    // process weights in a greedy manner
    // choose the smallest
    // once we visit a node we dont again
    using P = pair<int, int>;

    int vis[V] = {0};

    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, 0}); // wt, node

    int sum = 0;

    while(!pq.empty()) {
        auto [wt, node] = pq.top();
        pq.pop();

        if(vis[node]) continue;

        vis[node] = 1;
        sum += wt;

        for(auto& vec : adj[node]) {
            int nei = vec[0];
            int nei_wt = vec[1];

            if(!vis[nei]) {
                pq.push({nei_wt, nei});
            }            
        }
    }

    return sum;
}


// kruskals
int spanningTree2(int V, vector<vector<int>> adj[]) {
    // we use a disjoint set
    // we use a pq to choose the smallest path
    // then do a unionbyrank

    // sort edges by weight
    // as we choose minimal weight paths we keep checking the parent
    vector<vector<int>> edges;
    for(int i=0; i<V; i++) {
        for(auto& it : adj[i]) {
            int u = it[0];
            int v = it[1];
            int wt = it[2];

            edges.push_back({wt, u, v});
        }
    }
    sort(edges.begin(), edges.end());

    int mst = 0;

    DisJointSet ds(V);
    for(auto edge : edges) {
        int wt = edge[0];
        int u = edge[0];
        int v = edge[0];
        
        if(!ds.find(u,v)) {
            mst += wt;
            ds.unionByRank(u,v);
        }
    }

    return mst;
}

int main() {

    return 0;
}
