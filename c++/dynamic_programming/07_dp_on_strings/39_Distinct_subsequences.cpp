/*
Distinct subsequences
    [https://takeuforward.org/practice/dsa/distinct-subsequences?category=dp-on-strings&source=strivers-a2z-dsa-sheet]

Given two strings s and t, return the number of distinct subsequences 
of s that equal t.

A subsequence of a string is a new string generated from the original 
string with some characters (can be none) deleted without changing 
the relative order of the remaining characters. For example, "ace" is 
a subsequence of "abcde" while "aec" is not.

The task is to count how many different ways we can form t from s by 
deleting some (or no) characters from s. Return the result modulo 
109+7.

Example 1:
    Input: s = "axbxax", t = "axa"

    Output: 2

    Explanation: In the string "axbxax", there are two distinct 
    subsequences "axa":

    (a)(x)bx(a)x

    (a)xb(x)(a)x

Example 2:
    Input: s = "babgbag", t = "bag"

    Output: 5

    Explanation: In the string "babgbag", there are five distinct 
    subsequences "bag":

    (ba)(b)(ga)(g)

    (ba)(bg)(ag)

    (bab)(ga)(g)

    (bab)(g)(ag)

    (babg)(a)(g)


*/

/*
f(i,j, s, t)
    number of subsequences to form t using s
    starting at i,j

    if(t==end)
        return 1
    if(s == end)
        return 0

    if(s[i] == t[j])
        pick = f(i+1, j+1)
        skip = f(i+1, j)
        return pick + skip
    else
        skip = f(i+1, j)

*/
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

// 2^n time
// n stack space
int f(int i, int j, string &s, string &t) {

    const int MOD = 1e9+7;

    if(j == t.size())
        return 1;

    if(i == s.size())
        return 0;

    if(s[i] == t[j]) {
        int pick = f(i+1, j+1, s, t);
        int skip = f(i+1, j, s, t);
        return (pick + skip) % MOD;
    }

    // skip
    return f(i+1, j, s, t);
}

int distinctSubsequences1(string s, string t) {
    return f(0, 0, s, t);
}

// nm time
// nm space
// n+m stack space
int memo(int i, int j, string &s, string &t, vector<vector<int>> &dp) {

    const int MOD = 1e9+7;

    if(j == t.size())
        return 1;

    if(i == s.size())
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    if(s[i] == t[j]) {
        int pick = memo(i+1, j+1, s, t, dp);
        int skip = memo(i+1, j, s, t, dp);
        return dp[i][j] = (pick + skip) % MOD;
    }

    // skip
    return dp[i][j] = memo(i+1, j, s, t, dp);
}

int distinctSubsequences2(string s, string t) {
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return memo(0, 0, s, t, dp);
}

/*
tabulation
    list the dependencies
    
    dp[i][j] = dp[i+1][j+1] + dp[i+1][j]
    OR
    dp[i][j] = dp[i+1][j]

    we need i+1
        start n-1..0 for i
    j need j+1
        j..0

    dp[*][t] = 1
    dp[s][*] = 0
    
       a x a 0
    a  2 2 1 1
    x  0 2 1 1
    b  0 1 1 1
    x  0 1 1 1
    a  0 0 1 1
    x  0 0 0 1
    0  0 0 0 1
*/
int distinctSubsequences3(string s, string t) {
    int n = s.size();
    int m = t.size();
    const int MOD = 1e9+7;
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    
    for(int i=0; i<=n; i++) {
        dp[i][m] = 1;
    }
    
    for(int i=n-1; i>=0; i--) {
        for(int j=m-1; j>=0; j--) {

            if(s[i] == t[j]) {
                int pick = dp[i+1][j+1];
                int skip = dp[i+1][j];
                dp[i][j] = (pick + skip) % MOD;
            }
            else {
                // skip
                dp[i][j] = dp[i+1][j];
            }            
        }
    }
    return dp[0][0];
}

int distinctSubsequences4(string s, string t) {
    int n = s.size();
    int m = t.size();
    const int MOD = 1e9+7;    
    vector<int> curr(m+1, 0);
    vector<int> next(m+1, 0);
    
    curr[m] = 1;
    next[m] = 1;
        
    for(int i=n-1; i>=0; i--) {

        for(int j=m-1; j>=0; j--) {

            if(s[i] == t[j]) {
                int pick = next[j+1];
                int skip = next[j];
                curr[j] = (pick + skip) % MOD;
            }
            else {
                // skip
                curr[j] = next[j];
            }            
        }
        next = curr;
    }
    return next[0];
}

int distinctSubsequences5(string s, string t) {
    int n = s.size();
    int m = t.size();
    const int MOD = 1e9+7;    
    vector<int> dp(m+1, 0);    
    
    dp[m] = 1;
    
    // int diagonal = 1; // we werent setting it to 1 inside each loop
    for(int i=n-1; i>=0; i--) {

        int diagonal = 1;

        for(int j=m-1; j>=0; j--) {

            int old = dp[j];
            if(s[i] == t[j]) {
                int pick = diagonal;                
                int skip = dp[j];
                dp[j] = (pick + skip) % MOD;
            }
            else {
                // skip
                dp[j] = dp[j];
            }    
            diagonal = old;        
        }        
    }
    return dp[0];
}

int main() {
    string s = "axbxax";
    string t = "axa";    
    assert(distinctSubsequences1(s, t) == 2);
    assert(distinctSubsequences2(s, t) == 2);
    assert(distinctSubsequences3(s, t) == 2);
    assert(distinctSubsequences4(s, t) == 2);
    assert(distinctSubsequences5(s, t) == 2);

    s = "babgbag"; t = "bag";
    assert(distinctSubsequences1(s, t) == 5);
    assert(distinctSubsequences2(s, t) == 5);
    assert(distinctSubsequences3(s, t) == 5);
    assert(distinctSubsequences4(s, t) == 5);
    assert(distinctSubsequences5(s, t) == 5);
    return 0;
}