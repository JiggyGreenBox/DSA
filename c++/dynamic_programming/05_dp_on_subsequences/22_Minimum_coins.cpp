#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
Minimum coins

    Given an integer array of coins representing coins of different 
    denominations and an integer amount representing a total amount of 
    money. Return the fewest number of coins that are needed to make up 
    that amount. If that amount of money cannot be made up by any 
    combination of the coins, return -1. There are infinite numbers of 
    coins of each type
*/

// f(idx, amount_left) 
//     from this idx onwards
//     whats the minimum number of coins
//     to create amount left

int f_rec(int idx, vector<int> &coins, int amount) {
    int n = coins.size();

    if(amount == 0) return 0; // success
    if(idx == n) return 1e9; // ignore from min comparison
 
    // skip 
    int skip = f_rec(idx+1, coins, amount);

    // take 
    int take = 1e9;
    if(coins[idx] <= amount) {
        take = 1 + f_rec(idx, coins, amount - coins[idx]);
    }
    return min(skip, take);    
}


int MinimumCoins_1(vector<int>& coins, int amount) {
    int res = f_rec(0, coins, amount);
    if(res == 1e9) res = -1;
    return res;    
}
// ===================================================================
int f_memo(int idx, vector<int> &coins, int amount, vector<vector<int>> &dp) {
    int n = coins.size();

    if(amount == 0) return 0; // success
    if(idx == n) return 1e9; // ignore from min comparison

    if(dp[idx][amount] != -1) return dp[idx][amount];
 
    // skip 
    int skip = f_memo(idx+1, coins, amount, dp);

    // take 
    int take = 1e9;
    if(coins[idx] <= amount) {
        take = 1 + f_memo(idx, coins, amount - coins[idx], dp);
    }
    return dp[idx][amount] = min(skip, take);    
}
// dp array, 
    // range idx, 0..n-1,
    // amount 0..amount
int MinimumCoins_2(vector<int>& coins, int amount) {
    int n = coins.size();
    vector<vector<int>> dp(n, vector<int>(amount+1, -1));
    int res = f_memo(0, coins, amount, dp);
    if(res == 1e9) res = -1;
    return res;    
}

// ===================================================================
/*
tabulation
    dp[n][*] = inf, amount not reachable
    dp[*][0] = 0, success

    range idx, 0..n
    range amount, 0..amount


    iterate backwards because of i+1, for skip condition
*/
int MinimumCoins_3(vector<int>& coins, int amount) {

    int n = coins.size();

    vector<vector<int>> dp(n+1, vector<int>(amount+1, 1e9));

    // unreachable past array limits
    for(int i=0; i<=n; i++) {
        dp[i][0] = 0;
    }

    for(int i=n-1; i>=0; i--) {
        for(int a=0; a<=amount; a++) {

            int skip = dp[i+1][a];

            int take = 1e9;
            if(coins[i] <= a) {
                take = 1 + dp[i][a - coins[i]];
            }
            dp[i][a] = min(skip, take);
        }
    }

    return dp[0][amount] == 1e9 ? -1 : dp[0][amount];
}
// ===================================================================
int MinimumCoins_4(vector<int>& coins, int amount) {

    int n = coins.size();

    // vector<vector<int>> dp(n+1, 
    vector<int> next(amount+1, 1e9);

    next[0] = 0;    

    for(int i=n-1; i>=0; i--) {

        vector<int> curr(amount+1, 1e9);
        curr[0] = 0;

        for(int a=coins[i]; a<=amount; a++) {

            int skip = next[a];

            int take = 1e9;
            // if(coins[i] <= a) {
                take = 1 + curr[a - coins[i]];
            // }
            curr[a] = min(skip, take);
        }
        next = curr;
    }

    return next[amount] == 1e9 ? -1 : next[amount];
}

