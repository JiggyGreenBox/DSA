#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // sort
using namespace std;

// O(n) time, O(n) space
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

/*
Building pairs: O(n)
Sorting:        O(n log n)
Two pointers:   O(n)

Total:          O(n log n)
Space:          O(n)
*/
vector<int> two_sum_no_hashmap(vector<int>& nums, int target) {

    int n = nums.size();

    vector<pair<int, int>> pairs; // num, idx

    for(int i=0; i<n; i++)
        pairs.push_back({nums[i], i});

    std::sort(pairs.begin(), pairs.end());

    // now classic 2 pointer and sum
    int i=0;
    int j = n-1;

    while(i < j) {

        int sum = pairs[i].first + pairs[j].first;

        if(sum == target) {
            return {pairs[i].second, pairs[j].second};
        }
        else if(sum < target) {
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