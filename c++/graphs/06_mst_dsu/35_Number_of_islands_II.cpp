#include <iostream>
#include <vector>
using namespace std;

/*
since this the first problem involving a 2d matrix
we have to figure out how to store this in a DSU

from gemini:
we flatten the 2D array into 1D
    [m*n]
        [i][j] -> i*m + j

        [0][3] -> 3
        [1][3] -> 3+3 = 6
        [2][2] -> 6+2 = 8

*/
class DSU {
public:
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n);
        size.resize(n,1);
        for(int i=0; i<n; i++) parent[i] = i;
    }

    int leader(int n) {
        if(parent[n] == n) return n;
        return parent[n] = leader(parent[n]);
    }
    
    bool same(int u, int v) {
        return leader(u) == leader(v);
    }

    void merge(int u, int v) {
        u = leader(u);
        v = leader(v);
        if(u == v) return;

        if(size[u] < size[v]) {
            parent[u] = v;
            size[v] += size[u];
        }
        else {
            parent[v] = u;
            size[u] += size[v];
        }
    }
};

vector<int> numOfIslands(int n, int m, vector<vector<int>> &A) {

    DSU ds(n*m);

    vector<vector<int>> grid(n, vector<int>(m, 0));
 
    int dx[] = {0, 0,-1, 1};
    int dy[] = {1,-1, 0, 0};    


    int size = A.size();
    vector<int> res(size);
    int count = 0;

    for(int i=0; i<size; i++) {
        int x = A[i][0];
        int y = A[i][1];

        if(grid[x][y] == 0) {
            grid[x][y] = 1;
            count++;
        }
        

        for(int k=0; k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            // 
            if(nx>=0 && nx<n && ny>=0 && ny<m && grid[nx][ny] == 1) {
                int nei = (nx*m) + ny; 
                int curr = (x*m) + y;
                if(!ds.same(curr, nei)) {
                    ds.merge(curr, nei);
                    count--;
                }                
            }
        }
            
        res[i] = count;
    }

    return res;
}

void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

int main() {
    vector<vector<int>> A = {{1,1},{0,1},{3,3},{3,4}};
    int n = 4;
    int m = 5;
    print(numOfIslands(n, m, A));


    n = 4; m = 5;
    A = {{0,0},{0,0},{1,1},{1,0},{0,1},{0,3},{1,3},{0,4}, {3,2}, {2,2},{1,2}, {0,2}};

    print(numOfIslands(n, m, A));

    return 0;
}