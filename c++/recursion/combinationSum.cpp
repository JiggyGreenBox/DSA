#include <bits/stdc++.h>
using namespace std;

void backtrack( int idx, 
                int cur_sum,
                vector<int>& current, 
                const vector<int>& candidates, 
                int target, 
                vector<vector<int>>& results) 
{
    // base cases
    if(cur_sum > target) return;
    if(cur_sum == target) {
        results.push_back(current);
        return;
    }
    if(idx >= candidates.size()) return;

    // pick element
    current.push_back(candidates[idx]);
    backtrack(idx, cur_sum + candidates[idx], current, candidates, target, results);
    current.pop_back();

    // ignore element
    backtrack(idx+1, cur_sum, current, candidates, target, results);
}

vector<vector<int>> combinationSum(const vector<int>& candidates, int target) {
    vector<vector<int>> results;
    vector<int> current;
    backtrack(0, 0, current, candidates, target, results);
    return results;
}

void printResults(const vector<vector<int>>& results){
    for(auto x : results) {
        cout << "[ ";
        for(auto y : x) {
            cout << y << " ";
        }
        cout << "]\n";
    }    
}

int main() {
    auto results = combinationSum({2, 3, 5, 4}, 7);
    cout << results.size() << endl;
    printResults(results);
    return 0;
}