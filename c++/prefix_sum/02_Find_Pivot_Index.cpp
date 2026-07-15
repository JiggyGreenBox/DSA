
/*
Find Pivot Index
    [https://leetcode.com/problems/find-pivot-index/description/]

Given an array of integers nums, calculate the pivot index of this 
array.

The pivot index is the index where the sum of all the numbers 
strictly to the left of the index is equal to the sum of all the 
numbers strictly to the index's right.

If the index is on the left edge of the array, then the left sum is 0 
because there are no elements to the left. This also applies to the 
right edge of the array.

Return the leftmost pivot index. If no such index exists, return -1.

 

Example 1:

Input: nums = [1,7,3,6,5,6]
Output: 3
Explanation:
The pivot index is 3.
Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
Right sum = nums[4] + nums[5] = 5 + 6 = 11
Example 2:

Input: nums = [1,2,3]
Output: -1
Explanation:
There is no index that satisfies the conditions in the problem 
statement.
Example 3:

Input: nums = [2,1,-1]
Output: 0
Explanation:
The pivot index is 0.
Left sum = 0 (no elements to the left of index 0)
Right sum = nums[1] + nums[2] = 1 + -1 = 0
*/

/*

1,7, 3, 6, 5, 6
1,8,11,17,22,28

1 == 28-8 = 20?

8 == 28-11 17?

11 == 28 - 17? 11 YES
  
build prefix sum
iter 0 to n-2
*/

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int pivotIndex(vector<int>& nums) {
    int n = nums.size();
    vector<int> prefix(n + 1);

    for(int i=0; i<n; i++) {
        prefix[i+1] = prefix[i] + nums[i];
    }

    for(int i=0; i<n; i++) {


        // sum = prefix[r+1] - prefix[l]
        // or sum = prefix[r+1] - prefix[l-1]
        // we dont count the index we are standing at

        // for any idx m
        // left = pre[m-1] - pre[-1]
        // right = pre[n-1] - pre[m+1-1]

        // if we use a +1 version
        // left = pre[m-1+1] - pre[-1+1]
        // right = pre[n-1+1] - pre[m+1-1+1]

        // left = pre[m] - pre[0]
        // right = pre[n] - pre[m+1]

        int left = prefix[i] - prefix[0];
        int right = prefix[n] - prefix[i+1];
        if(left == right)
            return i;
    }
    return -1;
}


int pivotIndex2(vector<int>& nums) {
/*
    int left = prefix[i] - prefix[0];
    int right = prefix[n] - prefix[i+1];
    if(left == right)
        return i;

    prefix[0] is 0
    and prefix[n] is total

    then 
        if leftsum == total - leftsum - curr
            return index

        add curr to leftsum
*/
    int total = accumulate(nums.begin(), nums.end(), 0);
    int leftsum = 0;

    for(int i=0; i<nums.size(); i++) {
        if(leftsum == total - leftsum - nums[i])
            return i;

        leftsum += nums[i];
    }
    return -1;
}


int main() {
    vector<int> v ={1,7,3,6,5,6}; // 3    


    cout << pivotIndex2(v) << endl;

    v = {1,2,3}; // -1

    cout << pivotIndex2(v) << endl;

    v = {2,1,-1}; // 0

    cout << pivotIndex2(v) << endl;

    return 0;
}