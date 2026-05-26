#include <bits/stdc++.h>
using namespace std;

void dfs2(   int i, int j,
                int n, int m,
                string& current,
                vector<vector<int>> &grid,
                vector<string>& ans )
{        
    // 1. base case
    if(i==n-1 && j==m-1) {
        ans.push_back(current);
        return;
    }

    // 2. explore directions
    const int  di[] = {-1,  1,  0,  0};
    const int  dj[] = { 0,  0, -1,  1};
    const char dc[] = {'U','D','L','R'};

    for(int x=0; x<4; x++) {
        int next_i = i + di[x];
        int next_j = j + dj[x];
        
        if( next_i >=0 && next_i < n &&
            next_j >=0 && next_j < m &&
            grid[next_i][next_j] == 1)
        {
            grid[next_i][next_j] = 2;
            current.push_back(dc[x]);

            dfs2(next_i, next_j, n, m, current, grid, ans);

            current.pop_back();
            grid[next_i][next_j] = 1;
        }
    }
}


void dfs(int i, int j,
         int n, int m,
         string& current,
         vector<vector<int>> &grid, 
         vector<string>& ans) 
{
    // 1. base condition, end of maze
    if(i == n-1 && j == m-1) {
        ans.push_back(current);
        return;
    }

    // 2. explore    
    //      up    i-1,j+0
    //      down  i+1,j+0
    //      left  i+0,j-1
    //      right i+0,j+1
    int di[] = {-1,1,0,0};
    int dj[] = {0,0,-1,1};
    char dL[] = {'U', 'D', 'L', 'R'};
     

    for(int x=0; x<4; x++) {
        int next_i = i + di[x];
        int next_j = j + dj[x];

        if( next_i >= 0 && next_i <n &&
            next_j >= 0 && next_j <m &&
            grid[next_i][next_j] == 1)
        {
            // mark it to prevent infinite loops
            grid[next_i][next_j] = 2;
            current.push_back(dL[x]);

            dfs(next_i, next_j, n, m, current, grid, ans);

            // unmark
            current.pop_back();
            grid[next_i][next_j] = 1;
        }
    }

}

vector<string> findPath(vector<vector<int>> &grid) {
    
    vector<string> ans;
    int n = grid.size(), m = grid[0].size();

    // invalid starting and ending point
    if(grid[0][0] != 1 || grid[n-1][m-1] != 1) return ans;

    cout << "starging";

    string current = "";
    grid[0][0] = 2; // mark the first as visited
    dfs2(0, 0, n, m, current, grid, ans);

    return ans;
}

void printResults(const vector<string>& results) {
    for(auto single : results) {
        cout << "[ ";
        cout << single;
        cout << "]\n";
    }
}

// {1, 0, 0, 0}
// {1, 1, 0, 1} 
// {1, 1, 0, 0} 
// {0, 1, 1, 1}


// TODO
// use a vistied matrix
// interviewer may want no modifications to the original
// lexicographical order DLRU for directions

int main() {
    vector<vector<int>> grid = { {1, 0, 0, 0} , {1, 1, 0, 1}, {1, 1, 0, 0}, {0, 1, 1, 1} };
    // vector<vector<int>> grid = { {1, 0},{1, 0} };
    auto results = findPath(grid);
    printResults(results);
    return 0;
}