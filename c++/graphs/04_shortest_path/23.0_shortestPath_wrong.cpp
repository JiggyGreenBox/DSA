#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <queue>
using namespace std;


vector<int> shortestPath(int n, int m, vector<vector<int>> &edges) {
    // 1. construct adjacency list
    vector<vector<int>> adj[n+1];
    for(auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    // 2. priority queue
    using P = pair<int, vector<int>>;
    priority_queue<P, vector<P>, greater<P>> pq;

    // 3. we want to traverse in a greedy manner
    // and not go back to source nodes
    // we can check in our visited vector in the pair
    // we wont go to any of those nodes
    pq.push({0,{1}}); // [int wt, vec<int>{nodes}]

    // store best ans so far
    P ans = {INT_MAX,{}};

    while(!pq.empty()) {
        int wt = pq.top().first;
        auto visited = pq.top().second;
        pq.pop();

        int curr_node = visited.back();

        // path found
        if(curr_node == n) {
            // choose lower path weight
            if(wt < ans.first) {
                ans = {wt, visited};
            }
        }

        for(auto it : adj[curr_node]) {
            int adjNode = it[0];
            int adj_wt = it[1];

            // ensure node isnt used before
            if(find(visited.begin(), visited.end(), adjNode) == visited.end()) {
                visited.push_back(adjNode); // choose
                pq.push({wt + adj_wt, visited});
                visited.pop_back(); // unchoose
            }
        }
    }

    
    if(ans.first == INT_MAX) return {-1};

    vector<int> result;
    result.push_back(ans.first);
    result.insert(result.end(), ans.second.begin(), ans.second.end());
    return result;
}

void print(const vector<int>& v) {
    cout << "[ ";
    for(auto x : v) cout << x << " ";
    cout << "]\n";
}

int main() {

    int n = 5;
    vector<vector<int>> edges = {{1,2,2}, {2,5,5}, {2,3,4}, {1,4,1},{4,3,3},{3,5,1}};
    print(shortestPath(n, edges.size(), edges));
    return 0;
}