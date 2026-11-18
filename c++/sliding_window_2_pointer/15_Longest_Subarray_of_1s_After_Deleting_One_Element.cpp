/*
Longest_Subarray_of_1s_After_Deleting_One_Element
    [https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/description/]

Given a binary array nums, you should delete one element from it.

Return the size of the longest non-empty subarray containing only 1's 
in the resulting array. Return 0 if there is no such subarray.

 

Example 1:

Input: nums = [1,1,0,1]
Output: 3
Explanation: After deleting the number in position 2, [1,1,1] 
contains 3 numbers with value of 1's.
Example 2:

Input: nums = [0,1,1,1,0,1,1,0,1]
Output: 5
Explanation: After deleting the number in position 4, 
[0,1,1,1,1,1,0,1] longest subarray with value of 1's is [1,1,1,1,1].
Example 3:

Input: nums = [1,1,1]
Output: 2
Explanation: You must delete one element.


*/

/*
Longest_Subarray_of_1s_After_Deleting_One_Element
this can be like
    Longest Repeating Character Replacement
        with total - maxFreq, and freqMap

but instead we only delete one element
    we can store the non1 idx
        and keep updating 
            left to be idx+1 on next pass

        then len
            right - left (dont consider the non1 element)
*/

#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;
int longestSubarray(vector<int>& nums) {

    int left = 0;    
    int last_zero = -1;
    int max_len = 0;

    for(int right = 0; right<nums.size(); right++) {
        if(nums[right] != 1) {
            left = last_zero + 1;
            last_zero = right;
        }
        max_len = max(max_len, right - left);
    }
    return max_len;
}

int longestSubarray2(vector<int>& nums) {

    int left = 0;        
    int max_len = 0;
    int zeros = 0;

    for(int right = 0; right<nums.size(); right++) {

        if(nums[right] == 0) 
            zeros++;

        while(zeros > 1) { // one zero is allowed
            if(nums[left] == 0)
                zeros--;
            left++;
        }            
        
        max_len = max(max_len, right - left); // either we delete one zero, or one 1 if no zeros
    }
    return max_len;
}

int main() {
    vector<int> nums = {1,1,0,1};
    cout << longestSubarray(nums) << endl; // 3
    assert(longestSubarray(nums) == 3);
    assert(longestSubarray2(nums) == 3);

    nums = {0,1,1,1,0,1,1,0,1};
    cout << longestSubarray(nums) << endl; // 5
    assert(longestSubarray(nums) == 5);
    assert(longestSubarray2(nums) == 5);

    nums = {1,1,1};
    cout << longestSubarray(nums) << endl; // 2
    assert(longestSubarray(nums) == 2);
    assert(longestSubarray2(nums) == 2);
    return 0;
}