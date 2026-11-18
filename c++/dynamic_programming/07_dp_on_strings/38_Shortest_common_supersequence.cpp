/*
Shortest common supersequence
    [https://takeuforward.org/practice/dsa/shortest-common-supersequence?category=dp-on-strings&source=strivers-a2z-dsa-sheet&tab=problem]

Given two strings str1 and str2, find the shortest common 
supersequence.

The shortest common supersequence is the shortest string that 
contains both str1 and str2 as subsequences.

Note: The problem may have multiple valid answers. Since the return 
type is a string, the judge will output 1 if your returned string is 
a valid shortest common supersequence and 0 otherwise.

Example 1:
    Input: str1 = "mno", str2 = "nop"

    Output: "mnop"

    Explanation: The shortest common supersequence is "mnop". It contains 
    "mno" as the first three characters and "nop" as the last three 
    characters, thus including both strings as subsequences.

Example 2:
    Input: str1 = "dynamic", str2 = "program"

    Output: "dynprogramic"

    Explanation: The shortest common supersequence is "dynprogramic". It 
    includes all characters from both "dynamic" and "program", with 
    minimal overlap. For example, "dynamic" appears as "dyn...amic" and 
    "program" appears as "...program..." within "dynprogramic".

Example 3:
    Input: str1 = "apple", str2 = "orange"

    Output:
    "orapplnge"
*/

#include <string>
#include <algorithm>
#include <vector>
#include <assert.h>
using namespace std;

string shortestCommonSupersequence1(string a, string b) {

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
            ans += a[i-1];  // add character from A, (table has A rows, B cols)
            i--;            
        }
        else {
            ans += b[j-1];  // add character from B, (table has A rows, B cols)
            j--;            
        }
    }

    /*
    dp[i][j]
        i how much of A is left
        j how much of B is left
    */

    // add remaining chars from A
    // rows remaining
    while(i > 0) {
        ans += a[i-1];
        i--;
    }

    // add remaining chars from B
    // cols remaining
    while(j > 0) {
        ans += b[j-1];
        j--;
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    string str1 = "mno";
    string  str2 = "nop";
    auto x = shortestCommonSupersequence1(str1, str2);
    assert(shortestCommonSupersequence1(str1, str2) == "mnop");

    str1 = "dynamic"; str2 = "program";
    assert(shortestCommonSupersequence1(str1, str2) == "dynprogramic");
    return 0;
}