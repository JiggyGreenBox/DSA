/*
Squares of a Sorted Array
    [https://leetcode.com/problems/squares-of-a-sorted-array/description/]

Given an integer array nums sorted in non-decreasing order, return an 
array of the squares of each number sorted in non-decreasing order.

 

Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].
Example 2:

Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
 

Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums is sorted in non-decreasing order.
*/


#include <vector>
#include <algorithm>
using namespace std;

// Time:  O(n)        // two-pointer scan + reverse
// Space: O(n)        // output
vector<int> sortedSquares(vector<int>& nums) {
    
    int n = nums.size();

    vector<int> ans(n);

    // the largest square is on either ends
    int i = 0;
    int j = n - 1;
    int k = n - 1;

    while(i <= j) {
        int n1 = nums[i] * nums[i];
        int n2 = nums[j] * nums[j];
        

        // push larger first
        // then reverse
        if(n1 > n2) {
            ans[k] = n1;
            i++;
        }
        else {
            ans[k] = n1;
            j--; 
        }
        k--;
    }    
    return ans;
}

int main() {
    vector<int> v = {-7, -3, -1, 4, 8};
    auto ans = sortedSquares(v);
    int x = 5;

    return 0;
}