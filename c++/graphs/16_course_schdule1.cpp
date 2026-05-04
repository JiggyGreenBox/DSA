#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    bool canFinish(int N, vector<vector<int>> arr) {
        // return topo.size() == N

        // 1. build adjacency list
        vector<int> adj[N];
        for(auto& r : arr) {
            adj[r[1]].push_back(r[0]);
        }

        // 2. calculate indegree
        vector<int> indegree(N, 0);
        for(int i=0; i<N; i++) {
            for(int nei : adj[i]) {
                indegree[nei]++;
            }
        }

        // 3. push degree==0
        queue<int> q;
        for(int i=0; i<N; i++) {
            if(indegree[i] == 0) q.push(i);
        }

        // 4. topo sort
        vector<int> topo;
        while(!q.empty()) {
            int node = q.front();
            q.pop();

            topo.push_back(node);

            for(int nei : adj[node]) {
                indegree[nei]--;
                if(indegree[nei] == 0) q.push(nei);
            }
        }

        return topo.size() == N;
    }
};