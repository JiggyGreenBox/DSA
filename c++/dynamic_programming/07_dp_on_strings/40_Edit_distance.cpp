/*
Edit distance
    [https://takeuforward.org/practice/dsa/edit-distance?category=dp-on-strings&source=strivers-a2z-dsa-sheet]

Given two strings start and target, you need to determine the minimum 
number of operations required to convert the string start into the 
string target. The operations you can use are:

Insert a character: Add any single character at any position in the 
string.

Delete a character: Remove any single character from the string.

Replace a character: Change any single character in the string to 
another character.

The goal is to transform start into target using the fewest number of 
these operations.

Example 1:
    Input: start = "planet", target = "plan"

    Output: 2

    Explanation: 

    To transform "planet" into "plan", the following operations are 
    required:

    1. Delete the character 'e': "planet" -> "plan"

    2. Delete the character 't': "plan" -> "plan"

    Thus, a total of 2 operations are needed.

Example 2:
    Input: start = "abcdefg", target = "azced"

    Output: 4

    Explanation: 

    To transform "abcdefg" into "azced", the following operations are 
    required:

    1. Replace 'b' with 'z': "abcdefg" -> "azcdefg"

    2. Delete 'd': "azcdefg" -> "azcefg"

    3. Delete 'f': "azcefg" -> "azceg"

    4. Replace 'g' with 'd': "azceg" -> "azced"

    Thus, a total of 4 operations are needed.
*/

/*

abce
abcf


if characters match

    "abc"
    "abc"
    we do nothing move to the next pair
        i+1, j+1

    when they dont match
        
        replace
            "abc"
            "axc"
                i+1, j+1
                    this is +1 operations

        insert into A
            "ac"
            "abc"
                i+1,j
                    this is +1 operation

        insert into B
            "abc"
            "ac"
                i, j+1
                    this is +1 operation

    then
        f(i,j) = min(replace, insertA, insertB)

        base case
            if i==end || j == end
                return 0

    f(i,j)
        min operations from i,j onwards to make strings same


*/
#include <string>
#include <algorithm>
#include <vector>
#include <assert.h>
using namespace std;

// 3^(n+m) time
// n+m stack
int f(int i, int j, string &a, string &b) {
    int n = a.size();
    int m = b.size();

    // planet
    // plan
    // at n, remove "et"
    if(i == n) 
        return m-j; // insert all b[rem] into a

    if(j == m)
        return n-i; // delete all a[rem]

    if(a[i] == b[j]) {
        return f(i+1, j+1, a, b);
    }

    // replace a[i] with b[j]
    int replace = 1 + f(i+1, j+1, a, b);

    // insert b[j] into a[i]
    int insert = 1 + f(i, j+1, a, b);

    // delete a[i]
    int del = 1 + f(i+1, j, a, b);
    
    return min({replace, insert, del});
}
int editDistance1(string start, string target) {
    return f(0, 0, start, target);
}

// nm time
// nm space
// n+m stack
int memo(int i, int j, string &a, string &b, vector<vector<int>> &dp) {
    int n = a.size();
    int m = b.size();

    // planet
    // plan
    // at n, remove "et"
    if(i == n) 
        return m-j; // insert all b[rem] into a

    if(j == m)
        return n-i; // delete all a[rem]

    if(dp[i][j] != -1)
        return dp[i][j];

    if(a[i] == b[j]) {
        return dp[i][j] = memo(i+1, j+1, a, b, dp);
    }

    // replace a[i] with b[j]
    int replace = 1 + memo(i+1, j+1, a, b, dp);

    // insert b[j] into a[i]
    int insert = 1 + memo(i, j+1, a, b, dp);

    // delete a[i]
    int del = 1 + memo(i+1, j, a, b, dp);
    
    return dp[i][j] = min({replace, insert, del});
}
int editDistance2(string start, string target) {
    int n = start.size();
    int m = target.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return memo(0, 0, start, target, dp);
}

/*
tabulation
    list the dependencies

    match
        dp[i][j] = dp[i+1][j+1]

    no match
        replace = 1 + dp[i+1][j+1]

        insert = 1 + dp[i][j+1]

        delete = 1 + dp[i+1][j]
        
        max(...)

    we need i+1
        so i = [n-1..0]

    we need j+1
        so j = [m-1..0]

    what about boundaries
        dp[n][*] = m - (*)
        dp[*][m] = n - (*)
*/
/*
  j      p l a n 0       m
i   p    2 3 4 5 6
    l    3 2 3 4 5
    a    4 3 2 3 4
    n    4 3 3 2 3
    e    4 3 2 2 2
    t    4 3 2 1 1
n   0    4 3 2 1 0

*/

