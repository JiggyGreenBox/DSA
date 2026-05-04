#include <bits/stdc++.h>
using namespace std;

void printResults(const vector<vector<int>> & results) {
    for(auto set : results){
        cout << "[ ";
        for(auto x : set){
            cout << x << " ";
        }
        cout << "]\n";
    }
}

void printvec(const vector<int> & results) {
    for(auto x: results) cout << x << " ";
    cout << "\n";    
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
void backtrack(int start_idx, vector<int>& current, vector<int>& nums, vector<vector<int>>& results) {

    cout << "start_idx: " << start_idx << endl;
    cout << "current: " << endl;
    printvec(current);

    // 1. GOAL / Base case
    // if(start_idx > nums.size()) return; // check not needed

    results.push_back(current);

    cout << "results: " << endl;
    printResults(results);

    // if(current.size() == nums.size()){
    //     results.push_back(current);
    //     return;
    // }

    // 2. explore options
    for(int i=start_idx; i<nums.size(); i++) {
        current.push_back(nums[i]);
        cout << "push_back: " << nums[i]<< endl;
        backtrack(i+1, current, nums, results);
        current.pop_back();
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





int main() {
    vector<int> v = {1, 2, 3};
    auto results = powerSet(v);
    // printResults(results);
    return 0;
}