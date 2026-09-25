#include <vector>
#include <string>
#include <iostream>
using namespace std;

int dfs(int row, int n, 
        vector<bool> &colseen,
        vector<bool> &d1seen,
        vector<bool> &d2seen
) {
    if (row == n)
        return 1;

    int count = 0;

    for (int col = 0; col < n; col++) {

        int d1 = row + col;         // '/d' 
        int d2 = row - col + n - 1; // '\d'

        if(colseen[col] || d1seen[d1] || d2seen[d2])
            continue;

        
        colseen[col] = true;
        d1seen[d1] = true;
        d2seen[d2] = true;

        count += dfs(row + 1, n, colseen, d1seen, d2seen);

        colseen[col] = false;
        d1seen[d1] = false;
        d2seen[d2] = false;
        
    }

    return count;
}

int totalNQueens(int n) {

    vector<bool> colseen(n, false);
    vector<bool> d1seen(2*n-1, false);
    vector<bool> d2seen(2*n-1, false);

    return dfs(0, n, colseen, d1seen, d2seen);    
}

int main() {
    cout << totalNQueens(4) <<  endl;
    return 0;
}

