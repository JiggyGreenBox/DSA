#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
/*
Count partitions with given difference

    Given an array arr of n integers and an integer diff, count the 
    number of ways to partition the array into two subsets S1 and S2 such 
    that:

    ∣S1−S2∣ = diff and S1 ≥ S2
    Where |S1| and |S2| are sum of Subsets S1 and S2 respectively.    
*/

/*
∣S1−S2∣ = diff and S1 ≥ S2


    s1 + s2 = total

    s1 - s2 = diff

    2s1 = total + diff

    sum = (total+diff)/2
*/

int f_rec(int idx, int target, vector<int> &arr, int n) {
    if(idx == n) {        
        if(target == 0) return 1;
        return 0;
    }

    int skip = f_rec(idx+1, target, arr, n);

    int take = 0;
    if(arr[idx] <= target) { // s1 >= s2
        take = f_rec(idx+1, target - arr[idx], arr, n);
    }

    return skip + take;
}
int countPartitions1(int n, int diff, vector<int>& arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);

    if((total + diff)%2) return 0; // target not integer

    int target = (total + diff)/2;
    return f_rec(0, target,  arr, n);
}

// ===========================================================
int f_memo(int idx, int target, vector<int> &arr, int n, vector<vector<int>> &dp) {
    if(idx == n) {        
        if(target == 0) return 1;
        return 0;
    }

    if(dp[idx][target] != -1) return dp[idx][target];

    int skip = f_memo(idx+1, target, arr, n, dp);

    int take = 0;
    if(arr[idx] <= target) { // s1 >= s2
        take = f_memo(idx+1, target - arr[idx], arr, n, dp);
    }

    return dp[idx][target] = skip + take;
}
int countPartitions2(int n, int diff, vector<int>& arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);

    if((total + diff)%2) return 0; // target not integer

    int target = (total + diff)/2;

    vector<vector<int>> dp(n, vector<int>(target+1, -1));

    return f_memo(0, target,  arr, n, dp);
}

// ===========================================================
/*
tabulation
    base cases are prefilled
    dp[n][0] = true

*/
int countPartitions3(int n, int diff, vector<int>& arr) {
        int total = accumulate(arr.begin(), arr.end(), 0);

    // if((total + diff)%2) return 0; // target not integer
    if(total < diff || (total + diff)%2) return 0;

    int target = (total + diff)/2;

    vector<vector<int>> dp(n+1, vector<int>(target+1, 0));
    dp[n][0] = 1;

    for(int i=n-1; i>=0; i--) {
        for(int s=0; s<=target; s++) {
            // int skip = f_memo(idx+1, target, arr, n, dp);
            int skip = dp[i+1][s];

            int take = 0;
            if(arr[i] <= s) { // s1 >= s2
                // take = f_memo(idx+1, target - arr[idx], arr, n, dp);
                take = dp[i+1][s - arr[i]];
            }

            dp[i][s] = skip + take;   
        }
    }
    return dp[0][target];
}

int countPartitions4(int n, int diff, vector<int>& arr) {
        int total = accumulate(arr.begin(), arr.end(), 0);

    // if((total + diff)%2) return 0; // target not integer
    if(total < diff || (total + diff)%2) return 0;

    int target = (total + diff)/2;

    
    vector<int> next(target+1, 0);
    next[0] = 1;

    for(int i=n-1; i>=0; i--) {

        vector<int> curr(target+1, 0);

        for(int s=0; s<=target; s++) {
            
            int skip = next[s];

            int take = 0;
            if(arr[i] <= s) { // s1 >= s2
                // take = f_memo(idx+1, target - arr[idx], arr, n, dp);
                take = next[s - arr[i]];
            }

            curr[s] = skip + take;
        }
        next = curr;
    }
    return next[target];
}


