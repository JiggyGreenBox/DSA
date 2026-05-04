#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // sort
using namespace std;

vector<int> two_sum(vector<int>& nums, int target) {
    vector<int> ans;
    unordered_map<int, int> mpp; // value, index


    int n = nums.size();

    for(int i=0; i<n; i++) {
        int search = target - nums[i];
        if(mpp.count(search) > 0) {
            // return {mpp[search], i};
            ans.push_back(mpp[search]);
            ans.push_back(i);
            return ans;
        }
        else{
            mpp[nums[i]] = i;
        }
    }

    for(auto pair : mpp){
        cout << pair.first << " " << pair.second << endl;
    }
    // cout << mpp[]

    return ans;
}

vector<int> two_sum_no_hashmap(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> num_w_idx; // num, idx
    for(int i=0; i<n; i++){
        num_w_idx.push_back({nums[i], i});
    }

    // for(auto pair : num_w_idx){
    //     cout << pair[0] << " : " <<pair[1] << endl;
    // }

    std::sort(num_w_idx.begin(), num_w_idx.end(), [](const vector<int>& a, const vector<int>& b){
        return a[0] < b[0];
    });

    // cout << endl;
    // for(auto pair : num_w_idx){
    //     cout << pair[0] << " : " <<pair[1] << endl;
    // }

    // now classic 2 pointer and sum
    int i=0;
    int j = n-1;

    while(i<j){
        int sum = num_w_idx[i][0] + num_w_idx[j][0];
        if(sum == target){
            return {num_w_idx[i][1], num_w_idx[j][1]};
        }
        else if(sum < target){
            i++;
        }
        else{
            j--;
        }
    }

    return {-1,-1};
}

void print(vector<int>& nums){
    for(auto x : nums) cout << x << " ";
    cout << endl;
    cout << endl;
}

int main(){

    vector<int> v = {1, 6, 2, 10, 3};
    int target = 7;

    // vector<int> ans = two_sum(v, target);
    // print(ans);

    vector<int> ans = two_sum_no_hashmap(v, target);
    print(ans);

    

    return 0;
}