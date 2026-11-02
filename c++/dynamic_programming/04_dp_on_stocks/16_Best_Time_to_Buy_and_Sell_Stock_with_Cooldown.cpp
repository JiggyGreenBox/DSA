/*
Best Time to Buy and Sell Stock with Cooldown
    [https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/]

You are given an array prices where prices[i] is the price of a given 
stock on the ith day.

Find the maximum profit you can achieve. You may complete as many 
transactions as you like (i.e., buy one and sell one share of the 
stock multiple times) with the following restrictions:

After you sell your stock, you cannot buy stock on the next day 
(i.e., cooldown one day).
Note: You may not engage in multiple transactions simultaneously 
(i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
Example 2:

Input: prices = [1]
Output: 0
*/

#include <vector>
#include <assert.h>
using namespace std;

// 2^n time
// n stack space
int rec(int idx, int canBuy, vector<int>& prices) {
    if(idx >= prices.size())
        return 0;

    int profit = 0;
    if(canBuy) {
        int buy = -prices[idx] + rec(idx+1, 0, prices);
        int skip = rec(idx+1, 1, prices);
        profit = max(buy, skip);
    }
    else {
        int sell = prices[idx] + rec(idx+2, 1, prices); // +2 skip 
        int hold = rec(idx+1, 0, prices);
        profit = max(sell, hold);
    }
    return profit;
}

int maxProfit1(vector<int>& prices) {
    return rec(0, 1, prices);
}

// 2n time
// 2n dp vector space
// n stack space
int memo(int idx, int canBuy, vector<int>& prices, vector<vector<int>> &dp) {
    if(idx >= prices.size())
        return 0;

    if(dp[idx][canBuy] != -1)
        return dp[idx][canBuy];

    int profit = 0;
    if(canBuy) {
        int buy = -prices[idx] + memo(idx+1, 0, prices, dp);
        int skip = memo(idx+1, 1, prices, dp);
        profit = max(buy, skip);
    }
    else {
        int sell = prices[idx] + memo(idx+2, 1, prices, dp); // +2 skip 
        int hold = memo(idx+1, 0, prices, dp);
        profit = max(sell, hold);
    }
    return dp[idx][canBuy] = profit;
}

int maxProfit2(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2, -1));
    return memo(0, 1, prices, dp);
}


// tabulation
// 2n time
// 2n space
// 1 stack space
int maxProfit3(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n+2, vector<int>(2, 0));
    
    for(int idx = n-1; idx >= 0; idx--) {
        for(int canBuy = 0; canBuy <= 1; canBuy++) {

            int profit = 0;
            if(canBuy) {
                int buy = -prices[idx] + dp[idx+1][0];
                int skip = dp[idx+1][1];
                profit = max(buy, skip);
            }
            else {
                int sell = prices[idx] + dp[idx+2][1];
                // int sell = prices[idx];
                // if(idx < n-1)
                //     sell += dp[idx+2][1];

                int hold = dp[idx+1][0];
                profit = max(sell, hold);
            }
            dp[idx][canBuy] = profit;
        }
    }
    return dp[0][1];
}

// tabulation
// 2n time
// 3 space
// 1 stack space
int maxProfit4(vector<int>& prices) {
    int n = prices.size();
    vector<int> ahead1(2, 0);
    vector<int> ahead2(2, 0);
    vector<int> curr(2, 0);
    
    for(int idx = n-1; idx >= 0; idx--) {
        
        curr[1] = max(
            -prices[idx] + ahead1[0], 
            ahead1[1]
        );
            
        curr[0] = max(
            prices[idx] + ahead2[1], 
            ahead1[0]
        );

        ahead2 = ahead1;
        ahead1 = curr;
    }
    return ahead1[1];
}



int main() {
    vector<int> prices = {1,2,3,0,2};
    assert(maxProfit1(prices) == 3);
    assert(maxProfit2(prices) == 3);
    // auto x = maxProfit3(prices);
    assert(maxProfit3(prices) == 3);
    assert(maxProfit4(prices) == 3);
    return 0;
}