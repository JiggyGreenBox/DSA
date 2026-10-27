#include <iostream>
#include <vector>
using namespace std;


// f_rec(idx, remaining_wt)
//      max val of any combination of idx onwards
//      with w <= remaining_wt
int f_rec(int idx, int W, vector<int>& wt, vector<int>& val, int n) {
    if(W == 0) return 0;
    if(idx == n) return 0;

    int skip = f_rec(idx+1, W, wt, val, n);

    int take = 0;
    if(wt[idx] <= W) {
        take = val[idx] + f_rec(idx, W - wt[idx], wt, val, n);
    }
    return max(take, skip);
}

int unboundedKnapsack1(vector<int>& wt, vector<int>& val, int n, int W) {
    return f_rec(0, W, wt, val, n);
}
// ===================================================================
/*
memo
    dp-array range
        idx: 0.. n-1
        remaining weight: 0..W
*/
int f_memo(int idx, int W, vector<int>& wt, vector<int>& val, int n, vector<vector<int>> &dp) {
    if(W == 0) return 0;
    if(idx == n) return 0;

    if(dp[idx][W] != -1) return dp[idx][W];

    int skip = f_memo(idx+1, W, wt, val, n, dp);

    int take = 0;
    if(wt[idx] <= W) {
        take = val[idx] + f_memo(idx, W - wt[idx], wt, val, n, dp);
    }
    return dp[idx][W] = max(take, skip);
}
int unboundedKnapsack2(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<vector<int>> dp(n, vector<int>(W+1, -1));
    return f_memo(0, W, wt, val, n, dp);
}
// ===================================================================
/*
tabulation
    base cases become prefilled in dp-array
    dp[*][0] = 0
    dp[n][*] = 0

    we need idx+1, so iterate backwards

    dp range idx: 0..n
             W: 0..W


*/
int unboundedKnapsack3(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    for(int i=n-1; i>=0; i--) {
        for(int w=0; w<=W; w++) {
            
            int skip = dp[i+1][w];

            int take = 0;
            if(wt[i] <= w) {                
                take = val[i] + dp[i][w - wt[i]];
            }
            dp[i][w] = max(take, skip);
        }
    }
    return dp[0][W];
}

int unboundedKnapsack4(vector<int>& wt, vector<int>& val, int n, int W) {    
    vector<int> next(W+1, 0);

    for(int i=n-1; i>=0; i--) {

        vector<int> curr(W+1, 0);

        for(int w=0; w<=W; w++) {
            
            int skip = next[w];

            int take = 0;
            if(wt[i] <= w) {                
                take = val[i] + curr[w - wt[i]];
            }
            curr[w] = max(take, skip);
        }
        next = curr;
    }
    return next[W];
}

int unboundedKnapsack5(vector<int>& wt, vector<int>& val, int n, int W) {    
    vector<int> dp(W+1, 0);

    for(int i=n-1; i>=0; i--) {        

        for(int w=0; w<=W; w++) {
            
            int skip = dp[w];

            int take = 0;
            if(wt[i] <= w) {                
                take = val[i] + dp[w - wt[i]];
            }
            dp[w] = max(take, skip);
        }        
    }
    return dp[W];
}

int main() {
    vector<int> wt = {2, 4, 6};
    vector<int> val =  {5, 11, 13};
    int W = 10;

    cout << unboundedKnapsack1(wt, val, wt.size(), W) << endl;
    cout << unboundedKnapsack2(wt, val, wt.size(), W) << endl;
    cout << unboundedKnapsack3(wt, val, wt.size(), W) << endl;
    cout << unboundedKnapsack4(wt, val, wt.size(), W) << endl;
    cout << unboundedKnapsack5(wt, val, wt.size(), W) << endl;


    wt = {1, 3, 4, 5};
    val =  {10, 40, 50, 70};
    W = 8;

    cout << unboundedKnapsack1(wt, val, wt.size(), W) << endl;
    cout << unboundedKnapsack2(wt, val, wt.size(), W) << endl;
    cout << unboundedKnapsack3(wt, val, wt.size(), W) << endl;
    cout << unboundedKnapsack4(wt, val, wt.size(), W) << endl;
    cout << unboundedKnapsack5(wt, val, wt.size(), W) << endl;

    return 0;
}