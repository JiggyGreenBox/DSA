/*
First Missing Positive

Given an unsorted integer array nums. Return the smallest positive 
integer that is not present in nums.

You must implement an algorithm that runs in O(n) time and uses O(1) 
auxiliary space.

 

Example 1:

Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,2] are all in the array.
Example 2:

Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.
Example 3:

Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.


*/

/*
For every number x, try to put x at index x-1.

nums = [3, 4, -1, 1]
useful numbers are only 1,2,3,4
they should be at 0,1,2,3

anything not in this range is missing
    for every idx
        if not nums[idx] != idx+1
            return idx+1

put numbers in correct position
    for each num
        if >=1 and <=n  [1,n]

        and already in correct position
        nums[nums[i] - 1] != nums[i]

        [1,2,3]
            1 is at 0
                nums[1] is at 1-1 = 0
                    correct

            2 is at 1
                nums[2] is at 2-1 = 1 position

        then swap
            swap(nums[i], nums[nums[i] - 1]);

    we use a while because after a swap
        we now check the swapped number

*/

#include <vector>
#include <iostream>
using namespace std;

int firstMissingPositive(vector<int>& nums) {

    int n = nums.size();

    for(int i=0; i<n; i++) {

        while(nums[i] >= 1 && nums[i] <= n && 
                nums[nums[i] - 1] != nums[i]) 
        {
            swap(nums[i], nums[nums[i] - 1]);
        }

    }

    for(int i=0; i<n; i++) {
        if(nums[i] != i+1)
            return i+1;
    }
    
    return n + 1;
}


int main() {
    vector<int> nums = {1,2,0};
    cout << firstMissingPositive(nums) << endl;

    nums = {3,4,-1,1};
    cout << firstMissingPositive(nums) << endl;

    nums = {7,8,9,11,12};
    cout << firstMissingPositive(nums) << endl;
    return 0;
}