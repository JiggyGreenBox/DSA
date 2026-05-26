#include <iostream>
#include <vector>
using namespace std;

/*

b,s,b,s

b,----s,b,s

*/
int f_rec(int day, int buy, int k, vector<int> &arr) {

    if(day == arr.size() || k == 0) return 0;

    int profit = 0;
    if(buy) {
        // buy or skip
        profit = max(-arr[day] + f_rec(day+1, 0, k, arr), 
                      f_rec(day+1, 1, k, arr));
    }
    else {
        // sell or skip
        profit = max(arr[day] + f_rec(day+1, 1, k-1, arr),
                      f_rec(day+1, 0, k, arr));
    }
    return profit;
}
int stockBuySell1(vector<int> arr, int n) {
    return f_rec(0, 1, 2, arr);
}

int f_memo(int day, int buy, int k, vector<int> &arr, vector<vector<vector<int>>> &dp) {

    if(day == arr.size() || k == 0) return 0;

    if(dp[day][buy][k] != -1) return dp[day][buy][k];

    int profit = 0;
    if(buy) {
        // buy or skip
        profit = max(-arr[day] + f_memo(day+1, 0, k, arr, dp), 
                      f_memo(day+1, 1, k, arr, dp));
    }
    else {
        // sell or skip
        profit = max(arr[day] + f_memo(day+1, 1, k-1, arr, dp),
                      f_memo(day+1, 0, k, arr, dp));
    }
    return dp[day][buy][k] = profit;
}

int stockBuySell2(vector<int> arr, int n) {
    vector<vector<vector<int>>> dp(arr.size(), vector<vector<int>>(2, vector<int>(3, -1)));    
    return f_memo(0, 1, 2, arr, dp);
}


/*
tabulation
start with the recursive solutions base cases

    day
    buy
    cap

    if day == n return 0
    if cap == 0 return 0

    for all n=0, buy and cap, dp will be zero
    for all cap=0, all day and buy will be zero

    for n-1 to 0
        for 0 and 1
            // for 0,1,2 NOT 0, they are all = ZERO
            for 1,2

    Base cases in recursion become:
        pre-filled DP boundary states
*/
int stockBuySell3(vector<int> arr, int n) {
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(3, 0)));        

    for(int day=n-1; day>=0; day--) {
        for(int buy=0; buy<=1; buy++) {
            for(int cap=1; cap<=2; cap++) { // cap=0, is zerp


                int profit = 0;
                if(buy == 1) {
                    // buy or skip
                    profit = max(-arr[day] + dp[day+1][0][cap], 
                                dp[day+1][1][cap]);                                
                }
                else {
                    // sell or skip
                    profit = max(arr[day] + dp[day+1][1][cap-1],
                                dp[day+1][0][cap]);
                }
                dp[day][buy][cap] = profit;
            }
        }
    }
    return dp[0][1][2];
}

int stockBuySell4(vector<int> arr, int n) {
    // vector<vector<vector<int>>> dp(n+1, 
    //     vector<vector<int>>(2, vector<int>(3, 0)));        

    
    vector<vector<int>> next(2, vector<int>(3, 0));        
    vector<vector<int>> curr(2, vector<int>(3, 0));        

    

    for(int day=n-1; day>=0; day--) {
        for(int buy=0; buy<=1; buy++) {
            for(int cap=1; cap<=2; cap++) { // cap=0, is zerp


                int profit = 0;
                if(buy == 1) {
                    // buy or skip
                    profit = max(-arr[day] + next[0][cap], 
                                next[1][cap]);                                
                }
                else {
                    // sell or skip
                    profit = max(arr[day] + next[1][cap-1],
                                next[0][cap]);
                }
                curr[buy][cap] = profit;
                next = curr;
            }
        }
    }
    return next[1][2];
}

int main() {
    vector<int> v = {4, 2, 7, 1, 11, 5};
    cout << stockBuySell1(v, v.size())  << endl;
    cout << stockBuySell2(v, v.size())  << endl;
    cout << stockBuySell3(v, v.size())  << endl;
    cout << stockBuySell4(v, v.size())  << endl;

    v = {1, 3, 2, 8, 4, 9};
    cout << stockBuySell1(v, v.size())  << endl;
    cout << stockBuySell2(v, v.size())  << endl;
    cout << stockBuySell3(v, v.size())  << endl;
    cout << stockBuySell4(v, v.size())  << endl;
    return 0;
}

int maxProfit(int k, vector<int>& prices) {

    int n = prices.size();

    vector<vector<int>> dp(
        n + 1,
        vector<int>(2 * k + 1, 0)
    );

    for(int day = n - 1; day >= 0; day--) {

        for(int trans = 2*k - 1; trans >= 0; trans--) {

            if(trans % 2 == 0) {

                // BUY
                dp[day][trans] = max(
                    -prices[day] + dp[day+1][trans+1],
                    dp[day+1][trans]
                );

            } else {

                // SELL
                dp[day][trans] = max(
                    prices[day] + dp[day+1][trans+1],
                    dp[day+1][trans]
                );
            }
        }
    }

    return dp[0][0];
}

/*
during revision
revise state compression of removing buy, sell state
*/