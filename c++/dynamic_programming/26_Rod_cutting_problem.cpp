#include <iostream>
#include <vector>
using namespace std;

// f(idx, inches_left):
//     from idx onwards
//     what will give the maximum price
//     with inches <= inches_left

int f_rec(int idx, vector<int> &price, int inches) {
    int n = price.size();
    if(inches == 0) return 0;
    if(idx == n) return 0;

    // dont cut
    int skip = f_rec(idx+1, price, inches);

    int take = 0;
    if(idx+1 <= inches) { // 1-based indexing
        take = price[idx] + f_rec(idx, price, inches - (idx+1));
    }

    return max(skip, take);
}
int rodCutting1(vector<int> price, int n) {
    return f_rec(0, price, n);
}
// ===================================================================
// dp-array, range idx: 0..n-1, length: 0..length
int f_memo(int idx, vector<int> &price, int inches, vector<vector<int>> &dp) {
    int n = price.size();
    if(inches == 0) return 0;
    if(idx == n) return 0;

    if(dp[idx][inches] != -1) return dp[idx][inches];

    // dont cut
    int skip = f_rec(idx+1, price, inches);

    int take = 0;
    if(idx+1 <= inches) { // 1-based indexing
        take = price[idx] + f_rec(idx, price, inches - (idx+1));
    }

    return dp[idx][inches] = max(skip, take);
}
int rodCutting2(vector<int> price, int n) {
    vector<vector<int>> dp(n, vector(n+1, -1));
    return f_memo(0, price, n, dp);
}
// ===================================================================
/*
tabulation
    base cases become prefilled in dp array
    dp[*][0] = 0;
    dp[n][*] = 0;

    we need idx+1, iterate backwards

    range:
        idx 0..n
        in 0..in
*/
int rodCutting3(vector<int> price, int n) {
    vector<vector<int>> dp(n+1, vector(n+1, 0));
    
    for(int i=n-1; i>=0; i--) {
        for(int in=0; in<=n; in++) {
            int skip = dp[i+1][in];

            int take = 0;
            if(i+1 <= in) { // 1-based indexing
                take = price[i] + dp[i][in - (i+1)];                
            }

            dp[i][in] = max(skip, take);
        }
    }
    return dp[0][n];
}
// ===================================================================
int rodCutting4(vector<int> price, int n) {
    
    vector next(n+1, 0);
    
    for(int i=n-1; i>=0; i--) {

        vector curr(n+1, 0);

        for(int in=0; in<=n; in++) {
            int skip = next[in];

            int take = 0;
            if(i+1 <= in) { // 1-based indexing
                take = price[i] + curr[in - (i+1)];                
            }

            curr[in] = max(skip, take);
        }

        next = curr;
    }
    return next[n];
}

int rodCutting5(vector<int> price, int n) {
    
    vector dp(n+1, 0);
    
    for(int i=n-1; i>=0; i--) {
        

        for(int in=0; in<=n; in++) {
            int skip = dp[in];

            int take = 0;
            if(i+1 <= in) { // 1-based indexing
                take = price[i] + dp[in - (i+1)];                
            }

            dp[in] = max(skip, take);
        }        
    }
    return dp[n];
}

int main() {

    vector<int> prices = {1, 6, 8, 9, 10, 19, 7, 20};
    cout << rodCutting1(prices, prices.size()) << endl;
    cout << rodCutting2(prices, prices.size()) << endl;
    cout << rodCutting3(prices, prices.size()) << endl;
    cout << rodCutting4(prices, prices.size()) << endl;
    cout << rodCutting5(prices, prices.size()) << endl;

    prices = {1, 5, 8, 9};
    cout << rodCutting1(prices, prices.size()) << endl;
    cout << rodCutting2(prices, prices.size()) << endl;
    cout << rodCutting3(prices, prices.size()) << endl;
    cout << rodCutting4(prices, prices.size()) << endl;
    cout << rodCutting5(prices, prices.size()) << endl;
    return 0;
}