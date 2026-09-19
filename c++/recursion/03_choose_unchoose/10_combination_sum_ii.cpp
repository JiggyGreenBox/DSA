/*
Combination Sum II
    [https://leetcode.com/problems/combination-sum-ii/description/]

Given a collection of candidate numbers (candidates) and a target 
number (target), find all unique combinations in candidates where the 
candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.

 

Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
Example 2:

Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]
*/

/*
similar to permutations with duplicates
    we dont want duplicates at the same recursion level
        we want a assurance it was used before
            for permutations we need !used[i-1]

        for combinations we use a loop to handle duplicates
        with start,
            if i> start && nums[i] == nums[i-1]
                was used, continue
*/

#include <vector>
#include <algorithm>
using namespace std;

void helper(int start, int target, vector<int> &candidates, vector<int> &curr, vector<vector<int>> &ans) {
    if(target == 0) {
        ans.push_back(curr);
        return;
    }

    for(int i=start; i<candidates.size(); i++) {


        // if used at this level, skip
        if(i > start && candidates[i] == candidates[i-1])
            continue;


        if(candidates[i] > target)
            continue;

        curr.push_back(candidates[i]);
        helper(i+1, target - candidates[i], candidates, curr, ans);
        curr.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    vector<int> curr;
    sort(candidates.begin(), candidates.end());
    helper(0, target, candidates, curr, ans);
    return ans;
}

int main() {
    vector<int> candidates = {10,1,2,7,6,1,5};
    int target = 8;
    auto x = combinationSum2(candidates, target);
    return 0;
}