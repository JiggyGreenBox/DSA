#include <bits/stdc++.h>
using namespace std;

bool backtrack( int idx, // next index to look for
                int i,
                int j,
                const string& word, 
                const vector<vector<char>> board)
{
    // base condition
    if(idx == word.size()) return true;

    // explore choices
    char c = word[idx];

    int max_rows = board.size()-1;
    int max_cols = (max_rows>0) ? board[0].size()-1 : 0;

    // up       i-1, j
    if(i>0 && board[i-1][j] == c){
        cout << "checking up" << endl;
        cout << "from " << i <<" ," << j << endl;
        cout << "to " << i-1 <<" ," << j << endl;
        if(backtrack(idx+1, i-1, j, word, board)){
            return true;
        }
    }

    // down     i+1, j
    if(i<max_rows && board[i+1][j] == c){
        cout << "checking down" << endl;
        cout << "from " << i <<" ," << j << endl;
        cout << "to " << i+1 <<" ," << j << endl;
        if(backtrack(idx+1, i+1, j, word, board)){
            return true;
        }
    }

    // left     i,   j-1
    if(j>0 && board[i][j-1] == c){
        cout << "checking left" << endl;
        cout << "from " << i <<" ," << j << endl;
        cout << "to " << i <<" ," << j-1 << endl;
        if(backtrack(idx+1, i, j-1, word, board)){
            return true;
        }
    }

    // right    i,   j+1
    if(j<max_cols && board[i][j+1] == c){
        cout << "checking right" << endl;
        cout << "from " << i <<" ," << j << endl;
        cout << "to " << i <<" ," << j+1 << endl;
        if(backtrack(idx+1, i, j+1, word, board)){
            return true;
        }
    }
    return false;
}

bool exist(const vector<vector<char>>& board, string word) {

    if(word.empty()) return false;

    // find the starting point
    // process each recursion char by char
    // 4 possible directions
    // up, down, left, right
    
    for(int i=0;i<board.size();i++){
        // cout << "[ ";
        for(int j=0;j<board[0].size();j++){
            // cout << board[i][j] << " ";
            if(board[i][j] == word[0]){
                cout << "starting point found at " << i << ", " << j << endl;
                if(backtrack(1, i,j, word, board)){
                    return true;
                }
            }
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
    
    print(exist({ {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'} }, "ABCCED"));
    // print(exist({ {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'} }, "SEE"));
    return 0;
}