/*
Permutations
    [https://leetcode.com/problems/permutations/description/]

Given an array nums of distinct integers, return all the possible 
permutations. You can return the answer in any order.

 
Example 1:

    Input: nums = [1,2,3]
    Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:

    Input: nums = [0,1]
    Output: [[0,1],[1,0]]

Example 3:

    Input: nums = [1]
    Output: [[1]]
*/

/*
for combinations 
    we kept moving forward

for permuations
    the order matters
    we should be able to use a prev idx
    and not reuse the current or prev used idx

so we need another array for used[]
    then
        used[i] = true
        push_back(i)
        solve
        pop_back
        used[i] = false
*/

/*
COMBINATION
ordering doesn't matter
→ impose increasing index order
→ no used[] needed

PERMUTATION
ordering matters
→ cannot impose increasing index order
→ need used[] to prevent repetition
*/

#include <vector>
using namespace std;

void helper(int idx, vector<int> &nums, vector<bool> &used, vector<int> &curr, vector<vector<int>> &ans) {
    if(curr.size() == nums.size()) {
        ans.push_back(curr);
        return;
    }

    for(int i=0; i<nums.size(); i++) {
        if(used[i])
            continue;

        used[i] = true;
        curr.push_back(nums[i]);

        helper(idx + 1, nums, used, curr, ans);

        curr.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<bool> used(nums.size(), false);
    vector<int> curr;    
    vector<vector<int>> ans;
    helper(0, nums, used, curr, ans);
    return ans;
}

int main() {
    vector<int> nums = {1,2,3};
    auto x = permute(nums);
    return 0;
}
/*
COMBINATIONS
number of answers = C(n,k)
time = O(k * C(n,k))

PERMUTATIONS
number of answers = n!
time = O(n * n!)
*/