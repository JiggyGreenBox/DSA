#include <iostream>
#include <vector>
using namespace std;

// Count Subsets
//     Given an array arr of n integers and an integer K, 
//     count the number of subsets of the given array that have a sum equal to K.
//     Return the result modulo (109 + 7).

// int perfectSum(vector<int>&arr, int K) {}

/*
recursive
    if target == 0, return 1
    if(idx == end) return 0

    count += take
    count += skip

    if u TAKE and reach the end and find the sum add to the count
    if u SKIP and reach the end and find the sum add to the count


*/
int f_rec(int idx, int target, vector<int> &arr, int n) {
    // may contain zeros
    // if(target == 0) return 1;
    // if(idx == n) return 0;

    if(idx == n) {
        return (target == 0);
    }

    int skip = f_rec(idx+1, target, arr, n);

    int take = 0;
    if(arr[idx] < target){
        take = f_rec(idx+1, target - arr[idx], arr, n);
    }
    
    int mod = 1e9 + 7;
    return (skip + take) % mod;
}
int perfectSum1(vector<int>&arr, int K) {
    return f_rec(0, K, arr, arr.size());
}

/*
memoization
    dp array
    idx [0..n-1]
    target [0..target]
*/
int f_memo(int idx, int target, vector<int> &arr, int n, vector<vector<int>> &dp) {
    
    if(target == 0) return 1;
    if(idx == n) return 0;

    if(dp[idx][target] != -1) return dp[idx][target];

    int skip = f_memo(idx+1, target, arr, n, dp);

    int take = 0;
    if(arr[idx] < target){
        take = f_memo(idx+1, target - arr[idx], arr, n, dp);
    }
    
    int mod = 1e9 + 7;
    return dp[idx][target] = (skip + take) % mod;
}
int perfectSum2(vector<int>&arr, int K) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(K+1, -1));
    return f_memo(0, K, arr, arr.size(), dp);
}

/*
tabulation
    base cases become prefilled in dp array
    

    dp[*][0] = 1
    dp[n][*] = 0

    skip = f_memo(idx+1

    so we need future values, we iterate from the back

    possible values for idx 0..n
    possible values for target 1..K


*/
int perfectSum(vector<int>&arr, int K) {

    int n = arr.size();
    vector<vector<int>> dp(n+1, vector<int>(K+1, 0));

    for(int i=0; i<=n; i++) {
        dp[i][0] = 1;
    }

    for(int i=n-1; i>=0; i--) {
        for(int t=1; t<=K; t++) {

            int skip = dp[i+1][t];

            int take = 0;

            if(arr[i] <= t) {
                take = dp[i+1][t - arr[i]];
            }

            dp[i][t] = take + skip;
        }
    }

    return dp[0][K];
}

int perfectSum(vector<int>&arr, int K) {

    int n = arr.size();
    
    vector<int> next(K+1, 0);

    next[0] = 1;
    

    for(int i=n-1; i>=0; i--) {

        vector<int> curr(K+1, 0);        

        for(int t=1; t<=K; t++) {

            int skip = next[t];

            int take = 0;

            if(arr[i] <= t) {
                take = next[t - arr[i]];
            }

            curr[t] = take + skip;
        }
        next = curr;
    }

    return next[K];
}
/*

in some versions we may have 0 present in the array
in this case we have to account for them
that means the sum could be found, but we still proceed

// zero not present
    vector<vector<int>> dp(n+1, vector<int>(K+1, 0));
    for(int i=0; i<=n; i++) {
        dp[i][0] = 1;
    }

    for(s=1; s<=target; s++) {}

// zero present
    vector<vector<int>> dp(n+1, vector<int>(K+1, 0));
    
    dp[n][0] = 1;
    

    for(s=0; s<=target; s++) {}

//
target 0 states are no longer constant

| No Zeros           | Zeros Allowed       |
| ------------------ | ------------------- |
| `dp[*][0] = 1`     | only `dp[n][0] = 1` |
| target loop from 1 | target loop from 0  |
| target 0 fixed     | target 0 dynamic    |

*/

#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <assert.h>
#include <algorithm>
#include <numeric>
using namespace std;

