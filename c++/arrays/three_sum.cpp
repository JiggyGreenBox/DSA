#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end()); // nlogn

    for(auto x: nums) cout << x << " ";
    cout << endl;

    int n = nums.size();
    if(n<3) return {{}};
    int i=0;
    int j=1;
    int k = n-1;

    vector<vector<int>> ans;

    // stop with 2 spots left for j and k
    for(int i=0; i<n-2; i++){
        
        // skip first and curr == prev
        if(i>0 && nums[i] == nums[i-1]) continue;

        j=i+1;
        k = n-1;

        // loop for each j,k combination
        while(j<k) {

            int sum = nums[i] + nums[j] + nums[k];

            if (sum == 0) {
                ans.push_back({nums[i] , nums[j] , nums[k]});      
                // skip same j and k values
                while(j<k && nums[j]==nums[j+1]) ++j;
                while(j<k && nums[k]==nums[k-1]) --k;
                --k;
                ++j;
            } else if (sum > 0) {
                --k;
            } else {
                ++j;
            } 
        }        
    }

    return ans;        
}

int main() {

    // vector<int> v = {2, -2, 0, 3, -3, 5};
    vector<int> v = {2, -1,  -1, 3, -1};    

    vector<vector<int>> ans = threeSum(v);

    for(auto vec: ans){
        cout << "[";
        for(auto x: vec){
            cout << x << " ";
        }
        cout << "]" << endl;
    }
    return 0;
}