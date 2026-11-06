/*
Longest palindromic subsequence
    [https://takeuforward.org/practice/dsa/longest-palindromic-subsequence?category=dp-on-strings&source=strivers-a2z-dsa-sheet]
Given a string, Find the longest palindromic subsequence length in 
given string.

A palindrome is a sequence that reads the same backwards as forward.

A subsequence is a sequence that can be derived from another sequence 
by deleting some or no elements without changing the order of the 
remaining elements.

Example 1:
    Input: s = "eeeme"

    Output: 4

    Explanation: The longest palindromic subsequence is "eeee", which has 
    a length of 4.

Example 2:
    Input: s = "annb"

    Output: 2

    Explanation: The longest palindromic subsequence is "nn", which has a 
    length of 2.
*/ 

/*
the hint we received is
    if a palindrome exists
    then first == last
        then we can check within

f(first, last)
    if the chars are the same
        we can add 2 to the inner substr

    if different
        we can add 1 without last
        we can add 1 without first

    return max()



aba
    return 3
abbda
    return 4
abda
    return 3
abba
    return 4
*/
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

bool isPalindrome(int start, int end, string &s) {

    while(start < end) {
        if(s[start] != s[end])
            return false;

        start++;
        end--;
    }
    return true;
}


// 2^n time, n stack space
int rec(int start, int end, string &s) {

    if(start > end) 
        return 0;

    if(start == end)
        return 1;
    
    if(s[start] == s[end]) {
        return 2 + rec(start+1, end-1, s);
    }

    int skip1 = rec(start, end-1, s);
    int skip2 = rec(start+1, end, s);
    return max(skip1, skip2);
}

int longestPalinSubseq1(string s) {
    return rec(0, s.size()-1, s);
}

// 2n^2 time
// n^2 space
// n stack space
int memo(int start, int end, string &s, vector<vector<int>> &dp) {

    if(start > end) 
        return 0;

    if(start == end)
        return 1;

    if(dp[start][end] != -1)
        return dp[start][end];
    
    if(s[start] == s[end]) {
        return dp[start][end] = 2 + memo(start+1, end-1, s, dp);
    }

    int skip1 = memo(start, end-1, s, dp);
    int skip2 = memo(start+1, end, s, dp);
    return dp[start][end] = max(skip1, skip2);
}

int longestPalinSubseq2(string s) {
    // f(i,j) palim len from i,j
    // then each i and j can be combined
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return memo(0, s.size()-1, s, dp);
}

// get the dp dependency order first
// dp[start][end] = 2 + dp[start+1][end-1];
// int skip1 = dp[start][end-1];
// int skip2 = dp[start+1][end];            
// dp[start][end] = max(skip1, skip2);

// we need start+1, need to come backwards from start
// end-1 forwards for end

int longestPalinSubseq3(string s) {
    // f(i,j) palim len from i,j
    // then each i and j can be combined
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for(int start=n-1; start>=0; start--) {

        dp[start][start] = 1; // each single char is a palindrome

        for(int end=start+1; end<n; end++) {

            if(s[start] == s[end]) {
                dp[start][end] = 2 + dp[start+1][end-1];  // this is the next diagonal, who overwrites it?            
            }
            else {
                int skip1 = dp[start][end-1]; // 1 cell behind?
                int skip2 = dp[start+1][end];            // next and below?
                dp[start][end] = max(skip1, skip2);
            }            
        }
    }
    return dp[0][n-1];
}

// 2 row
// next row and end-1 is only required
int longestPalinSubseq4(string s) {    
    int n = s.size();    
    vector<int> next(n, 0);
    vector<int> curr(n, 0);
    
    for(int start=n-1; start>=0; start--) {

        curr[start] = 1; // each single char is a palindrome

        for(int end=start+1; end<n; end++) {
            
            if(s[start] == s[end]) {
                curr[end] = 2 + next[end-1];                
            }
            else {
                int skip1 = curr[end-1];
                int skip2 = next[end];            
                curr[end] = max(skip1, skip2);
            }            
        }
        next = curr;
    }
    return next[n-1];
}


int longestPalinSubseq5(string s) {
    int n = s.size();

    vector<int> dp(n, 0);

    for (int i = n - 1; i >= 0; i--) {
        dp[i] = 1;

        int diagonal = 0;

        for (int j = i + 1; j < n; j++) {
            int old = dp[j];

            if (s[i] == s[j]) {
                dp[j] = 2 + diagonal;
            } else {
                dp[j] = max(dp[j], dp[j - 1]);
            }

            diagonal = old;
        }
    }

    return dp[n - 1];
}



int main() {
    string s = "annb";
    auto x = longestPalinSubseq3(s);
    assert(longestPalinSubseq1(s) == 2);
    assert(longestPalinSubseq2(s) == 2);
    assert(longestPalinSubseq3(s) == 2);
    assert(longestPalinSubseq4(s) == 2);
    assert(longestPalinSubseq5(s) == 2);

    s = "eeeme";
    // x = longestPalinSubseq1(s);
    assert(longestPalinSubseq1(s) == 4);
    assert(longestPalinSubseq2(s) == 4);
    assert(longestPalinSubseq3(s) == 4);
    assert(longestPalinSubseq4(s) == 4);
    assert(longestPalinSubseq5(s) == 4);
    return 0;
}