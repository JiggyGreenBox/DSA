/*
Count_Number_of_Nice_Subarrays
    [https://leetcode.com/problems/count-number-of-nice-subarrays/description/]

Given an array of integers nums and an integer k. A continuous 
subarray is called nice if there are k odd numbers on it.

Return the number of nice sub-arrays.

 

Example 1:

    Input: nums = [1,1,2,1,1], k = 3
    Output: 2
    Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and 
    [1,2,1,1].

Example 2:

    Input: nums = [2,4,6], k = 1
    Output: 0
    Explanation: There are no odd numbers in the array.

Example 3:

    Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
    Output: 16
*/

/*
[1,1,2,1,1], k = 3
[1,2,2,3,4]

mpp odd, count

we want 
    prefix[r] - prefix[l-1] = k

    prefix[l-1] = prefix[r] - k

[2,2,1] k = 1
[0,0,1]


*/
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

int numberOfSubarrays(vector<int>& nums, int k) {
    unordered_map<int, int> freq; // oddCount, freq

    freq[0] = 1;

    int count = 0;
    int prefix = 0;
    for(int num : nums) {
        
        if(num & 1)
            prefix++;

        if(freq.count(prefix - k)) {
            count += freq[prefix - k];
        }
        freq[prefix]++;
    }
    return count;
}

int main() {
    vector<int> nums = {1,1,2,1,1};
    int k = 3;
    cout << numberOfSubarrays(nums, k) << endl;

    nums = {2,4,6}; k = 1;
    cout << numberOfSubarrays(nums, k) << endl;

    nums = {2,2,2,1,2,2,1,2,2,2}; k = 2;
    // nums = {2, 1}; k = 1;
    cout << numberOfSubarrays(nums, k) << endl;
    return 0;
}