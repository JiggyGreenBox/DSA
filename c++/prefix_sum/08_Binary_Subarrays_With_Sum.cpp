/*
Binary Subarrays With Sum
    [https://leetcode.com/problems/binary-subarrays-with-sum/]

    Given a binary array nums and an integer goal, return the number of 
    non-empty subarrays with a sum goal.

    A subarray is a contiguous part of the array. 

Example 1:

    Input: nums = [1,0,1,0,1], goal = 2
    Output: 4
    Explanation: The 4 subarrays are bolded and underlined below:
    [1,0,1,0,1]
    [1,0,1,0,1]
    [1,0,1,0,1]
    [1,0,1,0,1]

Example 2:

    Input: nums = [0,0,0,0,0], goal = 0
    Output: 15
 
*/
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
/*
prefix[i] = num[0] + ... nums[i]

subarray[l,r]
    sum(l,r) = prefix[r] - prefix[l-1]

we want 
    prefix[r] - prefix[l-1] = goal
    prefix[r] - goal = prefix[l-1]

    prefix[l-1] = prefix[r] - goal

so keep a sum and a frequency in hashmap

mpp[0] = 1
    why??
    nums = [1,1], goal=2
    at 1, 1-2 = -1
    at 1, 2-2 = 0
    so count of 0 = 1



LC 525:
same prefix sum → longest
                 → store earliest index

LC 930:
prefix - goal    → count all
                 → store frequency
    
*/



int numSubarraysWithSum(vector<int>& nums, int goal) {
    unordered_map<int, int> freq; // sum, freq

    freq[0] = 1;

    int prefix = 0;
    int count = 0;

    for (int x : nums) {
        prefix += x;

        if (freq.count(prefix - goal))
            count += freq[prefix - goal];

        freq[prefix]++;
    }

    return count;
}

int main() {
    vector<int> nums = {1,0,1,0,1};
    int goal = 2;
    cout << numSubarraysWithSum(nums, goal) << endl;


    nums = {0,0,0,0,0}; goal = 0;
    cout << numSubarraysWithSum(nums, goal) << endl;

    return 0;
}