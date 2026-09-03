/*
Find the Duplicate Number
    [https://leetcode.com/problems/find-the-duplicate-number/description/]

Given an array of integers nums containing n + 1 integers where each 
integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated 
number.

You must solve the problem without modifying the array nums and using 
only constant extra space.

 

Example 1:

Input: nums = [1,3,4,2,2]
Output: 2
Example 2:

Input: nums = [3,1,3,4,2]
Output: 3
Example 3:

Input: nums = [3,3,3,3,3]
Output: 3


(1 ^ 3 ^ 4 ^ 2 ^ 2) ^ (1 ^ 2 ^ 3 ^ 4)
1+1
3+3
4+4
2+2+2

*/

#include <vector>
using namespace std;

int findDuplicate(vector<int>& nums) {
    int slow = nums[0];
    int fast = nums[nums[0]];

    // Phase 1: find meeting point
    while(slow != fast) {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }

    // Phase 2: find cycle entrance
    slow = nums[0];

    while(slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }

    return slow;
}