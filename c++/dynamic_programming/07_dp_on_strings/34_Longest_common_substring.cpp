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
int rec(int idx1, int idx2, string &s1, string &s2) {

    if(idx1 == 0 || idx2 == 0)
        return 0;
    
    if(s1[idx1-1] == s2[idx2-1])
        return 1 + rec(idx1-1, idx2-1, s1, s2);
    
    return 0;
}

// O(n*m *min(n,m)) time
// 1 space
// min(n,m) stack space
int longestCommonSubstr1(string str1, string str2) {

    int ans = 0;
    for(int i=str1.size(); i>=0; i--) {
        for(int j=str2.size(); j>=0; j--) {
            ans = max(ans, rec(i,j,str1, str2));
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
int longestCommonSubstr2(string str1, string str2) {

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
        }
    }
    return ans;
}

/*
compression to 1D

we look at 2 loops and think i needs all j's
but look at the assignment
dp[i][j] = 1 + dp[i-1][j-1]
    dp[i-1] and dp[j-1] should be old

    if j=5, 4 should be old value
        so j goes from m-1 .. 0

    what about i-1 being old?
        if we use dp[j] before updating
        then i-1 is handled

    why m+1 and not n+1 for dp array?
        the original is dp(n+1, vector(m+1, 0))

    we eliminate rows but keep cols
*/
int longestCommonSubstr3(string str1, string str2) {

    int s1 = str1.size();
    int s2 = str2.size();

    // vector<vector<int>> dp(s1+1, vector<int>(s2+1, 0));
    vector<int> dp(s2+1, 0);

    // right shift by 1
    // because dp[0][0] = 0

    int ans = 0;

    for(int i=1; i<=s1; i++) {
        for(int j=s2; j>=1; j--) {

            if(str1[i-1] == str2[j-1]) {
                dp[j] = 1 + dp[j-1];
                ans = max(ans, dp[j]);
            }
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

    str1 = "abcdxyz"; str2 = "xyzabcd";
    assert(longestCommonSubstr1(str1, str2) == 4);
    assert(longestCommonSubstr2(str1, str2) == 4);
    assert(longestCommonSubstr3(str1, str2) == 4);

    return 0;
}



