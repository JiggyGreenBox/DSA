#include <iostream>
#include <vector>
using namespace std;


void addResults(int idx,
                int n,
                const vector<int>& nums, 
                vector<vector<int>>& results) 
{
    vector<int> temp;
    // check bits set
    for(int i=0; i<n; i++) {
        if((1<<i) & idx) {
            temp.push_back(nums[i]);
        }
    }
    results.push_back(temp);
}


vector<vector<int>> powerSet(const vector<int>& nums) {
    vector<vector<int>> results;
    int n = nums.size();
    
    // int limit = 1<<(n-1);
    // limit |= limit-1;
    // int limit = (1<<n) - 1;
    int limit = (1<<n);

    for(int i=0; i<limit; i++){
        // cout << i << endl;
        addResults(i, n, nums, results);
    }
    return results;
}

void printResults(const vector<vector<int>>& res) {
    for(const auto& row : res){
        cout << "[ ";
        for(auto x : row) cout << x << " ";
        cout << "]\n";
    }
    cout << "\n";
}

int main() {
    printResults(powerSet({1, 2, 3}));    
    return 0;
}