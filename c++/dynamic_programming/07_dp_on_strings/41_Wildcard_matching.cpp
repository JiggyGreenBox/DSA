/*
Wildcard matching
    [https://takeuforward.org/practice/dsa/wildcard-matching?category=dp-on-strings&source=strivers-a2z-dsa-sheet]

Given a string str and a pattern pat, implement a pattern matching 
function that supports the following special characters:

'?' Matches any single character.

'*' Matches any sequence of characters (including the empty sequence).

The pattern must match the entire string.

Example 1:
    Input: str = "xaylmz", pat = "x?y*z"

    Output: true

    Explanation: 

    The pattern "x?y*z" matches the string "xaylmz":

    - '?' matches 'a'

    - '*' matches "lm"

    - 'z' matches 'z'

Example 2:
    Input: str = "xyza", pat = "x*z"

    Output: false

    Explanation: 

    The pattern "x*z" does not match the string "xyza" because there is 
    an extra 'a' at the end of the string that is not matched by the 
    pattern.

*/

/*
gpt hint

    choices
    f(i,j)

        if(p[j] == ?)
            can skip this char
            return f(i+1, j+1)
        else if(p[j] == *)
            can skip current char or skip *
            c1 = f(i+1, j)                
            c2 = f(i, j+1)
            return c1 || c2

        else if(s[i] == p[j])            
            char match proceed
            f(i+1, j+1)
        
        return false, no char match and not ? or *

    whats the base case
        both have no chars left
        if(j==m)
            return i==n

        // the remaining chars contain non *
        if(i==n)
            while(j<m) {
                if(p[j++] != *) return false
            }
            return true

        the pattern matches the string not the other way around
*/
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>
using namespace std;

/*
f(i,j)
    return if string matches the pattern
    from i of str and j of pattern
*/
// 2^n+m time
// n+m stack space
int f(int i, int j, string &str, string &pat) {
    int n = str.size();
    int m = pat.size();

    if(j == m)
        return i == n; // true if we used all of str to match pat

    // we finished the string
    // only if pattern has ***s remaining is this valid now
    if(i == n) {
        while(j<m) {
            if(pat[j++] != '*')
                return false;            
        }
        return true;
    }

    if(str[i] == pat[j] || pat[j] == '?') {
        return f(i+1, j+1, str, pat);
    }

    // str1
    // s*1
    if(pat[j] == '*') {
        bool pick = f(i+1, j, str, pat); // we picked the char at i from str
        bool skip = f(i, j+1, str, pat); // we chose nothing

        return pick || skip;
    }

    return false;
}
bool wildCard1(string str, string pat) {
    return f(0, 0, str, pat);
}

// nm time
// nm space
// n+m stack space
int memo(int i, int j, string &str, string &pat, vector<vector<int>> &dp) {
    int n = str.size();
    int m = pat.size();

    if(j == m)
        return i == n; // true if we used all of str to match pat

    // we finished the string
    // only if pattern has ***s remaining is this valid now
    if(i == n) {
        while(j<m) {
            if(pat[j++] != '*')
                return false;            
        }
        return true;
    }

    if(dp[i][j] != -1)
        return dp[i][j];

    if(str[i] == pat[j] || pat[j] == '?') {
        return dp[i][j] = memo(i+1, j+1, str, pat, dp);
    }

    // str1
    // s*1
    if(pat[j] == '*') {
        bool pick = memo(i+1, j, str, pat, dp); // we picked the char at i from str
        bool skip = memo(i, j+1, str, pat, dp); // we chose nothing

        return dp[i][j] = pick || skip;
    }

    return dp[i][j] = false;
}
bool wildCard2(string str, string pat) {
    int n = str.size();
    int m = pat.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return memo(0, 0, str, pat, dp);
}

