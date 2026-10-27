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