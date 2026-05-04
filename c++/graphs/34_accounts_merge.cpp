#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

class DisjointSet {
public:
    vector<int> parent, size;
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for(int i=0; i<n; i++) parent[i] = i;
    }

    int leader(int n) {
        if(parent[n] == n) return n;
        return parent[n] = leader(parent[n]);
    }

    bool same(int u, int v) {
        return leader(u) == leader(v);
    }

    void unionBySize(int u, int v) {
        u = leader(u);
        v = leader(v);

        if(u == v) return;
        if(size[u] < size[v]) {
            parent[u] = v;
            size[v] += size[u];
        }
        else{
            parent[v] = u;
            size[u] += size[v];
        }
    }
};

vector<vector<string>> accountsMerge(vector<vector<string>> accounts) {
    int n = accounts.size();
    DisjointSet ds(n);

    unordered_map<string, int> mpp;

    for(int i=0; i<n; i++) {
        for(int j=1; j<accounts[i].size(); j++) {
            string mail = accounts[i][j];
            
            if(mpp.count(mail)) {
                // duplicated mail not added
                // accounts merged
                ds.unionBySize(i, mpp[mail]);
            }
            else{
                mpp[mail] = i;
            }
        }
    }

    vector<string> sortedMails[n]; // this might have empty entries

    // iterate over mpp
    for(auto& it : mpp) {
        int merged = ds.leader(it.second);
        sortedMails[merged].push_back(it.first);
    }

    vector<vector<string>> ans;

    for(int i=0; i<n; i++) {
        if(sortedMails[i].size() == 0) continue;
        
        sort(sortedMails[i].begin(), sortedMails[i].end());

        vector<string> temp;

        temp.push_back(accounts[i][0]);

        for(auto mail : sortedMails[i]) {
            temp.push_back(mail);
        }

        ans.push_back(temp);
    }

    return ans;
}

int main() {
    return 0;
}