int MinimumCoins_5(vector<int>& coins, int amount) {

    int n = coins.size();
    
    vector<int> curr(amount+1, 1e9);
    curr[0] = 0;    

    for(int i=n-1; i>=0; i--) {
        
        for(int a=coins[i]; a<=amount; a++) {

            int skip = curr[a];
            
            int take = 1e9;
            if(curr[a - coins[i]] != 1e9) { // overflow protection
                take = 1 + curr[a - coins[i]];
            }                

            curr[a] = min(skip, take);
        }        
    }

    return curr[amount] == 1e9 ? -1 : curr[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    // vector<int> coins = {1,2};
    // int amount = 3;
    cout << MinimumCoins_1(coins, amount) << endl;
    cout << MinimumCoins_2(coins, amount) << endl;
    cout << MinimumCoins_3(coins, amount) << endl;
    cout << MinimumCoins_4(coins, amount) << endl;
    cout << MinimumCoins_5(coins, amount) << endl;


    coins = {2, 5};
    amount = 3;
    cout << MinimumCoins_1(coins, amount) << endl;
    cout << MinimumCoins_2(coins, amount) << endl;
    cout << MinimumCoins_3(coins, amount) << endl;
    cout << MinimumCoins_4(coins, amount) << endl;
    cout << MinimumCoins_5(coins, amount) << endl;
    return 0;
}

#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <assert.h>
#include <algorithm>
#include <numeric>
using namespace std;

/*
Minimum coins
we want minimum coins that can be used to create a sum
 [1,3]
    target = 3

then [3] not [1,1,1]
    ans = 3

f(0,3)
    pick = 1 + f(1, 2)
    skip = f(1,3)
    return min(pick, skip)

f(idx, target)
    minimum number of coins to create target

*/

// 2 choices at each idx
// we can skip till the end (n)
// or we can reduce by 1 t times (t)
// 2^(n+t) time
// n+t stack space
int rec(int idx, int target, vector<int> &coins) {
    // whats the base case  
    if(target == 0)
        return 0;
    
    if(idx == coins.size())
        return INT_MAX; // represents an invalid state

    int pick = INT_MAX;
    if(coins[idx] <= target) {
        int res = rec(idx, target - coins[idx], coins);
        if(res != INT_MAX)
            pick = 1 + res; // safe to pick
    }        

    int skip = rec(idx+1, target, coins);

    return min(pick, skip);
}


int MinimumCoins1(vector<int>& coins, int amount) {
    int ret =  rec(0, amount, coins);
    if(ret == INT_MAX)
        return -1;    
    return ret;
}


// 2nT time
// 2nT space
// n+t stack space
int memo(int idx, int target, vector<int> &coins, vector<vector<int>> &dp) {
    // whats the base case  
    if(target == 0)
        return 0;
    
    if(idx == coins.size())
        return INT_MAX; // represents an invalid state

    if(dp[idx][target] != -1)
        return dp[idx][target];

    int pick = INT_MAX;
    if(coins[idx] <= target) {
        int res = memo(idx, target - coins[idx], coins, dp);
        if(res != INT_MAX)
            pick = 1 + res; // safe to pick
    }        

    int skip = memo(idx+1, target, coins, dp);

    return dp[idx][target] = min(pick, skip);
}

// dp cache for recursion
// 0..n-1 states
// 0..target states
int MinimumCoins2(vector<int>& coins, int amount) {
    int n = coins.size();

    vector<vector<int>> dp(n, vector<int>(amount+1, -1));
    // handled by base case
    // for(int i=0; i<n; i++)
    //     dp[i][0] = 0;


    int ret =  memo(0, amount, coins, dp);
    if(ret == INT_MAX)
        return -1;    
    return ret;
}

int MinimumCoins3(vector<int>& coins, int amount) {
    int n = coins.size();

    vector<vector<int>> dp(n+1, vector<int>(amount+1, INT_MAX));
    for(int i=0; i<n; i++)
        dp[i][0] = 0;

    
    for(int idx = n-1; idx >= 0; idx--) {
        for(int t=1; t<=amount; t++) {

            int pick = INT_MAX;
            if(coins[idx] <= t) {
                int res = dp[idx][t - coins[idx]];
                if(res != INT_MAX)
                    pick = 1 + res; // safe to pick
            }        

            int skip = dp[idx+1][t];

            dp[idx][t] = min(pick, skip);
        }
    }


    int ret =  dp[0][amount];
    if(ret == INT_MAX)
        return -1;    
    return ret;    
}

int MinimumCoins4(vector<int>& coins, int amount) {
    int n = coins.size();

    vector<int> curr(amount+1, INT_MAX);
    vector<int> ahead(amount+1, INT_MAX);
    for(int i=0; i<n; i++) {
        curr[0] = 0;
        ahead[0] = 0; // a target of zero requires zero coins
    }
        

    
    for(int idx = n-1; idx >= 0; idx--) {
        for(int t=1; t<=amount; t++) {

            int pick = INT_MAX;
            if(coins[idx] <= t) {
                int res = curr[t - coins[idx]];
                if(res != INT_MAX)
                    pick = 1 + res; // safe to pick
            }        

            int skip = ahead[t];

            curr[t] = min(pick, skip);
        }
        ahead = curr;
    }


    int ret =  ahead[amount];
    if(ret == INT_MAX)
        return -1;    
    return ret;    
}

int MinimumCoins5(vector<int>& coins, int amount) {
    int n = coins.size();

    vector<int> dp(amount+1, INT_MAX);
    dp[0] = 0; // a target of zero requires zero coins
        
    for(int idx = n-1; idx >= 0; idx--) {
        for(int t=coins[idx]; t<=amount; t++) {
            // we start from lower t 
            // because pick needs the new version of dp

            
            int pick = dp[t - coins[idx]];
            if(pick != INT_MAX)
                pick += 1;                    

            int skip = dp[t];

            dp[t] = min(pick, skip);
        }        
    }


    int ret =  dp[amount];
    if(ret == INT_MAX)
        return -1;    
    return ret;    
}

int main() {
    
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    // auto x = MinimumCoins3(coins, amount);
    assert(MinimumCoins1(coins, amount) == 3);
    assert(MinimumCoins2(coins, amount) == 3);
    assert(MinimumCoins3(coins, amount) == 3);
    assert(MinimumCoins4(coins, amount) == 3);
    assert(MinimumCoins5(coins, amount) == 3);


    coins = {2, 5}; amount = 3;
    // x = MinimumCoins3(coins, amount);

    assert(MinimumCoins1(coins, amount) == -1);
    assert(MinimumCoins2(coins, amount) == -1);
    assert(MinimumCoins3(coins, amount) == -1);
    assert(MinimumCoins4(coins, amount) == -1);
    assert(MinimumCoins5(coins, amount) == -1);
    return 0;
}

/*
1d walkthrough

coins = {2, 3} and amount = 6.

loop goes backwards
    so first 3 then 2

    init
    dp[0,1,2,3,4,5,6]
      [0,INF,INF,INF,..]

    
    at idx=n-1
        coin = 3

        for t = [3..6]

            pick = dp[3-3] = 0
            pick += 1
            skip = dp[3] = INF

            dp[3] = min(1, INF) = 1

        coin 4,5 return inf

        coin = 6

            pick = dp[6-3] = 1
            pick += 1 // 2
            skip = dp[6] = INF

            dp[6] = min(2,INF) = 2

    dp[0,1,2,3,4,5,6]
      [0,F,F,1,F,F,F]

    so when moving from t=3..6
        we used the latest version of dp[3]

*/