int main() {
    vector<int> v = {1, 2, 3, 4};
    int diff = 2;
    cout << countPartitions1(v.size(), diff, v) << endl;
    cout << countPartitions2(v.size(), diff, v) << endl;
    cout << countPartitions3(v.size(), diff, v) << endl;
    cout << countPartitions4(v.size(), diff, v) << endl;
    
    

    v = {1, 1, 2, 3};
    diff = 1;
    cout << countPartitions1(v.size(), diff, v) << endl;
    cout << countPartitions2(v.size(), diff, v) << endl;
    cout << countPartitions3(v.size(), diff, v) << endl;
    cout << countPartitions4(v.size(), diff, v) << endl;
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
Count partitions with given difference

Given an array arr of n integers and an integer diff, count the 
number of ways to partition the array into two subsets, S1 and S2, 
such that:

sum(S1) ≥ sum(S2)
sum(S1) − sum(S2) = diff
Here, sum(S1) and sum(S2) denote the sums of the elements in the 
respective subsets.

Return the result modulo 109 + 7.

Note: A partition means that the union of S1 and S2 is the original 
array, and no element is left out or used twice — every element of 
the array belongs to exactly one of the two subsets.

Example 1:
Input: arr = [1, 1, 2, 3], diff = 1

Output: 3

Explanation: The subsets are [1, 2] and [1, 3], [1, 3] and [1, 2], 
[1, 1, 2] and [3].

Example 2:
Input: arr = [1, 2, 3, 4], diff = 2

Output: 2

Explanation: The subsets are [1, 3] and [2, 4], [1, 2, 3] and [4].


*/

/*
sum(S1) ≥ sum(S2)
sum(S1) − sum(S2) = diff

total = ...
for any sum S1
    S1 = total - S2
    S2 = total - S1
we want
    S1 - S2 == diff

    2S1 - total == diff
    2S1 = diff + total
    S1 = (total+diff)/2

[1, 2, 3, 4]
    total = 10
    diff = 2
    we want (10+2)/2 = 6
        num of subarray-sums == 6

[1, 1, 2, 3]
    total = 7
    diff = 1
    we want (7+1)/2 = 4
        num of subarray-sums == 3
*/

int rec(int idx, int sum, vector<int> &arr) {

    const int MOD = 1e9+7;

    if(idx == arr.size()) {
        if(sum == 0)
            return 1;
        return 0;
    }

    int skip = rec(idx+1, sum, arr);
    int pick = 0;
    if(arr[idx] <= sum)
        pick = rec(idx+1, sum - arr[idx], arr);
    return (skip + pick) % MOD;
}

int countPartitions1(int n, int diff, vector<int>& arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    int target = (total + diff) / 2;
    return rec(0, target, arr);
}

int memo(int idx, int sum, vector<int> &arr, vector<vector<int>> &dp) {

    const int MOD = 1e9+7;

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
    return dp[idx][sum] = (skip + pick) % MOD;
}

int countPartitions2(int n, int diff, vector<int>& arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    
    int target = (total + diff) / 2;
    vector<vector<int>> dp(n, vector<int>(target+1, -1));
    return memo(0, target, arr, dp);
}

int countPartitions3(int n, int diff, vector<int>& arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    
    int target = (total + diff) / 2;
    vector<vector<int>> dp(n+1, vector<int>(target+1, 0));
    dp[n][0] = 1;

    const int MOD = 1e9+7;

    for(int idx=n-1; idx>=0; idx--) {
        for(int t=0; t<=target; t++) {

            int skip = dp[idx+1][t];
            int pick = 0;
            if(arr[idx] <= t)
                pick = dp[idx+1][t - arr[idx]];

            dp[idx][t] = (skip + pick) % MOD;
        }
    }

    return dp[0][target];
}

int countPartitions4(int n, int diff, vector<int>& arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    
    int target = (total + diff) / 2;
    // vector<vector<int>> dp(n+1, vector<int>(target+1, 0));
    // dp[n][0] = 1;
    vector<int> ahead(target+1, 0);
    vector<int> curr(target+1, 0);
    ahead[0] = 1;

    const int MOD = 1e9+7;

    for(int idx=n-1; idx>=0; idx--) {
        for(int t=0; t<=target; t++) {

            int skip = ahead[t];
            int pick = 0;
            if(arr[idx] <= t)
                pick = ahead[t - arr[idx]];

            curr[t] = (skip + pick) % MOD;
        }
        ahead = curr;
    }

    return ahead[target];
}

int countPartitions5(int n, int diff, vector<int>& arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    
    int target = (total + diff) / 2;    
    vector<int> dp(target+1, 0);
    dp[0] = 1;

    const int MOD = 1e9+7;

    for(int x : arr) {
        for(int t=target; t >= x; t--) {            
            dp[t] = (dp[t] + dp[t - x]) % MOD;
        }        
    }

    return dp[target];
}

int main() {

    
    vector<int> arr = {1, 1, 2, 3};
    int diff = 1;

    assert(countPartitions1(arr.size(), diff, arr) == 3);
    assert(countPartitions2(arr.size(), diff, arr) == 3);
    assert(countPartitions3(arr.size(), diff, arr) == 3);
    assert(countPartitions4(arr.size(), diff, arr) == 3);
    assert(countPartitions5(arr.size(), diff, arr) == 3);

    arr = {1, 2, 3, 4};
    diff = 2;    

    assert(countPartitions1(arr.size(), diff, arr) == 2);
    assert(countPartitions2(arr.size(), diff, arr) == 2);
    assert(countPartitions3(arr.size(), diff, arr) == 2);
    assert(countPartitions4(arr.size(), diff, arr) == 2);
    assert(countPartitions5(arr.size(), diff, arr) == 2);

    return 0;
}