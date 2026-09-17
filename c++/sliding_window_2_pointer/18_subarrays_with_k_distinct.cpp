/*
Subarrays with K Different Integers
    [https://leetcode.com/problems/subarrays-with-k-different-integers/description/]

Given an integer array nums and an integer k, return the number of 
good subarrays of nums.

A good array is an array where the number of different integers in 
that array is exactly k.

For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [1,2,1,2,3], k = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: 
[1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]
Example 2:

Input: nums = [1,2,1,3,4], k = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: 
[1,2,1,3], [2,1,3], [1,3,4].

*/

/*
use a count array to cound distinct chars

left
right

for char,c in str (right++)
    if(count[c] == 0)
        distinct++
    count[c]++
    
    while(distinct > k)        
        count[left]--
        if(count[left] == 0)
            distinct--
        left++

    if(distinct == k)
        total += right-left+1

return total
*/

#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;


/*
we want count of subarrays
    where distinct is == k

for checking equals or not equals we can use a sliding window easily
for counting how do we do this?
    if keep distinct == k
        how do we know the inner subarray details without checking each subarray?

but we can say in this subarray
    all subarrays have distinct <= k 
        without check each combination in O(n) pass

    so perform another O(n) pass
        and find distinct <= k-1

    then the diff is exacly == k

*/

int atMostKDistinct(vector<int>& nums, int k) {

    int left = 0;

    int distinct = 0;

    int total = 0;

    unordered_map<int, int> count;

    for(int right=0; right<nums.size(); right++) {

        if(count[nums[right]] == 0)
            distinct++;

        count[nums[right]]++;

        while(distinct > k) {
            count[nums[left]]--;
            if(count[nums[left]] == 0)
                distinct--;
            left++;
        }

        total += (right - left + 1);
    }

    return total;
}

int subarraysWithKDistinct(vector<int>& nums, int k) {
    return atMostKDistinct(nums, k) -  atMostKDistinct(nums, k-1);
}

int main() {

    vector<int> nums = {1,2,1,2,3};
    int k = 2;
    cout << subarraysWithKDistinct(nums, k) << endl;

    nums = {1,2,1,3,4}; k = 3;
    cout << subarraysWithKDistinct(nums, k) << endl;
    
    return 0;
}