/*
Longest common subsequence
    [https://takeuforward.org/practice/dsa/longest-common-subsequence?category=dp-on-strings&source=strivers-a2z-dsa-sheet]

    Given two strings str1 and str2, find the length of their longest 
    common subsequence.

    A subsequence is a sequence that appears in the same relative order 
    but not necessarily contiguous and a common subsequence of two 
    strings is a subsequence that is common to both strings.

    Example 1:
        Input: str1 = "bdefg", str2 = "bfg"

        Output: 3

        Explanation: The longest common subsequence is "bfg", which has a 
        length of 3.

    Example 2:
        Input: str1 = "mnop", str2 = "mnq"

        Output: 2

        Explanation: The longest common subsequence is "mn", which has a 
        length of 2.
*/

#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <assert.h>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <string>
using namespace std;

/*
Longest common subsequence


if we have the larger and smaller string 
then the largest common sub can be len of smaller


we can pick and skip the larger string
using the smaller string as reference


bdefg
bfg


f(idx1, idx2)
    if(idx1 == end)
        return 0

    pick = 0
    if s1[0] == s2[0]
        pick = 1 + f(1,1)
    skip = f(1,0)

    return max(pick, skip)

*/
// either n or m is advanced
// so reaching the end depends on n + m
// branching factor is 2^n+m
// stack is n + m
int rec(int idx1, int idx2, string &s1, string &s2) {
    if(idx1 == s1.size() || idx2 == s2.size())
        return 0;
    
    if(s1[idx1] == s2[idx2])
        return 1 + rec(idx1+1, idx2+1, s1, s2);
    
    int skip1 = rec(idx1+1, idx2, s1, s2);
    int skip2 = rec(idx1, idx2+1, s1, s2);
    return max(skip1, skip2);
}

int lcs1(string str1, string str2) {

    if(str1.size() < str2.size())         
        swap(str1, str2);

    return rec(0, 0, str1, str2);
}

// O(n*m) time
// O(n+m) stack space
// O(n*m) dp vector space
int memo(int idx1, int idx2, string &s1, string &s2, vector<vector<int>> &dp) {
    if(idx1 == s1.size() || idx2 == s2.size())
        return 0;

    if(dp[idx1][idx2] != -1)
        return dp[idx1][idx2];
    
    if(s1[idx1] == s2[idx2])
        return dp[idx1][idx2] = 1 + memo(idx1+1, idx2+1, s1, s2, dp);
    
    int skip1 = memo(idx1+1, idx2, s1, s2, dp);
    int skip2 = memo(idx1, idx2+1, s1, s2, dp);
    return dp[idx1][idx2] = max(skip1, skip2);
}


// memo
// cache for all possible 
// f(idx1, idx2)
// idx1 range 0..n
// idx2 range 0..n
int lcs2(string str1, string str2) {

    if(str1.size() < str2.size())         
        swap(str1, str2);

    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
    return memo(0, 0, str1, str2, dp);
}


// base cases become prefilled in dp array
/*
tabulation
    derive the table

    dp[i][j] = 1 + dp[i+1][j+1]
    

    dp[i][j] = dp[i+1][j]
    dp[i][j] = dp[i][j+1]
    
    depends on next row
        bot up
    depends on j or j+1
        right to left?

    if match
         1+ diagonal down
    else
        max of right | down


       b  f  g  END
    ----------------
b |    3  2  1   0
d |    2  2  1   0
e |    2  2  1   0
f |    2  2  1   0
g |    1  1  1   0
END    0  0  0   0
    
*/
int lcs3(string str1, string str2) {

    if(str1.size() < str2.size())         
        swap(str1, str2);

    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for(int idx1=str1.size()-1; idx1>=0; idx1--) {
        for(int idx2=str2.size()-1; idx2>=0; idx2--) {
            
            /*
            myversion
            
            int pick = 0;
            if(str1[idx1] == str2[idx2])
                pick = 1 + dp[idx1+1][idx2+1];
                        
            int skip1 = dp[idx1+1][idx2];
            int skip2 = dp[idx1][idx2+1];

            dp[idx1][idx2] = max({pick, skip1, skip2});
            */

            // canonical
            if (str1[idx1] == str2[idx2])
                dp[idx1][idx2] = 1 + dp[idx1+1][idx2+1];
            else
                dp[idx1][idx2] = max(dp[idx1+1][idx2],
                                    dp[idx1][idx2+1]);

        }
    }
    return dp[0][0];
}

// base cases become prefilled in dp array
int lcs4(string str1, string str2) {

    if(str1.size() < str2.size())         
        swap(str1, str2);

    int n = str1.size();
    int m = str2.size();

    
    vector<int> next(m+1, 0);
    vector<int> curr(m+1, 0);

    for(int idx1=str1.size()-1; idx1>=0; idx1--) {
        for(int idx2=str2.size()-1; idx2>=0; idx2--) {
            // canonical
            if (str1[idx1] == str2[idx2])
                curr[idx2] = 1 + next[idx2+1];
            else
                curr[idx2] = max(next[idx2],
                                    curr[idx2+1]);

        }
        next = curr;
    }
    return next[0];
}

// base cases become prefilled in dp array
// to make 1 dp 
// list all values
//  next[idx2+1]    old (store this)
//  next[idx2]      old
//  curr[idx2 + 1]  newly calculated value

int lcs5(string str1, string str2) {

    if(str1.size() < str2.size())         
        swap(str1, str2);

    int n = str1.size();
    int m = str2.size();

    
    vector<int> next(m+1, 0);
    vector<int> curr(m+1, 0);
    vector<int> dp(m+1, 0);
    int diagonal = dp[m];

    for(int idx1=str1.size()-1; idx1>=0; idx1--) {
        // diagonal = 0;
        for(int idx2=str2.size()-1; idx2>=0; idx2--) {
            // canonical
            // if (str1[idx1] == str2[idx2])
            //     curr[idx2] = 1 + next[idx2+1];
            // else
            //     curr[idx2] = max(next[idx2],
            //                         curr[idx2+1]);

            int temp = dp[idx2];

            if (str1[idx1] == str2[idx2])
                dp[idx2] = 1 + diagonal; // idx2+1, inital value is 0 aka dp[m]
            else
                dp[idx2] = max(dp[idx2],
                                    dp[idx2+1]);
                
            diagonal = temp; // becomes the idx2+1 in the next iter
        }
        // next = curr;
    }
    return dp[0];
}

/*
    | a a b
    | 0 1 2 3

a 0 | 2 2 1 0
b 1 | 1 1 1 0
  2 | 0 0 0 0

here dp[0][0] uses 1 + 1
if we use single dp array
    it will use 1 + 2
    we need the diagonal before update (1) before it becomes (2)
*/

int main() {

    string str1 = "bdefg";
    string  str2 = "bfg";
    assert(lcs1(str1, str2) == 3);
    assert(lcs2(str1, str2) == 3);
    assert(lcs3(str1, str2) == 3);
    assert(lcs4(str1, str2) == 3);
    assert(lcs5(str1, str2) == 3);

    str1 = "mnop", str2 = "mnq";
    assert(lcs1(str1, str2) == 2);
    assert(lcs2(str1, str2) == 2);    
    assert(lcs3(str1, str2) == 2);
    assert(lcs4(str1, str2) == 2);
    assert(lcs5(str1, str2) == 2);

    
    
    
    return 0;
}