#include <bits/stdc++.h>
using namespace std;

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