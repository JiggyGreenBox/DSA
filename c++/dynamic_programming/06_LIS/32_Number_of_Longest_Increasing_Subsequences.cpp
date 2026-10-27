#include <iostream>
#include <vector>
using namespace std;


int numberOfLIS(vector<int> nums) {
    int n = nums.size();
    vector<pair<int,int>> dp(n, {1,1});
    int maxLis = 1;
    int count = 0;

    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            if(nums[j] < nums[i]) {
                // increase the LIS[i] for this j                
                if(dp[i].first < 1 + dp[j].first){
                    dp[i].first = 1 + dp[j].first;
                    dp[i].second = dp[j].second;
                }
                // another LIS[i] for this idx, from another j
                else if(dp[i].first == 1 + dp[j].first) {
                    dp[i].second = dp[i].second + dp[j].second;                    
                    // count = max(count, dp[i].second);
                }
            }            
        }
        // what if other i's have the same LIS
        if(dp[i].first == maxLis) {
            count += dp[i].second;
        }
        else if(dp[i].first > maxLis) {
            maxLis = dp[i].first;
            count = dp[i].second;
        }
    }
    int x = 5;
    return count;
}

int numberOfLIS_cannon(vector<int> nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    vector<int> cnt(n, 1);
    int max_len = 1;

    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            if(nums[j] < nums[i]) { // increasing number found

                // [1,3,2,5]
                // [1,2,5]
                // [1,3,5]

                // dp [1,2,2,3]
                // cnt[1,1,1,2]
                if(dp[i] < 1 + dp[j]) {
                    dp[i] = 1 + dp[j];
                    cnt[i] = cnt[j];
                }
                else if(dp[i] == 1 + dp[j]) {
                    cnt[i] += cnt[j];
                }
            }            
        }
        max_len = max(max_len, dp[i]);
    }
    int ans = 0;
    for(int i=0; i<n; i++) {
        if(dp[i] == max_len) ans += cnt[i];
    }
    return ans;
}


int main() {
    vector<int> v = {1, 3, 5, 4, 7};
    cout << numberOfLIS(v) << endl;
    cout << numberOfLIS_cannon(v) << endl;

    v = {2, 2, 2, 2, 2};
    cout << numberOfLIS(v) << endl;
    cout << numberOfLIS_cannon(v) << endl;
    return 0;
}