/*
Count subsets with sum K

f(idx, sum)
    return the number of subsets
    from idx onwards equal to sum

int rec(idx, sum, arr) {
    if(idx == arr.size()) {
        if(sum == 0)
            return 1;
        return 0;
    }

    int skip = rec(idx+1, sum, arr);

    int pick = rec(idx+1, sum - arr[i], arr);

    return skip + pick;
}
*/


// 2^n time
// n stack space
int rec(int idx, int sum, vector<int> &arr) {
    if(idx == arr.size()) {
        if(sum == 0)
            return 1;
        return 0;
    }

    int skip = rec(idx+1, sum, arr);

    int pick = 0;
    if(arr[idx] <= sum)
        pick = rec(idx+1, sum - arr[idx], arr);

    return skip + pick;
}

int perfectSum1(vector<int>&arr, int K) {
    return rec(0, K, arr);
}

// 2nK time
// 2nk dp array space
// n stack space
int memo(int idx, int sum, vector<int> &arr, vector<vector<int>> &dp) {
    if(idx == arr.size()) {
        if(sum == 0)
            return 1;
        return 0;
    }

    if(dp[idx][sum] != -1)
        return dp[idx][sum];

    int skip = memo(idx+1, sum, arr, dp);

    int pick = 0;
    if(arr[idx] <= sum)
        pick = memo(idx+1, sum - arr[idx], arr, dp);

    return dp[idx][sum] = skip + pick;
}

int perfectSum2(vector<int>&arr, int K) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(K+1, -1));
    return memo(0, K, arr, dp);
}

// 2nK time
// 2nk dp array space
// 1 stack space
int perfectSum3(vector<int>&arr, int K) {
    int n = arr.size();
    vector<vector<int>> dp(n+1, vector<int>(K+1, 0));
    dp[n][0] = 1;

    for(int idx = n-1; idx >= 0; idx--) {
        for(int k=0; k<=K; k++) {

            int skip = dp[idx+1][k];

            int pick = 0;
            if(arr[idx] <= k)
                pick = dp[idx+1][k - arr[idx]];

            dp[idx][k] = skip + pick;
        }
    }
    return dp[0][K];
}

// 2nK time
// 2k dp array space
// 1 stack space
int perfectSum4(vector<int>&arr, int K) {
    int n = arr.size();
    // vector<vector<int>> dp(n+1, vector<int>(K+1, 0));
    // dp[n][0] = 1;
    vector<int> ahead(K+1, 0);
    vector<int> curr(K+1, 0);
    ahead[0] = 1;

    for(int idx = n-1; idx >= 0; idx--) {
        for(int k=0; k<=K; k++) {

            int skip = ahead[k];

            int pick = 0;
            if(arr[idx] <= k)
                pick = ahead[k - arr[idx]];

            curr[k] = skip + pick;
        }
        ahead = curr;
    }
    return ahead[K];
}

// 2nK time
// k dp array space
// 1 stack space
int perfectSum5(vector<int>&arr, int K) {
    int n = arr.size();    
    // vector<int> ahead(K+1, 0);
    // vector<int> curr(K+1, 0);
    // ahead[0] = 1;
    vector<int> dp(K+1, 0);
    dp[0] = 1;

    for(int x : arr) {
        for(int k=K; k >= x; k--) {

            int skip = dp[k]; // skip for values k < x

            int pick = dp[k - x];

            dp[k] = skip + pick;
        }        
    }
    return dp[K];
}




int main() {

    vector<int> arr = {2, 3, 5, 16, 8, 10};
    int K = 10;

    auto x = perfectSum1(arr, K);

    assert(perfectSum1(arr, K) == 3);
    assert(perfectSum2(arr, K) == 3);
    assert(perfectSum3(arr, K) == 3);
    assert(perfectSum4(arr, K) == 3);
    assert(perfectSum5(arr, K) == 3);


    arr = {1, 2, 3, 4, 5}; K = 5;
    assert(perfectSum1(arr, K) == 3);
    assert(perfectSum2(arr, K) == 3);
    assert(perfectSum3(arr, K) == 3);
    assert(perfectSum4(arr, K) == 3);
    assert(perfectSum5(arr, K) == 3);

    return 0;
}