/*
============================================
oct 10
    last oct 9
============================================

S3 — Problem 1 of 3

Remove Invalid Parentheses
Medium+

From your sheet: 04_partition/17_remove_invalid_parentheses.cpp
Given a string s containing parentheses and lowercase English 
letters, remove the minimum number of parentheses so that the 
resulting string is valid.
Return all possible results. The order of the results does not matter.
Example 1
Input:  "()())()"
Output: ["(())()", "()()()"]

Input:  "(a)())()"
Output: ["(a())()", "(a)()()"]


derivation
    we need to remove invalid parenthesis to make a valid string
    we could try to pick/ skip every parenthesis
        2^n
    
    but it is better to find imbalanced parenthesis first
        then its 2^unbalanced choices

    for now my approach to duplicates is to use a set

complexity
    2^unbalance choices
    n copies at each step

    n2^un

    space
        stack O(n)
        curr n
        res 2^n
        
void helper(int idx, 
        string &input, 
        string &curr, 
        int left_rem, 
        int right_rem, 
        int balance, 
        unordered_set<string> &res) {

    if(balance < 0)
        return;

    // exit condition
    if(idx == input.size()) {

        if( left_rem == 0 && 
            right_rem == 0 && 
            balance == 0
        ) {            
            res.insert(curr);
        }
        return;
    }

    char c = input[idx];

    if(c == '(') {

        if(left_rem > 0) {
            // skip
            helper(idx+1, input, curr, left_rem-1, right_rem, balance, res);
        }

        // pick
        curr.push_back(c);
        helper(idx+1, input, curr, left_rem, right_rem, balance + 1, res);
        curr.pop_back();
    }
    else if(c == ')') {        

        if(right_rem > 0) {
            // skip
            helper(idx+1, input, curr, left_rem, right_rem-1, balance, res);
        }

        // pick
        curr.push_back(c);
        helper(idx+1, input, curr, left_rem, right_rem, balance - 1, res);
        curr.pop_back();
    }
    else {

        curr.push_back(c);
        helper(idx+1, input, curr, left_rem, right_rem, balance, res);
        curr.pop_back();
    }
}

vector<string> removeInvalid(string &input) {
    string curr;
    unordered_set<string> res;

    int balance = 0;
    int left_rem = 0;
    int right_rem = 0;
    for(char c : input) {
        if(c == '(') {
            balance++;
        }
        else if(c == ')') {
            if(balance > 0)
                balance--;
            else
                right_rem++;
        }
    }
    left_rem = balance;

    helper(0, input, curr, left_rem, right_rem, 0, res); // reset balance

    vector<string> ans(res.begin(), res.end());
    return ans;
}

============================================

n queens


derivation:
    a queen can kill another queen in the same row col or diagonal

    our approach
        we will place 1 queen per row
        then we need a lookup for column and diagonal

    for diagonals we have 2 ways to look
        \ and /

    / row+col is the same for d1 diagonals
    [0,0] [0,1] [0,2]  [0][1][2]
    [1,0] [1,1] [1,2]  [1][2][3]
    [2,0] [2,1] [2,2]  [2][3][4]    

    \ for d2 diagonal row-col gives us
    [0,0] [0,1] [0,2]  [ 0][-1][-2]
    [1,0] [1,1] [1,2]  [ 1][ 0][-1]
    [2,0] [2,1] [2,2]  [ 2][ 1][ 0]    

    square mat
    we want to normalize the and add the largest neg
    n-1 to all row-col + (n-1)
    [2][1][0]
    [3][2][1]
    [4][3][2]    

    0,1,2,3,4, 5 vals
    2n-1 vals


3. Complexity
Search time: O(n!) candidate arrangements, with O(n) work to copy each complete board
(O(n * n!)

aus space n^2 for the board

res S*n^2 where S is valid sols

O(n) for recur stack


void helper(int row, 
    vector<bool> &colseen, 
    vector<bool> &d1seen, 
    vector<bool> &d2seen, 
    vector<string> &board, 
    vector<vector<string>> &res) {

    if(row == board.size()) {
        res.push_back(board);
        return;
    }

    int n = board.size();

    for(int col=0; col<n; col++) {

        // can place?
        int d1 = row + col;
        int d2 = row - col + n - 1;
        if(colseen[col] || d1seen[d1] || d2seen[d2])
            continue;

        colseen[col] = true;
        d1seen[d1] = true;
        d2seen[d2] = true;
        board[row][col] = 'Q';

        helper(row+1, colseen, d1seen, d2seen, board, res);

        board[row][col] = '.';
        colseen[col] = false;
        d1seen[d1] = false;
        d2seen[d2] = false;
    }
}

vector<vector<string>> nqueens(int n) {
    vector<string> board(n, string(n, '.'));
    vector<vector<string>> res;

    vector<bool> colseen(n, false);
    vector<bool> d1seen(2*n-1, false);
    vector<bool> d2seen(2*n-1, false);

    helper(0, colseen, d1seen, d2seen, board, res);

    return res;
}

============================================

Unique Paths III

Given a grid where:
- 1 is the starting square.
- 2 is the ending square.
- 0 is an empty square.
- -1 is an obstacle.
Return the number of paths from start to end that visit every 
non-obstacle square exactly once.
You may move up, down, left, or right.


derivation:
    we need to move from start to end
    this is not bfs
    we need a valid path where all valid squares are reached

    we need a visited matrix to prevent revisit

    we need a counter to make sure we have all squares visited
        precompute and carry as state

    move in 4 dirs
        if not visited
            and square is valid
                backtrack

    if square is at destination and visited==0
        store result

complexity:
    from each square we can move 4 directions
        4^nm search

    each each step we copy
        nm*4^nm

    space
        visited nm
        stack space nm
        

    

*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


int helper(int x, int y, 
    int valid,
    vector<vector<int>> &grid, 
    vector<vector<int>> &visited) {

    if(grid[x][y] == 2) {
        if(valid == 0)
            return 1;
        return 0;
    }

    visited[x][y] = 1;

    int n = grid.size();
    int m = grid[0].size();

    int dx[] = {1,-1, 0, 0};
    int dy[] = {0, 0,-1, 1};

    int count = 0;

    for(int k=0; k<4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if( nx>=0 && nx<n && 
            ny>=0 && ny<m && 
            grid[nx][ny] != -1 && 
            !visited[nx][ny]) {

            count += helper(nx, ny, valid-1, grid, visited);
        }
    }

    visited[x][y] = 0;

    return count;
}

int countPaths(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> visited(n, vector<int>(m, 0));


    int valid = 0;
    int sx = 0, sy = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(grid[i][j] != -1) {
                valid++;
            }
            if(grid[i][j] == 1) {
                sx = i;
                sy = j;
            }
        }
    }

    // visited[sx][sy] = 1;
    valid--; // start is already visited
    return  helper(sx, sy, valid, grid, visited);
}


int main() {
    vector<vector<int>> grid = {{1, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 2,-1}};


    // vector<vector<int>> grid = {{1, 0,},
    //                     {0, 2}};

    auto x = countPaths(grid);

    return 0;
}

