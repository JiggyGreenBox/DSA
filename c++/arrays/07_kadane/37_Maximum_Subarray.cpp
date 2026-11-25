/*
Maximum Subarray
    [https://leetcode.com/problems/maximum-subarray/description/]

Given an integer array nums, find the subarray with the largest sum, 
and return its sum.

 

Example 1:

    Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
    Output: 6
    Explanation: The subarray [4,-1,2,1] has the largest sum 6.

Example 2:

    Input: nums = [1]
    Output: 1
    Explanation: The subarray [1] has the largest sum 1.

Example 3:

    Input: nums = [5,4,-1,7,8]
    Output: 23
    Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
 
*/

/*
Observation:
    If the current prefix becomes negative,
    it can only hurt future subarrays.



1 way
    curr = max(nums[i], curr + nums[i]);
    best = max(best, curr);

2nd way
    curr += nums[i];
    best = max(best, curr);

    if(curr < 0)
        curr = 0;
*/
#include <iostream>
#include <vector>
using namespace std;


int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    if(n == 0)
        return 0;

    int curr = nums[0];
    int best = nums[0];

    for(int i=1; i<n; i++) {
        curr = max(nums[i], curr + nums[i]);
        best = max(best, curr);
    }
    return best;
}

/*
brute force
    generate all subarrays
        track max sum

The DP interpretation
    f(i)
        best sum ending at idx i

        either we extend the previous sum
        or start a fresh sum

        dp[i] = max(nums[i], dp[i-1] + nums[i])

    then once we have the dp table
    return max value
    int ans = *max_element(dp.begin(), dp.end());

kadane optimization
    we only depend on dp[i-1]
        can be replaced by 1 var
    and track max at each step
*/

int main() {

    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << maxSubArray(nums) << endl;

    nums = {1};
    cout << maxSubArray(nums) << endl;

    nums = {5,4,-1,7,8};
    cout << maxSubArray(nums) << endl;

    return 0;
}

// modification, return the starting and ending index for the best sum
// return 
// start-idx, end-idx,sum
tuple<int,int,int> maxsum2(vector<int> &nums) {

    int n = nums.size();
    if(n == 0)
        return {-1,-1,0};

    int curr = nums[0];
    int best = nums[0];
    int prev_start = 0;
    int best_start = 0;
    int best_end = 0;

    for(int i=1; i<n; i++) {

        // curr = max(nums[i], curr+nums[i]);
        if(curr + nums[i] < nums[i]) {
            curr = nums[i];
            prev_start = i;
        }
        else{
            curr += nums[i];
        }

        // best = max(best, curr);
        if(curr > best) {
            best_start = prev_start;
            best_end = i;
            best = curr;
        }
        
        
    }
    return {best_start, best_end, best};
}