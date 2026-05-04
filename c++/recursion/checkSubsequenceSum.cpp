#include <bits/stdc++.h>
using namespace std;

void print(bool b){
    if(b){
        cout << "true" << endl;
        return;
    }
    cout << "false" << endl;
}

void backtrack( int start_idx, 
                vector<int>& cur_sub,
                const vector<int>& nums, 
                int k, 
                bool& isSum)
{
    int sum = std::accumulate(cur_sub.begin(), cur_sub.end(), 0);
    if(sum == k) {
        isSum = true;
        return;
    }

    for(int i=start_idx; i<nums.size(); i++) {
        cur_sub.push_back(nums[i]);
        backtrack(i+1, cur_sub, nums, k, isSum);
        cur_sub.pop_back();
    }
}

bool checkSubsequenceSum(const vector<int>& nums, int k) {    
    vector<int> cur_sub;
    bool isSum = false;
    backtrack(0, cur_sub, nums, k, isSum);
    return isSum;
}

bool backtrack2(int idx, int cur_sum, const vector<int>& nums, int k) {
    if(cur_sum == k) return true;    

    if(cur_sum > k || idx >= nums.size()) return false; // assuming no negatives

    // 2. try adding the element
    if(backtrack2(idx+1, cur_sum + nums[idx], nums, k)){
        return true;
    }
    // 3. try skipping the element
    if(backtrack2(idx+1, cur_sum, nums, k)){
        return true;
    }

    return false;
}

bool checkSubsequenceSum2(const vector<int>& nums, int k) {            
    return backtrack2(0, 0, nums, k);
}

int main() {    
    print(checkSubsequenceSum2({1, 2, 3, 4, 5}, 8));
    print(checkSubsequenceSum2({4, 3, 9, 2}, 10));
    return 0;
}