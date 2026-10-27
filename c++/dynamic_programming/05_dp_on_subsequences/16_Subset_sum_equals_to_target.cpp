#include <iostream>
#include <vector>
using namespace std;

/*

isSubsetSum

dp vs recursion

in recursion we carry a sum globally
which gives us 2^n TC

if we can make this into dp, we can bring that to 2*n TC

but how can we make this dp without carrying a sum globally

i think we need more states in DP

f(index, remaining_sum)



*/

bool f_rec(int i, int target, vector<int> &arr) {
    

    // cout << "target:" << target << endl;
    if(target == 0) return true;
    if(i == arr.size()) return false;


    // take or skip
    bool notTake = f_rec(i+1, target, arr);

    bool take = false;
    if(arr[i] <= target) {
        take = f_rec(i+1, target - arr[i], arr);
    }    

    return take || notTake;
}

bool isSubsetSum1(vector<int>arr, int target) {
    // take and skip
    return f_rec(0, target, arr);
}


bool f_memo(int i, int target, vector<int> &arr, vector<vector<int>> &dp) {
    if(target == 0) return true;
    if(i==arr.size()) return false;

    if(dp[i][target] != -1) return dp[i][target];

    bool skip = f_memo(i+1, target, arr, dp);


    bool take = false;
    if(arr[i] <= target) {
        take = f_memo(i+1, target -arr[i], arr, dp);
    }
    return dp[i][target] = skip || take;
}


bool isSubsetSum2(vector<int>arr, int target) {
    int n = arr.size();
    // idx range 0..n, target range 0..target
    vector<vector<int>> dp(n+1, vector<int>(target+1, -1));
    return f_memo(0, target, arr, dp);
}

/*
tabulation

    base cases become prefilled in dp array
    dp[n][*] = 0

    dp[*][0] = 1

    is dp vector of int or bool


*/
bool isSubsetSum3(vector<int>arr, int target) {
    int n = arr.size();
    vector<vector<bool>> dp(n+1, vector<bool>(target+1, false));

    // target[0] = true
    for(int i=0; i<=n; i++) {
        dp[i][0] = true;
    }

    for(int i=n-1; i>=0; i--) {
        for(int t=1; t<=target; t++) {

            bool skip = dp[i+1][t];

            bool take = false;
            if(arr[i] <= t){
                take = dp[i+1][t - arr[i]];
            }

            dp[i][t] = skip || take;
        }
    }
    return dp[0][target];
}

bool isSubsetSum4(vector<int>arr, int target) {
    int n = arr.size();    
    vector<bool> next(target+1, false);
    vector<bool> curr(target+1, false);

    // target[0] = true    
    next[0] = true;

    for(int i=n-1; i>=0; i--) {

        curr[0] = true;

        for(int t=1; t<=target; t++) {

            bool skip = next[t];

            bool take = false;
            if(arr[i] <= t){
                take = next[t - arr[i]];
            }

            curr[t] = skip || take;
        }
        next = curr;
    }
    return next[target];
}

void print(const bool &b) {
    if(b) cout << "true";
    else cout << "false";
    cout << endl;
}

int main() {
    vector<int> v = {1, 2, 7, 3};
    int target = 6;

    print(isSubsetSum1(v, target));
    print(isSubsetSum2(v, target));
    print(isSubsetSum3(v, target));
    print(isSubsetSum4(v, target));
    

    v = {2, 3, 5};

    print(isSubsetSum1(v, target));
    print(isSubsetSum2(v, target));
    print(isSubsetSum3(v, target));
    print(isSubsetSum4(v, target));
    


    return 0;
}