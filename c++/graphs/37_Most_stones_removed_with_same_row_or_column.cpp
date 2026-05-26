#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
/*
There are n stones at integer coordinate points on a 2D plane, with
at most one stone per coordinate point. Some stones need to be
removed.A stone can be removed if it shares the same row or the same
column as another stone that has not been removed.

Given an array of stones of length n where stones[i] = [xi, yi]
represents the location of the ith stone, return the maximum
possible number of stones that can be removed.
*/

/*
why did this code below fail?

because of chain of command 
1
1 1 1

    2 removals
        1
        - 1 1

        1
        - - 1

    3 removals
        1
        - 1 1

        -
        - 1 1

        -
        - - 1

so the order mattered

instead lets connect components using row and col
    then the number of removals is (total-in-component - 1)
    because the component will the last element not connected to anyone

    c1-1
    c2-1
    c3-1
    c4-1

    if all these are added, all c's == n
    and all -1's == comp-count

    so ans = (n - num_comps)
*/

int maxRemove_wrong(vector<vector<int>>& stones, int n) {
    unordered_map <int, int> mp_r;
    unordered_map <int, int> mp_c;

    for(auto& s : stones) {
        mp_r[s[0]]++;
        mp_c[s[1]]++;
    }

    int count = 0;
    for(auto& s : stones) {
        if(mp_r[s[0]] > 1 || mp_c[s[1]] > 1) {
            mp_r[s[0]]--;
            mp_c[s[1]]--;
            ++count;
        }
    }

    return count;
}

class DSU {
public:
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for(int i=0; i<n; i++) parent[i] = i;
    }

    int leader(int n) {
        if(parent[n] != n) {
            parent[n] = leader(parent[n]);
        }
        return parent[n];
    }

    bool same(int u, int v) {
        return leader(u) == leader(v);
    }

    bool merge(int u, int v) {
        u = leader(u), v = leader(v);
        if(u == v) return false;
        // v is the larger set
        if(size[u] > size[v]) swap(u,v);
        parent[u] = v;
        size[v] += size[u];
        return true;
    }

    int get_size(int n) {
        return size[leader(n)];
    }
};

int maxRemove(vector<vector<int>>& stones, int n) {
    int max_row = 0, max_col = 0;
    for(auto& s : stones) {
        max_row = max(max_row, s[0]);
        max_col = max(max_col, s[1]);
    }

    DSU ds(max_row + max_col + 2);

    unordered_set<int> nodes;
    for(auto& s : stones) {
        
        int row = s[0];
        int col = s[1] + max_row + 1;

        ds.merge(row, col);

        nodes.insert(row);
        nodes.insert(col);
    }

    int components = 0;
    for(auto it : nodes) {
        if(ds.leader(it) == it) 
            components++;
    }
    return n - components;
}

int main() {
    return 0;
}