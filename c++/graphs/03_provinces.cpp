// #include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution{
public:
    int numProvinces(vector<vector<int>> adj) {
        int n = adj.size();        

        vector<int> visited(n, 0);
        int provinces = 0;
        for(int i=0; i<n; i++) {
            if(!visited[i]) {
                queue<int> q;
                q.push(i);
                visited[i] = 1;

                while(!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    for(int j=0; j<n; j++) {
                        if(adj[node][j] == 1 && !visited[j]){
                            visited[j] = 1;
                            q.push(j);
                        }
                    }
                }

                provinces++;
            }
        }
        return provinces;
    }
};
