#include <iostream>
#include <vector>
using namespace std;


void rotateMatrix_extra_space(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    // vector<vector<int>> ans = matrix;
    vector<vector<int>> ans = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    for(int j=0; j<m; j++) {
        cout << "[ ";
        for(int i=0; i<n; i++) {
            cout << matrix[j][i] << " |";
            cout << "R " << j;
            cout << " C " << i;
            cout << " m-j " << m-j;
            cout << " mn-i " << n-i;
            cout << "| ";
            
            // if(j==0){
                ans[i][m-j-1] = matrix[j][i];
            // }
            // // ans[j][i] = matrix[m-i-1][i];                
            
        }
        cout << "]" << endl;
    }
    matrix = ans;
}

void reverseRow(vector<int>& row){
    int start = 0;
    int end = row.size()-1;
    while(start < end ){
        swap(row[start++], row[end--]);
    }
}

void rotateMatrix(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    // transpose matrix
    // we need to swap diagonally
    // if not we swap every element twice and return the same matrix
    for(int row=0; row<m; row++){
        for(int col=row; col<n; col++){
            // cout << matrix[row][col] << endl;
            // cout << matrix[col][row] << endl;
            swap(matrix[row][col], matrix[col][row]);            
        }
    }
    
    // reverse columns
    // aka reverse each row
    for(auto &row: matrix){
        reverseRow(row);
    }
}

void printMat(vector<vector<int>>& v) {
    
    for(auto row :v){
        cout << "[ ";
        for(auto row_ele :row){
            cout << row_ele << " ";
        }
        cout << "]" << endl;
    }    
}

int main() {
    vector<vector<int>> v = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

    printMat(v);

    // rotateMatrix_extra_space(v);
    rotateMatrix(v);

    printMat(v);    

    return 0;
}


/*
123
456
789

741
852
963
*/