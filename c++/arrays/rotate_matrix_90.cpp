#include <iostream>
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

void print_corner1(vector<vector<int>>& mat){
    int m = mat.size();
    int n = mat[0].size();
    cout << "m x n matrix: " << m << " x " << n << endl;

    for(int i=0; i<m; i++){
        cout << "[ ";
        for(int j=0; j<=i; j++){
            cout << mat[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

void print_corner2(vector<vector<int>>& mat){
    int m = mat.size();
    int n = mat[0].size();
    cout << "m x n matrix: " << m << " x " << n << endl;

    for(int i=0; i<m; i++){
        cout << "[ ";
        for(int j=i; j<n; j++){
            cout << mat[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

void transpose(vector<vector<int>>& mat){
    int m = mat.size();
    int n = mat[0].size();

    for(int i=0; i<m; i++){        
        for(int j=i; j<n; j++){
            cout << "swapping " 
                 << i << "," << j 
                 << " with " 
                 << j << "," << i
                 << endl;
            swap(mat[i][j], mat[j][i]);
        }        
    }
}

void transpose2(vector<vector<int>>& mat){
    int m = mat.size();
    int n = mat[0].size();

    for(int i=0; i<m; i++){        
        for(int j=0; j<=i; j++){            
            cout << "swapping " 
                 << i << "," << j 
                 << " with " 
                 << j << "," << i
                 << endl;
            swap(mat[i][j], mat[j][i]);
        }        
    }

    // Transpose the matrix
    // striver code
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < i; j++) {
        //         swap(matrix[i][j], matrix[j][i]);
        //     }
        // }
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

int main() {
    // vector<vector<int>> mat =   {
    //                                 {1, 2, 3},
    //                                 {4, 5, 6}, 
    //                                 {7, 8, 9}
    //                             };


    vector<vector<int>> mat =   {
                                    {1, 2, 3},
                                    {4, 5, 6}, 
                                    {7, 8, 9},
                                    {10, 11, 12},
                                };
    // print(mat);

    
    // print(transpose_any(mat));

    // print(transpose_any({}));
    // print(transpose_any({{}}));

    // print_corner1(mat);    
    // // print(mat);
    // print_corner2(mat);   
    
    print(mat);
    transpose(mat);
    print(mat);
    
    // transpose2(mat);
    // print(mat);
    return 0;
}