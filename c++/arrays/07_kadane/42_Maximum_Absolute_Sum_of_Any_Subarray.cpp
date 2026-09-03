/*
Maximum Absolute Sum of Any Subarray
    [https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/description/]

You are given an integer array nums. The absolute sum of a subarray 
[numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + 
numsr-1 + numsr).

Return the maximum absolute sum of any (possibly empty) subarray of 
nums.

Note that abs(x) is defined as follows:

If x is a negative integer, then abs(x) = -x.
If x is a non-negative integer, then abs(x) = x.
 

Example 1:

Input: nums = [1,-3,2,3,-4]
Output: 5
Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) 
= 5.
Example 2:

Input: nums = [2,-5,1,-4,3,-2]
Output: 8
Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = 
abs(-8) = 8.
*/

/*
for this problem i think keeping a max kadane and min kadane is good, 
then at the end return the abs max of both?
*/


#include <vector>
#include <cmath>
using namespace std;

int maxAbsoluteSum(vector<int>& nums) {
    int maxSubarray = nums[0];
    int minSubarray = nums[0];

    int currMax = nums[0];
    int currMin = nums[0];

    for(int i = 1; i < nums.size(); i++) {
        int x = nums[i];

        currMax = max(x, currMax + x);
        maxSubarray = max(maxSubarray, currMax);

        currMin = min(x, currMin + x);
        minSubarray = min(minSubarray, currMin);
    }

    return max(abs(maxSubarray), abs(minSubarray));
}