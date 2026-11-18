/*
A = "abc"
B = "ac"

answer should be "ac"

          ∅   a   c
        ┌───────────
∅       │ 0   0   0
a       │ 0   1   1
b       │ 0   1   1
c       │ 0   1   2


idx is +1 shifted
    then 0 row col is 0
    so we can have a valid i-1, j-1 access

dp[i][j]
    match s1[i-1] == s2[j-1]
        dp[i][j] = 1 + dp[i-1][j-1]
    else
        dp[i][j] = max( dp[i-1][j],
                        dp[i][j-1]);

the LCS is stored in dp[n][m]

to reconstruct
    start from dp[n][m]
        access chars by -1

        if equal
            add
            go i-1,j-1
        else
            check max of up and left
                if up is larger go up
            else
                go left

    reverse ans

*/

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string printLCS(string a, string b) {
    int n = a.size();
    int m = b.size();

    // LCS
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(a[i-1] == b[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = max(dp[i-1][j],
                                    dp[i][j-1]);
            }
        }
    }

    string ans;
    int i=n;
    int j=m;
    while(i > 0 && j > 0) {
        if(a[i-1] == b[j-1]) {
            ans += a[i-1];
            i--;
            j--;
        }
        // up > left?
        else if(dp[i-1][j] > dp[i][j-1]) {
            i--;
        }
        else {
            j--;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    string str1 = "ac";
    string str2 = "abc";
    auto x = printLCS(str1, str2);
    return 0;
}