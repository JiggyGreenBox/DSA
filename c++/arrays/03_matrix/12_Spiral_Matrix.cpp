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


    while(left <= right && top<=bot) {
        // go right
        for(int i=left; i<=right; i++) {
            ans.push_back(matrix[top][i]);
        }
        top++;

        // go down
        for(int i=top; i<=bot; i++) {
            ans.push_back(matrix[i][right]);
        }
        right--;

        // go left
        if(top<=bot) { // edge case for single row matrix
            for(int i=right; i>=left; i--) {
                ans.push_back(matrix[bot][i]);
            }
        }        
        bot--;

        // go up
        if(left<=right) { // edge case single column matrix
            for(int i=bot; i>=top; i--) {
                ans.push_back(matrix[i][left]);
            }
        }
        left++;
    }
    
    return ans;
}

void print(const vector<int> & v) {
    cout << "[";
    for(auto x : v) cout << x << " ";
    cout << "]\n";
}

int main(){
    // vector<vector<int>> v = {{1, 2, 3}, {4 ,5 ,6}, {7, 8, 9}};


    // vector<vector<int>> v = {{1, 2, 3, 4 ,5 ,6}, {7, 8, 9, 10, 11, 12}};


    // vector<vector<int>> v = {{1}, {2}, {3}, {4} ,{5} ,{6}, {7}, {8}, {9}, {10}, {11}, {12}};

    vector<vector<int>> v = {{1,2},{4,3}};
    print(spiralOrder(v));

    // vector<vector<int>> v = {{1, 2, 3, 4 ,5 ,6, 7, 8, 9, 10, 11, 12}};
    

    v = {{1, 2, 3, 4 ,5 ,6, 7, 8, 9, 10, 11, 12}};
    print(spiralOrder(v));

    v = {{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{ 12}};
    print(spiralOrder(v));

    return 0;
}

/*

top = 0
bot = rows-1
left = 0
right = cols-1

while
    
    for each i in [left,right]
        push
    top++

    for each i in [top,bot]
        push
    right--

    edgecase, if(top<=bot)

        for each i in [right, left]
            push
        bot--

    edgecase, if(left<=right)
        for each i in [bot,top]
            push
        left++

*/