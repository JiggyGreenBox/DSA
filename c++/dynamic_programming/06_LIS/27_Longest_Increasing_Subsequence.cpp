#include <iostream>
#include <vector>
using namespace std;

/*
Longest Increasing Subsequence
    Given an integer array nums, return the length of the longest 
    strictly increasing subsequence.

    A subsequence is a sequence derived from an array by deleting some or 
    no elements without changing the order of the remaining elements. For 
    example, [3, 6, 2, 7] is a subsequence of [0, 3, 1, 6, 2, 2, 7].

    The task is to find the length of the longest subsequence in which 
    every element is greater than the previous one.

    Example 1:
        Input: nums = [10, 9, 2, 5, 3, 7, 101, 18]
        Output: 4

        Explanation: The longest increasing subsequence is [2, 3, 7, 101], 
        and its length is 4.

    Example 2
        Input: nums = [0, 1, 0, 3, 2, 3]
        Output: 4

        Explanation: The longest increasing subsequence is [0, 1, 2, 3], and 
        its length is 4
*/
// ===================================================================
// recursive, pick or dont pick
// f_rec(idx, prev_val)
//     from this idx onwards, 
//     what is the maximum subsequence length
//     that can be obtained
//     as long as all values selected are greater than prev_val

int f_rec_wrong(int idx, int prev, vector<int>& nums, int n) {
    if(idx == n) return 0;

    int skip = f_rec_wrong(idx+1, prev, nums, n);
    int take = 0;
    if(nums[idx] > prev) {
        take = 1 + f_rec_wrong(idx+1, nums[idx], nums, n);
    }

    return max(skip, take);
} 
int LIS_1_wrong(vector<int>& nums) {
    return f_rec_wrong(0, -1e9, nums, nums.size());
}

// -1e6 <= nums[i] <= 1e6, issue with memoization

// prev = actual value
// is not ideal for memoization/tabulation.
//     values can be huge
//     negative
//     sparse

// canonical LIS uses:
//     prev_index

// ===================================================================

// recursive, pick or dont pick
// f_rec(idx, prev_idx)
//     from this idx onwards, 
//     what is the maximum subsequence length
//     that can be obtained
//     as long as all values selected are greater than nums[prev_idx]
int f_rec(int idx, int prev_idx, vector<int>& nums, int n) {
    if(idx == n) return 0;

    int skip = f_rec(idx+1, prev_idx, nums, n);
    int take = 0;
    if(prev_idx == -1 || nums[idx] > nums[prev_idx]) {
        take = 1 + f_rec(idx+1, idx, nums, n);
    }

    return max(skip, take);
} 
int LIS_1(vector<int>& nums) {
    return f_rec(0, -1, nums, nums.size());
}
// ===================================================================
/*
memoization:
    idx range: 0..n-1
    prev_idx range -1..n-2

    offset -1 only while storing
*/
int f_memo(int idx, int prev_idx, vector<int>& nums, int n, vector<vector<int>> &dp) {
    if(idx == n) return 0;

    if(dp[idx][prev_idx+1] != -1) return dp[idx][prev_idx+1];

    int skip = f_memo(idx+1, prev_idx, nums, n, dp);
    int take = 0;
    if(prev_idx == -1 || nums[idx] > nums[prev_idx]) {
        take = 1 + f_memo(idx+1, idx, nums, n, dp);
    }

    return dp[idx][prev_idx+1] = max(skip, take);
}
int LIS_2(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n+1, -1)); // prev_idx + 1 can become n
    return f_memo(0, -1, nums, n, dp);
}
// ===================================================================
/*
tabulation:
    base cases become prefilled in dp array
    dp[n][*] = 0
    
    prev_idx = i-1..-1
*/
// ===================================================================
int LIS_3(vector<int>& nums) {
    int n = nums.size();

    vector<vector<int>> dp(n+1, vector<int>(n+1, 0)); // prev_idx + 1 can become n
    
    for(int i=n-1; i>=0; i--) {
        for(int prev_idx = i-1; prev_idx >=-1; prev_idx--) {

            int skip = dp[i+1][prev_idx+1];

            int take = 0;
            if(prev_idx == -1 || nums[i] > nums[prev_idx]) {
                take = 1 + dp[i+1][i+1]; // prev updated to i
            }

            dp[i][prev_idx+1] = max(skip, take);
        }
    }
    return dp[0][0];
}
// ===================================================================
// space optimization 1
int LIS_4(vector<int>& nums) {
    int n = nums.size();
    
    vector<int> next(n+1, 0); // prev_idx + 1 can become n
    
    for(int i=n-1; i>=0; i--) {

        vector<int> curr(n+1, 0);

        for(int prev_idx = i-1; prev_idx >=-1; prev_idx--) {

            int skip = next[prev_idx+1];

            int take = 0;
            if(prev_idx == -1 || nums[i] > nums[prev_idx]) {
                take = 1 + next[i+1]; // prev updated to i
            }

            curr[prev_idx+1] = max(skip, take);
        }
        next = curr;
    }
    return next[0];
}

