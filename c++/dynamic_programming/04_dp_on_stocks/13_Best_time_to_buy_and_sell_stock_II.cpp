#include <iostream>
#include <vector>
using namespace std;

int stockBuySell1(vector<int> arr, int n) {
    int total = 0;
    for(int i=1; i<n; i++) {
        int prof = arr[i] - arr[i-1];
        total += max(prof, 0); // only add +ve profits
    }
    return total;
}

int f_rec(int idx, int buy, vector<int> &arr) {
    int n = arr.size();
    if(idx == n) return 0;

    int profit = 0;

    if(buy) {
        // buy now, try sell tomorrow
        // or dont buy try buy tomorrow
        profit += max(-arr[idx] + f_rec(idx+1, 0, arr),
                      0 + f_rec(idx+1, 1, arr));
    }
    else{
        // sell now, try buy tomorrow
        // or dont sell try sell tomorrow
        profit += max(arr[idx] + f_rec(idx+1, 1, arr),
                      0 + f_rec(idx+1, 0, arr));
    }
    return profit;
}

int stockBuySell2(vector<int> arr, int n) {
    return f_rec(0, 1, arr);
}


/*
tabulation
dp[n+1][2]
    dp[n][0] = 0
    dp[n][1] = 0

go backwards
iterate thru 0 and 1
*/
int stockBuySell4(vector<int> arr, int n) {
    vector<vector<int>> dp(n+1, vector<int>(2,0));
    dp[n][0] = dp[n][1] = 0;

    for(int i=n-1; i>=0; i--) {
        for(int buy=0; buy<=1; buy++) {
            if(buy) {
                // sell, or skip
                dp[i][buy] = max(-arr[i] + dp[i+1][0], dp[i+1][1]);
            }
            else {
                // buy or skip
                dp[i][buy] = max(arr[i] + dp[i+1][1], dp[i+1][0]);
            }
        }
    }
    return dp[0][1];
}

int stockBuySell5(vector<int> arr, int n) {
    vector<int> ahead(2, 0);
    vector<int> curr(2, 0);    
    ahead[0] = ahead[1] = 0;

    for(int i=n-1; i>=0; i--) {
        for(int buy=0; buy<=1; buy++) {
            if(buy) {
                // sell today, or skip
                curr[buy] = max(-arr[i] + ahead[0], ahead[1]);
            }
            else {
                // buy today, or skip
                curr[buy] = max(arr[i] + ahead[1], ahead[0]);
            }
            ahead = curr;
        }
    }
    return ahead[1];
}

int stockBuySell6(vector<int> arr, int n) {
    int nextBuy = 0;
    int nextSell = 0;

    int currBuy = 0;
    int currSell = 0;
    
    for(int i=n-1; i>=0; i--) {
        
        // allowed to buy
        currBuy = max(
            -arr[i] + nextSell, // buy today
            nextBuy             // skip
        );

        // currently holding stock -> allowed to sell
        currSell = max(
            arr[i] + nextBuy, // sell today
            nextSell          // hold
        );

        nextBuy = currBuy;
        nextSell = currSell;
    }
    return nextBuy;
}


int main() {
    vector<int> v = {9, 2, 6, 4, 7, 3};
    cout << stockBuySell1(v, v.size()) << endl;
    cout << stockBuySell2(v, v.size()) << endl;
    cout << stockBuySell4(v, v.size()) << endl;
    cout << stockBuySell5(v, v.size()) << endl;
    cout << stockBuySell6(v, v.size()) << endl;
    v = {2, 3, 4, 5, 6};
    cout << stockBuySell1(v, v.size()) << endl;
    cout << stockBuySell2(v, v.size()) << endl;
    cout << stockBuySell4(v, v.size()) << endl;
    cout << stockBuySell5(v, v.size()) << endl;
    cout << stockBuySell6(v, v.size()) << endl;
    return 0;
}

/*

f(day, buy)
    if buy == true
        profit = -ar[day] + f(day+1, sell), buy today
        OR
        profit = 0 + f(day+1, buy), skip the buy
    else
        sell == true

        profit = arr[day] + f(day+1, buy), sell today
        OR
        profit = 0 + f(day+1, sell), skip the sell



*/
