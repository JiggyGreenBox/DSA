/*
Count Palindromic Subsequences
    [https://takeuforward.org/practice/dsa/count-palindromic-subsequences?category=dp-on-strings&source=strivers-a2z-dsa-sheet]

You are given a string s consisting of lowercase English letters.

Return the total number of palindromic subsequences present in the 
string.

A subsequence is a sequence that can be derived from another string 
by deleting some or no characters without changing the order of the 
remaining characters.

A palindromic subsequence is one that reads the same forward and 
backward.

Example 1:
    Input: s = "abcd"

    Output: 4

    Explanation: Only the single characters are palindromic: "a", "b", 
    "c", "d"

Example 2:
    Input: s = "aab"

    Output: 4

    Explanation: The palindromic subsequences are: "a", "a", "b", and "aa"
*/

/*
derivation
    if have a palindrome, bxb
        and for f(i,j)
            if s[i] == s[j] == a
                a(bxb)a
        then the 2 a's add +1 to palindrome count

    then
        we need count of ALL

    so we try skip1 and skip2

    but there is overlap
        this overlap is f(i+1, j-1)

    f(i,j)
        if i>j return 0
        if i==j return 1

        int pick = 0
        if s[i] == s[j]
            pick = 1 + f(i+1, j-1)
        
        int skip1 = f(i+1, j)
        int skip2 = f(i, j+1)
        int overlap = f(i+1, j-1)

        int ans = skip1 + skip2 - overlap + pick
            but pick = overlap+1
                when characters match

                    return skip1 + skip2 + 1

            and pick = 0
                when characters dont match

                return skip1 + skip2 - overlap
        
*/
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

int f(int i, int j, const string &s) {
    if(i > j)
        return 0;

    if(i == j)
        return 1;


    int skip1 = f(i+1, j, s);
    int skip2 = f(i, j-1, s);

    if(s[i] == s[j])
        return skip1 + skip2 + 1;

    return skip1 + skip2 - f(i+1, j-1, s);
}
int countPalSubseq(const string& s) {
    int n = s.size();
    return f(0, n-1, s);
}

int memo(int i, int j, const string &s, vector<vector<int>> &dp) {
    if(i > j)
        return 0;

    if(i == j)
        return 1;

    if(dp[i][j] != -1)
        return dp[i][j];

    int skip1 = memo(i+1, j, s, dp);
    int skip2 = memo(i, j-1, s, dp);

    if(s[i] == s[j])
        return dp[i][j] = skip1 + skip2 + 1;

    return dp[i][j] = skip1 + skip2 - memo(i+1, j-1, s, dp);
}
int countPalSubseq2(const string& s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n,-1));
    return memo(0, n-1, s, dp);
}


/*
tabulation
    list dependencies / draw table

    i>j, 0
    i==j, 1

    skip1 = dp[i+1, j] next row
    skip2 = dp[i][j-1] prev col
    overlap = dp[i+1][j01] next diagonal, bot-right

    we move from n-1 to 0 for i
    and j=n-1 till i+1 for j

    if chars equal
        dp[i][j] = dp[i+1][j] + dp[i][j-1] + 1

            bot + left + 1

    else
        dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1]
            bot + left - botleft


    
        |  0 1 2 3
        |  a a b -
    0 a |  1 3 4 0
    1 a |  0 1 2 0
    2 b |  0 0 1 0
    3 - |  0 0 0 0
*/
int countPalSubseq3(const string& s) {
    int n = s.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    for(int i=n-1; i>=0; i--) {

        dp[i][i] = 1;

        for(int j=i+1; j<n; j++) {

            if(s[i] == s[j]) {
                dp[i][j] = dp[i+1][j] + dp[i][j-1] + 1;
            }
            else {
                dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
            }
        }
    }
    return dp[0][n-1];
}

int countPalSubseq4(const string& s) {
    int n = s.size();    
    
    vector<int> next(n+1, 0);
    vector<int> curr(n+1, 0);

    for(int i=n-1; i>=0; i--) {
                
        curr.assign(n+1, 0);
        curr[i] = 1;

        for(int j=i+1; j<n; j++) {

            if(s[i] == s[j]) {                
                curr[j] = next[j] + curr[j-1] + 1;
            }
            else {                
                curr[j] = next[j] + curr[j-1] - next[j-1];
            }
        }
        next = curr;
    }
    return next[n-1];
}

int countPalSubseq5(const string& s) {
    int n = s.size();    
        
    vector<int> dp(n+1, 0);

    for(int i=n-1; i>=0; i--) {
        dp[i] = 1;

        int diag = 0;

        for(int j=i+1; j<n; j++) {

            int old = dp[j];

            if(s[i] == s[j]) {
                dp[j] = dp[j] + dp[j-1] + 1;
            }
            else {
                dp[j] = dp[j] + dp[j-1] - diag;
            }

            diag = old;
        }
    }
    return dp[n-1];
}

int main() {
    string s = "abcd";
    assert(countPalSubseq(s) == 4);
    assert(countPalSubseq2(s) == 4);
    assert(countPalSubseq3(s) == 4);
    assert(countPalSubseq4(s) == 4);
    assert(countPalSubseq5(s) == 4);

    s = "aab";
    assert(countPalSubseq(s) == 4);
    assert(countPalSubseq2(s) == 4);
    assert(countPalSubseq3(s) == 4);
    assert(countPalSubseq4(s) == 4);
    return 0;
}