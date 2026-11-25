/*
============================================
nov 25
    last nov 24
============================================
Problem 1
============================================

Search in Rotated Sorted Array — LC 33

nums = [4,5,6,7,0,1,2]
target = 0

Output: 4

derivation
    brute force is linear search
        O(n) time

    a better approach is to take advantage of the sorted nature of the array

    find the sorted half and check if target is in that range
    we can discard half and get a logn time

code
    int find(vector<int> &nums, int target) {
        int n = nums.size();
        int l = 0;
        int r = n-1;

        while(l<=r) {
            int m = l + (r-l)/2;

            if(nums[m] == target)
                return m;

            // left is sorted
            if(nums[l] <= nums[m]) {
                if(nums[l] <= target && target < nums[m]) {
                    r = m-1;
                }
                else {
                    l = m+1;
                }
            }
            // right is sorted
            else {
                if(nums[m] < target && target <= nums[r]) {
                    l = m+1;                
                }
                else {
                    r = m-1;
                }
            }        
        }
        return -1;
    }

============================================
Problem 2
============================================
Problem 2 — Maximum Subarray (LC 53)

find the contiguous subarray with the largest sum and return that sum.

nums = [-2,1,-3,4,-1,2,1,-5,4]

Output: 6

Subarray: [4,-1,2,1]


approach
    we start with the brute force approach
    we generate each subarray n^2
        and check the largest sum

    we can have a dp approach
        at each idx
            return the max sum acheivable at that idx


    f(idx)
        extend the previous sum
        start a new sum

        return max(extend, new)

    f(idx)
        extend the previous sum

        extend = nums[i] + dp[i-1]

        start a new sum
        new = nums[i]

        return max(extend, new)


    we can store this in the dp array
    we see that we only depend on the previous value  dp[i-1]
        we can space optimize this into 1 variable

    this is kadanes algorithm to compress the dp state

    O(n) time
    O(1) space

code

    int maxsum(vector<int> &nums) {

        int n = nums.size();
        if(n == 0)
            return 0;

        int curr = nums[0];
        int best = nums[0];

        for(int i=1; i<n; i++) {
            curr = max(nums[i], curr+nums[i]);
            best = max(best, curr);
        }
        return best;
    }

    // return 
    // start-idx, end-idx,sum
    tuple<int,int,int> maxsum2(vector<int> &nums) {

        int n = nums.size();
        if(n == 0)
            return {-1,-1,0};

        int curr = nums[0];
        int best = nums[0];
        int prev_start = 0;
        int best_start = 0;
        int best_end = 0;

        for(int i=1; i<n; i++) {

            // curr = max(nums[i], curr+nums[i]);
            if(curr + nums[i] < nums[i]) {
                curr = nums[i];
                prev_start = i;
            }
            else{
                curr += nums[i];
            }

            // best = max(best, curr);
            if(curr > best) {
                best_start = prev_start;
                best_end = i;
                best = curr;
            }
            
            
        }
        return {best_start, best_end, best};
    }

============================================
Problem 3
============================================
Problem 3 — Find the Duplicate Number (LC 287)

You are given an array of n + 1 integers where every integer is in 
the range [1, n].

There is exactly one repeated number, but it may appear more than 
twice.

Return the repeated number.

nums = [1, 3, 4, 2, 2]

Output: 2

approach
    brute force
        n time, n space
        use a hashmap num, count
            return for count > 1

        nlogn time, 1 space
        sort and use 2 pointer
            if i==i+1

        n^2 loop 
            to check if number exists

    observation
        we are given numbers in the range 1..n
        we can use the xor property of num^num = 0

    if we were to xor all numbers in the array with this expected range 
    only the duplicate number would remain
    as others would get cancelled out

    

*/
#include <vector>
#include <assert.h>
using namespace std;

int findDup(vector<int> &nums) {

    int n = nums.size();
    int xorr = 0;
    for(int i=0; i<n; i++) {
        xorr = xorr ^ nums[i];        
    }

    for(int i=1; i<n; i++) {
        xorr = xorr^i;
    }
    return xorr;
}

int findDup2(vector<int> &nums) {

    int n = nums.size();
    int xorr = nums[0];    

    for(int i=1; i<n; i++) {
        xorr = xorr ^ nums[i];
        xorr = xorr^i;
    }
    return xorr;
}


int main() {
    vector<int> nums = {1, 3, 4, 2, 2};
    
    auto x = findDup2(nums);
    // assert(maxsum(nums) == 6);
    return 0;
}