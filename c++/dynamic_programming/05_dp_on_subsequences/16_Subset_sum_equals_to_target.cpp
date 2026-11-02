#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <assert.h>
#include <algorithm>
using namespace std;


/*
pick / skip
return if sum == target


2^n time
n stack space
*/
bool rec(int idx, int sum, vector<int> &arr) {
    // for and idx and sum
    // is it possible to form this sum
    if(idx == arr.size())
        return sum == 0;

    
    // pick
    // all nums are +ve for this problem
    if(arr[idx] <= sum) {
        if(rec(idx+1, sum - arr[idx], arr))
            return true;
    }
        

    // skip
    if(rec(idx+1, sum, arr))
        return true;

    return false;
}

bool isSubsetSum1(vector<int>arr, int target) {
    return rec(0, target, arr);
}

// 2n states
// 2n space for dp array
// n stack space
// we add a cache
// for am idx and sum
// is it possible to form the sum
// all idx ranges are 0..n-1
// all targets are 0..target
int memo(int idx, int sum, vector<int> &arr, vector<vector<int>> &dp) {
    if(idx == arr.size())
        return sum == 0;

    if(dp[idx][sum] != -1)
        return dp[idx][sum];
    
    // pick
    // all nums are +ve for this problem
    bool take = false;
    if(arr[idx] <= sum)
        take = memo(idx+1, sum - arr[idx], arr, dp);
        

    // skip
    bool skip = memo(idx+1, sum, arr, dp);        

    return dp[idx][sum] = take || skip;
}

bool isSubsetSum2(vector<int>arr, int target) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(target+1, -1));
    return memo(0, target, arr, dp) == 1;
}

/*
in recursion we start from idx=0 and go till the end
with a pick or skip branching
then at the last idx if the remaining sum is zero
then we return true/1

dp[idx][rem_sum] = bool (possible/not-possile)
so dp[n][0] = 1

target=6
[1,2,3]

    [0][6]
        [1][5]
            [2][3]
                [3][0] = 1

        [1][6]
            [2][4]
                [3][2] = 0

                [3][4] = 0

            [2][6]
                [3][3] = 0

                [3][6] = 0

so to go backwards
we add the idx val to the dp mat 

dp[n][0] = 1
dp[n][*] = 0

for n-1
    for t=0 to target
        if need to recreate the pick and skip

        skip = dp[idx+1][t]

        pick = false
        if t > arr[idx]
            pick = dp[idx+1][t - arr[i]]

        dp[idx][t] = skip || pick

then return dp[0][target]


the base case wants to find dp[n][0] = 1
then arr[i]
    for pick
        will be dp[n-1][arr[i]]

*/ 


// 2nk time
// 2nk space
// 1 stack space
bool isSubsetSum3(vector<int>arr, int target) {
    int n = arr.size();
    vector<vector<int>> dp(n+1, vector<int>(target+1, 0));
    dp[n][0] = 1; // true

    for(int idx = n-1; idx>=0; idx--) {
        for(int t=0; t<=target; t++) {

            bool skip = dp[idx+1][t];

            
            bool pick = false;
            if(arr[idx] <= t)
                pick = dp[idx+1][t - arr[idx]];

            dp[idx][t] = pick || skip;
        }
    }

    return dp[0][target];
}

// 2nk time
// 2k space
// 1 stack space
bool isSubsetSum4(vector<int>arr, int target) {
    int n = arr.size();
    vector<int> curr(target+1, 0);
    vector<int> ahead(target+1, 0);
    ahead[0] = 1; // true

    for(int idx = n-1; idx>=0; idx--) {
        for(int t=0; t<=target; t++) {

            bool skip = ahead[t];

            
            bool pick = false;
            if(arr[idx] <= t)
                pick = ahead[t - arr[idx]];

            curr[t] = pick || skip;
        }
        ahead = curr;
    }

    return ahead[target];
}

/*
arr = {2, 3};
target = 5;

init
    dp[0] = 1;
    dp
    [0][1][2][3][4][5]
    [1][0][0][0][0][0]

process 2
    iterate from 5 to 2
        dp[t] = dp[t] || dp[t-x]

    dp[5] = dp[5] || dp[3] = 0
    dp[4] = dp[4] || dp[2] = 0
    dp[3] = dp[3] || dp[1] = 0
    dp[2] = dp[2] || dp[0] = 1

    dp
    [0][1][2][3][4][5]
    [1][0][1][0][0][0]

process 3
    iterate from 5 to 3

    dp[5] = dp[5] || dp[2] = 1
    dp[4] = dp[4] || dp[1] = 0
    dp[3] = dp[3] || dp[0] = 1

    dp
    [0][1][2][3][4][5]
    [1][0][1][1][0][1]

now when we check dp[5] == 1

============================

why iterate backwards?
{2}
target=4

dp = [1, 0, 0, 0, 0]

for t=0..4
    dp[2] = 1
    dp[4] = 1
    we used 2 twice

backwards
    t=4..0
    dp[4] = dp[4-2] = dp[2] = 0 // cant form 4
    dp[2] = dp[2-2] = dp[0] = 1 // can form 2


*/

bool isSubsetSum5(vector<int>& arr, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int x : arr) {
        for (int t = target; t >= x; --t) {
            dp[t] = dp[t] || dp[t - x];
        }
    }

    return dp[target];
}

int main() {

    vector<int> arr = {1, 2, 7, 3};
    int target = 6;    
    // auto x = isSubsetSum(arr, target);
    assert(isSubsetSum1(arr, target) == true);
    assert(isSubsetSum2(arr, target) == true);
    assert(isSubsetSum3(arr, target) == true);
    assert(isSubsetSum4(arr, target) == true);
    assert(isSubsetSum5(arr, target) == true);


    arr = {2, 3, 5}; target = 6;
    assert(isSubsetSum1(arr, target) == false);
    assert(isSubsetSum2(arr, target) == false);
    assert(isSubsetSum3(arr, target) == false);
    assert(isSubsetSum4(arr, target) == false);
    assert(isSubsetSum5(arr, target) == false);

    // arr = {1, 2, 5}; target = 5;
    // assert(isSubsetSum2(arr, target) == true);


    arr = {5, 5, 5, 6}; target = 6;
    assert(isSubsetSum2(arr, target) == true);
    assert(isSubsetSum3(arr, target) == true);
    assert(isSubsetSum4(arr, target) == true);
    assert(isSubsetSum5(arr, target) == true);

    return 0;
}