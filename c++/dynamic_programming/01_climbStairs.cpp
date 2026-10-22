#include <iostream>
#include <vector>
using namespace std;

/*
Determine the number of unique ways to reach the nth step, given that each
move can be either 1 or 2 steps at a time.

the last step is
    +1 from n-1
    +2 from n-2

State: dp[n] = number of ways to reach step n.
    dp[n] = dp[n-1] + dp[n-2];

Base cases:
    dp[0] = 1;  //  One way: take no steps (empty sequence)
    dp[1] = 1   // [1] take 1 step
    dp[2] = 2   // [1, 1], [2] 
*/

/*
=======================================
Recursion
    2 branches at each level
    n levels
    O(2^n) time
    O(1) space  
*/
int climbStairs_rec(int n) {
    if(n <= 1) return 1;
    
    // 0, 1
    // 1, 1
    // 2, 2 f(1)+f(0)

    return climbStairs_rec(n-1) + climbStairs_rec(n-2);
}
int climb(int n) {
    if(n == 0 || n == 1) return 1;

    return climb(n-1) + climb(n-2);
}
// =======================================
/*
2. Memoization (Top-Down DP)
    O(n) time
    O(n) space 

    we dont recalculate compared to rec
    to we only calculate n+1 states once
    number of calls is only n

    stack space is o(n)
    dp array space is O(n)
*/

int helper(int n, vector<int> & dp) {
    if(n<=1) return 1;
    if(dp[n] != -1) return dp[n];

    return dp[n] = helper(n-1, dp) + helper(n-2, dp);
}

int climbStairs_memo(int n) {        
    vector<int> dp(n+1, -1);
    return helper(n, dp);
}


// Time: O(n)
// Auxiliary space: O(1)
int climbStairs_bot_up(int n) {    
    if(n <= 1) return 1;    
    if(n == 2) return 2;

    int prev2 = 1; // dp[1]
    int prev1 = 2; // dp[2]

    for(int i=3; i<=n; i++) {
        int curr = prev1 + prev2;
        
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main() {
    cout << climbStairs_rec(5) << endl;
    cout << climbStairs_rec(6) << endl;
    cout << climbStairs_rec(7) << endl;

    cout << climbStairs_memo(5) << endl;
    cout << climbStairs_memo(6) << endl;
    cout << climbStairs_memo(7) << endl;

    cout << climbStairs_bot_up(5) << endl;
    cout << climbStairs_bot_up(6) << endl;
    cout << climbStairs_bot_up(7) << endl;


    return 0;
}
