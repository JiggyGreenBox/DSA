/*
============================================
nov 26
    last nov 25
============================================
Problem 1
============================================
Problem 1
Given a directed graph with n vertices and m edges, determine whether 
the graph contains a cycle.

Constraints:
- The graph may be disconnected.
- There may be multiple components.
- Return true if any component contains a cycle.
Start from scratch:
1. What's your brute-force or initial approach?
2. How would you optimize it?
3. Explain the reasoning before writing C++ code.

derivation / approach
    the graph is directed 
        so we cant just check if a node was previously visited

    is the brute force
        to perform dfs from every possible node?
    
    we need a visited and path visited vector

    time complexity
        O(V+E) time to visit 
        space
            O(V+E) adj list
            O(V) vis
            O(V) pathvis
bool helper(int node, 
    vector<vector<int>> &adj, 
    vector<int> &vis, 
    vector<int> &pathvis) 
{
    if(vis[node])
        return false;

    vis[node] = true;
    pathvis[node] = true;

    for(int nei : adj[node]) {
        if(!vis[nei]) {
            if(helper(nei, adj, vis, pathvis))
                return true;
        }
        else if(pathvis[nei]) {
            return true; // cycle found
        }
    }

    pathvis[node] = false;

    return false;
}

bool isCycle(int n, vector<vector<int>> edges) {
    vector<vector<int>> adj(n);

    for(auto &e : edges) {
        adj[e[0]].push_back(e[1]);        
    }

    vector<int> vis(n, 0);
    vector<int> pathvis(n, 0);
    for(int i=0; i<n; i++) {
        if(!vis[i]) {
            if(helper(i, adj, vis, pathvis))
                return true;
        }

    }
    return false;
}

Suppose the graph is directed and you need to detect a cycle, but you 
cannot use recursion because the graph might have 200,000 vertices.

kahns topo sort

bool isCycle(int n, vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);

    for(auto &e : edges) {
        int u = e[0];
        int v = e[1];

        adj[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;

    for(int i = 0; i < n; i++) {
        if(indegree[i] == 0)
            q.push(i);
    }

    int processed = 0;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        processed++;

        for(int nei : adj[node]) {
            indegree[nei]--;

            if(indegree[nei] == 0)
                q.push(nei);
        }
    }

    return processed != n;
}


============================================
Problem 2
============================================
Combination Sum II (LC 40)
Given an array of candidate numbers and a target, return all unique 
combinations where the chosen numbers sum to the target.

Rules:
- Each candidate can be used at most once.
- The solution must not contain duplicate combinations.
- The candidates may contain duplicates.

candidates = {10, 1, 2, 7, 6, 1, 5};
target = 8;

// Output:
{
    {1, 1, 6},
    {1, 2, 5},
    {1, 7},
    {2, 6}
}

candidates = {2, 5, 2, 1, 2};
target = 5;

// Output:
{
    {1, 2, 2},
    {5}
}


revision questions
    how to know when we have recursion problems, vs when we have dp problems
        dp has a pick and skip approach

    here we need to first sort
        so that duplicates are next to each other

    {2, 5, 2, 1, 2}
    {1, 2, 2, 2, 5}

    f(idx, sum, curr, res)
        if(sum == 0)
            res.push(curr)

        for(i=idx, i<n; i++)

            if(i>idx && num[i] == num[i-1])
                continue

            curr.push(nums[i])
            f(i+1, ..)
            curr.pop_back

        
    time complexity
        2^n time? not sure
        n aux space
        n stack
*/
#include <vector>
#include <algorithm>
using namespace std;

void dfs(
    int idx, 
    vector<int> &nums, 
    int sum, 
    vector<int> &curr, 
    vector<vector<int>> &res) 
{
    if(sum == 0) {
        res.push_back(curr);
        return;
    }

    int n = nums.size();

    for(int i=idx; i<n; i++) {

        if(i>idx && nums[i] == nums[i-1])
            continue; // skip duplicates at same rec level

        if(nums[i] > sum)
            continue;

        curr.push_back(nums[i]);
        dfs(i+1, nums, sum - nums[i], curr, res);
        curr.pop_back();
    }

}

vector<vector<int>> combination_sum(vector<int> &nums, int target) {
    sort(nums.begin(), nums.end());

    vector<int> curr;
    vector<vector<int>> res;
    dfs(0, nums, target, curr, res);
    return res;
}


int main() {
    
    vector<int> nums = {2, 5, 2, 1, 2};
    int target = 5;

    auto x = combination_sum(nums, target);

    nums = {10, 1, 2, 7, 6, 1, 5};
    target = 8;
    x = combination_sum(nums, target);


    return 0;
}

