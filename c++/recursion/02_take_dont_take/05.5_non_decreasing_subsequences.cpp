/*


#LC 491
Non-decreasing Subsequences

Given an integer array nums, return all the different possible 
non-decreasing subsequences of the given array with at least two 
elements. You may return the answer in any order.

 

Example 1:

Input: nums = [4,6,7,7]
Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
Example 2:

Input: nums = [4,4,3,2,1]
Output: [[4,4]]
*/

/*
at least 2 elements
    its not a permutation its a combination

    we can take forward idxs
*/

#include <vector>
using namespace std;

void backtrack( int idx, 
                vector<int> &nums, 
                vector<int> &curr, 
                vector<vector<int>> &res) 
{
    // if(idx == nums.size()) {
        if(curr.size() > 1)
            res.push_back(curr);
    // }

    // pick and skip using a loop
    for(int i=idx; i<nums.size(); i++) {
        
        // number is not increasing
        if(!curr.empty() && nums[i] < curr.back())
            continue;

        // duplicate at this level
        if(i>idx && nums[i] == nums[i-1])
            continue;

        curr.push_back(nums[i]);
        backtrack(i+1, nums, curr, res);
        curr.pop_back();
    }
}

vector<vector<int>> findSubsequences(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> curr;
    backtrack(0, nums, curr, res);
    return res;
}

int main() {
    vector<int> nums = {4,6,7,7};
    auto x = findSubsequences(nums);

    nums = {4,4,3,2,1};
    x = findSubsequences(nums);
    return 0;
}