// ===================================================================
// Recursive DP, O(2^n)
// DP, O(n²)
// 
// binary search approach, O(n log n)
/*
    ans.push_back(nums[0])

    if(nums[i] > ans.back()) push
    else if
        replace value at correct index
        lower_bound

    return ans.size()

    this is O(n log n) compression

    this is a greedy approach where we prefer smaller values
    as long at the length is the same

*/
int LIS_5(vector<int>& nums) {
    vector<int> ans;
    ans.push_back(nums[0]);
    for(int i=1; i<nums.size(); i++) {
        if(nums[i] > ans.back()) {
            ans.push_back(nums[i]);
        }
        else{
            auto it = lower_bound(ans.begin(), ans.end(), nums[i]);
            *it = nums[i];
        }
    }
    return ans.size();
}

// used for print LIS in the next question
int LIS_6(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);

    int ans = 1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            if(nums[i] > nums[j]){
                dp[i] = max(dp[i], 1 + dp[j]);
                ans = max(ans, dp[i]);
            }            
        }
    }
    return ans;
}

int main2() {

    vector<int> v = {10, 9, 2, 5, 3, 7, 101, 18};

    cout << LIS_1(v) << endl;
    cout << LIS_2(v) << endl;
    cout << LIS_3(v) << endl;
    cout << LIS_4(v) << endl;
    cout << LIS_5(v) << endl;
    cout << LIS_6(v) << endl;

    
    v = {7, 7, 7, 7, 7, 7, 7};

    cout << LIS_1(v) << endl;
    cout << LIS_2(v) << endl;
    cout << LIS_3(v) << endl;
    cout << LIS_4(v) << endl;
    cout << LIS_5(v) << endl;
    cout << LIS_6(v) << endl;

    v = {0, 1, 0, 3, 2, 3};

    cout << LIS_1(v) << endl;
    cout << LIS_2(v) << endl;
    cout << LIS_3(v) << endl;
    cout << LIS_4(v) << endl;
    cout << LIS_5(v) << endl;
    cout << LIS_6(v) << endl;
    
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
Longest Increasing Subsequence


    find subseq where i+1 > i
        then len of longest

f(idx, prev)

    if(idx == end)
        return 0

    
    if(idx == 0 || idx > prev)
        pick = 1 + f(idx+1)
    skip
    return max(pick, skip)
*/


/*
rec(idx)
    longest increasing subseq from idx onwards

2 choices
2^n time
n stack space
*/
int rec(int idx, int prev, vector<int> &nums) {
    if(idx == nums.size())
        return 0;

    int pick = 0;
    if(prev == -1 || nums[idx] > nums[prev])
        pick = 1 + rec(idx+1, idx, nums);

    int skip = rec(idx+1, prev, nums);

    return max(pick, skip);
}

int LIS1(vector<int>& nums) {
    return rec(0, -1, nums);
    // return rec(0, 0, nums); // doesnt work?
}

// 2n time
// n dp space
// n stack space
int memo(int idx, int prev, vector<int> &nums, vector<vector<int>> &dp) {
    if(idx == nums.size())
        return 0;

    if(dp[idx][prev+1] != -1)
        return dp[idx][prev+1];

    int pick = 0;
    if(prev == -1 || nums[idx] > nums[idx - 1])
        pick = 1 + memo(idx+1, idx, nums, dp);

    int skip = memo(idx+1, prev, nums, dp);

    return dp[idx][prev+1] = max(pick, skip);
}

// ranges idx : 0..n-1
// prev: -1..n-2
// encode prev with +1
int LIS2(vector<int>& nums) {
    int n = nums.size();
    // dp only depends on idx
    vector<vector<int>> dp(n, vector<int>(n,-1));
    return memo(0, -1, nums, dp);
}


// n^2 time
// n^2 space
// 1 stack space
int LIS3(vector<int>& nums) {
    int n = nums.size();    
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));    
    // idx, prev
    // prev is the idx last selected
    // -1 means nothing selected
    // we encode +1 to store results

    for(int idx=n-1; idx >=0; idx--) {
        for(int prev = idx-1; prev >= -1; prev--) {
            

            int pick = 0;
            if(prev == -1 || nums[idx] > nums[prev])
                pick = 1 + dp[idx+1][idx+1];

            int skip = dp[idx+1][prev+1];

            dp[idx][prev+1] = max(pick, skip);
        }
    }
    return dp[0][0];
}

