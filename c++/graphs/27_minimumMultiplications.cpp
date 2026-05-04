#include <bits/stdc++.h>
using namespace std;


// i think this is a BFS problem
// we generate neighbour candidate
// we need to store results level wise
// as similar numbers will be generated

int minimumMultiplications(const vector<int> &arr,
                               int start, int end)
{
    queue<int> q;
    q.push(start);

    int step = 0;

    unordered_set<int> used;
    used.insert(start);

    while(!q.empty()) {
        int size = q.size();
        

        step++;
        while(size--) {
            int curr = q.front();
            q.pop();

            for(auto i : arr) {
                int res = (curr * i) % 100000;
                if(res == end) return step;

                if(res < end && used.find(res) == used.end()) {
                    used.insert(res);
                    q.push(res);
                }
            }
        }
    }
    return -1;
}

/*
since all nodes are mod 10000
the entire graph fits in 0..9999

use a normal queue and use the dist vector

*/
int minimumMultiplications_cannonical(const vector<int> &arr,
                               int start, int end)
{
    vector<int> dist(100000, INT_MAX);
    dist[start] = 0;

    queue<int> q;
    q.push(start);

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int i : arr) {
            int next = (i*node) % 100000;
            if(dist[node] + 1 < dist[next]) {
                dist[next] = dist[node] + 1;

                if(next == end) return dist[next];

                q.push(next);
            }
        }
    }

    return -1;
}


int main() {

    cout << minimumMultiplications({3,4,65}, 7, 66175) << endl;
    cout << minimumMultiplications_cannonical({3,4,65}, 7, 66175) << endl;
    
    cout << minimumMultiplications({2,5,7}, 3, 30) << endl;
    cout << minimumMultiplications_cannonical({2,5,7}, 3, 30) << endl;
    

    return 0;
}