#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;


/*
Time:  O(V³)
Space: O(V²)

So it is only practical when:
     V ≤ ~400

*/
void shortestDistance(vector<vector<int>>&matrix) {
    int V = matrix.size();
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX));

    for(int k=0; k<V; k++) {
        for(int i=0; i<V; i++) {
            for(int j=0; j<V; j++) {

                if(matrix[i][k] == INT_MAX || matrix[k][j] == INT_MAX)
                    continue;

                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
}

int main() {
    return 0;
}

class Solution {
public:
	void shortestDistance(vector<vector<int>>&matrix) {
        int n = matrix.size();
        for(int k=0; k<n; k++) {
            for(int i=0; i<n; i++) {
                for(int j=0; j<n; j++) {
                    if(matrix[i][k] == -1 || matrix[k][j] == -1) {
                        continue;                        
                    }

                    // first time
                    if(matrix[i][j] == -1) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                    // update time
                    else{
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }                    
                }
            }
        }
	}
};