/*
Maximum Sum Circular Subarray
    [Maximum_Sum_Circular_Subarray]

Given a circular integer array nums of length n, return the maximum 
possible sum of a non-empty subarray of nums.

A circular array means the end of the array connects to the beginning 
of the array. Formally, the next element of nums[i] is nums[(i + 1) % 
n] and the previous element of nums[i] is nums[(i - 1 + n) % n].

A subarray may only include each element of the fixed buffer nums at 
most once. Formally, for a subarray nums[i], nums[i + 1], ..., 
nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.

 

Example 1:

    Input: nums = [1,-2,3,-2]
    Output: 3
    Explanation: Subarray [3] has maximum sum 3.

Example 2:

    Input: nums = [5,-3,5]
    Output: 10
    Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.

Example 3:

    Input: nums = [-3,-2,-3]
    Output: -2
    Explanation: Subarray [-2] has maximum sum -2.
*/

/*
Maximum Sum Circular Subarray
    prefix approach is not correct

    2 cases
        1 2 [3 4 -1 5] 6
            no wrap

        [5 6] 1 2 3 [4]


    if we are tracking total
        and X is the middle part
    then ans is total - X


    so maybe there are no negatives
        find maxKadane
        find minKadane

    [5,-3, 5]
        normal kadane, 5
        total = 7
        minKadance = -3

    we can choose total and remove -3
    7 - (-3) = 10 = [5,5]
*/

#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int maxSubarraySumCircular(vector<int>& nums) {
    int n = nums.size();
    if(n == 0)
        return 0;

    int total = accumulate(nums.begin(), nums.end(), 0);

    int currMax = nums[0];
    int currMin = nums[0];
    int maxKad = nums[0];
    int minKad = nums[0];

    for(int i=1; i<n; i++) {
        // maxKadane
        currMax = max(nums[i], currMax + nums[i]);
        maxKad = max(currMax, maxKad);

        // minKadane
        currMin = min(nums[i], currMin + nums[i]);        
        minKad = min(currMin, minKad);
    }    

    // all negative edge case
    if (maxKad < 0)
        return maxKad;

    return max(maxKad, total - minKad);
}


int main() {

    vector<int> nums = {1,-2,3,-2};
    cout << maxSubarraySumCircular(nums) << endl;

    nums = {5,-3,5};
    cout << maxSubarraySumCircular(nums) << endl;

    nums = {-3,-2,-3};
    cout << maxSubarraySumCircular(nums) << endl;

    nums = {-5};
    cout << maxSubarraySumCircular(nums) << endl;

    return 0;
}