/*
tabulation
    list the dependencies
    i+1,j+1

    i+1,j
    i,j+1

    need next row
        come backwards
    next next col
        come backwards
       
           0 1 2 3 4 5
        |  x ? y * z -
        | 
    0 x |  T F F T F F
    1 a |  F T F T F F
    2 y |  F T T T F F
    3 l |  F F F T F F
    4 m |  F F F T F F
    5 z |  F F F T T F
    6 - |  F F F F F T


*/
bool wildCard3(string str, string pat) {

    int n = str.size();
    int m = pat.size();

    vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
            
    dp[n][m] = true;        
    
    // set j as true if all chars till end are *
    for(int j=m-1; j>=0; j--) {
        if(pat[j] == '*') {
            dp[n][j] = true;
        }
        else{
            break;
        }
    }

    for(int i=n-1; i>=0; i--) {
        for(int j=m-1; j>=0; j--) {

            if(str[i] == pat[j] || pat[j] == '?') {
                dp[i][j] = dp[i+1][j+1];
            }            
            else if(pat[j] == '*') {
                bool pick = dp[i+1][j];
                bool skip = dp[i][j+1];
                    
                dp[i][j] = pick || skip;
            }
            else {
                dp[i][j] = false;
            }
        }
    }
    return dp[0][0];
}

bool wildCard4(string str, string pat) {

    int n = str.size();
    int m = pat.size();

    // vector<vector<bool>> dp(n+1, 
    vector<bool> next(m+1, false);
    vector<bool> curr(m+1, false);
            
    next[m] = true;        
    
    // set j as true if all chars till end are *
    for(int j=m-1; j>=0; j--) {
        if(pat[j] == '*') {
            next[j] = true;
        }
        else{
            break;
        }
    }

    for(int i=n-1; i>=0; i--) {
        curr[m] = false;
        for(int j=m-1; j>=0; j--) {

            if(str[i] == pat[j] || pat[j] == '?') {
                curr[j] = next[j+1];
            }            
            else if(pat[j] == '*') {
                bool pick = next[j];
                bool skip = curr[j+1];
                    
                curr[j] = pick || skip;
            }
            else {
                curr[j] = false;
            }
        }
        next = curr;
    }
    return next[0];
}

bool wildCard5(string str, string pat) {

    int n = str.size();
    int m = pat.size();
    
    vector<bool> dp(m+1, false);
            
    // next[m] = true;        
    dp[m] = true;
    
    // set j as true if all chars till end are *
    for(int j=m-1; j>=0; j--) {
        if(pat[j] == '*') {
            // next[j] = true;
            dp[j] = true;
        }
        else{
            break;
        }
    }

    for(int i=n-1; i>=0; i--) {

        dp[m] = false;
        // bool diagonal = false;
        bool diagonal = (i == n-1); // only last diagonal is T

        for(int j=m-1; j>=0; j--) {

            bool old = dp[j];

            if(str[i] == pat[j] || pat[j] == '?') {
                // curr[j] = next[j+1];
                dp[j] = diagonal;
            }            
            else if(pat[j] == '*') {

                dp[j] = dp[j] || dp[j+1];
            }
            else {
                dp[j] = false;
            }
            diagonal = old;
        }
    }
    return dp[0];
}



int main() {
    string str = "xaylmz";
    string pat = "x?y*z";
    assert(wildCard1(str, pat) == true);
    assert(wildCard2(str, pat) == true);
    assert(wildCard3(str, pat) == true);
    assert(wildCard4(str, pat) == true);
    assert(wildCard5(str, pat) == true);

    str = "xyza"; pat = "x*z";
    assert(wildCard1(str, pat) == false);
    assert(wildCard2(str, pat) == false);
    assert(wildCard3(str, pat) == false);
    assert(wildCard4(str, pat) == false);
    assert(wildCard5(str, pat) == false);

    assert(wildCard5("", "") == true);
    assert(wildCard5("", "***") == true);
    assert(wildCard5("", "*a") == false);
    assert(wildCard5("abc", "") == false);
    assert(wildCard5("abc", "abc") == true);
    assert(wildCard5("abc", "a?c") == true);
    assert(wildCard5("abc", "a*c") == true);
    assert(wildCard5("abc", "a*d") == false);
    assert(wildCard5("abc", "*") == true);
    assert(wildCard5("abc", "a**c") == true);

    // vector<pair<string, string>> tests = {
    //     {"", ""},
    //     {"", "***"},
    //     {"", "*a"},
    //     {"abc", ""},
    //     {"abc", "abc"},
    //     {"abc", "a?c"},
    //     {"abc", "a*c"},
    //     {"abc", "a*d"},
    //     {"abc", "*"},
    //     {"abc", "a**c"}
    // };

    // for (auto &[s, p] : tests) {
    //     cout << "str: [" << s << "]"
    //         << " pat: [" << p << "]"
    //         << " result: " << wildCard5(s, p) << '\n';
    // }

    return 0;
}