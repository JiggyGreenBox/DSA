/*
Partition to K Equal Sum Subsets
    [https://leetcode.com/problems/partition-equal-subset-sum/description/]

Given an integer array nums and an integer k, return true if it is 
possible to divide this array into k non-empty subsets whose sums are 
all equal.

 

Example 1:

Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true
Explanation: It is possible to divide it into 4 subsets (5), (1, 4), 
(2,3), (2,3) with equal sums.
Example 2:

Input: nums = [1,2,3,4], k = 3
Output: false
*/

/*
we want to split the array into k bucket such that
each bucket has sum == target

target = total / k
    if total % k != 0
        not possible

k buckets
    for each num
        try k buckets
            recurse

if we reach the end
    return if all buckets have value == target
*/

#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

bool dfs(int idx, 
        vector<int> &buckets, 
        const vector<int> &nums, 
        const int target) {
    
    // successfully placed all elements
    if(idx == nums.size()) {
        for(auto b : buckets) {
            if(b != target)
                return false;
        }            
        return true;
    }
        

    int num = nums[idx];

    for(int b=0; b<buckets.size(); b++) {

        if(buckets[b] + num > target)
            continue;

        // choose
        buckets[b] += num;

        if(dfs(idx + 1, buckets, nums, target))
            return true;

        // unchoose
        buckets[b] -= num;
    }

    return false;
}

bool canPartitionKSubsets(vector<int>& nums, int k) {

    int total = accumulate(nums.begin(), nums.end(), 0);

    if(total % k != 0)
        return false;

    vector<int> buckets(k, 0);
    return dfs(0, buckets, nums, total/k);
}

int main() {

    vector<int> nums = {4,3,2,3,5,2,1};
    int k = 4;
    auto x = canPartitionKSubsets(nums, k);

    nums = {1,2,3,4};
    k = 3;
    x = canPartitionKSubsets(nums, k);
    return 0;
}

// ======================================================

bool dfs(int idx,
         vector<int>& buckets,
         const vector<int>& nums,
         int target) {

    // All numbers assigned successfully
    if (idx == nums.size())
        return true;

    int num = nums[idx];

    for (int b = 0; b < buckets.size(); b++) {

        // Don't exceed target
        if (buckets[b] + num > target)
            continue;

        // Symmetry pruning:
        // all empty buckets are equivalent
        if (b > 0 && buckets[b] == 0 && buckets[b - 1] == 0)
            continue;

        // choose
        buckets[b] += num;

        if (dfs(idx + 1, buckets, nums, target))
            return true;

        // unchoose
        buckets[b] -= num;

        // If putting num into an empty bucket didn't work,
        // putting it into any other empty bucket won't work either.
        if (buckets[b] == 0)
            break;
    }

    return false;
}

bool canPartitionKSubsets(vector<int>& nums, int k) {

    int total = accumulate(nums.begin(), nums.end(), 0);

    if (total % k != 0)
        return false;

    int target = total / k;

    // Larger numbers first → fail earlier
    // reverse sort
    sort(nums.rbegin(), nums.rend());

    if (nums[0] > target)
        return false;

    vector<int> buckets(k, 0);

    return dfs(0, buckets, nums, target);
}

/*
...
...
code
...
if (buckets[b] == 0)
    break;

        try empty bucket
            ↓
        fails
            ↓
        all OTHER empty buckets are identical → stop

        but...

        non-empty bucket?
            ↓
        different state → KEEP TRYING

pruning after rec call
*/

/*
if (b > 0 && buckets[b] == 0 && buckets[b - 1] == 0)
    continue;

...
...
code
...

pruning before rec call

we are at bucket 2nd or more
    the previous bucket is zero
    and curr bucket is zero
        that means that the previous bucket state will be repeated here
            dont proceed
*/