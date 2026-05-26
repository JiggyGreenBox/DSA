#include <iostream>
#include <vector>
using namespace std;

/*
0 and 1 Knapsack

    Given two integer arrays, val and wt, each of size N, which represent 
    the values and weights of N items respectively, and an integer W 
    representing the maximum capacity of a knapsack, determine the 
    maximum value achievable by selecting a subset of the items such that 
    the total weight of the selected items does not exceed the knapsack 
    capacity W.

    Each item can either be picked in its entirety or not picked at all 
    (0-1 property). The goal is to maximize the sum of the values of the 
    selected items while keeping the total weight within the knapsack's 
    capacity.
*/

int f_rec(int idx, int wt_rem, vector<int>& wt, vector<int>& val, int n) {
    if(wt_rem == 0) return 0;
    if(idx == n) return 0;
    
    int skip = f_rec(idx+1, wt_rem, wt, val, n);

    int take = 0;
    if(wt[idx] <= wt_rem) {
        take = val[idx] + f_rec(idx+1, wt_rem - wt[idx], wt, val, n);
    }
    
    return max(skip, take);
}

/*
f(idx, wt_left)
    from this idx further can we pick or skip elements
    return the max sum possible
*/


int knapsack01_1(vector<int>& wt, vector<int>& val, int n, int W) {
    return f_rec(0, W, wt, val, n);
}
//_===================================================================
/*
dp array sizing
    idx range 0..n-1
    wt 0..target
*/
int f_memo(int idx, int wt_rem, vector<int>& wt, vector<int>& val, int n, vector<vector<int>> &dp) {
    if(wt_rem == 0) return 0;
    if(idx == n) return 0;

    if(dp[idx][wt_rem] != -1) return dp[idx][wt_rem];

    int skip = f_memo(idx+1, wt_rem, wt, val, n, dp);

    int take = 0;
    if(wt[idx] <= wt_rem) {
        take = val[idx] + f_memo(idx+1, wt_rem - wt[idx], wt, val, n, dp);
    }

    return dp[idx][wt_rem] = max(take, skip);    
}
int knapsack01_2(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<vector<int>> dp(n, vector<int>(W+1, -1));
    return f_memo(0, W, wt, val, n, dp);
}
//_===================================================================
/*
tabulation
    base cases are pre filled in dp array
    dp[*][0] = 0

    we need future value, so dp[n+1]

    wt_rem range 0..W+1

    iterate from n-1
*/
int knapsack01_3(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    for(int i=n-1; i>=0; i--) {
        for(int w=1; w<=W; w++) { // dp[i=*][wt=0] = 0
            int skip = dp[i+1][w];

            int take = 0;
            if(wt[i] <= w) {
                take = val[i] + dp[i+1][w-wt[i]];
            }
            
            dp[i][w] = max(skip, take);
        }
    }
    return dp[0][W];
}

int knapsack01_4(vector<int>& wt, vector<int>& val, int n, int W) {    
    vector<int> next(W+1, 0);
    

    for(int i=n-1; i>=0; i--) {

        vector<int> curr(W+1, 0);

        for(int w=1; w<=W; w++) { // dp[i=*][wt=0] = 0
            int skip = next[w];

            int take = 0;
            if(wt[i] <= w) {
                take = val[i] + next[w-wt[i]];
            }
            
            curr[w] = max(skip, take);
        }
        next = curr;
    }
    return next[W];
}

/*
further space optimization:
curr[10]
depends on:
    skip: next[10]
    take: next[7]

we can reuse the same row, if we iterate backwards
curr[10]
depends on:
    skip: curr[10]
    take: curr[7], curr 7 is old value, because 10...7
*/
int knapsack01_5(vector<int>& wt, vector<int>& val, int n, int W) {    
    vector<int> curr(W+1, 0);
    

    for(int i=n-1; i>=0; i--) {

        // vector<int> curr(W+1, 0);

        for(int w=W; w>=wt[i]; w--) { // dp[i=*][wt=0] = 0
            int skip = curr[w];

            int take = 0;
            // if(wt[i] <= w) {
                take = val[i] + curr[w-wt[i]];
            // }
            
            curr[w] = max(skip, take);
        }
        // next = curr;
    }
    return curr[W];
}

int main() {
    vector<int> wt = {10, 20, 30};
    vector<int> val = {60, 100, 120};
    int W = 50;

    cout << knapsack01_1(wt, val, wt.size(), W) << endl;
    cout << knapsack01_2(wt, val, wt.size(), W) << endl;
    cout << knapsack01_3(wt, val, wt.size(), W) << endl;
    cout << knapsack01_4(wt, val, wt.size(), W) << endl;
    cout << knapsack01_5(wt, val, wt.size(), W) << endl;

    wt = {5, 4, 6, 3};
    val = {10, 40, 30, 50};
    W = 10;
    cout << knapsack01_1(wt, val, wt.size(), W) << endl;
    cout << knapsack01_2(wt, val, wt.size(), W) << endl;
    cout << knapsack01_3(wt, val, wt.size(), W) << endl;
    cout << knapsack01_4(wt, val, wt.size(), W) << endl;
    cout << knapsack01_5(wt, val, wt.size(), W) << endl;

    return 0;
}
