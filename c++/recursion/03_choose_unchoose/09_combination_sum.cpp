#include <bits/stdc++.h>
using namespace std;


void helper(int idx, const vector<int> &nums, int target, vector<int> &curr, vector<vector<int>> &ans) {

    if(target == 0) {
        ans.push_back(curr);
        return;
    }

    if(target < 0)
        return;

    if(idx >= nums.size())
        return;

    // pick
    curr.push_back(nums[idx]);
    helper(idx, nums, target-nums[idx], curr, ans);
    curr.pop_back();

    // skip
    helper(idx+1, nums, target, curr, ans);
}

vector<vector<int>> combinationSum2(const vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    vector<int> curr;
    helper(0, candidates, target, curr, ans);
    return ans;
}


void loop(int idx, const vector<int> &nums, int target, vector<int> &curr, vector<vector<int>> &ans) {
    if(target == 0) {
        ans.push_back(curr);
        return;
    }

    for(int i=idx; i<nums.size(); i++) {

        if(nums[i] > target)
            continue;

        curr.push_back(nums[i]);
        loop(i, nums, target - nums[i], curr, ans);
        curr.pop_back();
    }
}

vector<vector<int>> combinationSum(const vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    vector<int> curr;
    loop(0, candidates, target, curr, ans);
    return ans;
}

int main() {
    auto results = combinationSum({2,3,6,7}, 7);    
    return 0;
}