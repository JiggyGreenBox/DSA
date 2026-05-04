#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// if O-island is surrounded  by X
// change to X
// any O-island touching the boundary cannot be surrounded
// visit boundary O's
// the remaining O's are surrounded
// vector<vector<char>> fill(vector<vector<char>> mat) {
//     vector<vector<int>> visited;

//     for each border mat
//         if == 'O'
//             q.push
//             visited[i][j] = 1;

//     while q
//         x,y = q
//         q.pop

//         int dx
//         int dy

//         if valid && !visited
//             visited[nx][ny] = 1;

//     result = grid
//     for each grid
//         if == O and not visited
//             result[][] = X
            
// }

// Surrounded Regions
// You are given a matrix mat of size N x M where each cell contains either 'O' or 'X'.

// Your task is to replace all 'O' cells that are completely surrounded by 'X' with 'X'.



// Rules:

// An 'O' (or a group of connected 'O's) is considered surrounded if it is not connected to any border of the matrix.
// Two 'O' cells are considered connected if they are adjacent horizontally or vertically (not diagonally).
// A region of connected 'O's that touches the border (i.e., first row, last row, first column, or last column) is not surrounded and should not be changed.
vector<vector<char>> fill2(vector<vector<char>> mat) {
    int m = mat.size();
    int n = mat[0].size();

    vector<vector<char>> res(m, vector<char>(n, 'y')); // need a third value
    queue<pair<int,int>> q;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(mat[i][j] == 'X') res[i][j] = 'X';
            if((i==0 || i == m-1 || j == 0 || j == n-1) && mat[i][j] == 'O') {
                res[i][j] = 'O';
                q.push({i,j});
            }
        }
        
    }

    int dx[] = {0, 0,-1, 1};
    int dy[] = {1,-1, 0, 0};
    

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(int k=0; k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if(nx>=0 && nx<m && ny>=0 && ny<n && res[nx][ny] == 'y') {
                res[nx][ny] = 'O';
                q.push({nx, ny});
            }
        }
    }

    // any remaining y is a surrounded O
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(res[i][j] == 'y') res[i][j] = 'X';
        }
    }
    return res;
}

vector<vector<char>> fill(vector<vector<char>> mat) {
    int m = mat.size();
    int n = mat[0].size();

    queue<pair<int,int>> q;

    // Step 1: push all boundary O's
    for(int i = 0; i < m; i++) {
        if(mat[i][0] == 'O') {
            q.push({i,0});
            mat[i][0] = '#';
        }
        if(mat[i][n-1] == 'O') {
            q.push({i,n-1});
            mat[i][n-1] = '#';
        }
    }

    for(int j = 0; j < n; j++) {
        if(mat[0][j] == 'O') {
            q.push({0,j});
            mat[0][j] = '#';
        }
        if(mat[m-1][j] == 'O') {
            q.push({m-1,j});
            mat[m-1][j] = '#';
        }
    }

    int dx[] = {0,0,1,-1};
    int dy[] = {1,-1,0,0};

    // Step 2: BFS → mark all safe O's
    while(!q.empty()) {
        auto [x,y] = q.front(); q.pop();

        for(int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if(nx>=0 && nx<m && ny>=0 && ny<n && mat[nx][ny] == 'O') {
                mat[nx][ny] = '#';
                q.push({nx, ny});
            }
        }
    }

    // Step 3: flip surrounded + restore safe
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(mat[i][j] == 'O') mat[i][j] = 'X';  // surrounded
            if(mat[i][j] == '#') mat[i][j] = 'O';  // safe
        }
    }

    return mat;
}

void print(const vector<vector<char>>& mat) {
    for(auto& row : mat) {
        cout << "[ ";
        for(auto cell : row) cout << cell << " ";
        cout << "]\n";
    }
    cout << "\n";
}
int main() {

    vector<vector<char>> mat = {{'X', 'X', 'X'}, {'X', 'O', 'X'}, {'X', 'X', 'X'}};
    print(mat);
    print(fill2(mat));

    mat = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
    print(mat);
    print(fill2(mat));

    return 0;
}