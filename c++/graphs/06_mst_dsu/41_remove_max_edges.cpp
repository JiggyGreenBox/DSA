// Remove Max Number of Edges            LC 1579

#include <iostream>
#include <vector>
using namespace std;


/*
we have edges for alice, bob, and common


common edges allow both bob and alice to travel

we want to see if there are any edges we can remove that
still allow bob and alice to travel the entire graph

if we use a DSU and if only 1 component exists
after all edges are processed then the entire graph is reachable

make a DSU for alice and 1 for bob


instead of thinking which edges to REMOVE
think which edges are required to KEEP

start with common edges
    we sort the edges in reverse
    
try to use these edges for both alice and bob

then move to user edges
    if it creates a cycle, that means we can reach the node
    without this edge
        can remove

*/ 


class DSU {
    private:
        vector<int> parent, size;

    public:
        DSU(int n) {
            parent.resize(n+1);
            size.resize(n+1, 1);

            for(int i=0; i<=n; i++) {
                parent[i] = i;
            }
        }

        int find(int x) {
            if(parent[x] == x)
                return x;

            return parent[x] = find(parent[x]); // path compression
        }

        bool unite(int x, int y) {
            x = find(x);
            y = find(y);

            if(x == y)
                return false;

            if(size[x] < size[y])
                swap(x, y);

            parent[y] = x;
            size[x] += size[y];

            return true;
        }

        int num_components() {
            int count = 0;
            for(int i=1; i<parent.size(); i++) {
                if(parent[i] == i)
                    count++;
            }
            return count;
        }
};

class Solution {
    public:
        int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
            DSU alice(n), bob(n);
            
            int removals = 0;

            // edges[i] = [typei, ui, vi]
            for(auto &e : edges) {
                // process common edges firs
                if(e[0] == 3) {
                    bool alice_used = alice.unite(e[1], e[2]);
                    bool bob_used = bob.unite(e[1], e[2]);    
                    
                    if(!alice_used && !bob_used)
                        removals++;
                }
            }

            
            for(auto &e : edges) {

                int type = e[0];
                int u = e[1];
                int v = e[2];
                
                // alice edges
                if(type == 1) {
                    if(!alice.unite(u, v))
                        removals++;
                }

                // bob edges
                else if(type == 2) {
                    if(!bob.unite(u, v))
                        removals++;
                }
            }

            // check if all nodes are reachable
            // components == 1
            if(alice.num_components() != 1 || bob.num_components() != 1)
                return -1;

            return removals;
        }


};

int main() {

    Solution sol;

    int n = 4; 
    vector<vector<int>> edges = {{3,1,2},{3,2,3},{1,1,4},{2,1,4}};
    auto x = sol.maxNumEdgesToRemove(n, edges); // 0


    n = 4; edges = {{3,1,2},{3,2,3},{1,1,3},{1,2,4},{1,1,2},{2,3,4}};
    x = sol.maxNumEdgesToRemove(n, edges); // 2

    n = 4; edges = {{3,2,3},{1,1,2},{2,3,4}};
    x = sol.maxNumEdgesToRemove(n, edges);

    return 0;
}

