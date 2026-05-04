#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;


// using a priority queue
vector<int> dijkstra1(int V, vector<vector<int>> adj[], int S) {
    
    using P = pair<int, int>;
    // min heap with pair-int-int
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, S});

    vector<int> dist(V, 1e9);
    dist[S] = 0;

    while(!pq.empty()) {
        auto [node_dist, node] = pq.top();
        pq.pop();

        if(node_dist > dist[node]) continue; // why this line?

        for(auto nei_adj : adj[node]) {
            int adj_node = nei_adj[0];
            int adj_wt   = nei_adj[1];

            if(dist[node] + adj_wt < dist[adj_node]) {
                dist[adj_node] = dist[node] + adj_wt;
                pq.push({dist[adj_node], adj_node});
            }
        }
    }
    return dist;
}

vector<int> dijkstra2(int V, vector<vector<int>> adj[], int S) {
    using P = pair<int, int>;
    set<P> st;
    st.insert({0, S});

    vector<int> dist(V, 1e9);
    dist[S] = 0;

    while(!st.empty()) {
        auto it = *(st.begin());
        int node_dis = it.first;
        int node = it.second;
        st.erase(it);

        for(auto vec : adj[node]) {
            
            int adjNode = vec[0];
            int adjWt = vec[1];
            
            if(node_dis + adjWt < dist[adjNode]) {
                if(dist[adjNode] != 1e9)
                    st.erase({dist[adjNode], adjNode});
                dist[adjNode] = node_dis + adjWt; 
                st.insert({dist[adjNode], adjNode});
            }
        }
    }
    return dist;
}

void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

int main() {
    // int V = 2, S = 0;
    // vector<vector<int>> adj[V] = {
    //     {{1, 9}}, 
    //     {{0, 9}}
    // };
    
    // vector<vector<int>> edges= {
    //     {0,1,1},
    //     {0,3,2},
    //     {1,2,4},
    //     {2,3,3}
    // };

    // vector<vector<int>> addddj[4];
    // for(auto edge : edges) {
    //     int u = edge[0];
    //     int v = edge[1];
    //     int wt = edge[2];
        
    //     addddj[u].push_back({v, wt});
    //     addddj[v].push_back({u, wt});
    // }

    // int x = 5;

    int V=4;
    vector<vector<int>> adj[V] = {
        {{1, 1}, {3,2}}, 
        {{0, 1}, {2,4}}, 
        {{1, 4}, {3,3}}, 
        {{0, 2}, {2,3}}
    };

    int S=0;
    

    print(dijkstra1(V, adj, S));
    print(dijkstra2(V, adj, S));

    return 0;
}
