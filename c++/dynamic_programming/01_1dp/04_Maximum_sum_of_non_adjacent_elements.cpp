#include <iostream>
#include <vector>
using namespace std;

// ===========================================================================
// this is the backtracking way of solving
// we can not use memoization on this solution easily
// the global state creates this problem
//    explore all paths and track best
//    That’s DFS thinking, not DP thinking.

// But DP needs:
//      f(idx) = best answer from idx onward

// f(i) = maximum sum we can get starting from index i
void helper(int idx, int curr_sum, vector<int> &nums, int &max_sum) {

    // if(idx > nums.size()) return;

    if(idx >= nums.size()) {
        max_sum = max(max_sum, curr_sum);
        return;
    }
    
    // skip
    helper(idx+1, curr_sum, nums, max_sum);

    // choose
    helper(idx+2, curr_sum + nums[idx], nums, max_sum);
}
int nonAdjacent_backtracking_style(vector<int>& nums) {
    int max_sum = 0;
    helper(0, 0, nums, max_sum);
    return max_sum;
}

// ===========================================================================

int helper_dp_no_memo(int i, vector<int>& nums) {
    if(i >= nums.size()) return 0;

    // skip or choose
    int skip = helper_dp_no_memo(i+1, nums);
    int choose = nums[i] + helper_dp_no_memo(i+2, nums);
    return max(skip, choose);
}

int nonAdjacent_dp_style_no_memo(vector<int>& nums) {
    return helper_dp_no_memo(0, nums);
}

// ===========================================================================

// f(0)
//     f(1)
//         f(2)
//             f(3)
//             f(4)
//         f(3)
//     f(2)
//         f(3)
//         f(4)

int helper_memo(int i, vector<int> &nums, vector<int> &dp) {
    if(i >= nums.size()) return 0;

    if(dp[i] != -1) return dp[i];

    int skip = helper_memo(i+1, nums, dp);
    int take = nums[i] + helper_memo(i+2, nums, dp);

    return dp[i] = max(skip, take);
}

int nonAdjacent_memo(vector<int>& nums) {
    vector<int> dp(nums.size(), -1);
    return helper_memo(0, nums, dp);
}

// ===========================================================================
// we go from the start
// for any i we either pick or skip
// f[i] = max(f[i-1], a[i] + f[i-2])
int nonAdjacent_tab(vector<int>& nums) {
    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return max(0, nums[0]); // negative guard


    vector<int> dp(n, 0);
    dp[0] = max(0, nums[0]); // negative guard
    dp[1] = max(dp[0], nums[1]);
    for(int i=2; i<n; i++) {
        dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
    }
    return dp[n-1];
}
// ===========================================================================
int nonAdjacent_tab2(vector<int>& nums) {
    int prev1 = 0;
    int prev2 = 0;
    for(int x : nums) {
        int curr = max(prev1, x + prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}


int main() {
    vector<int> nums = {1,2,4};     
    cout << nonAdjacent_backtracking_style(nums) << endl;
    cout << nonAdjacent_dp_style_no_memo(nums) << endl;
    cout << nonAdjacent_memo(nums) << endl;
    cout << nonAdjacent_tab(nums) << endl;
    cout << nonAdjacent_tab2(nums) << endl;
    
    
    
    nums = {2, 1, 4, 9};
    cout << nonAdjacent_backtracking_style(nums) << endl;
    cout << nonAdjacent_dp_style_no_memo(nums) << endl;
    cout << nonAdjacent_memo(nums) << endl;
    cout << nonAdjacent_tab(nums) << endl;
    cout << nonAdjacent_tab2(nums) << endl;
    return 0;
}

// 2^n time
// n stack space
int rec(int idx, vector<int> &nums, bool picked) {
    if(idx >= nums.size())
        return 0;

    int pick = nums[idx] + rec(idx+2, nums, true);

    // skip
    int skip = rec(idx+1, nums, false);

    return max(pick, skip);
}

int nonAdjacent(vector<int>& nums) {
    return rec(0, nums, false);
}

// O(n) time
// O(n) dp array space O(n) stack space
int memo(int idx, vector<int> &nums, vector<int> &dp) {
    if(idx == nums.size())
        return 0;

    if(dp[idx] != -1)
        return dp[idx];


    int pick = nums[idx] + memo(idx+2, nums, dp);

    int skip = memo(idx+1, nums, dp);

    return dp[idx] = max(pick, skip);
}

int nonAdjacent2(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, -1);
    return memo(0, nums, dp);
}

/*
how do we go to tabulation
dp[idx][bool]

dp[0][false] = 0
dp[0][true] = nums[0]

for i = [1..n]

    dp[i][false] = max(dp[i-1][true], dp[i-1][false])
    dp[i][true] = nums[i] + dp[i-1][false]
*/


// O(n) time
// (n) dp space
int nonAdjacent3(vector<int>& nums) {
    int n = nums.size();
    if(n==0)
        return 0;

    vector<int> dp(n, 0);
    
    dp[0] = nums[0];

    for(int i=1; i<n; i++) {
        int pick = nums[i];
        if(i>1)
            pick += dp[i-2];
        
        int skip = dp[i-1];

        dp[i] = max(pick, skip);
    }

    return dp[n-1];
}

// O(2n) time
// (1) dp space
int nonAdjacent4(vector<int>& nums) {
    int n = nums.size();    

    int prev2 = 0;
    int prev1 = nums[0];

    for(int i=1; i<n; i++) {
        int pick = prev2 + nums[i];
        int skip = prev1;

        int curr = max(pick, skip);

        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}


int main() {

    vector<int>  nums = {1, 2, 4};
    auto x = nonAdjacent2(nums);
    x = nonAdjacent3(nums);
    x = nonAdjacent4(nums);
    nums = {2, 1, 4, 9};
    x = nonAdjacent2(nums);
    x = nonAdjacent3(nums);
    x = nonAdjacent4(nums);
    return 0;
}