/*
399. Evaluate Division
[https://leetcode.com/problems/evaluate-division/description/]


You are given an array of variable pairs equations and an array of 
real numbers values, where equations[i] = [Ai, Bi] and values[i] 
represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string 
that represents a single variable.

You are also given some queries, where queries[j] = [Cj, Dj] 
represents the jth query where you must find the answer for Cj / Dj = 
?.

Return the answers to all queries. If a single answer cannot be 
determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the 
queries will not result in division by zero and that there is no 
contradiction.

Note: The variables that do not occur in the list of equations are 
undefined, so the answer cannot be determined for them.

 

Example 1:

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries 
= [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
note: x is undefined => -1.0
Example 2:

Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = 
[1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]
Example 3:

Input: equations = [["a","b"]], values = [0.5], queries = 
[["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]
*/



/*
derivation

a / b = 2
b / c = 3


lets model these as nodes in a graph

src --wt--> dst

value at src/ value at dst = wt of edge

a/b = 2

a -- 2 -- b
b -- 1/2 -- a


a--2--b--3--c

for a/c
    a--b--c is 2*3 = 6
*/

#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

double dfs(
    const string& curr,
    const string& target,
    unordered_map<string, vector<pair<string, double>>>& graph,
    unordered_set<string>& visited
) {
    if (curr == target)
        return 1.0;

    visited.insert(curr);

    for (auto& [nei, weight] : graph[curr]) {
        if (visited.count(nei))
            continue;

        double result = dfs(nei, target, graph, visited);

        if (result != -1.0)
            return weight * result; // chain multiplication
    }

    return -1.0;
}

vector<double> calcEquation(
    vector<vector<string>>& equations,
    vector<double>& values,
    vector<vector<string>>& queries
) {
    unordered_map<string, vector<pair<string, double>>> graph;

    // Build weighted directed graph
            // graph["a"] = {
            //     {"b", 2},
            //     {"d", 5}
            // };
    for (int i = 0; i < equations.size(); i++) {
        string a = equations[i][0];
        string b = equations[i][1];
        double value = values[i];

        graph[a].push_back({b, value});
        graph[b].push_back({a, 1.0 / value});
    }

    vector<double> ans;

    for (auto& query : queries) {
        string start = query[0];
        string target = query[1];

        // x,x none of them exist
        // or a,x
        if (!graph.count(start) || !graph.count(target)) {
            ans.push_back(-1.0);
            continue;
        }

        unordered_set<string> visited; //unset cuz we have no idea about size of input

        ans.push_back(dfs(start, target, graph, visited));
    }

    return ans;
}

/*
for E equations
and V unique nodes

to construct the graph
    O(E)

to run Q queries across graph(V+E)
O( Q*(V+E) )

time O(E) + O(Q*(V+E))
space
    O(V+E)
*/