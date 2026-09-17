/*
Minimum_Size_Subarray_Sum
[https://leetcode.com/problems/minimum-size-subarray-sum/description/]

Given an array of positive integers nums and a positive integer 
target, return the minimal length of a subarray whose sum is greater 
than or equal to target. If there is no such subarray, return 0 
instead.

 

Example 1:

    Input: target = 7, nums = [2,3,1,2,4,3]
    Output: 2
    Explanation: The subarray [4,3] has the minimal length under the 
    problem constraint.

Example 2:

    Input: target = 4, nums = [1,4,4]
    Output: 1

Example 3:

    Input: target = 11, nums = [1,1,1,1,1,1,1,1]
    Output: 0

*/

/*
we want a sum(l,r) == target
    but we want this to have the smallest len
        min(r-l+1)

    prefix[r] - prefix[l-1] == target    

    prefix[l-1] == prefix[r] - target

    when found update minLen

    since we want len
        we keep it as
        mpp[] =
        
    
*/


#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
using namespace std;

// prefix sum can allow an exact match
// but when we introduce a range this is not possible with un-map

// sliding window
// O(n) time
// O(1) space
int minSubArrayLen2(int target, vector<int>& nums) {
    int sum = 0;
    int min_len = INT_MAX;
    int left = 0;

    for(int right=0; right<nums.size(); right++) {
        sum += nums[right];

        while(sum >= target) {
            min_len = min(min_len, right - left + 1);
            sum -= nums[left];
            left++;
        }
        
    }
    return min_len == INT_MAX ? 0 : min_len;
}

int main() {
    int target = 7;
    vector<int> nums = {2,3,1,2,4,3};
    cout << minSubArrayLen2(target, nums) << endl;

    target = 4; nums = {1,4,4};
    cout << minSubArrayLen2(target, nums) << endl;

    target = 11; nums = {1,1,1,1,1,1,1,1};
    cout << minSubArrayLen2(target, nums) << endl;

    return 0;
}