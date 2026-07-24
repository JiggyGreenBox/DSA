#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;


string findOrder(string dict[], int N, int K) {

    // asumptions
    // k starting alphabets
    // no missing
    // start counting at 0 using (char-'a')

    // 1. build adjacency list and indegree a the same time
    // 2. indegree
    vector<int> adj[K];
    vector<int> indegree(K,0);

    for(int i=1; i<N; i++) {

        string &s1 = dict[i-1];
        string &s2 = dict[i];

        int len = min(s1.size(), s2.size());
        int j=0;

        while(j<len && s1[j] == s2[j]) 
            j++;        

        if(j < len) {

            int u = s1[j] - 'a';
            int v = s2[j] - 'a';

            adj[u].push_back(v);
            indegree[v]++;
        }
        else if(s1.size() > s2.size()){

            // invalid case
            // ab came before abc
            return "";
        }        
    }

    // 3. topo
    queue<int> q;
    // vector<int> topo;
    string ans = "";
    for(int i=0; i<K; i++) {
        if(indegree[i] == 0) 
            q.push(i);
    }

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        // topo.push_back(node);
        ans += (node + 'a');
        ans += " ";

        for(int it : adj[node]) {
            indegree[it]--;
            if(indegree[it] == 0) q.push(it);
        }
    }    

    // Cycle exists    
    // if (ans.size() != K)
    if (ans.size() != (K*2))
        return "";

    return ans;
}

int main() {
    int N = 5, K = 4;
    string dict[N] = {
        "baa","abcd","abca","cab","cad"
    };

    // int N = 13;
    // int K = 4;
    // string dict[N] = {"c","bdbccbaacdc","badbddcdbd","ddd","adcbbcadd","adcbbcadd","adcbbcadd","aabcdcaccbcdbb","aaaaaccadcabddc","aaaaaccadcabddc","aaaaaccadcabddc","aaaaaccadcabddc","aaaaaccadcabddc"};

    cout << findOrder(dict, N, K) << endl;
    return 0;
}