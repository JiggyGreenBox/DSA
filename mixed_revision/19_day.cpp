/*
============================================
sep 23
    last sep 22
============================================

Session 2 - Arrays / Prefix Sum / Hashing.

============================================

Question 1

Given an integer array nums, find the length of the longest 
consecutive sequence of integers.

The elements do not need to be adjacent in the original array.

nums = [100, 4, 200, 1, 3, 2]

answer = 4

nums = [0,3,7,2,5,8,4,6,0,1]

answer = 9

brute force
    store all elements in a set
    n^2 loop from each to find how many exist
        n^2time, n space

    sort elements
        use 2 pointer to check the longest consecutive

    nlogn time
    1 space

observation
    we can use a set to store all elements
    then for each element
        if num-1 exists
            not starting, skip

        count=1
        till num++ in set
            count++
        store max
    
    O(n) space for set
    O(n) time
    

invariant
    use a set to store occurance
    clever pruning to avoid checking non-starting elements
algorithm
    int longest_consec_subseq(vector<int> &nums) {
        int max_count = 0;
        unordered_set<int> mset;

        for(int num : nums)
            mset.insert(num);

        for(int num : nums) {

            // num is not the starting of a sequence
            if(mset.count(num-1) > 0)
                continue;

            int count = 1;
            while(mset.count(++num) > 0)
                count++;
            
            max_count = max(max_count, count);
        }

        return max_count;
    }
complexity
    O(n) time expected
    O(n) space

============================================

Question 2

Given an integer array nums, return the maximum length of a subarray 
whose sum is 0.

The array may contain positive, negative, and zero values.

nums = [9, -3, 3, -1, 6, -5]
    5

brute force
    generate all subarrays
        n^2 check sum ==0
            return longest

observation
    we could have used sliding window to check subarray sums 
    if positive numbers were present

    but negative numbers dont allow for a monotonic sum
    we can use prefix arrays to get subarray sums

    we want 
        longest subarray sum == 0
    prefix[r] - prefix[l-1] = 0

    we want prefix[r] = prefix[l-1]

    since we want longest, dont update if a duplicate
    prefix sum is found

invariant
    use prefix sums with hashing to find the best subarray
        hashtable stores earliest sum

algorithm
    int subsumzero(vector<int> &nums) {
        unordered_map<int, int> mpp; // <prefix_sum, idx>
        mpp[0] = -1;

        int max_len = 0;

        int prefix = 0;

        for(int i=0; i<nums.size(); i++) {
            prefix += nums[i];

            if(mpp.count(prefix) > 0) {
                max_len = max(max_len, i - mpp[prefix]);
            }
            else {
                mpp[prefix] = i;
            }
        }

        return max_len;
    }
complexity:
    O(n) time
    O(n) space


=====================================

Question 3 — last one of Session 1

Let's move away from the obvious prefix-sum pattern.

Given an array nums and an integer k, return the number of subarrays 
whose sum is divisible by k.

nums = [4, 5, 0, -2, -3, 1]
k = 5

brute force:
    generate all subarrays
        add the sum
            if %k == 0
                count++

    n^2 time, O(1) space


observation:
    can predicably use a sliding window due to negative numbers
    we can use prefix sums to query subarray sums

    we want
        subarraysum %k == 0

        (prefix[r] - prefix[l-1])%k == 0

        prefix[r]%k == prefix[l-1]%k

    just a note
        we need to take care of (-ve)%k
        by search = ((num%k) + k ) % k

invariant:
    use prefix sums with hashing to find count of subarrays

algorithm:
    int num_subarrays_div_k(vector<int> &nums, int k) {
        unordered_map<int, int> mpp; // <prefixsum % k, count>

        mpp[0] = 1;

        int prefix = 0;
        int count = 0;

        for(int i=0; i<nums.size(); i++) {
            prefix += nums[i];

            int search = ((prefix % k) + k) % k;

            if(mpp.count(search)) {
                count += mpp[search];
            }

            mpp[search]++;
        }

        return count;
    }
complexity:
    O(n) time
    O(n) space
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;



int main() {
    vector<int> nums = {4, 5, 0, -2, -3, 1};
    // cout << num_subarrays_div_k(nums, 5) << endl; // 7
    return 0;
}