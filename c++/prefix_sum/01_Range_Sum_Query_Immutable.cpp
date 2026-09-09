/*
Range Sum Query - Immutable
    [https://leetcode.com/problems/range-sum-query-immutable/description/]

Given an integer array nums, handle multiple queries of the following 
type:

Calculate the sum of the elements of nums between indices left and 
right inclusive where left <= right.
Implement the NumArray class:

NumArray(int[] nums) Initializes the object with the integer array 
nums.
int sumRange(int left, int right) Returns the sum of the elements of 
nums between indices left and right inclusive (i.e. nums[left] + 
nums[left + 1] + ... + nums[right]).
 

Example 1:

Input
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
Output
[null, 1, -1, -3]

Explanation
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3


*/
#include <iostream>
#include <vector>

using namespace std;

class NumArray {
private:
    vector<int> prefix_sum;
public:
    NumArray(vector<int>& nums) {
        prefix_sum = nums;
        prefix_sum[0] = nums[0];
        for(int i=1; i<nums.size(); i++) {
            prefix_sum[i] = prefix_sum[i-1] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        if(left == 0)
            return prefix_sum[right];
        return prefix_sum[right] - prefix_sum[left-1];
    }
};

class NumArray_canon {
private:
    vector<int> prefix_sum;
public:
    NumArray_canon(vector<int>& nums) {
        prefix_sum.resize(nums.size() + 1);        
        for(int i=0; i<nums.size(); i++) {
            prefix_sum[i+1] = prefix_sum[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {        
        return prefix_sum[right+1] - prefix_sum[left];
    }
};

int main() {
    vector<int> v = {-2, 0, 3, -5, 2, -1};
    NumArray_canon numArray = NumArray_canon(v);
    cout << numArray.sumRange(0, 2) << endl; // return (-2) + 0 + 3 = 1
    cout << numArray.sumRange(2, 5) << endl; // return 3 + (-5) + 2 + (-1) = -1
    cout << numArray.sumRange(0, 5) << endl; // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3
}

/*

prefix array:
    prefix[i] = nums[0] + nums[1] + ... + nums[i]

To find the sum [left, right]:
    prefix[right] - prefix[left - 1]

    prefix[right]
        = nums[0] + ... + nums[left-1] + nums[left] + ... + nums[right]

    prefix[left-1]
        = nums[0] + ... + nums[left-1]

so the formula becomes if left == 0
    return prefix[right]
    else return prefix[right] - prefix[left-1]

instead we move everything +1
    prefix.resize(n+1)

    for each i
        prefix[i+1] = prefix[i] + nums[i]
    
query(left, right)
    return prefix[right+1] - prefix[left]
*/