/*
Maximum Average Subarray I
    [https://leetcode.com/problems/maximum-average-subarray-i/description/]

You are given an integer array nums consisting of n elements, and an 
integer k.

Find a contiguous subarray whose length is equal to k that has the 
maximum average value and return this value. Any answer with a 
calculation error less than 10-5 will be accepted.

 

Example 1:

Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75
Example 2:

Input: nums = [5], k = 1
Output: 5.00000


*/

#include <vector>
#include <iostream>
using namespace std;



double findMaxAverage2(const vector<int>& nums, int k) {
    int window_sum = 0;

    for (int i = 0; i < k; i++)
        window_sum += nums[i];

    int max_sum = window_sum;

    for (int i = k; i < nums.size(); i++) {
        window_sum += nums[i] - nums[i - k];
        max_sum = max(max_sum, window_sum);
    }

    return (double)max_sum / k;
}

int main() {

    vector<int> nums = {1,12,-5,-6,50,3};
    int k = 4;
    cout << findMaxAverage2(nums, k) << endl;

    return 0;

}