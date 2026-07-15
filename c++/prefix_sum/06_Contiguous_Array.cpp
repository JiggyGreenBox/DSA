/*
Contiguous Array
    [https://leetcode.com/problems/contiguous-array/description/]

Given a binary array nums, return the maximum length of a contiguous 
subarray with an equal number of 0 and 1.

 
Example 1:

    Input: nums = [0,1]
    Output: 2
    Explanation: [0, 1] is the longest contiguous subarray with an equal 
    number of 0 and 1.

Example 2:

    Input: nums = [0,1,0]
    Output: 2
    Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with 
    equal number of 0 and 1.

Example 3:

    Input: nums = [0,1,1,1,1,1,0,0,0]
    Output: 6
    Explanation: [1,1,1,0,0,0] is the longest contiguous subarray with 
    equal number of 0 and 1.

*/

/*
Contiguous Array
lets consider 0 as -1 and 1 as 1
    then for any subarray sum == 0
        there will be equal 0s and 1s


 0,1,1,1,1,1,0,0,0
-1,0,1,2,3,4,3,2,1

we can use a prefix sum array
    if (running_total) found in prefix
        calculate len
        update max_len
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

int findMaxLength(vector<int>& nums) {
    unordered_map<int, int> mpp; // sum, idx

    mpp[0] =  -1;

    
    int sum = 0;
    int max_len = 0;
    for(int i=0; i<nums.size(); i++) {

        if(nums[i] == 0)
            sum += -1;
        else
            sum += 1;

        if(mpp.find(sum) != mpp.end()) {
            int len = i - mpp[sum];
            max_len = max(max_len, len);
        }
        
        if(mpp.count(sum) == 0)
            mpp[sum] = i;
    }
    return max_len;
}

int main() {

    vector<int> nums = {0,1};    
    cout << findMaxLength(nums) << endl;

    nums = {0,1,0};
    cout << findMaxLength(nums) << endl;

    nums = {0,1,1,1,1,1,0,0,0};
    cout << findMaxLength(nums) << endl;

    return 0;
}