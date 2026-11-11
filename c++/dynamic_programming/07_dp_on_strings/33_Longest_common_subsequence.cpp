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


f(i, j)
    if(i == end)
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
int rec(int i, int j, string &s1, string &s2) {
    if(i == s1.size() || j == s2.size())
        return 0;
    
    if(s1[i] == s2[j])
        return 1 + rec(i+1, j+1, s1, s2);
    
    int skip1 = rec(i+1, j, s1, s2);
    int skip2 = rec(i, j+1, s1, s2);
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
int memo(int i, int j, string &s1, string &s2, vector<vector<int>> &dp) {
    if(i == s1.size() || j == s2.size())
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];
    
    if(s1[i] == s2[j])
        return dp[i][j] = 1 + memo(i+1, j+1, s1, s2, dp);
    
    int skip1 = memo(i+1, j, s1, s2, dp);
    int skip2 = memo(i, j+1, s1, s2, dp);
    return dp[i][j] = max(skip1, skip2);
}


// memo
// cache for all possible 
// f(i, j)
// i range 0..n
// j range 0..n
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

/*

f(i,j)
    longest common subsequence from i,j onwards

    if(s1[i] == s2[j])
        dp[i][j] = 1 + dp[i+1][j+1]

    dp[i][j] = max(dp[i+1][j], dp[i][j+1])


    need next row, i+1
        move from last row to first
    need j or j+1
        move from last col to first


      0 1 2 3 4 5
      b d e f g
    --------------
0 b | 3 2 2 2 1 0
1 f | 2 2 2 2 1 0
2 g | 1 1 1 1 1 0
3   | 0 0 0 0 0 0

return dp[0][0]
*/


int lcs3(string str1, string str2) {

    if(str1.size() < str2.size())         
        swap(str1, str2);

    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for(int i=str1.size()-1; i>=0; i--) {
        for(int j=str2.size()-1; j>=0; j--) {
            
            /*
            myversion
            
            int pick = 0;
            if(str1[i] == str2[j])
                pick = 1 + dp[i+1][j+1];
                        
            int skip1 = dp[i+1][j];
            int skip2 = dp[i][j+1];

            dp[i][j] = max({pick, skip1, skip2});
            */

            // canonical
            if (str1[i] == str2[j])
                dp[i][j] = 1 + dp[i+1][j+1];
            else
                dp[i][j] = max(dp[i+1][j],
                                    dp[i][j+1]);

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

    for(int i=str1.size()-1; i>=0; i--) {
        for(int j=str2.size()-1; j>=0; j--) {
            // canonical
            if (str1[i] == str2[j])
                curr[j] = 1 + next[j+1];
            else
                curr[j] = max(next[j],
                                    curr[j+1]);

        }
        next = curr;
    }
    return next[0];
}

// base cases become prefilled in dp array
// to make 1 dp 
// list all values
//  next[j+1]    old (store this)
//  next[j]      old
//  curr[j + 1]  newly calculated value

int lcs5(string str1, string str2) {

    if(str1.size() < str2.size())         
        swap(str1, str2);

    int n = str1.size();
    int m = str2.size();

    
    vector<int> next(m+1, 0);
    vector<int> curr(m+1, 0);
    vector<int> dp(m+1, 0);
    int diagonal = dp[m];

    for(int i=str1.size()-1; i>=0; i--) {
        // diagonal = 0;
        for(int j=str2.size()-1; j>=0; j--) {
            // canonical
            // if (str1[i] == str2[j])
            //     curr[j] = 1 + next[j+1];
            // else
            //     curr[j] = max(next[j],
            //                         curr[j+1]);

            int temp = dp[j];

            if (str1[i] == str2[j])
                dp[j] = 1 + diagonal; // j+1, inital value is 0 aka dp[m]
            else
                dp[j] = max(dp[j],
                                    dp[j+1]);
                
            diagonal = temp; // becomes the j+1 in the next iter
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