/*
Longest common substring
    [https://takeuforward.org/practice/dsa/longest-common-substring?category=dp-on-strings&source=strivers-a2z-dsa-sheet]


Given two strings str1 and str2, find the length of their longest 
common substring.

A substring is a contiguous sequence of characters within a string.

    Example 1:
        Input: str1 = "abcde", str2 = "abfce"

        Output: 2

        Explanation: The longest common substring is "ab", which has a length 
        of 2.

    Example 2:
        Input: str1 = "abcdxyz", str2 = "xyzabcd"

        Output: 4

        Explanation: The longest common substring is "abcd", which has a 
        length of 4.

*/

/*

for longest subsequence

    prefix based idx approach

    f(i,j)
        len of longest common substring ending at i,j

        if(s[i] == s[j])
            dp[i][j] = 1 + dp[i-1][j-1]

        else
            dp[i][j] = 0
*/

#include <string>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

// O(min(n,m))
int rec(int i, int j, string &s1, string &s2) {

    if(i < 0 || j < 0)
        return 0;
    
    if(s1[i] == s2[j])
        return 1 + rec(i-1, j-1, s1, s2);
    
    return 0;
}

// O(n*m *min(n,m)) time
// 1 space
// min(n,m) stack space
int longestCommonSubstr1(string str1, string str2) {

    int ans = 0;
    for(int i=0; i<str1.size(); i++) {
        for(int j=0; j<str2.size(); j++) {
            ans = max(ans, rec(i,j,str1, str2));
        }
    }
    return ans;
}

int memo(int i, int j, string &s1, string &s2, vector<vector<int>> &dp) {

    if(i < 0 || j < 0)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];
    
    if(s1[i] == s2[j])
        return dp[i][j] = 1 + rec(i-1, j-1, s1, s2);
    
    return dp[i][j] = 0;
}

int longestCommonSubstr2(string str1, string str2) {

    int n = str1.size();
    int m = str2.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));

    int ans = 0;
    for(int i=0; i<str1.size(); i++) {
        for(int j=0; j<str2.size(); j++) {
            ans = max(ans, memo(i,j,str1, str2, dp));
        }
    }
    return ans;
}

// we are going to tabulation
// because we need to query the dp table
// rather than look for every index here

// time n*m
// space n*m
// dont think 1dp is possible here
// beacuse we do a full i..
// and need access to j at each step

/*
f(i,j)
    length of longest substring ending at i,j

    we depend on earlier values, prefix based

    if(s1[i] == s2[j])
        dp[i][j] = 1 + dp[i-1][j-1]

    right shift by 1


      | 0 a a b
      |-----------
    0 | 0 0 0 0
    a | 0 1 1 0
    b | 0 0 0 2

    max can happen any where so 
    track max(dp[i][j])
    as we assign
*/

int longestCommonSubstr3(string str1, string str2) {

    int s1 = str1.size();
    int s2 = str2.size();

    vector<vector<int>> dp(s1+1, vector<int>(s2+1, 0));

    // right shift by 1
    // because dp[0][0] = 0

    int ans = 0;

    for(int i=1; i<=s1; i++) {
        for(int j=1; j<=s2; j++) {

            if(str1[i-1] == str2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
                ans = max(ans, dp[i][j]);
            }
            else {
                dp[i][j] = 0;
            }
        }
    }
    return ans;
}

/*
compression to 1D

look at the table
we need prev upper diagonal
in the base case it is zero
    store col, so next time it becomes j-1
*/
int longestCommonSubstr4(string str1, string str2) {

    int s1 = str1.size();
    int s2 = str2.size();
    
    vector<int> prev(s2+1, 0);
    vector<int> curr(s2+1, 0);

    // right shift by 1
    // because dp[0][0] = 0

    int ans = 0;

    for(int i=1; i<=s1; i++) {
        for(int j=1; j<=s2; j++) {

            if(str1[i-1] == str2[j-1]) {
                curr[j] = 1 + prev[j-1];
                ans = max(ans, curr[j]);
            }
            else {
                curr[j] = 0;
            }
        }
        prev = curr;
    }
    return ans;
}

int longestCommonSubstr5(string str1, string str2) {

    int s1 = str1.size();
    int s2 = str2.size();
        
    vector<int> dp(s2+1, 0);

    // right shift by 1
    // because dp[0][0] = 0

    int ans = 0;

    for(int i=1; i<=s1; i++) {
        int diagonal = 0;
        for(int j=1; j<=s2; j++) {
            int old = dp[j];
            if(str1[i-1] == str2[j-1]) {
                dp[j] = 1 + diagonal;
                ans = max(ans, dp[j]);
            }
            else {
                dp[j] = 0;
            }
            diagonal = old;
        }        
    }
    return ans;
}

int main() {
    string str1 = "abcde";
    string  str2 = "abfce";

    assert(longestCommonSubstr1(str1, str2) == 2);
    assert(longestCommonSubstr2(str1, str2) == 2);
    assert(longestCommonSubstr3(str1, str2) == 2);
    assert(longestCommonSubstr4(str1, str2) == 2);
    assert(longestCommonSubstr5(str1, str2) == 2);

    str1 = "abcdxyz"; str2 = "xyzabcd";
    assert(longestCommonSubstr1(str1, str2) == 4);
    assert(longestCommonSubstr2(str1, str2) == 4);
    assert(longestCommonSubstr3(str1, str2) == 4);
    assert(longestCommonSubstr4(str1, str2) == 4);
    assert(longestCommonSubstr5(str1, str2) == 4);

    return 0;
}



