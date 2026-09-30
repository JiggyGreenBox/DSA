#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

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

    int get_size(int n) {
        return size[leader(n)];
    }
};

int largestIsland(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    DSU ds(n*m);
    vector<vector<int>> visited(n, vector<int>(m, 0));

    int dx[] = {0, 0, 1,-1};
    int dy[] = {1,-1, 0, 0};

    int max_count = 0;

    // add existing 1's to DSU
    // get island information before processing 0's
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            // if(grid[i][j] == 1 && visited[i][j] == 0) {
            if(grid[i][j] == 1) {
                // visited[i][j] = 1;

                for(int k=0; k<4; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];

                    // if(nx>=0 && nx<n && ny>=0 && ny<m && grid[nx][ny] == 1 && visited[nx][ny] == 0) {
                    if(nx>=0 && nx<n && ny>=0 && ny<m && grid[nx][ny] == 1) {
                        // visited[nx][ny] = 1;
                        int next = nx*m + ny;
                        int curr = i*m + j;
                        ds.merge(next, curr);                        
                        max_count = max(max_count, ds.get_size(curr));
                    }
                }
            }
        }
    }

    // look if we can increase max_count
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(grid[i][j] == 0 && visited[i][j] == 0) {


                unordered_set<int> islands;
                for(int k=0; k<4; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];

                    
                    if(nx>=0 && nx<n && ny>=0 && ny<m && grid[nx][ny] == 1) {                        
                        int next = nx*m + ny;
                        // int curr = i*m + j;

                        islands.insert(ds.leader(next)); // add unique islands                        
                        
                    }
                }
                
                int new_count = 1;
                for(auto it : islands) {
                    new_count += ds.get_size(it);
                }
                max_count = max(max_count, new_count);
            }
        }
    }

    return max_count;
}


int largestIsland_cannonical(vector<vector<int>>& grid) {
    int n = grid.size();

    DSU ds(n*n);

    int dx[] = {0, 0, 1,-1};
    int dy[] = {1,-1, 0, 0};

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(grid[i][j] == 0) continue;             

             
            for(int k=0; k<4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                
                if(nx>=0 && nx<n && ny>=0 && ny<n && grid[nx][ny] == 1) {
                    int next = nx*n + ny;
                    int curr = i*n + j;
                    ds.merge(next, curr);
                }
            }            
        }
    }

    int ans = 0;

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(grid[i][j] == 1) continue;             

            unordered_set<int> comps;
            for(int k=0; k<4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                
                if(nx>=0 && nx<n && ny>=0 && ny<n && grid[nx][ny] == 1) {
                    int next = nx*n + ny;                    
                    comps.insert(ds.leader(next));
                }
            } 
            
            int size = 1;

            for(int root : comps)
                size += ds.get_size(root);

            ans = max(ans, size);
        }
    }

    // STEP 3: handle all-1 grid
    for(int i=0;i<n*n;i++)
        ans = max(ans, ds.get_size(i));

    return ans;
}

int main() {
    vector<vector<int>> grid = {{1,0},{0,1}};

    cout << largestIsland(grid) << endl;

    grid = {{1,1},{1,1}};

    cout << largestIsland(grid) << endl;

    return 0;
}