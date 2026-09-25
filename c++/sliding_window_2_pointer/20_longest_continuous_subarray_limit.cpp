/*
Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
    [https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/description/]

Given an array of integers nums and an integer limit, return the size 
of the longest non-empty subarray such that the absolute difference 
between any two elements of this subarray is less than or equal to 
limit.

 

Example 1:

    Input: nums = [8,2,4,7], limit = 4
    Output: 2 
    Explanation: All subarrays are: 
    [8] with maximum absolute diff |8-8| = 0 <= 4.
    [8,2] with maximum absolute diff |8-2| = 6 > 4. 
    [8,2,4] with maximum absolute diff |8-2| = 6 > 4.
    [8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
    [2] with maximum absolute diff |2-2| = 0 <= 4.
    [2,4] with maximum absolute diff |2-4| = 2 <= 4.
    [2,4,7] with maximum absolute diff |2-7| = 5 > 4.
    [4] with maximum absolute diff |4-4| = 0 <= 4.
    [4,7] with maximum absolute diff |4-7| = 3 <= 4.
    [7] with maximum absolute diff |7-7| = 0 <= 4. 
    Therefore, the size of the longest subarray is 2.

Example 2:

    Input: nums = [10,1,2,4,7,2], limit = 5
    Output: 4 
    Explanation: The subarray [2,4,7,2] is the longest since the maximum 
    absolute diff is |2-7| = 5 <= 5.

Example 3:

    Input: nums = [4,2,2,2,4,4,2,2], limit = 0
    Output: 3


*/

/*
Longest Continuous Subarray With Absolute Diff <= Limit

For every window:
    max(window) - min(window) <= limit

Need max and min efficiently:
    maxDeque → decreasing values
    minDeque → increasing values

Expand right.

When window becomes invalid:
    max - min > limit
    → shrink from left until valid again

Once valid:
    max_len = max(max_len, window length)


---
maxDeque:
    remove smaller elements from back
    remove expired indices from front

minDeque:
    remove larger elements from back
    remove expired indices from front

*/
#include <vector>
#include <deque>
using namespace std;

int longestSubarray(const vector<int>& nums, int limit) {
    
    deque<int> maxDeque;
    deque<int> minDeque;

    int left = 0;
    int max_len = 0;

    for (int right = 0; right < nums.size(); right++) {

        // max dq, has a largest at the front
        // if the back is less than incoming
        // pop
        // [100,20,10]  40
        // finally [100,40]
        while (!maxDeque.empty() &&
               nums[maxDeque.back()] <= nums[right])
            maxDeque.pop_back();

        // min is at front
        // if the back is larger than incoming pop
        // [0,10,20,30,40] 5
        // finally [0,5]
        while (!minDeque.empty() &&
               nums[minDeque.back()] >= nums[right])
            minDeque.pop_back();

        maxDeque.push_back(right);
        minDeque.push_back(right);

        while (nums[maxDeque.front()] - nums[minDeque.front()] > limit) {
            if (maxDeque.front() == left)
                maxDeque.pop_front();

            if (minDeque.front() == left)
                minDeque.pop_front();

            left++;
        }

        max_len = max(max_len, right - left + 1);
    }

    return max_len;
}
/*
valid window is
max - min <= limit
now
    10-5 <= 7
later
    100-5 > 7

max is too large
we need a smaller max
        deque has [100,50,40,...]
        eventually we find what we need 
        by shrinking

        this may also change the min as well
        so track that
        [0,5,10,..]


maxDeque.front() = max(window)
minDeque.front() = min(window)

while max - min > limit:
    shrink left
    shrink window
*/