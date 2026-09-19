#include <bits/stdc++.h>
using namespace std;


bool solve(int i, int target, const vector<int>& nums) {
    if (target == 0)
        return true;

    if (i == nums.size())
        return false;

    // Pick
    if (solve(i + 1, target - nums[i], nums))
        return true;

    // Don't pick
    if (solve(i + 1, target, nums))
        return true;

    return false;
}

bool subsetSum(const vector<int>& nums, int target) {
    return solve(0, target, nums);
}

int main() {    
    auto x = subsetSum({2,3}, 5);    
    x = subsetSum({5,2,1}, 6);
    return 0;
}