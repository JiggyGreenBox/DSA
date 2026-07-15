/*
Continuous Subarray Sum
    [https://leetcode.com/problems/continuous-subarray-sum/description/]

Given an integer array nums and an integer k, return true if nums has 
a good subarray or false otherwise.

A good subarray is a subarray where:

its length is at least two, and
the sum of the elements of the subarray is a multiple of k.
Note that:

A subarray is a contiguous part of the array.
An integer x is a multiple of k if there exists an integer n such 
that x = n * k. 0 is always a multiple of k.
 

Example 1:

    Input: nums = [23,2,4,6,7], k = 6
    Output: true
    Explanation: [2, 4] is a continuous subarray of size 2 whose elements 
    sum up to 6.

Example 2:

    Input: nums = [23,2,6,4,7], k = 6
    Output: true
    Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 
    whose elements sum up to 42.
    42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.

Example 3:

    Input: nums = [23,2,6,4,7], k = 13
    Output: false
*/

/*
Continuous Subarray Sum
for any query on prefix
    we want (prefix[R] - prefix[L-1]) % k == 0

    17 and 10
    (17 - 10) % 7 == 0

    17 % 7 == 3
    10 % 7 == 3

    so if (A % k) == (B % k)
        return true if len >1

    [7,7,7] k=7
    mpp[-1] = k or 0
*/
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;


bool checkSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> mpp; // (pref % k), first_idx
    mpp[0] = -1;

    int leftsum = 0;
    for(int i=0; i<nums.size(); i++) {

        leftsum += nums[i];

        if(mpp.find(leftsum%k) != mpp.end()) {
            int len = i - mpp[leftsum%k];
            if(len > 1) 
                return true;
        }
        else {
            mpp[leftsum%k] = i;
        }        
    }
    return false;
}

void print(bool b) {
    if(b) cout << "true" << endl;
    else cout << "false" << endl;
}

int main() {

    vector<int> nums = {23,2,4,6,7};
    int k = 6;
    print(checkSubarraySum(nums, k));

    nums = {23,2,6,4,7};
    k = 6;
    print(checkSubarraySum(nums, k));

    k = 13;
    print(checkSubarraySum(nums, k));

    return 0;
}