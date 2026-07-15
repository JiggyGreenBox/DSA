/*
Subarray Sum Equals K
    [https://leetcode.com/problems/subarray-sum-equals-k/description/]
Given an array of integers nums and an integer k, return the total 
number of subarrays whose sum equals to k.

A subarray is a contiguous non-empty sequence of elements within an 
array.

 

Example 1:

Input: nums = [1,1,1], k = 2
Output: 2
Example 2:

Input: nums = [1,2,3], k = 3
Output: 2

*/

/*
we want any subarray which has a sum equal to k

any query for subarrays sum(l,r) = pre[r+1] - pre[l]

we could have a 2 pass solution
we can also check it while as we go

keep total-so-far
    we keep hashmap for O(1) search
    if total-k found
        count++
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

// wrong code
// why wrong?
/*
[0,0,0]
k=0

ans=3
but it is actually 6
*/
int subarraySum_wrong(vector<int>& nums, int k) {
    unordered_set<int> mpp;

    mpp.insert(0);

    int total = 0;
    int count = 0;
    for(int num : nums) {
        total += num;
        if(mpp.count(total - k) > 0) {
            count++;
        }
        mpp.insert(total);
    }
    return count;
}
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    freq[0] = 1;    

    int total = 0;
    int count = 0;
    for(int num : nums) {
        total += num;
        if(freq.count(total - k) > 0) {
            count += freq[total - k];
        }
        freq[total]++;
    }
    return count;
}




int main() {

    vector<int> nums = {1,1,1}; 
    int k = 2;
    cout << subarraySum(nums, k) << endl;

    nums = {1,2,3};
    k = 3;
    cout << subarraySum(nums, k) << endl;

    nums = {0,0,0};
    k = 0;
    cout << subarraySum(nums, k) << endl;

    return 0;
}