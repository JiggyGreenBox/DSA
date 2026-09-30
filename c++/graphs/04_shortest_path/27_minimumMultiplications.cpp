#include <bits/stdc++.h>
using namespace std;



/*
since all nodes are mod 10000
the entire graph fits in 0..9999

use a normal queue and use the dist vector

*/
int minimumMultiplications_cannonical(const vector<int> &arr,
                               int start, int end)
{
    vector<int> dist(100000, -1);
    dist[start] = 0;

    queue<int> q;
    q.push(start);

    while(!q.empty()) {

        int curr = q.front();
        q.pop();

        if(curr == end) 
            return dist[curr];

        for(int i : arr) {

            int next = (i*curr) % 100000;

            // vector<int> dist(100000, INT_MAX);
            // if(dist[curr] + 1 < dist[next]) {                
            //     dist[next] = dist[curr] + 1;                
            //     q.push(next);
            // }
            if(dist[next] == -1) {
                dist[next] = dist[curr] + 1;
                q.push(next);
            }
        }
    }

    return -1;
}

/*
time
    M = 100000
    N = nums size
    M states × N multipliers
    = O(M × N)

space
    dist → O(M)
    queue → O(M)
*/

int main() {

    cout << minimumMultiplications_cannonical({3,4,65}, 7, 66175) << endl;
    
    cout << minimumMultiplications_cannonical({2,5,7}, 3, 30) << endl;
    

    return 0;
}