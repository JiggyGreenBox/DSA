#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // nlogn sorting
    // o(n^3) for i, j, (k/l)
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
      // 2 loops then 2 sum
      int n = nums.size();
      vector<vector<int>> ans;
      sort(nums.begin(),nums.end());

      int k=0;
      int l=0;

      for(int i=0; i<n-3; i++){

        // process first skip dups after
        if(i>0 && nums[i] == nums[i-1]) 
            continue; 

        for(int j=i+1; j<n-2; j++){

            // process first skip dups after
            if(j>i+1 && nums[j] == nums[j-1]) 
                continue; 

            k = j+1;
            l = n-1;

            while(k < l) {

                long long sum = (long long) nums[i] + nums[j] + nums[k] + nums[l];                

                if(sum == target){
                    // ans.push_back({i,j,k,l});
                    ans.push_back({nums[i],nums[j],nums[k],nums[l]});

                    // skip duplicate k and l
                    while(k<l && nums[k] == nums[k+1]) 
                        k++;

                    while(k<l && nums[l] == nums[l-1]) 
                        l--;

                    k++;
                    l--;
                }
                else if(sum < target){
                    k++;
                }
                else{
                    l--;
                }
            }

        }
      }
      return ans;
    }
};

void print(const vector<int>& v){
    for(auto x : v) {
        cout << x << " ";
    }
    cout << endl;
    cout << endl;
}

void print(const vector<vector<int>>& v){
    for(const auto& row : v) {
        for(auto x : row) {
            cout << x << " ";
        }   
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

int main(){
    Solution sol;

    vector<int> v = {1, -2, 3, 5, 7, 9};
    int target = 7;

    v = {0,5,0,0,0};
    target = 5;

    vector<vector<int>> ans = sol.fourSum(v, target);
    print(ans);
}