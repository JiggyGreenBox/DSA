#include <iostream>
#include <vector>
using namespace std;

/*
Coin change II

    Give an array coins of n integers representing coin denominations. 
    Your task is to find the number of distinct combinations that sum up 
    to a specified amount of money. If it's impossible to achieve the 
    exact amount with any combination of coins, return 0.

    Single coin can be used any number of times.

    Return your answer with modulo 10^9+7.

    Example 1
        Input: coins = [2, 4,10], amount = 10
        Output: 4

        Explanation: The four combinations are:
        10 = 10
        10 = 4 + 4 + 2
        10 = 4 + 2 + 2 + 2
        10 = 2 + 2 + 2 + 2 + 2


    Example 2
        Input: coins = [5], amount = 5
        Output: 1

        Explanation: There is one combination: 5 = 5.
*/

/*
f_rec(idx, sum)
    from idx onwards 
    how many ways can we acheive sum

    skip = f_rec(idx+1, sum)
    take = f_rec(idx, sum - a[idx])

    return take + skip
*/
int f_rec(int idx, int amount, vector<int>&coins, int n) {
    if(idx == n) {
        return (amount == 0);
    }

    int skip = f_rec(idx+1, amount, coins, n);

    int take = 0;
    if(coins[idx] <= amount) {
        take = f_rec(idx, amount - coins[idx], coins, n);
    }

    const int mod = 1e9 + 7;
    return (skip + take) % mod;
}

int count1(vector<int>&coins, int N, int amount) {
    return f_rec(0, amount, coins, N);
}


int f_memo(int idx, int amount, vector<int>&coins, int n, vector<vector<int>> &dp) {
    if(idx == n) {
        return (amount == 0);
    }

    if(dp[idx][amount] != -1) return dp[idx][amount];

    int skip = f_memo(idx+1, amount, coins, n, dp);

    int take = 0;
    if(coins[idx] <= amount) {
        take = f_memo(idx, amount - coins[idx], coins, n, dp);
    }

    const int mod = 1e9 + 7;
    return dp[idx][amount] = (skip + take) % mod;
}
int count2(vector<int>&coins, int N, int amount) {
    
    // dp-array, range, idx: 0..n-1, amount: 0..amount
    
    int n = coins.size();
    vector<vector<int>> dp(n, vector<int>(amount+1, -1));
    return f_memo(0, amount, coins, N, dp);
}

int count3(vector<int>&coins, int N, int amount) {
    
    // tabulation
    // dp-array, range, idx: 0..n, amount: 0..amount
    // need idx+1, so iterate backwards
    int n = coins.size();
    vector<vector<int>> dp(n+1, vector<int>(amount+1, 0));
    dp[n][0] = 1;

    const int mod = 1e9 + 7;
    

    for(int i=n-1; i>=0; i--)  {
        for(int a=0; a<=amount; a++) {

            int skip = dp[i+1][a];            

            int take = 0;
            if(coins[i] <= a) {
                take = dp[i][a - coins[i]];                
            }

            dp[i][a] = (skip + take) % mod;
        }
    }
    return dp[0][amount];
}

int count4(vector<int>&coins, int N, int amount) {
    
    // tabulation
    // dp-array, range, idx: 0..n, amount: 0..amount
    // need idx+1, so iterate backwards
    int n = coins.size();    
    vector<int> next(amount+1, 0);
    next[0] = 1;

    const int mod = 1e9 + 7;
    

    for(int i=n-1; i>=0; i--)  {

        vector<int> curr(amount+1, 0);

        for(int a=0; a<=amount; a++) {

            int skip = next[a];            

            int take = 0;
            if(coins[i] <= a) {
                take = curr[a - coins[i]];                
            }

            curr[a] = (skip + take) % mod;
        }
        next = curr;
    }
    return next[amount];
}

int count5(vector<int>&coins, int N, int amount) {
    
    // tabulation
    // dp-array, range, idx: 0..n, amount: 0..amount
    // need idx+1, so iterate backwards
    int n = coins.size();    
    vector<int> dp(amount+1, 0);
    dp[0] = 1;

    const int mod = 1e9 + 7;
    

    for(int i=n-1; i>=0; i--)  {        

        for(int a=0; a<=amount; a++) {

            int skip = dp[a];            

            int take = 0;
            if(coins[i] <= a) {
                take = dp[a - coins[i]];                
            }

            dp[a] = (skip + take) % mod;
        }        
    }
    return dp[amount];
}

int main() {
    vector<int> coins = {2, 4, 10};
    int amount = 10;

    cout << count1(coins, coins.size(), amount) << endl;
    cout << count2(coins, coins.size(), amount) << endl;
    cout << count3(coins, coins.size(), amount) << endl;
    cout << count4(coins, coins.size(), amount) << endl;
    cout << count5(coins, coins.size(), amount) << endl;

    coins = {5};
    amount = 5;
    cout << count1(coins, coins.size(), amount) << endl;
    cout << count2(coins, coins.size(), amount) << endl;
    cout << count3(coins, coins.size(), amount) << endl;
    cout << count4(coins, coins.size(), amount) << endl;
    cout << count5(coins, coins.size(), amount) << endl;
    return 0;
}