int editDistance3(string start, string target) {
    int n = start.size();
    int m = target.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i=0; i<=n; i++) {
        dp[i][m] = n-i; // at end of target, insert start into target
    }
    for(int j=0; j<=m; j++) {
        dp[n][j] = m-j; // at end of start, delete from target
    }

    for(int i=n-1; i>=0; i--) {
        for(int j=m-1; j>=0; j--) {


            if(start[i] == target[j]) {
                dp[i][j] = dp[i+1][j+1];
            }
            else {
                // replace a[i] with b[j]
                int replace = dp[i+1][j+1];

                // insert b[j] into a[i]
                int insert = dp[i][j+1];

                // delete a[i]
                int del = dp[i+1][j];
                
                dp[i][j] = 1 + min({replace, insert, del});
            }            
        }
    }
    return dp[0][0];
}

int editDistance4(string start, string target) {
    int n = start.size();
    int m = target.size();
    // vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    vector<int> next(m+1, 0);
    vector<int> curr(m+1, 0);


    // for(int i=0; i<=n; i++) {
    //     dp[i][m] = n-i; // at end of target, insert start into target
    // }
    for(int j=0; j<=m; j++) {
        next[j] = m-j; // at end of start, delete from target
    }    

    for(int i=n-1; i>=0; i--) {

        curr[m] = n-i;

        for(int j=m-1; j>=0; j--) {

            if(start[i] == target[j]) {
                curr[j] = next[j+1];
            }
            else {
                // replace a[i] with b[j]
                int replace = next[j+1];

                // insert b[j] into a[i]
                int insert = curr[j+1];

                // delete a[i]
                int del = next[j];
                
                curr[j] = 1 + min({replace, insert, del});
            }            
        }
        next = curr;
    }
    return next[0];
}

int editDistance5(string start, string target) {
    int n = start.size();
    int m = target.size();
    // vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    // vector<int> next(m+1, 0);
    // vector<int> curr(m+1, 0);

    vector<int> dp(m+1, 0);


    // for(int i=0; i<=n; i++) {
    //     dp[i][m] = n-i; // at end of target, insert start into target
    // }
    for(int j=0; j<=m; j++) {
        dp[j] = m-j; // at end of start, delete from target
    }    

    for(int i=n-1; i>=0; i--) {

        dp[m] = n-i;
        int diagonal = n-i-1;

        for(int j=m-1; j>=0; j--) {

            int old = dp[j];

            if(start[i] == target[j]) {
                // curr[j] = next[j+1];
                dp[j] = diagonal;
            }
            else {
                // replace a[i] with b[j]
                // int replace = next[j+1];
                int replace = diagonal;

                // insert b[j] into a[i]
                // int insert = curr[j+1];
                int insert = dp[j+1];

                // delete a[i]
                // int del = next[j];
                int del = dp[j];
                
                // curr[j] = 1 + min({replace, insert, del});
                dp[j] = 1 + min({replace, insert, del});
            }  
            diagonal = old;          
        }
        // next = curr;
    }
    // return next[0];
    return dp[0];
}

int main() {

    string start = "planet";
    string target = "plan";
    // auto x = editDistance2(start, target);
    assert(editDistance1(start, target) == 2);
    assert(editDistance2(start, target) == 2);
    assert(editDistance3(start, target) == 2);
    assert(editDistance4(start, target) == 2);
    assert(editDistance5(start, target) == 2);

    start = "abcdefg"; target = "azced";
    assert(editDistance1(start, target) == 4);
    assert(editDistance2(start, target) == 4);
    assert(editDistance3(start, target) == 4);
    assert(editDistance4(start, target) == 4);
    assert(editDistance5(start, target) == 4);


    assert(editDistance5("planet", "plan") == 2);
    assert(editDistance5("abcdefg", "azced") == 4);
    assert(editDistance5("", "abc") == 3);
    assert(editDistance5("abc", "") == 3);
    assert(editDistance5("", "") == 0);
    assert(editDistance5("horse", "ros") == 3);

    return 0;
}