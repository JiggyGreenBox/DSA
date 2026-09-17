/*
============================================
sep 17
    last sep 14
============================================


Problem 1 — Arrays

Product of Array Except Self

Given an integer array nums, return an array answer such that:

answer[i] is equal to the product of all elements of nums except 
nums[i].

Constraints:

2 <= nums.length <= 10^5
-30 <= nums[i] <= 30
The product of any prefix or suffix fits in a 32-bit integer.
Do not use division.
Target: O(n) time and O(1) extra space (excluding the output array).


nums = [1,2,3,4]

answer = [24,12,8,6]

---

Derivation
    for any idx
    [-,-,i,-,-]
    ans[i] = prod[0..i-1] * prod[i+1..n-1]

    we can use a left prefix
    and then a right prefix with 2 passes

algorithm
    vector<int> prod(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans(n, 1);

        int prefix = 1;
        for(int i=0; i<n; i++) {
            ans[i] *= prefix;
            prefix *= nums[i];
        }

        prefix = 1;
        for(int i=n-1; i>=0; i--) {
            ans[i] *= prefix;
            prefix *= nums[i];
        }

        return ans;
    }

complexity
    O(n) time
    O(1) space 
==========================================

Problem 2 — Prefix Sum + Hashing

Subarray Sum Equals K

Given an integer array nums and an integer k, return the total number 
of subarrays whose sum equals k.

    nums = [1, 1, 1]
    k = 2

    answer = 2

nums = [1, 2, 3]
k = 3

answer = 2


Brute force
    generate every subarray
        check sum
            if == k
                increase total count
Observation
    negative numbers are allowed
    so sliding window approach is not possible

    we want sum(subarray) == k
    sum(l,r) == k

    prefix[r] - prefix[l-1] == k
    prefix[l-1] == prefix[r] - k

    so we can look for a curprefix sum - k  in a hashmap

    keep a count

Invariant
    use prefix sums and hashmap to keep a count of possible sums
Algorithm
    int countSubarraySum(vector<int> &nums, int k) {
        unordered_map<int,int> freq; // prefix_sum, count

        freq[0] = 1;

        int prefix = 0;
        int total = 0;

        for(int i=0; i<nums.size(); i++) {
            prefix += nums[i];

            int search = prefix - k;
            if(freq.count(search) > 0) {
                total += freq[search];
            }

            freq[prefix]++;
        }
        return total;
    }
Complexity
    O(n) time
    O(n) space
============================================

Problem 3 — Sliding Window

Longest Substring Without Repeating Characters

Given a string s, find the length of the longest substring without 
repeating characters.

Examples
    s = "abcabcbb"
    answer = 3


    s = "bbbbb"
    answer = 1

    s = "pwwkew"
    answer = 3

Brute force
    generate every substring
        use a set
            if any character is present
                break
            store maxlen
Observation
    we can use a sliding window approach here
    expand as long as characters dont repeat
        we keep a count of chars to know this
    when window is invalid
        we shrink till the window is valid again

    track len for each valid window

    another approach is to skip ahead
    we store idx for each char
    then when we find a duplicate
        make the window left jump to idx+1
Invariant
    use a hashmap to store char,idx
    as long as a char is unique within our window 
    the window is valid
    note len, track max_len

    if not unique shrink window using the duplicate char idx
Algorithm
Complexity
    O(n) time
    O(n) space
===================================

Problem 4 — mixed / transfer

Now I want to test whether you can transfer the pattern rather than 
recognize a familiar problem.

Minimum Size Subarray Sum

Given an array of positive integers nums and a positive integer 
target, return the minimum length of a contiguous subarray whose sum 
is greater than or equal to target.

If no such subarray exists, return 0.

Example:

nums = [2,3,1,2,4,3]
target = 7

answer = 2

because [4,3] has sum 7.
------------
Derivation

    since numbers are positive
        adding numbers increases the sum
        and removing numbers reduces the sum
        sliding window approach is possile

    we want minlen of subarray sum >= target

    expand the window till sum >= target
        make the calculation of len
        then shrink and try to find a better target


Complexity
    O(n) time
    O(1) space
=======================================

Problem 4 — Transfer Problem

Contiguous Array

Given a binary array nums containing only 0 and 1, return the length 
of the longest contiguous subarray containing an equal number of 0 
and 1.

Derivation
    we want a subarray with equal number of 0s and 1s
    we can transform this into a prefix problem
        where 0 -1
        and   1 +1

    [0,1,0,1]
    [-1,0,-1,0]

    [ 0,1,1,1,0,0, 0,1,1,1,1,1,0,0,0,0, 0]
    [-1,0,1,2,1,0,-1,0,1,2,3,4,3,2,1,0,-1]
*/



#include <vector>
#include <iostream>
#include <climits>
#include <unordered_map>
using namespace std;

// [a,b,c,a,c,b,b,a]


int contiguousArray(vector<int> &nums) {
        
    unordered_map<int, int> freq;

    freq[0] = -1;
    
    int max_len = INT_MIN;

    int prefix = 0;

    for(int i=0; i<nums.size(); i++) {
        if(nums[i] > 0)
            prefix += 1;
        else
            prefix -= 1;

        if(freq.count(prefix) > 0) {
            max_len = max(max_len, i - freq[prefix]);
        }
        else {
            freq[prefix] = i;
        }
    }
    

    return max_len == INT_MAX ? 0 : max_len;
}

int main() {    
    vector<int> nums = {1,0,0,0,1,1,1};
    cout << contiguousArray(nums) << endl;
    return 0;
}