#include <bits/stdc++.h>
using namespace std;

void printResults(const vector<vector<int>>& results) {
    for(auto each : results){
        cout << "[ ";
        for(auto x : each) cout << x << " ";
        cout << "]\n";
    }
}

void backtrack( int idx, 
                vector<int>& current, 
                const vector<int>& nums, 
                vector<vector<int>>& results) 
{
    results.push_back(current);

    // prevent duplicates at this level
    for(int i=idx; i<nums.size(); i++) {
        if(i>idx && nums[i] == nums[i-1]) continue;
        current.push_back(nums[i]);
        backtrack(i+1, current, nums, results);
        current.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(const vector<int>& nums) {
    vector<vector<int>> results;
    vector<int> current;
    backtrack(0, current, nums, results);
    return results;
}

int main() {
    printResults(subsetsWithDup({1, 2, 2}));
    printResults(subsetsWithDup({1, 2}));
    return 0;
}