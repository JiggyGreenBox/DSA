#include <bits/stdc++.h>
using namespace std;


/*
Word Search
[https://leetcode.com/problems/word-search/description/]

Given an m x n grid of characters board and a string word, return 
true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent 
cells, where adjacent cells are horizontally or vertically 
neighboring. The same letter cell may not be used more than once.


*/

bool backtrack( int idx, // next index to look for
                int i,
                int j,
                const string& word, 
                vector<vector<char>>& board)
{
    // base condition
    if(idx == word.size()) return true;

    if( i < 0 || i >= board.size()    || 
        j < 0 || j >= board[0].size() || 
        board[i][j] != word[idx])
    {
        return false;
    } 

    // we need to mark the char as visited, before the recursion tree
    char temp = board[i][j];
    board[i][j] = '#';

    bool found =    backtrack(idx+1, i-1, j, word, board) || // up
                    backtrack(idx+1, i+1, j, word, board) || // down
                    backtrack(idx+1, i, j-1, word, board) || // left
                    backtrack(idx+1, i, j+1, word, board);   // right

    board[i][j] = temp;
    return found;
}

bool exist(vector<vector<char>>& board, string word) {

    if(word.empty()) return false;

    // find the starting point
    // process each recursion char by char
    // 4 possible directions
    // up, down, left, right
    
    for(int i=0;i<board.size();i++){
        // cout << "[ ";
        for(int j=0;j<board[0].size();j++){
            // cout << board[i][j] << " ";
            // if(board[i][j] == word[0]){
                if(backtrack(0, i, j, word, board)){
                    return true;
                }
            // }
        }        
        // cout << "]" << endl;
    }
    return false;
}

// =======================================
bool dfs(int idx, 
        int x, int y, 
        vector<vector<char>>& board, 
        string &word, 
        vector<vector<bool>> &visited
) {

    if(idx == word.size() - 1)
        return true;    

    int dx[] = {0, 0,-1, 1};
    int dy[] = {1,-1, 0, 0};

    int r = board.size();
    int c = board[0].size();

    visited[x][y] = true;

    // char temp = board[r][c];
    // board[r][c] = '#';  // mark as visited

    for(int i=0; i<4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if( nx>=0 && nx<r && 
            ny>=0 && ny <c && 
            !visited[nx][ny] &&
            board[nx][ny] == word[idx+1]
        ) {            
            if(dfs(idx + 1, nx, ny, board, word, visited))
                return true;
        }
    }

    visited[x][y] = false;
    // board[r][c] = temp; // undo

    return false;
}

bool exist(vector<vector<char>>& board, string word) {
    int r = board.size();
    int c = board[0].size();

     vector<vector<bool>> visited(r, vector<bool>(c, false));

    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(board[i][j] == word[0]) {
                if(dfs(0, i, j, board, word, visited))
                    return true;
            }
        }
    }
    return false;
}
// =======================================


void print(bool exists){
    if(exists) cout << "word exists" << endl;
    else cout << "does not exist" << endl;
}

// [ A B C E ]
// [ S F C S ]
// [ A D E E ]

int main() {
    vector<vector<char>> board = { {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'} };
    print(exist(board, "ABCCED"));
    // print(exist({ {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'} }, "SEE"));
    return 0;
}