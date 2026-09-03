/*
Find All Numbers Disappeared in an Array
    [https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/description/]

Given an array nums of n integers where nums[i] is in the range [1, 
n], return an array of all the integers in the range [1, n] that do 
not appear in nums.

 

Example 1:

Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]
Example 2:

Input: nums = [1,1]
Output: [2]


*/
#include <vector>
#include <cmath>
using namespace std;

vector<int> findDisappearedNumbers(vector<int>& nums) {
    vector<int> ans;

    for(int num : nums) {
        int idx = abs(num) - 1;

        if(nums[idx] > 0) {
            nums[idx] = -nums[idx];
        }
    }

    for(int i=0; i<nums.size(); i++) {
        if(nums[i] > 0) {
            ans.push_back(i+1);
        }
    }
    return ans;
}

int main() {
    vector<int> nums = {4,3,2,7,8,2,3,1};
    auto ans = findDisappearedNumbers(nums);
    int x = 5;
    return 0;
}