#include <bits/stdc++.h>
using namespace std;

int backtrack(  int idx, 
                int current_sum,
                const vector<int>& nums,
                int k
            )
{
    // base cases
    if(current_sum == k) return 1;
    if(idx >= nums.size()) return 0;

    int count = 0;

    // add to sum
    count += backtrack(idx+1, current_sum + nums[idx], nums, k);

    // ignore from sum
    count += backtrack(idx+1, current_sum, nums, k);

    return count;    
}

int countSubsequenceWithTargetSum(const vector<int>& nums, int k){
    return backtrack(0, 0, nums, k);
}

int main() {
    cout << countSubsequenceWithTargetSum({4, 9, 2, 5, 1}, 10) << endl;
    cout << countSubsequenceWithTargetSum({4, 2, 10, 5, 1, 3}, 5) << endl;
    return 0;
}