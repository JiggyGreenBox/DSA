#include <iostream>
#include <queue>
#include <vector>
using namespace std;


/*
find valid_cells

int valid_cells=0
for row
    for col
        find 1
            int valid_cells += dfs/bfs

return valid_cells
*/

/*
keep a count or return a count
early exit

int dfs
    int res=0;
    mark visited
    for 4 dirs:
        if not visited
            neighb = dfs()
            if(neighb == 0) return 0
            res += neighb
    return res;
*/

/* THIS LOGIC WRONG
        BECAUSE IF A BOUNDARY TILE WAS VISITED
        EARLY RETURN WITH 0
        DIDNT EXPLORE REMAINING CONNECTED TILES

    WE NEED TO VISIT ALL ENCLAVES
    AND MARK BOUNDARY TOUCHING ENCLAVES AS FALSE

    ANOTHER APPROACH IS TOO FOOD FILL ENCLAVES TOUCHING BORDER
    THEN COUNT ENCLAVES AFTER THAT
*/


/*
we have 3 approaches
    1. convert grid's connected 1's from the boundary to 0, count remaining 1's
    2. recursive dfs for enclaves with bool, but when boundary is met, mark as false, count only true's
    3. use a queue to traverse 1's from boundary in the visited matrix, then count 1's from non visited matrix

*/

int dfs1(int x, int y, vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    grid[x][y] = 0;

    int dx[] = {0, 0, 1,-1};
    int dy[] = {1,-1, 0, 0};

    for(int k=0; k<4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if(nx>=0 && nx<m && ny>=0 && ny<n && grid[nx][ny] == 1) {
            dfs1(nx, ny, grid);
        }
    }
}
// 1. convert grid's connected 1's from the boundary to 0, count remaining 1's
int numberOfEnclaves1(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    for(int i=0; i<m; i++) {
        if(grid[i][0]   == 1) dfs1(i, 0,   grid);
        if(grid[i][n-1] == 1) dfs1(i, n-1, grid);
    }

    for(int j=0; j<n; j++) {
        if(grid[0][j]   == 1) dfs1(0,   j, grid);
        if(grid[m-1][j] == 1) dfs1(m-1, j, grid);
    }

    int count = 0;
    for(auto& row : grid) {
        for(int cell : row) {
            if(cell == 1) count++;
        }
    }
    return count;
}


int dfs2(int x, int y, 
         vector<vector<int>> &grid, 
         vector<vector<int>> &visited, 
         bool& valid) 
{
    int m = grid.size();
    int n = grid[0].size();

    visited[x][y] = 1;
    int count = 1;

    if(x==0 || x == m-1 || y == 0 || y == n-1) valid = false;

    int dx[] = {0, 0, 1,-1};
    int dy[] = {1,-1, 0, 0};

    for(int k=0; k<4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if( nx>=0 && nx<m && ny>=0 && ny<n && 
            grid[nx][ny] == 1 && !visited[nx][ny]) 
        {
            count += dfs2(nx, ny, grid, visited, valid);
        }
    }
    return count;
}
// 2. recursive dfs for enclaves with bool, but when boundary is met, mark as false, count only true's
// we dont want to modify the original grid
int numberOfEnclaves2(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> visited(m, vector<int>(n, 0));

    int total = 0;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(grid[i][j] == 1 && !visited[i][j]) {
                bool isEnclave = true;
                int size = dfs2(i, j, grid, visited, isEnclave);
                if(isEnclave) total += size;
            }
        }
    }

    return total;
}

// 3. use a queue to traverse 1's from boundary in the visited matrix, 
//    then count 1's from non visited matrix

// use the visited matrix wisely
// from boundary land visit connected land
// after this is complete
// unvisited count of land is the answer
void bfs3(vector<vector<int>> &grid, 
          vector<vector<int>> &visited, 
          queue<pair<int,int>>& q) 
{
    int m = grid.size();
    int n = grid[0].size();

    int dx[] = {0, 0, 1,-1};
    int dy[] = {1,-1, 0, 0};

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(int k=0; k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if( nx>=0 && nx<m && ny>=0 && ny<n &&
                grid[nx][ny] == 1 && !visited[nx][ny])
            {
                visited[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
    }    
}

int numberOfEnclaves3(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> visited(m, vector<int>(n, 0));

    queue<pair<int, int>> q;
    
    // push boundary 1's
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if( (i==0 || i==m-1 || j==0 || j==n-1) 
                && grid[i][j] == 1 )
            {
                visited[i][j] = 1;
                q.push({i,j});
            }
        }        
    }

    bfs3(grid, visited, q);
    
    // count enclaves
    int count = 0;
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(grid[i][j] == 1 && !visited[i][j]) count++;
        }
    }
    return count;
}

/*
NOTES ON VISITED MATRIX

    BFS → mark when pushing
    DFS → mark when entering

    sometimes we can skip the visited matrix by using the grid itself

        grid[nx][ny] = 0;   // acts as visited
        q.push(...)
*/

int main() {
    return 0;
}