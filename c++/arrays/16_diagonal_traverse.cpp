/*
Diagonal Traverse
    [https://leetcode.com/problems/diagonal-traverse/description/]

Given an m x n matrix mat, return an array of all the elements of the 
array in a diagonal order.

Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,4,7,5,3,6,8,9]
Example 2:

Input: mat = [[1,2],[3,4]]
Output: [1,2,3,4]



[0,0][0,1][0,2]
[1,0][1,1][1,2]
[2,0][2,1][2,2]

Diagonal Traverse
i and j increment and decrement
    then decrement and increment
    in alternative fashion

i need a hint 

we can move:
    up      i--, j++

    down    i++, j--

    while going up
        if i-- < 0 flip

        or j == cols

    while going down
        i == rows

        j-- < 0


*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


vector<int> findDiagonalOrder(vector<vector<int>>& mat) {

    int m = mat.size();
    int n = mat[0].size();

    vector<int> ans;
    ans.reserve(m * n);

    int i = 0;
    int j = 0;

    bool up = true;

    while (ans.size() < m * n) {

        ans.push_back(mat[i][j]);

        if (up) {

            i--;
            j++;

            // Right wall (includes top-right corner)
            if (j == n) {
                j--;
                i += 2;
                up = false;
            }
            // Top wall
            else if (i < 0) {
                i = 0;
                up = false;
            }
        }
        else {

            i++;
            j--;

            // Bottom wall (includes bottom-left corner)
            if (i == m) {
                i--;
                j += 2;
                up = true;
            }
            // Left wall
            else if (j < 0) {
                j = 0;
                up = true;
            }
        }
    }

    return ans;
}
void print(const vector<int> & v) {
    cout << "[";
    for(auto x : v) cout << x << " ";
    cout << "]\n";
}

void printMat(vector<vector<int>>& v) {
    
    for(auto &r :v){
        cout << "[ ";
        for(auto x : r) cout << x << " ";        
        cout << "]" << endl;
    }    
}

int main() {
    vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    print(findDiagonalOrder(matrix));
    
    return 0;
}

/*

use bool of up
    i--,j++
    and 
    i++, j--

when we hit top or bottom, 
    i--, j++
    i++, j--
    col is correct, just clamp to 0

when we hit right or left
    we need to correct by +2

    this take care of the corners


stop when ans is equal of mat size, r*c

*/