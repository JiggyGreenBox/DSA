#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


/*
Subarray Sums Divisible by K
    [https://leetcode.com/problems/subarray-sums-divisible-by-k/description/]

Given an integer array nums and an integer k, return the number of 
non-empty subarrays that have a sum divisible by k.

A subarray is a contiguous part of an array.

 

Example 1:

    Input: nums = [4,5,0,-2,-3,1], k = 5
    Output: 7
    Explanation: There are 7 subarrays with a sum divisible by k = 5:
    [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], 
    [-2, -3]

Example 2:

    Input: nums = [5], k = 9
    Output: 0

*/

/*
we want (prefix[r] - prefix[l-1]) % k == 0
    prefix[l-1] % k = prefix[r] % k

    17 % 5 = 2
    7 % 5 = 2
    17-7 = 10 & 5 == 0

for prefix[l-1]
    what about l = 0

    [5], k=5
    5%5 = 0
        count += mpp[0] = 1
*/

int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int, int> freq; // sum%k, freq

    freq[0] = 1;

    int count = 0;
    int prefix = 0;

    for(int num : nums) {
        prefix += num;

        int rem = ((prefix % k) + k) % k;

        if(freq.count(rem)) {
            count += freq[rem];
        }

        freq[rem]++;
    }
    return count;
}

// review
// numbers can be negative
    // int rem = ((prefix % k) + k) % k;
// calculate rem once

int subarraysDivByK2(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    freq[0] = 1;

    int count = 0;
    int prefix = 0;

    for (int num : nums) {
        prefix += num;

        int rem = ((prefix % k) + k) % k;

        count += freq[rem];
        freq[rem]++;
    }

    return count;
}

int main() {

    // vector<int> nums = {4,5,0,-2,-3,1};
    // int k = 5;
    // cout << subarraysDivByK(nums, k) << endl;

    // nums = {5}, k = 9;
    // cout << subarraysDivByK(nums, k) << endl;

    /*
    MATHEMATICAL MODULO VS C++ MODULO

    6 % 5 = 5/5 + 1 so 1
    -3 % 5 = (-1) * 5 + 2 so +2

    but in C++
        -3 % 5 = (0) * 5 - 3 so -3

        so ((num % k) + k) % k
    */
    return 0;
}