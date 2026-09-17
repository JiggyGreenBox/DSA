/*
Sliding Window Maximum
    [https://leetcode.com/problems/sliding-window-maximum/description/]

You are given an array of integers nums, there is a sliding window of 
size k which is moving from the very left of the array to the very 
right. You can only see the k numbers in the window. Each time the 
sliding window moves right by one position.

Return the max sliding window.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]
*/


#include <vector>
#include <iostream>
#include <deque>
using namespace std;

vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    deque<int> dq;  // indices, values decreasing
    vector<int> result;

    for (int right = 0; right < nums.size(); right++) {

        // Remove expired indices
        // from front
        while (!dq.empty() && dq.front() <= right - k)
            dq.pop_front();

        // Remove useless smaller elements
        // from back
        while (!dq.empty() && nums[dq.back()] <= nums[right])
            dq.pop_back();

        dq.push_back(right);

        // Window is ready
        // answer is in the front
        if (right >= k - 1)
            result.push_back(nums[dq.front()]);
    }

    return result;
}

int main() {

    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;

    auto x = maxSlidingWindow(nums, k); // [3,3,5,5,6,7]

    int y = 5;

    return 0;
}