#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

/*

sum1 = sum2

choices once array is exhausted
sum1 == sum2

f(idx, sum1, sum2, arr) 
    if(idx == arr.size())
        return sum1 == sum2
    
    // choose sum1
    bool s1 = f(idx+1, sum1 + arr[idx], sum2, arr)
    // choose sum2
    bool s2 = f(idx+1, sum1, sum2 + arr[idx], arr)

    return s1 || s2;
*/

bool f_rec(int idx, int n, int sum1, int sum2, vector<int> &arr) {
    if(idx == n) return sum1 == sum2;

    bool s1 = f_rec(idx+1, n, sum1 + arr[idx], sum2, arr);
    bool s2 = f_rec(idx+1, n, sum1, sum2 + arr[idx], arr);

    return s1 || s2;
}

bool equalPartition1(int n, vector<int> arr) {
    return f_rec(0, n, 0, 0, arr);
}
/*
here we are tracking sum1 and sum2
but we could only track sum
how?
because the sum1 + sum2 = total
if total is odd return false immediately

now we can a target of total/2 from both

so f(idx, sum1, sum2)
now becomes f(idx, total)
    if(total == 0) return true

    caller
        total = accumulate(arr.begin, arr.end)
        f(0, total/2, arr)
*/
//========================================================================
bool f_rec2(int idx, int total, int n, vector<int> &arr) {
    if(total == 0) return true;
    if(idx == n) return false;

    bool take = f_rec2(idx+1, total, n, arr);
    bool notTake = false;
    if(arr[idx] <= total) {
        notTake = f_rec2(idx+1, total - arr[idx], n, arr);
    }
    return notTake || take;
}

bool equalPartition2(int n, vector<int> arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    if(total % 2) return false;
    return f_rec2(0, total/2, n, arr);
}

/*
dp 
    idx 0..n-1
    total = 0..totalsum/2
*/
bool f_memo(int i, int target, int n, vector<int> &arr, vector<vector<int>> &dp) {
    if(target == 0) return true;
    if(i == n) return false;

    if(dp[i][target] != -1) return dp[i][target];

    bool notTake = f_memo(i+1, target, n, arr, dp);
    bool take = false;
    if(arr[i] <= target) {
        take = f_memo(i+1, target - arr[i], n, arr, dp);
    }
    return dp[i][target] = notTake || take;
}
bool equalPartition3(int n, vector<int> arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    if(total % 2) return false;
    
    vector<vector<int>> dp(n+1, vector<int> (total/2+1, -1));

    return f_memo(0, total/2, n, arr, dp);
}

/*
tabulation
base cases become prefilled in dp array
    if(target == 0) return true;
    if(i == n) return false;

i range, 0..n
target 0..total/2

dp[n+1][total/2+1]
for(0..n)
    dp[*][0] = true
*/

bool equalPartition4(int n, vector<int> arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    if(total % 2) return false;
    
    vector<vector<bool>> dp(n+1, vector<bool> (total/2+1, false));
    for(int i=0; i<=n; i++) {
        dp[i][0] = true;
    }

    for(int i=n-1; i>=0; i--) {
        for(int t=1; t<=total/2; t++) {
            bool notTake = dp[i+1][t];

            bool take = false;
            if(arr[i] <= t) {
                take = dp[i+1][t - arr[i]];
            }

            dp[i][t] = notTake || take;
        }
    }
    return dp[0][total/2];
}

bool equalPartition5(int n, vector<int> arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    if(total % 2) return false;
    
    
    vector<bool> next(total/2+1, false);
    vector<bool> curr(total/2+1, false);    

    next[0] = true;

    for(int i=n-1; i>=0; i--) {

        curr[0] = true;

        for(int t=1; t<=total/2; t++) {
            bool notTake = next[t];

            bool take = false;
            if(arr[i] <= t) {
                take = next[t - arr[i]];
            }

            curr[t] = notTake || take;
        }
        next = curr;
    }
    return next[total/2];
}

void print(const bool &b) {
    if(b) cout << "true";
    else cout << "false";
    cout << endl;
}

int main() {
    vector<int> v = {1, 10, 21, 10};

    print(equalPartition1(v.size(), v));
    print(equalPartition2(v.size(), v));
    print(equalPartition3(v.size(), v));
    print(equalPartition4(v.size(), v));
    print(equalPartition5(v.size(), v));

    v = {1, 2, 3, 5};
    print(equalPartition1(v.size(), v));
    print(equalPartition2(v.size(), v));
    print(equalPartition3(v.size(), v));
    print(equalPartition4(v.size(), v));
    print(equalPartition5(v.size(), v));
    return 0;
}