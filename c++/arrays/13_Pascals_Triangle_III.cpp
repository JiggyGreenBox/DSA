#include <iostream>
#include <vector>
using namespace std;

// n is num of rows
vector<vector<int>> pascalTriangleIII(int n) {

    vector<vector<int>> ans(n);

    for(int i=0; i<n; i++) {
        ans[i].resize(i+1);

        ans[i][0] = 1;
        ans[i][i] = 1;

        for(int j=1; j<i; j++) {
            ans[i][j] = ans[i-1][j-1] + ans[i-1][j];
        }
    }
    return ans;
}

int main() {
    int n1 = 5; // 1-based
    auto ans = pascalTriangleIII(n1-1);

    int n0 = 7;
    auto ans = pascalTriangleIII(n0);
    return 0;
}