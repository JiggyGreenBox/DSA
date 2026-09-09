/*
Shortest Unsorted Continuous Subarray
    [https://leetcode.com/problems/shortest-unsorted-continuous-subarray/description/]

Given an integer array nums, you need to find one continuous subarray 
such that if you only sort this subarray in non-decreasing order, 
then the whole array will be sorted in non-decreasing order.

Return the shortest such subarray and output its length.

 

Example 1:

    Input: nums = [2,6,4,8,10,9,15]
    Output: 5
    Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to 
    make the whole array sorted in ascending order.

Example 2:

    Input: nums = [1,2,3,4]
    Output: 0

Example 3:

    Input: nums = [1]
    Output: 0
*/

#include <vector>
#include <climits>
#include <iostream>
using namespace std;

/*
1. Find first i where nums[i] > nums[i+1]
2. Find last j where nums[j-1] > nums[j]
3. Find min/max inside nums[i..j]
4. Expand left if something before the range > min
5. Expand right if something after the range < max
*/

int findUnsortedSubarray(vector<int>& nums) {
    int i = 0;
    int j = 0;

    int n = nums.size();

    if(n == 0)
        return 0;

    // find first inversion
    while(i<n-1 && nums[i] < nums[i+1])
        i++;

    if(i == n-1)
        return 0;

    // check if another inversion inversion    
    for(int k=i+1; k<n; k++) {
        if(nums[k-1] > nums[k])
            j = k;
    }

    int minNum = INT_MAX;
    int maxNum = INT_MIN;
    for(int k=i; k<=j; k++) {
        minNum = min(minNum, nums[k]);
        maxNum = max(maxNum, nums[k]);
    }

    // check for range [i,j] after min, max are at [i,j] after swapping
    // if we still need to extend the range further

    // 1,2,3 [2]
    while(i > 0 && nums[i-1] > minNum)
        i--;

    // [3,8] 7
    while(j < n-1 && nums[j+1] < maxNum)
        j++;

    return j - i + 1;

}

int findUnsortedSubarray2(vector<int>& nums) {
    int n = nums.size();

    int left = -1;
    int right = -1;

    int maxSeen = INT_MIN;
    int minSeen = INT_MAX;

    // Find right boundary
    for(int i = 0; i < n; i++) {
        maxSeen = max(maxSeen, nums[i]);

        if(nums[i] < maxSeen)
            right = i;
    }

    // Find left boundary
    for(int i = n - 1; i >= 0; i--) {
        minSeen = min(minSeen, nums[i]);

        if(nums[i] > minSeen)
            left = i;
    }

    if(left == -1)
        return 0;

    return right - left + 1;
}

int main() {
    vector<int> nums = {2,6,4,8,10,9,15};
    cout << findUnsortedSubarray(nums) << endl;

    nums = {1,2,3,4};
    cout << findUnsortedSubarray(nums) << endl;

    nums = {1};
    cout << findUnsortedSubarray(nums) << endl;
    return 0;
}