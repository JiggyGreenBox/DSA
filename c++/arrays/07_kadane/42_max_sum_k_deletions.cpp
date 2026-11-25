/*
Generalization: At most K deletions

arr = [1, -2, -3, 4, 5]
k = 2

we can delete -2,-3
    max-sum = 10



We introduce a state for every possible number of deletions.
    
    dp[i][k]
        max sum ending at i with exactly k deletions

    EXTEND:
        dp[i][k] = dp[i-1][k] + a[i]

    DELETE CURR ELEMENT
        dp[i][k] = dp[i-1][k-1]

    so we take the max of these 2 choices
        max(keep, delete)

    for 0 deletions
        we have normal kadane
*/

#include <vector>
#include <climits>
using namespace std;

int maxSubarraySumKDeletions(vector<int>& arr, int K) {
    int n = arr.size();
    const int NEG = INT_MIN / 2;
    /*
    we guard the sentinel
        const long long NEG = LLONG_MIN / 4;

    OR
        if(dp[k] != NEG)
            keep = dp[k] + arr[i];
    */

    vector<vector<int>> dp(
        n, vector<int>(K + 1, NEG)
    );

    dp[0][0] = arr[0];

    int ans = arr[0];

    for(int i = 1; i < n; i++) {

        // No deletion
        dp[i][0] = max(
            arr[i],
            dp[i-1][0] + arr[i]
        );

        for(int k = 1; k <= K; k++) {

            // Keep current element
            int keep = dp[i-1][k] + arr[i];

            // Delete current element
            int del = dp[i-1][k-1];

            dp[i][k] = max(keep, del);
        }

        // track the max sum across all cells
        for(int k = 0; k <= K; k++) {
            ans = max(ans, dp[i][k]);
        }
    }

    return ans;
}