#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
using namespace std;

int findCity(int n, int m, vector<vector<int>>& edges,
	             int distanceThreshold)
{
    // Given the array edges where edges[i] = [from.i, to.i,weight.i]
    
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

    for(auto &e : edges) {
        dist[e[0]][e[1]] = e[2];
        dist[e[1]][e[0]] = e[2];
    }

    for(int i=0; i<n; i++) dist[i][i] = 0;

    // floyd warshall
    for(int k=0; k<n; k++) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) continue;

                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // build result
    // map<int, vector<int>> mp;
    // for(int i=0; i<n; i++) {
    //     int count = 0;
    //     for(int j=0; j<n; j++) {
            // if(i != j && dist[i][j] <= distanceThreshold) count++;
    //     }
    //     mp[count].push_back(i);
    // }

    // return (*mp.begin()).second.back();

    // build result
    int city = -1;
    int minReach = INT_MAX;

    for(int i=0;i<n;i++){

        int count = 0;

        for(int j=0;j<n;j++){
            if(i != j && dist[i][j] <= distanceThreshold)
                count++;
        }

        if(count <= minReach){
            minReach = count;
            city = i;  // choose larger index on tie
        }
    }

    return city;
}

int main() {
    vector<vector<int>> edges = {{0,1,1},{0,2,3}};
    int n = 3;
    int d = 2;
    
    cout << findCity(n, edges.size(), edges, d) << endl;

    n=4;
    edges = {{0,1,3},{1,2,1},{1,3,4},{2,3,1}};
    d = 4;
    cout << findCity(n, edges.size(), edges, d) << endl;

    return 0;
}