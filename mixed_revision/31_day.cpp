/*
============================================
nov 23
    last nov 21
============================================
Problem 1
============================================
Search in Rotated Sorted Array (LC 33)

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Requirement: O(log n) time complexity.

brute force:
    linear search
        loop n time complexity

    sorted but rotated
        binary search to discard half the array
        but which half

    we can check which half is sorted and if
    the target is in this range


    [1 2 3 4 5 6 7]

    [5 6 7 1 2 3 4]
        target = 3

        l=5
        m=1
        h=4



    [2 3 4 5 6 7 1]
        l=2
        m=5
        h=1

    if target == m
        return m

    find sorted half
    if l<=m
        left sorted
        if target < l
            discard
        else 
            keep
    else
        right sorted

        if target < m
            discard
        else 
            keep

time complexity
    logn time
    1 space
code
    int findIndex(vector<int> &nums, int target) {
        int n = nums.size();
        int l = 0;
        int r = n-1;

        while(l <= r) {
            int m = l + (r-l)/2;

            if(nums[m] == target)
                return m;

            // left sorted
            if(nums[l] <= nums[m]) {
                // is target in the sorted range
                if(nums[l] <= target && target < nums[m])
                    r = m-1;
                else
                    l = m+1;
            }
            // right sorted
            else {
                // is target in the sorted range
                if(nums[m] < target && target <= nums[r])
                    l = m+1;                
                else
                    r = m-1;
            }

        }
        return -1;
    }

============================================
Problem 2
============================================
maximum length of a contiguous subarray with an equal number of 0s and 1s.

Input:  nums = [0,1,0]
Output: 2

first approach is a brute force
    generate every subarray (n^2) and use a counter
        +1 for a 1
        -1 for a 0
        total++ if the result is zero

    we can extend this logic and improve the time complexity
    lets store the +1 and -1 for each 0 and 1 we encounter
    in a prefix array
    we want sum(i,j) == 0
    prefix[r+1] - prefix[l] == 0
    prefix[r+1] == prefix[l]

    since the same prefix can occur multiple times
    we want len so the len is right-left, for prefix

    we want longest so we write the index if the prefix doesnt exist

    time O(n)
    space O(n)

code
    int longest(vector<int> &nums) {
        unordered_map<int, int> mpp; // sum, idx
        mpp[0] = -1;

        int prefix = 0;
        int max_len = 0;
        for(int i=0; i<nums.size(); i++) {
            
            if(nums[i] == 0)
                prefix -= 1;
            else
                prefix += 1;
            
            auto it = mpp.find(prefix);
            if(it != mpp.end()) {
                int len = i - it->second;
                max_len = max(max_len, len);
            }
            else {
                // only store unique prefix once
                mpp[prefix] = i;
            }        
        }    
        return max_len;   
    }

============================================
Problem 3
============================================
integer array nums, find a contiguous subarray that has the largest 
product, and return that product.


Input:  nums = [2,3,-2,4]
Output: 6

Input:  nums = [-2,0,-1]
Output: 0

brute force
    generate all subarrays
        track max product so far

    can we have a O(n) approach?
        at each step
        we extend pos
        we extend neg
        we start a new prod


whats the derivation
    [2,3,4]
        what is the max product ending at an idx
        [2,3,4]
        [2,6,24]

    [-2,3,4]
        [-2,3,12]  at 3 we chose max of -2*3, 3

    [-2,3,4,-2]
        [-2,-6,-24, 48]
        [-2, 3, 12, -24]

        we need to track maxpos, max neg

    max_pos = extend, new
    max_neg = extend, new

        but a neg flips

    one solution 


*/
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <assert.h>
using namespace std;



int maxProduct(vector<int>& nums) {
    long long curr_max = nums[0];
    long long curr_min = nums[0];
    long long ans = nums[0];

    for(int i = 1; i < nums.size(); i++) {
        long long x = nums[i];

        if(x < 0)
            swap(curr_max, curr_min);

        curr_max = max(x, curr_max * x);
        curr_min = min(x, curr_min * x);

        ans = max(ans, curr_max);
    }

    return static_cast<int>(ans);
}

int maxProduct2(vector<int>& nums) {
    long long curr_max = nums[0];
    long long curr_min = nums[0];
    long long ans = nums[0];

    for(int i = 1; i < nums.size(); i++) {
        long long x = nums[i];
        

        long long newMax = max({x, curr_max * x, curr_min*x});
        long long newMin = min({x, curr_max * x, curr_min*x});
        
        curr_max = newMax;
        curr_min = newMin;

        ans = max(ans, curr_max);
    }

    return static_cast<int>(ans);
}


int main() {
    vector<int> nums;
    nums = {2,3,4};         
    assert(maxProduct(nums) == 24);
    assert(maxProduct2(nums) == 24);

    nums = {-2,3,4};         
    assert(maxProduct(nums) == 12);
    assert(maxProduct2(nums) == 12);

    nums = {-2,3,4,-2};         
    assert(maxProduct(nums) == 48);
    assert(maxProduct2(nums) == 48);

    return 0;
}