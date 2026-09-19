#include <bits/stdc++.h>
using namespace std;


/*
[]
├── [1]
│   ├── [1,2]
│   │   └── [1,2,3]
│   └── [1,3]
├── [2]
│   └── [2,3]
└── [3]
*/
void backtrack(int idx, vector<int>& curr, vector<int>& nums, vector<vector<int>>& ans) {

    ans.push_back(curr);    
    
    for(int i=idx; i<nums.size(); i++) {

        curr.push_back(nums[i]);

        backtrack(i+1, curr, nums, ans);

        curr.pop_back();
    }
}

/*
[]
├── [1]
│   ├── [1,2]
│   │   └── [1,2,3]
│   └── [1,3]
├── [2]
│   └── [2,3]
└── [3]
*/
vector<vector<int>> powerSet(vector<int>& nums) {
    vector<vector<int>> results;
    vector<int> current;
    backtrack(0, current, nums, results);
    return results;
}


void solve(int idx, vector<int> &curr, vector<int> &nums, vector<vector<int>> &res) {
    if(idx == nums.size()) {
        res.push_back(curr);
        return;
    }
        

    // pick
    curr.push_back(nums[idx]);
    solve(idx+1, curr, nums, res);
    curr.pop_back();

    // skip
    solve(idx+1, curr, nums, res);
}


vector<vector<int>> powerSet2(vector<int>& nums) {
    vector<vector<int>> results;
    vector<int> current;
    solve(0, current, nums, results);
    return results;
}





int main() {
    vector<int> v = {1, 2, 3};
    auto results = powerSet(v);    
    return 0;
}

/*
subset is all combinations
including empty and all elements
we can pick or not pick
total subsets = 2^n


*/