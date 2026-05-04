#include <bits/stdc++.h>
using namespace std;


// REFERENCE FOR GENERATE SUBSETS
// void backtrack( int idx, 
//                 vector<int>& current,
//                 const vector<int>& nums, 
//                 vector<vector<int>>& results) 
// {
//     // base cases    
//     results.push_back(current);

//     // select element
//     for(int i=idx; i<nums.size(); i++) {
//         current.push_back(nums[i]);
//         backtrack(i+1, current, nums, results);
//         current.pop_back();
//     }
// }


// ONLY ADD SUM AT EACH STEP
void backtrack( int idx, 
                int sum,
                const vector<int>& nums, 
                vector<int>& results) 
{
    // base cases    
    results.push_back(sum);

    // select element
    for(int i=idx; i<nums.size(); i++) {        
        backtrack(i+1, sum + nums[i], nums, results);        
    }
}

// vector<vector<int>> subsetSums(vector<int>& nums) {    // GENERATE SUBSETS
vector<int> subsetSums(const vector<int>& nums) {    
    // GENERATE SUBSETS
    // vector<vector<int>> results;    
    // vector<int> current;    
    // backtrack(0, current, nums, results);

    vector<int> results;        
    backtrack(0, 0, nums, results);
    return results;
}

void printResults(const vector<int>& res) {
    cout << "[ ";
    for(auto x: res){
        cout << x << " ";
    }
    cout << "]\n";
}

void printResults(const vector<vector<int>>& res) {
    for(auto x: res){
        cout << "[ ";
        for(auto y: x){
            cout << y << " ";
        }
        cout << "]\n";
    }
}

int main() {    
    printResults(subsetSums({2,3}));    
    printResults(subsetSums({5,2,1}));
    return 0;
}