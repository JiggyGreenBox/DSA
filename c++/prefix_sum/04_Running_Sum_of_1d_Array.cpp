/*
Running Sum of 1d Array
[https://leetcode.com/problems/running-sum-of-1d-array/description/]


Given an array nums. We define a running sum of an array as 
runningSum[i] = sum(nums[0]…nums[i]).

Return the running sum of nums.

 

Example 1:

    Input: nums = [1,2,3,4]
    Output: [1,3,6,10]
    Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 
    1+2+3+4].

Example 2:

    Input: nums = [1,1,1,1,1]
    Output: [1,2,3,4,5]
    Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 
    1+1+1+1, 1+1+1+1+1].
    
Example 3:

    Input: nums = [3,1,2,10,1]
    Output: [3,4,6,16,17]
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> runningSum(vector<int>& nums) {
    vector<int> pre(nums.size() + 1);

    for(int i=0; i<nums.size(); i++) {
        pre[i+1] = pre[i] + nums[i];
    }
    pre.erase(pre.begin());
    return pre;
}

vector<int> runningSum2(vector<int>& nums) {
    vector<int> pre(nums.size());

    int leftsum = 0;
    for(int i=0; i<nums.size(); i++) {        
        leftsum += nums[i];
        pre[i] = leftsum;
    }    
    return pre;
}

void print(const vector<int> &v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

int main() {

    vector<int> nums = {1,2,3,4};
    print(runningSum(nums));
    print(runningSum2(nums));

    return 0;
}