#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Print Longest Increasing Subsequence

    Given an array of n integers arr, return the Longest Increasing 
    Subsequence (LIS) that is Index-wise Lexicographically Smallest.

    The Longest Increasing Subsequence (LIS) is the longest subsequence 
    where all elements are in strictly increasing order.

    A subsequence A1 is Index-wise Lexicographically Smaller than another 
    subsequence A2 if, at the first position where A1 and A2 differ, the 
    element in A1 appears earlier in the array arr than corresponding 
    element in S2.

*/

/*
for LIS, i need 2 things, the len, and also the elements

    how to do this in recursion while keeping the dp style?
*/

// used for print LIS in the next question
int LIS_6(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);

    int ans = 1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            if(nums[i] > nums[j]){
                dp[i] = max(dp[i], 1 + dp[j]);
                ans = max(ans, dp[i]);
            }            
        }
    }
    return ans;
}

vector<int> longestIncreasingSubsequence(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);
    vector<int> parent(n);
    
    int last_idx = 0;
    for(int i=0; i<n; i++) {

        parent[i] = i;

        for(int j=0; j<i; j++) {
            if(arr[i] > arr[j] && 1 + dp[j] > dp[i]){

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
        ans.push_back(arr[last_idx]);
        last_idx = parent[last_idx];
    }
    ans.push_back(arr[last_idx]);
    reverse(ans.begin(), ans.end());
    return ans;
}

void print(const vector<int> &v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]" << endl;
}

int main() {

    vector<int> v ={10, 22, 9, 33, 21, 50, 41, 60, 80};
    print(longestIncreasingSubsequence(v));

    return 0;
}