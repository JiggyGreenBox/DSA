/*
Binary Subarrays With Sum


Prefix sum + hashmap:
    works generally, including negative numbers

For non-negative numbers:
    sliding window can compute atMost(goal)

Why?
    adding nums[r] never decreases sum
    removing nums[l] never increases sum


So:
    atMost(goal) = number of subarrays with sum <= goal

For binary arrays:
    exactly(goal)
        = atMost(goal) - atMost(goal - 1)


Why subtraction?
    atMost(goal)
    includes sums 0,1,...,goal

    atMost(goal - 1)
    includes sums 0,1,...,goal-1

    difference
    = exactly goal
*/

/*
at most logic
    we want subarrays <= sum

    left=0
    for right .. end
        sum += nums[right]

        while(sum > goal)
            sum -= nums[left]
            left++

        total = every subarray between left and right
            [0,1,2,3]
            while i<=r
                n++

            3-0+1
            r-i+1

        total += right - left + 1
*/

#include <iostream>
#include <vector>
using namespace std;

int atMost(const vector<int> &nums, int goal) {
    int left = 0;
    int sum = 0;
    int total = 0;
    for(int right = 0; right < nums.size(); right++) {
        sum += nums[right];

        while(sum > goal) {
            sum -= nums[left];
            left++;
        }
        total += right - left + 1;
    }
    return total;
}

int numSubarraysWithSum(vector<int>& nums, int goal) {
    return atMost(nums, goal) - atMost(nums, goal - 1);
}