/*
3Sum Closest
    [https://leetcode.com/problems/3sum-closest/description/]

Given an integer array nums of length n and an integer target, find 
three integers at distinct indices in nums such that the sum is 
closest to target.

Return the sum of the three integers.

You may assume that each input would have exactly one solution.

 

Example 1:

    Input: nums = [-1,2,1,-4], target = 1
    Output: 2
    Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 
    = 2).

Example 2:

    Input: nums = [0,0,0], target = 1
    Output: 0
    Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 = 
    0).
*/
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
using namespace std;

/*
Sorting:       O(n log n)
Outer loop:    O(n)
Two pointers:  O(n) per i

Total:         O(n²)
Space:         O(1) auxiliary
*/
int threeSumClosest(vector<int>& nums, int target) {

    sort(nums.begin(), nums.end());

    int n = nums.size();
    int best = nums[0] + nums[1] + nums[2];

    for(int i=0; i<n-2; i++) {

        int j = i+1;
        int k = n-1;

        while(j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            
            if(abs(target - sum) < abs(target - best)) {                
                best = sum;
            }

            if(sum == target) {
                return sum;
            }                
            else if(sum > target) {
                k--;
            }                
            else if(sum < target) {
                j++;
            }                
        }
    }
    return best;
}