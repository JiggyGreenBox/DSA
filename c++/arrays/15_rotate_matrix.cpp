#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void print(const vector<vector<int>>& mat){
    for(const auto& row : mat){
        cout << "[ ";
        for(const auto element: row){
            cout << element << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

void transpose(vector<vector<int>>& mat){
    int n = mat.size();    

    for(int i=0; i<n; i++){        
        for(int j=i+1; j<n; j++){            
            swap(mat[i][j], mat[j][i]);
        }        
    }
}

void reverse_each_row(vector<vector<int>> &mat) {
    for(auto &row : mat) {
        reverse(row.begin(), row.end());
    } 
}
void reverse_each_col(vector<vector<int>> &mat) {
    reverse(mat.begin(), mat.end());
}


/*
our code doesnt work with non-square matrices
can use swap
we need a copy
M x N : N x M
*/
vector<vector<int>> transpose_any(const vector<vector<int>>& mat){
    

    if(mat.empty() || mat[0].empty()) return {};

    int rows = mat.size();
    int cols = mat[0].size();
    vector<vector<int>> ans(cols, vector<int>(rows));

    // for(int i=0; i<cols; i++){
    //     for(int j=0; j<rows; j++){
    //         ans[i][j] = mat[j][i];
    //     }
    // }

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            ans[j][i] = mat[i][j];
        }
    }

    return ans;
}


void rotateRight(vector<vector<int>> &mat) {
    transpose(mat);
    reverse_each_row(mat);
}
void rotateLeft(vector<vector<int>> &mat) {
    transpose(mat);
    reverse_each_col(mat);
}
void flipVertical(vector<vector<int>> &mat) {
    reverse_each_col(mat);
}
void flipHorizontal(vector<vector<int>> &mat) {
    reverse_each_row(mat);
}


int main() {
    vector<vector<int>> mat =   {
                                    {1, 1, 1},
                                    {2, 2, 2}, 
                                    {3, 3, 3}
                                };


    // vector<vector<int>> mat =   {
    //                                 {1, 2, 3},
    //                                 {4, 5, 6}, 
    //                                 {7, 8, 9},
    //                                 {10, 11, 12},
    //                             };
    // print(transpose_any(mat));

    print(mat);

    rotateRight(mat);
    print(mat);

    rotateLeft(mat);
    print(mat);

    flipVertical(mat);
    print(mat);
    
    flipHorizontal(mat);
    print(mat);

    
    return 0;
}