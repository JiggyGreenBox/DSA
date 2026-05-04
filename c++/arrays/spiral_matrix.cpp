#include <iostream>
#include <vector>

using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> ans;

    int m = matrix.size();
    int n = matrix[0].size();

    int top = 0;
    int bot = m-1;
    int left = 0;
    int right = n-1;


    while(left <= right && top<=bot){
        // go right
        for(int i=left; i<=right; i++){
            cout << "left" << endl;
            ans.push_back(matrix[top][i]);
        }
        top++;

        // go down
        for(int i=top; i<=bot; i++){
            cout << "down" << endl;
            ans.push_back(matrix[i][right]);
        }
        right--;

        // go left
        if(top<=bot){
            for(int i=right; i>=left; i--){
                cout << "left" << endl;
                ans.push_back(matrix[bot][i]);
            }
        }        
        bot--;

        // go up
        if(left<=right){
            for(int i=bot; i>=top; i--){
                cout << "up" << endl;
                ans.push_back(matrix[i][left]);
            }
        }
        left++;
        cout << left << right << top << bot << endl;
    }

    
    return ans;
}

int main(){
    // vector<vector<int>> v = {{1, 2, 3}, {4 ,5 ,6}, {7, 8, 9}};


    // vector<vector<int>> v = {{1, 2, 3, 4 ,5 ,6}, {7, 8, 9, 10, 11, 12}};


    // vector<vector<int>> v = {{1}, {2}, {3}, {4} ,{5} ,{6}, {7}, {8}, {9}, {10}, {11}, {12}};

    vector<vector<int>> v = {{1,2},{4,3}};


    // vector<vector<int>> v = {{1, 2, 3, 4 ,5 ,6, 7, 8, 9, 10, 11, 12}};

    vector<int> ans = spiralOrder(v);

    for(auto x:ans) cout << x << " ";
    cout << endl;
    return 0;
}