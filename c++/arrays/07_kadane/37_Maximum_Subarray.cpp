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
The DP interpretation
    curr = max(nums[i], curr + nums[i]);

    dp[i] = max(
        start new subarray,
        extend previous subarray
    )


    curr = -5
    nums[i] = 4

        Extend
        -5 + 4 = -1
    
        Start new
        4
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