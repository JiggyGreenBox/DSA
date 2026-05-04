#include <bits/stdc++.h>
using namespace std;


void printResults(const vector<vector<string>>& results) {
    for(auto row : results) {
        cout << "[ ";
        for(auto x : row) cout << x << " ";
        cout << "]\n";
    }
}

bool canPlace_old(int row_idx, int i, vector<int>& used){

    if(row_idx == 0) return true; // can place anywhere

    // up
    for(int r=row_idx-1; r>=0; r--) {
        if(used[r] == i) return false;
    }

    // diag left
    int look = i;
    for(int r=row_idx-1; r>=0; r--) {
        if(used[r] == look-1) return false;
        look--;
    }

    // diag right
    look = i;
    for(int r=row_idx-1; r>=0; r--) {
        if(used[r] == look+1) return false;
        look++;
    }

    return true;
}

bool canPlace(int row_idx, int i, vector<int>& used){

    if(row_idx == 0) return true; // can place anywhere

    // up
    for(int r=row_idx-1; r>=0; r--) {
        if(used[r] == i) return false;
    }

    // use distance formula from chatgpt to look for diagonal clash
    for(int r=row_idx-1; r>=0; r--) {
        int d1 = row_idx-r;
        int d2 = abs(i-used[r]);
        if(d1 == d2) return false;
    }    

    return true;
}


void dfs(int row_idx, vector<int>& used, vector<vector<string>>& results) {
    int n = used.size();
    if(row_idx == n){
        
        cout << "[ ";
        for(auto x:used){
            cout << x << " ";
        }
        cout << "]\n";

        vector<string> temp; // 1 string for each entry of used
        for(auto idx : used) {
            string s = "";
            for(int i=0;i<n;i++) {
                if(i==idx){
                    s+="Q";
                }
                else{
                    s+=".";
                }
            }
            temp.push_back(s);
        }
        results.push_back(temp);

        return;
    }

    for(int i=0; i<n; i++){
        if(canPlace(row_idx, i, used)){
            used[row_idx] = i;
            dfs(row_idx+1, used, results);
            used[row_idx] = -1;
        }
    }
}



vector<vector<string>> solveNQueens(int n) {
        
    vector<int> used(n, -1);
    vector<vector<string>> results;
    dfs(0, used, results);    

    return results;
}



int main() {
    printResults(solveNQueens(4));
    return 0;
}