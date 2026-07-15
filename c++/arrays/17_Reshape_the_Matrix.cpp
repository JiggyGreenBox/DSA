/*
Reshape the Matrix
    [https://leetcode.com/problems/reshape-the-matrix/description/]

In MATLAB, there is a handy function called reshape which can reshape 
an m x n matrix into a new one with a different size r x c keeping 
its original data.

You are given an m x n matrix mat and two integers r and c 
representing the number of rows and the number of columns of the 
wanted reshaped matrix.

The reshaped matrix should be filled with all the elements of the 
original matrix in the same row-traversing order as they were.

If the reshape operation with given parameters is possible and legal, 
output the new reshaped matrix; Otherwise, output the original matrix.
*/

/*
approach 1
    flatten into vector
    fill into new matrix

approach 2
    use flattern math
    and unflattern directly int new mat
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
    int m = mat.size();
    int n = mat[0].size();

    vector<vector<int>> ans(r, vector<int>(c));    

    if(m*n != r*c)
        return mat;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            int flat = i*n + j;            
            ans[flat/c][flat % c] = mat[i][j];
        }
    }

    return ans;
}

void printMat(const vector<vector<int>>& v) {    
    for(auto &r :v){
        cout << "[ ";
        for(auto x : r) cout << x << " ";        
        cout << "]" << endl;
    }    
}

int main() {
    vector<vector<int>> matrix = {{1,2},{3,4}};
    printMat(matrixReshape(matrix, 1, 4));
    
    return 0;
}

/*
flatten
    index = row * cols + col;

unflatten
    row = index / cols;
    col = index % cols;
*/