// n^2 time
// 2n space
// 1 stack space
int LIS4(vector<int>& nums) {
    int n = nums.size();    
    
    vector<int> ahead(n+1, 0);
    vector<int> curr(n+1, 0);
    // idx, prev
    // prev is the idx last selected
    // -1 means nothing selected
    // we encode +1 to store results

    for(int idx=n-1; idx >=0; idx--) {
        for(int prev = idx-1; prev >= -1; prev--) {
            

            int pick = 0;
            if(prev == -1 || nums[idx] > nums[prev])
                pick = 1 + ahead[idx+1];

            int skip = ahead[prev+1];

            curr[prev+1] = max(pick, skip);
        }
        ahead = curr;
    }
    return ahead[0];
}

// n^2 time
// n space
// 1 stack space
int LIS5(vector<int>& nums) {
    int n = nums.size();    
        
    vector<int> dp(n+1, 0);
    // idx, prev
    // prev is the idx last selected
    // -1 means nothing selected
    // we encode +1 to store results

    for(int idx=n-1; idx >=0; idx--) {
        for(int prev = idx-1; prev >= -1; prev--) {
            

            int pick = 0;
            if(prev == -1 || nums[idx] > nums[prev])
                pick = 1 + dp[idx+1];

            int skip = dp[prev+1];

            dp[prev+1] = max(pick, skip);
        }
    }
    return dp[0];
}


// prefix-based-dp
int LIS6(vector<int>& nums) {
    int n = nums.size();    
        
    vector<int> dp(n, 1);
    int ans = 1;
    for(int idx=1; idx <n; idx++) {

        for(int prev = 0; prev < idx; prev++) {
            
            if(nums[idx] > nums[prev]) {
                dp[idx] = max(dp[idx], 1 + dp[prev]);
                ans = max(ans, dp[idx]);
            }
                
        }
    }
    // return *max_element(dp.begin(), dp.end());
    return ans;
}

// prefix-based-dp
// we replace the inner n loop
// with log n binary search
// nlogn time n space
int LIS7(vector<int>& nums) {

    if(nums.empty()) return 0;

    int n = nums.size();    
        
    // tails[length - 1] = smallest possible ending value
    //                of an increasing subsequence
    //                of this length

    vector<int> dp;
    dp.push_back(nums[0]);

    for(int i=1; i <n; i++) {

        int num = nums[i];

        if(num > dp.back()) {
            dp.push_back(num);
        }
        else {
            auto it = lower_bound(dp.begin(), dp.end(), num);
            *it = num;
                // For strictly increasing LIS:
                // lower_bound()
                // For non-decreasing LIS:
                // upper_bound()
            
        }        
    }
    return dp.size();
}

int main() {

    
    vector<int>  nums = {10, 9, 2, 5, 3, 7, 101, 18};       

    auto x = LIS5(nums);

    assert(LIS1(nums) == 4);
    assert(LIS2(nums) == 4);
    assert(LIS3(nums) == 4);    
    assert(LIS4(nums) == 4);    
    assert(LIS6(nums) == 4);
    assert(LIS7(nums) == 4);


    nums = {0, 1, 0, 3, 2, 3};

    assert(LIS1(nums) == 4);
    assert(LIS2(nums) == 4);
    assert(LIS3(nums) == 4);    
    assert(LIS4(nums) == 4);
    assert(LIS6(nums) == 4);
    assert(LIS7(nums) == 4);    


    nums = {1, 2, 3, 4, 5};
    assert(LIS4(nums) == 5);
    assert(LIS6(nums) == 5);
    assert(LIS7(nums) == 5);    
    nums = {5, 4, 3, 2, 1};
    assert(LIS4(nums) == 1);    
    assert(LIS6(nums) == 1);
    assert(LIS7(nums) == 1);
    
    
    return 0;
}


/*
so we have 2 approaches
    prefix-based dp
    suffix-based dp

suffix is pick or skip
    f(idx, prev)
        dp[idx][prev]
            can compress into dp[idx]
                using loop of prev=-1..idx-1
    
    n^2 time, n space

prefix is
    loop from start till idx-1
        best = max(best, 1 + dp[i-1])
    dp[i] = best

    f(idx)
        dp[idx]
            already 1 row compressed

    n^2 time, n space

    the best longest increasing subsequence can be anywhere in the dp array
    need to look for it
*/