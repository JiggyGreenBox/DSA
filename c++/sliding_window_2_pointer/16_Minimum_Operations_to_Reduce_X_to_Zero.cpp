/*
Minimum_Operations_to_Reduce_X_to_Zero

You are given an integer array nums and an integer x. In one 
operation, you can either remove the leftmost or the rightmost 
element from the array nums and subtract its value from x. Note that 
this modifies the array for future operations.

Return the minimum number of operations to reduce x to exactly 0 if 
it is possible, otherwise, return -1.

 

Example 1:

Input: nums = [1,1,4,2,3], x = 5
Output: 2
Explanation: The optimal solution is to remove the last two elements 
to reduce x to zero.
Example 2:

Input: nums = [5,6,7,8,9], x = 4
Output: -1
Example 3:

Input: nums = [3,2,20,1,1,3], x = 10
Output: 5
Explanation: The optimal solution is to remove the last three 
elements and the first two elements (5 operations in total) to reduce 
x to zero.


*/

/*
Minimum_Operations_to_Reduce_X_to_Zero
my first thought was can we use 2 pointers from the left and the right
    always subtract the max

but this is not guaranteed to give the solution

what if we found total - subarray == x
        subarray == total - x
    we can use a prefix sum
    numbers are given to be >=1
    so sum is monotonic
        sliding window is possible

    we want the minimum possible subarray removal
        which means we want the max subarray sum == x


nums = [3,2,20,1,1,3], x = 10
    total = 30
        only 20 satifies


nums = [1,1,4,2,3], x = 5
    total = 11
    x = 5
        we want sum = 11-5 = 6
*/

#include <vector>
#include <numeric>
#include <climits>
#include <iostream>
using namespace std;
int minOperations(vector<int>& nums, int x) {

    int n = nums.size();

    int total = accumulate(nums.begin(), nums.end(), 0);

    int target = total - x;

    int left = 0;
    int sum = 0;
    int max_len = -1;
    for(int right = 0; right<n; right++) {
        sum += nums[right];

        while(sum > target) {
            sum -= nums[left];
            left++;
        }

        if(sum == target)
            max_len = max(max_len, right - left +1);
    }
        
    return max_len == -1? -1 : n - max_len;
}

int main() {
    vector<int> nums = {1,1,4,2,3};
    int x = 5;
    cout << minOperations(nums, x) << endl;


    nums = {5,6,7,8,9}; x = 4;
    cout << minOperations(nums, x) << endl;


    nums = {3,2,20,1,1,3}; x = 10;
    cout << minOperations(nums, x) << endl;

    return 0;

}