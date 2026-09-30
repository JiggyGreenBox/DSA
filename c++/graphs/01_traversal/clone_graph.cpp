/*
133. Clone Graph
    [https://leetcode.com/problems/clone-graph/description/]

Given a reference of a node in a connected undirected graph.

Return a deep copy (clone) of the graph.

Each node in the graph contains a value (int) and a list (List[Node]) 
of its neighbors.

class Node {
    public int val;
    public List<Node> neighbors;
}
 

Test case format:

For simplicity, each node's value is the same as the node's index 
(1-indexed). For example, the first node with val == 1, the second 
node with val == 2, and so on. The graph is represented in the test 
case using an adjacency list.

An adjacency list is a collection of unordered lists used to 
represent a finite graph. Each list describes the set of neighbors of 
a node in the graph.

The given node will always be the first node with val = 1. You must 
return the copy of the given node as a reference to the cloned graph.

 

Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node 
(val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node 
(val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node 
(val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node 
(val = 3).

*/


/*
133. Clone Graph
input is an adjacency list

if we knew all the nodes beforehand
    they also mentioned the rules for node values
    we can create all of the nodes

but here we are only given the starting node
so we have to discover the graph using dfs / bfs
    we will create the nodes, if not in our map
        our map <og, clone>

        mpp<Node*,Node*>
*/

#include <list>
#include <unordered_map>
#include <queue>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

Node* cloneGraph(Node* node) {
    if (!node) return nullptr;

    unordered_map<Node*, Node*> mp;

    queue<Node*> q;

    // first node no check
    mp[node] = new Node(node->val);
    q.push(node);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        for (Node* nei : curr->neighbors) {

            // check if created
            if (!mp.count(nei)) {
                // new
                mp[nei] = new Node(nei->val);
                q.push(nei); // process its neighbours next iter
            }

            mp[curr]->neighbors.push_back(mp[nei]);
        }
    }

    return mp[node]; // cloned head
}