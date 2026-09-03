/*
Find All Duplicates in an Array
    [https://leetcode.com/problems/find-all-duplicates-in-an-array/description/]

Given an integer array nums of length n where all the integers of 
nums are in the range [1, n] and each integer appears at most twice, 
return an array of all the integers that appears twice.

You must write an algorithm that runs in O(n) time and uses only 
constant auxiliary space, excluding the space needed to store the 
output

 

Example 1:

Input: nums = [4,3,2,7,8,2,3,1]
Output: [2,3]
Example 2:

Input: nums = [1,1,2]
Output: [1]
Example 3:

Input: nums = [1]
Output: []
*/

/*
use the nums array itself to mark seen
how?
    we know all numbers are positive
    range is [1,n]

    idx is [0,n-1]

    make the number at idx negative

    then if we find it negative again, this is a duplicate
*/
#include <vector>
#include <cmath>
using namespace std;

vector<int> findDuplicates(vector<int>& nums) {
    vector<int> ans;

    for (int x : nums) {
        int val = abs(x);   // second pass, this will be negative
        int idx = val - 1;  // range is [1,n] so idx is [0,n-1]

        if (nums[idx] < 0) {
            ans.push_back(val);
        }
        else {
            nums[idx] = -nums[idx];
        }
    }

    return ans;
}