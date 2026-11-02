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

// int main() {

//     vector<int> prices = {1, 6, 8, 9, 10, 19, 7, 20};
//     cout << rodCutting1(prices, prices.size()) << endl;
//     cout << rodCutting2(prices, prices.size()) << endl;
//     cout << rodCutting3(prices, prices.size()) << endl;
//     cout << rodCutting4(prices, prices.size()) << endl;
//     cout << rodCutting5(prices, prices.size()) << endl;

//     prices = {1, 5, 8, 9};
//     cout << rodCutting1(prices, prices.size()) << endl;
//     cout << rodCutting2(prices, prices.size()) << endl;
//     cout << rodCutting3(prices, prices.size()) << endl;
//     cout << rodCutting4(prices, prices.size()) << endl;
//     cout << rodCutting5(prices, prices.size()) << endl;
//     return 0;
// }

#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <assert.h>
#include <algorithm>
#include <numeric>
using namespace std;

/*
Rod cutting problem


price = [1, 6, 8, 9, 10, 19, 7, 20], N = 8


f(len, prices)
    return the max price
    for this length
    we may cut it however we want

    for i in [1..len]
        prices[i] +  f(len-i)


[1,2,3]
    [1][2,3]
    [1,2][3]
    [1,2,3]

for n len
    we can make n-1 cuts

for n-1 len
    we can make n-2 cuts

n! time complexity
*/


// f(n) = 1 + summation(f(n-1)..f(1))
// becomes 2^n time
int rec(int len, vector<int> &prices) {
    if(len == 0)
        return 0; // no price for zero length

    int best = 0;

    for(int i=1; i<=len; i++) {
        int pick = prices[i-1] + rec(len-i, prices);
        best = max(best, pick);
    }
    return best;
}

int rodCutting1a(vector<int> &price, int n) {
    return rec(n, price);
}

// outer loop looks for dp[n]
//  inner loop would visit dp[n-1]
// n*n-1
// n^2 time
// n space
// n stack space
int memo(int len, vector<int> &prices, vector<int> &dp) {
    if(len == 0)
        return 0; // no price for zero length

    if(dp[len] != -1)
        return dp[len];
    
    int best = 0;

    for(int i=1; i<=len; i++) {
        int pick = prices[i-1] + memo(len-i, prices, dp);
        best = max(best, pick);
    }
    return dp[len] = best;
}

//
int rodCutting2a(vector<int> &price, int n) {

    // the states are still the same
    // with memoization
    vector<int> dp(n+1, -1);
    dp[0] = 0;
    return memo(n, price, dp);
}

//
int rodCutting3a(vector<int> &price, int n) {

    // the states are still the same
    // with memoization
    vector<int> dp(n+1, 0);
    dp[0] = 0;    

    // the tabulation is 2 loops
    // first fixes the len
    // second loop fixes sub lens of the first    

    // rod len calculation
    // f[1], f[2], f[3]
    for(int len=1; len <= n; len++) {
        int best = 0;

        // for rod len, start with smaller parts
        // eg, for f[3], dp[2] + dp[len-1]
        for(int i=1; i <= len; i++) {
            int pick = price[i-1] + dp[len-i];
            best = max(best, pick);
        }

        dp[len] = best;
    }
    return dp[n];
}

int main() {

    
    vector<int> price = {1, 6, 8, 9, 10, 19, 7, 20};
    int N = 8;

    auto x = rodCutting3a(price, price.size());

    assert(rodCutting1a(price, price.size()) == 25);
    assert(rodCutting2a(price, price.size()) == 25);
    assert(rodCutting3a(price, price.size()) == 25);    

    price = {1, 5, 8, 9}; N = 4;
    assert(rodCutting1a(price, price.size()) == 10);
    assert(rodCutting2a(price, price.size()) == 10);
    assert(rodCutting3a(price, price.size()) == 10);    
    return 0;
}
