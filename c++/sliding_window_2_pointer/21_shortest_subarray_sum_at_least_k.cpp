/*
Shortest Subarray with Sum at Least K
    [https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/description/]

Given an integer array nums and an integer k, return the length of 
the shortest non-empty subarray of nums with a sum of at least k. If 
there is no such subarray, return -1.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [1], k = 1
Output: 1
Example 2:

Input: nums = [1,2], k = 4
Output: -1
Example 3:

Input: nums = [2,-1,2], k = 3
Output: 3

*/

/*
brute
    for all subarrays
        get sum
            if sum >= k
                store len
                update min_len

    negative numbers are allowed

-------------------
POSITIVE NUMBERS

Minimum sum >= K:
    expand → sum increases
    shrink → sum decreases
    → sliding window


NEGATIVE NUMBERS ALLOWED

Minimum sum >= K:
    adding can decrease sum
    removing can increase sum
    → normal sliding window breaks
    → prefix sum + monotonic deque
-------------------

prefix sum
    for sum(l,r) we want >=k

    prefix[r] - prefix[l-1] >=k

    prefix[l-1] - prefix[r] <= k
    prefix[l-1] <= prefix[r] - k
*/

/*
Shortest Subarray Sum >= K

Negative numbers → normal sliding window fails.

Use prefix sum:

sum(i..j-1) = prefix[j] - prefix[i]

Need:
    prefix[j] - prefix[i] >= K

For each j:
    find largest i such that
        prefix[i] <= prefix[j] - K

Need largest i → shortest length.

Monotonic deque of prefix indices:
    prefix values increasing

POP FRONT:
    prefix[j] - prefix[dq.front()] >= K
    → valid
    → update shortest
    → pop because this i won't give a shorter answer later

POP BACK:
    prefix[dq.back()] >= prefix[j]
    → new prefix is later AND smaller
    → old prefix is dominated
    → pop
*/

#include <vector>
#include <deque>
using namespace std;

int shortestSubarray(const vector<int>& nums, int k) {
    int n = nums.size();

    vector<long long> prefix(n + 1, 0);

    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + nums[i];

    deque<int> dq;
    int ans = n + 1;

    for (int j = 0; j <= n; j++) {

        // Remove dominated prefixes
        while (!dq.empty() &&
               prefix[dq.back()] >= prefix[j])
            dq.pop_back();

        // Find shortest valid subarray
        while (!dq.empty() &&
               prefix[j] - prefix[dq.front()] >= k) {

            ans = min(ans, j - dq.front());
            dq.pop_front();
        }

        dq.push_back(j);
    }

    return ans == n + 1 ? -1 : ans;
}


#include <climits>
// positive numbers allowed
int minSubArrayLen(int target, const vector<int>& nums) {
    int left = 0;
    int sum = 0;
    int min_len = INT_MAX;

    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];

        while (sum >= target) {
            min_len = min(min_len, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }

    return min_len == INT_MAX ? 0 : min_len;
}