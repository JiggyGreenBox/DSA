#include <iostream>
#include <vector>
using namespace std;

/*
Determine the number of unique ways to reach the nth step, given that each
move can be either 1 or 2 steps at a time.

at step 0, 0
at step 1, 1
at step 2, 1+1, 2 -> 2
at step 3, 1+1+1, 2+1, 1+2 -> 3 ways
at step 4, 1+1+1+1, 2+2, 1+2+1, 2+1+1, 1+1+2 -> 5 ways


steps[0] = 0
steps[1] = 1
steps[2] = 2
if n > 2
    steps[n] = (1 + steps[n-1]) + (2 + steps[n-2])


    6= 5 + 4

    5 = 4+3


    steps[3] = 2 + 1 = 3

    steps[4] = 3 + 2 = 5

    steps[5] = steps[4] + steps[3]
             = 5 + 3    

    steps[6] = steps[5] + steps[4]
             = 8 + 5 = 13
    11111
    222
    11112
    11121
    11211
    12111
    21111
    1122
    1212
    2112
    1221
    2121
    2211

    


target is 7
111111
21111
 2
  2
   2
    2
2211
1221
1122
2112
1212
2121
222

11
2

[6] + 1
[5] + 2



distince choices = 2
set = 5

5p2 = 5! / 3!
5*4 = 20

5 = 4

5 = 5p2



    
THE INTUITION:
for any step n, if we are 1 step away take 1 step
if we are 2 steps away then take 2 steps
    we could take 1+1 steps if we are n-2 steps away
    but that is already taken care of by n-1
        if we take 1 step from n-2 we are at n-1

if there are 3 ways to reach n-1, then there are 3 ways to take +1 steps and reach n
likewise if there 7 ways to reach n-2, then there are 7 ways to take +2 steps and reach n
total n = +1-step-ways + +2step-ways

f[n] = f[n-1] + f[n-2]
    
    

*/
int climbStairs_rec(int n) {
    if(n <= 0) return 0; // []
    if(n == 1) return 1; // [1]
    if(n == 2) return 2; // [1,1] , [2]

    return climbStairs_rec(n-1) + climbStairs_rec(n-2);
}
/*
above is mathematically correct
but for consistency we write it like this
f[0] = 1
f[1] = 1
which makes f[2] = 1+1 = 2
f[0] = 1 doesnt make sense
*/
int climb(int n) {
    if(n == 0 || n == 1) return 1;

    return climb(n-1) + climb(n-2);
}


int helper(int n, vector<int> & dp) {
    if(n<=1) return 1;
    if(dp[n] != -1) return dp[n];

    return dp[n] = helper(n-1, dp) + helper(n-2, dp);
}

int climbStairs_memo(int n) {        
    vector<int> dp(n+1, -1);
    return helper(n, dp);
}

// 1 = 1
// 2 = 2
// c = p1+p2
// 3 = 2+1
// 4 = 3+2



int climbStairs_bot_up(int n) {    
    // if(n<=2) return n;
    if(n == 0) return 1;
    if(n == 1) return 1;
    if(n == 2) return 2;

    int prev2 = 1;
    int prev1 = 2;

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


/*
climbing stairs
    f[1] = [1]
    f[2] = 2 (1+1 step or 2 steps)

    f[n] = take one step from f[n-1] + take 2 steps from f[n-2]
    f[n] = f[n-1] + f[n-2]

    if n <= 1 return 1, base case
    f[0] = 1, non intuitive but consistent vs
        if(n <= 0) return 0; // []
        if(n == 1) return 1; // [1]
        if(n == 2) return 2; // [1,1] , [2]

    
    int climb(int n) {
        if(n == 0 || n == 1) return 1;

        return climb(n-1) + climb(n-2);
    }

    // add dp array


    bottom up
            dp[0] = 1
            dp[1] = 1
        
        for i=2;i<n; i++
            dp[i] = dp[i-1] + dp[i-2]

    we only need last 2
        prev1 = 1
        prev2 = 1
    for i=2; i<n; i++
        curr = prev1 + prev2
        prev2 = prev1
        prev1 = curr

    
    
*/