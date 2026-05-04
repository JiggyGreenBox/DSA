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

    // 1. build adjacency list        
    vector<int> adj[K];

    for(int i=1; i<N; i++) {

        string s1 = dict[i-1];
        string s2 = dict[i];

        int len = min(s1.size(), s2.size());
        int j=0;

        while(j<len && s1[j] == s2[j]) j++;

        // invalid case
        // ab came before abc
        if(j == len && s1.size() > s2.size()) return "";

        // same string error
        // adj[s1[j] - 'a'].push_back(s2[j] - 'a');

        if(j< len) {
            adj[s1[j] - 'a'].push_back(s2[j] - 'a');
        }
        else{
            int x = 5;
        }        
    }
    
    // 2. indegree
    vector<int> indegree(K,0);
    for(int i=0; i<K; i++) {
        for(int it : adj[i]) {
            indegree[it]++;
        }
    }

    // 3. topo
    queue<int> q;
    // vector<int> topo;
    string res = "";
    for(int i=0; i<K; i++) {
        if(indegree[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        // topo.push_back(node);
        res += (node + 'a');
        res += " ";

        for(int it : adj[node]) {
            indegree[it]--;
            if(indegree[it] == 0) q.push(it);
        }
    }

    // string res = "";
    // for(int i=0; i<topo.size(); i++) {
    //     if(i>0) res += " ";
    //     res += topo[i]+'a';
    // }

    return res;
}

int main() {
    // int N = 5, K = 4;
    // string dict[N] = {
    //     "baa","abcd","abca","cab","cad"
    // };

    int N = 13;
    int K = 4;
    string dict[N] = {"c","bdbccbaacdc","badbddcdbd","ddd","adcbbcadd","adcbbcadd","adcbbcadd","aabcdcaccbcdbb","aaaaaccadcabddc","aaaaaccadcabddc","aaaaaccadcabddc","aaaaaccadcabddc","aaaaaccadcabddc"};

    cout << findOrder(dict, N, K) << endl;
    return 0;
}