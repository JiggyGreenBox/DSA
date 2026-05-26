#include <bits/stdc++.h>
using namespace std;


/*


buy
    profit = max (-ar[i] - fee + f(sell),
                  f(buy));

sell
    profit = max (ar[i] + f(buy),
                  f(sell));



*/
int f_rec(int day, int buy, vector<int> &arr, int n, int fee) {
    if(day == n) return 0;

    int profit = 0;
    if(buy) {
        // buy or skip
        profit = max(-arr[day] - fee + f_rec(day+1, 0, arr, n, fee),
                     f_rec(day+1, 1, arr, n, fee));
    }
    else {
        // sell or skip
        profit = max(arr[day] + f_rec(day+1, 1, arr, n, fee),
                     f_rec(day+1, 0, arr, n, fee));
    }
    return profit;
}
int stockBuySell1(vector<int> arr, int n, int fee) {
    return f_rec(0, 1, arr, n, fee);
}



int f_memo(int day, int buy, vector<int> &arr, int n, int fee, vector<vector<int>> &dp) {
    if(day == n) return 0;

    if(dp[day][buy] != -1) return dp[day][buy];

    int profit = 0;
    if(buy) {
        // buy or skip
        profit = max(-arr[day] - fee + f_memo(day+1, 0, arr, n, fee, dp),
                     f_memo(day+1, 1, arr, n, fee, dp));
    }
    else {
        // sell or skip
        profit = max(arr[day] + f_memo(day+1, 1, arr, n, fee, dp),
                     f_memo(day+1, 0, arr, n, fee, dp));
    }
    return dp[day][buy] = profit;

}

int stockBuySell2(vector<int> arr, int n, int fee) {
    vector<vector<int>> dp(n+1, vector<int>(2, -1));
    return f_memo(0, 1, arr, n, fee, dp);
}


/*
tabulation

base cases become pre-filled DP boundary states

dp[n][0] = 0
dp[n][1] = 0

*/
int stockBuySell3(vector<int> arr, int n, int fee) {
    vector<vector<int>> dp(n+1, vector<int>(2, 0));
    
    for(int day=n-1; day>=0; day--) {
        for(int buy=0; buy<=1; buy++) {
            int profit = 0;
            if(buy) {
                // buy or skip
                profit = max(-arr[day] - fee + dp[day+1][0],
                            dp[day+1][1]);
            }
            else {
                // sell or skip
                profit = max(arr[day] + dp[day+1][1],
                            dp[day+1][0]);
            }
            dp[day][buy] = profit;
        }
    }
    return dp[0][1];
}

int stockBuySell4(vector<int> arr, int n, int fee) {
    // vector<vector<int>> dp(n+1, vector<int>(2, 0));
    vector<int> next(2, 0);
    vector<int> curr(2, 0);
    
    for(int day=n-1; day>=0; day--) {
        for(int buy=0; buy<=1; buy++) {
            int profit = 0;
            if(buy) {
                // buy or skip
                // profit = max(-arr[day] - fee + dp[day+1][0],
                //             dp[day+1][1]);
                profit = max(-arr[day] - fee + next[0],
                            next[1]);
            }
            else {
                // sell or skip
                profit = max(arr[day] + next[1],
                            next[0]);
            }
            curr[buy] = profit;
            next = curr;
        }
    }
    return next[1];
}

int main() {
    vector<int> v = {1, 3, 4, 0, 2};
    int fee = 1;
    cout << stockBuySell1(v, v.size(), fee) << endl;
    cout << stockBuySell2(v, v.size(), fee) << endl;
    cout << stockBuySell3(v, v.size(), fee) << endl;
    cout << stockBuySell4(v, v.size(), fee) << endl;

    v = {1, 3, 2, 8, 4, 9};
    fee = 2;
    cout << stockBuySell1(v, v.size(), fee) << endl;
    cout << stockBuySell2(v, v.size(), fee) << endl;
    cout << stockBuySell3(v, v.size(), fee) << endl;
    cout << stockBuySell4(v, v.size(), fee) << endl;
    return 0;
}

/*

*/