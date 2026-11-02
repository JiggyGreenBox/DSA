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

#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <assert.h>
#include <algorithm>
#include <numeric>
using namespace std;

/*
Partition a set into two subsets with minimum absolute sum difference

total = ...
we want min(abs(ss1-sum - ss2sum))

if we find the subsetsum then the other sum is total-sss

so we want min(total-sum)

    range is 0..total

[1,2,4]
    total = 7
    target = 3

[1,2,3]
    total = 6
    target = 3

[1, 7, 14, 5]
    total = 24
    target = 12

we can have 
    rec(idx, target)

then 
    for i=total; i>=0; i--
        if(rec(idx, i))
            return (total-i)


sum1 = target
sum2 = total-target

sum2 = total - sum1

min(sum1-sum2)

min(sum1 - total+sum1)
min(2sum1 - total)
*/


// 2^n time
// n stack space
bool rec(int idx, int sum, vector<int>& arr) {
    if(idx == arr.size())
        return sum == 0;

    int skip = rec(idx+1, sum, arr);

    int pick = false;
    if(arr[idx] <= sum)
        pick = rec(idx+1, sum - arr[idx], arr);

    return pick || skip;
}

// Partition a set into two subsets with minimum absolute sum difference
// total/2 * 2^n time
// n stack space
int minDifference1(vector<int>&arr, int n)  {
    int total = accumulate(arr.begin(), arr.end(), 0);

    int target = total / 2;
    
    for(int i=target; i >= 0; i--) {
        if(rec(0, i, arr))
            return total - (2*i);
    }
    return total;
}

// 2n time
// 2n dp space
// n stack space
bool memo(int idx, int sum, vector<int>& arr, vector<vector<int>> &dp) {
    if(idx == arr.size())
        return sum == 0;

    if(dp[idx][sum] != -1)
        return dp[idx][sum];

    bool skip = memo(idx+1, sum, arr, dp);

    bool pick = false;
    if(arr[idx] <= sum)
        pick = memo(idx+1, sum - arr[idx], arr, dp);

    return dp[idx][sum] = pick || skip;
}

// Partition a set into two subsets with minimum absolute sum difference
// total/2 * 2n time
// 2n dp array space
// n stack space
int minDifference2(vector<int>&arr, int n)  {
    int total = accumulate(arr.begin(), arr.end(), 0);

    int target = total / 2;

    vector<vector<int>> dp(n, vector<int>(target+1, -1));
    
    for(int i=target; i >= 0; i--) {
        if(memo(0, i, arr, dp))
            return total - (2*i);
    }
    return total;
}

int minDifference3(vector<int>&arr, int n)  {
    int total = accumulate(arr.begin(), arr.end(), 0);

    int target = total / 2;

    vector<vector<int>> dp(n+1, vector<int>(target+1, 0));
    dp[n][0] = 1;

    

    for(int idx = n-1; idx >= 0; idx--) {
        for(int t=0; t<=target; t++) {

            bool skip = dp[idx+1][t];

            bool pick = false;
            if(arr[idx] <= t)
                pick = dp[idx+1][t - arr[idx]];

            dp[idx][t] = pick || skip;
        }
    }
    
    // we have built the dp table for
    // dp[0][target]
    // dp[0][target-1]
    // dp[0][target-2]
    // we want the first possible result

    for(int i=target; i>=0; i--) {
        if(dp[0][i])
            return total - 2*i;
    }
    return total;
}

int minDifference4(vector<int>&arr, int n)  {
    int total = accumulate(arr.begin(), arr.end(), 0);

    int target = total / 2;

    // vector<vector<int>> dp(n+1, vector<int>(target+1, 0));
    // dp[n][0] = 1;

    vector<int> ahead(target+1, 0);
    vector<int> curr(target+1, 0);
    ahead[0] = 1;

    

    for(int idx = n-1; idx >= 0; idx--) {
        for(int t=0; t<=target; t++) {

            bool skip = ahead[t];

            bool pick = false;
            if(arr[idx] <= t)
                pick = ahead[t - arr[idx]];

            curr[t] = pick || skip;
        }
        ahead = curr;
    }
    
    // we have built the dp table for
    // dp[0][target]
    // dp[0][target-1]
    // dp[0][target-2]
    // we want the first possible result

    for(int i=target; i>=0; i--) {
        if(ahead[i])
            return total - 2*i;
    }
    return total;
}

// 2nk time
// k space
// 1 stack space
int minDifference5(vector<int>&arr, int n)  {
    int total = accumulate(arr.begin(), arr.end(), 0);

    int target = total / 2;

    vector<bool> dp(target+1, 0);
    dp[0] = true;

    for(int x : arr) {
        for(int t=target; t >= x; t--) {
            dp[t] = dp[t] || dp[t - x]; // the skip will be old for values < x
            // t-x will be old as well aka ahead
        }
    }    

    for(int s=target; s>=0; s--) {
        if(dp[s])
            return total - 2*s;
    }
    return total;
}


int main() {

    vector<int> arr = {1, 7, 14, 5};
    // vector<int> arr = {1,2,9};

    // auto x = minDifference1(arr, arr.size());

    assert(minDifference1(arr, arr.size()) == 1);
    assert(minDifference2(arr, arr.size()) == 1);
    assert(minDifference3(arr, arr.size()) == 1);
    assert(minDifference4(arr, arr.size()) == 1);
    assert(minDifference5(arr, arr.size()) == 1);


    arr = {3, 1, 6, 2, 2};
    assert(minDifference1(arr, arr.size()) == 0);
    assert(minDifference2(arr, arr.size()) == 0);
    assert(minDifference3(arr, arr.size()) == 0);
    assert(minDifference4(arr, arr.size()) == 0);
    assert(minDifference5(arr, arr.size()) == 0);

    return 0;
}