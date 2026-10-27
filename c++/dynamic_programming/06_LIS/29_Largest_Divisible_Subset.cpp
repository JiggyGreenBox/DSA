#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Largest Divisible Subset

    Given an array nums of positive integers, the task is to find the 
    largest subset such that every pair (a, b) of elements in the subset 
    satisfies a % b == 0 or b % a == 0.

    Return the subset in any order. If there are multiple solutions, 
    return any one of them.    
*/

/*
similar to print LIS
    n^2 find dp[i], where dp[i] represents length of subset where each 
    element % element = 0



*/
vector<int> largestDivisibleSubset(vector<int> nums) {

    sort(nums.begin(), nums.end());

    int n = nums.size();
    vector<int> dp(n, 1); // a % a = 0
    vector<int> parent(n);

    int last_idx = 0;
    for(int i=0; i<n; i++) {
        parent[i] = i;
        for(int j=0; j<i; j++) {
            if((nums[j] % nums[i] == 0 || nums[i] % nums[j] == 0) && dp[i] < 1 + dp[j]) {
                dp[i] = 1 + dp[j];
                parent[i] = j;
            }            
        }
        if(dp[i] > dp[last_idx]) {
            last_idx = i;
        }
    }

    vector<int> ans;
    while(parent[last_idx] != last_idx) {
        ans.push_back(nums[last_idx]);
        last_idx = parent[last_idx];
    }
    ans.push_back(nums[last_idx]);
    reverse(ans.begin(), ans.end());
    return ans;
}

void print(const vector<int> &v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]" << endl;
}

int main() {
    vector<int> v = {3, 5, 10, 20};

    print(largestDivisibleSubset(v));

    v = {16, 8, 2, 4, 32};

    print(largestDivisibleSubset(v));

    v = {10, 240, 8, 4};
    print(largestDivisibleSubset(v));

    return 0;
}

// [ 5 10 20 ]
// [ 16 8 2 4 32 ]
// [ 10 240 8 4 ]