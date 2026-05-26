#include <iostream>
#include <numeric>
#include <climits>
#include <vector>
using namespace std;

/*

Partition a set into two subsets with minimum absolute sum difference

we can partition into sum1, sum2
    then we want min(sum1 - sum2)
    total = sum1 + sum2

    min(total-sum2-sum2)
    min(total-2*sum2)

    min(total-2sum)

f(idx, sum, total, arr)
    idx==n return 0

    int take_sum = 
    int skip_sum = 

    return min(total - 2*take_sum, total - 2*skip_sum)


we do NOT need recursion that returns minimum difference directly
we only need to know which subset sums are achievable

0 → total
    find achievable subset sum s
    that minimizes |total - 2s|

*/


/*
recursion
    global state
    we could track sum1, sum2
    for each idx
        put in sum1 or sum2
        return min-diff

    total = sum1 + sum2
    we want min(sum1-sum2)
    min(total - 2sum)

    we can pass total
        then track min(2sum)
    
    2,3,2,3
    5-5
    6-4
    7-3
    abs(total - 2*sum)
        abs takes care of both sums
        we could store dp[sum], dp[total-sum]

        total = sum1 + sum2
        so range is 0..total
    
*/
// 1 ≤ n * sum of array elements ≤ 10^6
// 0 < arr[i] <= 10^4
void f1(int idx, int total, int cur_sum, int &min_diff, vector<int> &arr, int n) {

    

    if(idx == n) {
        min_diff = min(min_diff, abs(total - 2*cur_sum));
        return;
    };

    // pick
    f1(idx+1, total, cur_sum + arr[idx], min_diff, arr, n);

    // choose
    f1(idx+1, total, cur_sum, min_diff, arr, n);
    
}
int minDifference1(vector<int> &arr, int n) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    int min_diff = INT_MAX;
    f1(0, total, 0, min_diff, arr, n);
    return min_diff;
}


/*
states
    total is constant
    idx, cur_sum

*/

int f2(int idx, int sum, int total, vector<int> &arr, int n) {

    if(idx == n) {
        return abs(total - 2*sum);
    }

    int take = f2(idx + 1, sum + arr[idx], total, arr, n);
    int skip = f2(idx + 1, sum, total, arr, n);

    return min(take, skip);
}

int minDifference2(vector<int> &arr, int n) {
    int total = accumulate(arr.begin(), arr.end(), 0);    
    return f2(0, 0, total, arr, n);
}


int f3(int idx, int sum, int total, vector<int> &arr, int n, vector<vector<int>> &dp) {

    if(idx == n) {
        return abs(total - 2*sum);
    }

    if(dp[idx][sum] != -1) return dp[idx][sum];

    int take = f2(idx + 1, sum + arr[idx], total, arr, n);
    int skip = f2(idx + 1, sum, total, arr, n);
    
    return dp[idx][sum] = min(take, skip);
}

int minDifference3(vector<int> &arr, int n) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    vector<vector<int>> dp(n, vector<int>(total+1, -1));
    return f3(0, 0, total, arr, n, dp);
}

// base cases become pre filled in dp array, tabulation
/*
    
    subset sum equals target, was a feasibility check
    partition equal subset sums, was also feasibility check
    with bools

    now the change is that from 0..total, can we reach the sum

    take = dp[i-1][s - arr[i]];

    arr[] = {3}, target 3
    dp[0] represents no choice, nothing picked
        dp[1] represents 1 choice, 0th idx
        dp[2] represents 2 choices, 0th,1st idx

    dp[0][0] + dp[1][3]
        dp[i] = dp[i-1][target(3) - arr[i](3)]

        0  1  2  3
    0   T  F  F  T


*/
int minDifference4(vector<int> &arr, int n) {
    int total = accumulate(arr.begin(), arr.end(), 0);

    vector<vector<bool>> dp(n+1, vector<bool>(total+1, false));

    for(int i=0; i<=n; i++) {
        dp[i][0] = true;
    }

    // check feasibility for all sums from 0..total
    for(int i=1; i<=n; i++) {

        for(int s=1; s<=total; s++) { // 0 already set to true

            bool notTake = dp[i-1][s]; // skip

            bool take = false;
            if(arr[i] <= s) {
                take = dp[i-1][s - arr[i]];
            }

            dp[i][s] = take || notTake;
        }        
    }

    int ans = INT_MAX;
    for(int s=0; s<=total/2; s++) {
        if(dp[n][s]) { // sum achievable
            ans = min(ans, total - 2*s);  // s1-s2 == total-2s
        }
    }
    return ans;
}


int minDifference(vector<int>& arr, int n) {

    int total = accumulate(arr.begin(), arr.end(), 0);

    vector<vector<bool>> dp(n+1,vector<bool>(total+1, false));

    dp[n][0] = true;

    for(int i=n-1; i>=0; i--) {

        for(int s=0; s<=total; s++) {

            bool skip = dp[i+1][s];

            bool take = false;
            if(arr[i] <= s) {
                take = dp[i+1][s-arr[i]];
            }

            dp[i][s] = take || skip;
        }
    }

    int ans = INT_MAX;

    for(int s=0; s<=total/2; s++) {
        
        if(dp[0][s]) {
            ans = min( ans, abs(total - 2*s) );
        }
    }

    return ans;
}

int main() {
    vector<int> v = {1, 7, 14, 5};

    cout << minDifference1(v, v.size()) << endl;
    cout << minDifference2(v, v.size()) << endl;
    cout << minDifference3(v, v.size()) << endl;

    v = {3, 1, 6, 2, 2};
    cout << minDifference1(v, v.size()) << endl;
    cout << minDifference2(v, v.size()) << endl;
    cout << minDifference3(v, v.size()) << endl;

    return 0;
}