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
        auto [currDist, currNode] = pq.top();
        pq.pop();

        if(currDist > dist[currNode]) 
            continue; // why this line?
            // Without it, you may process the same vertex many times.
            // With it, every outdated entry is discarded immediately.

        for(const auto &edge : adj[currNode]) {
            int nextNode = edge[0];
            int nextWeight = edge[1];

            int newDist = currDist + nextWeight;

            if(newDist < dist[nextNode]) {
                dist[nextNode] = newDist;
                pq.push({newDist, nextNode});
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
        auto [currDist, currNode] = *(st.begin());        
        st.erase(st.begin());

        for(const auto &edge : adj[currNode]) {
            
            int nextNode = edge[0];
            int weight = edge[1];

            int newDist = currDist + weight;
            
            if(newDist < dist[nextNode]) {

                if(dist[nextNode] != 1e9)
                    st.erase({dist[nextNode], nextNode});

                dist[nextNode] = newDist; 
                st.insert({newDist, nextNode});
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
