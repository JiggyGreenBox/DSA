#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> nums = {2, 3, 4, 5};
    int n = nums.size();
    int target = 6;

    // dp[i][t]: can we form sum t using nums[i...n-1]?
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // Base case: sum 0 is always possible
    dp[n][0] = true;

    // Build the DP table (bottom-up)
    for (int i = n - 1; i >= 0; i--) {
        for (int t = 0; t <= target; t++) {
            bool skip = dp[i + 1][t];

            bool pick = false;
            if (t >= nums[i])
                pick = dp[i + 1][t - nums[i]];

            dp[i][t] = pick || skip;
        }
    }

    // Query: is the target sum possible?
    cout << "Can form target? " << boolalpha << dp[0][target] << "\n";

    // Greedy reconstruction: follow a valid pick/skip path
    vector<int> subset;
    int t = target;

    for (int i = 0; i < n && t > 0; i++) {
        bool pick = (t >= nums[i] && dp[i + 1][t - nums[i]]);

        if (pick) {
            subset.push_back(nums[i]);
            t -= nums[i];
        }
        // Otherwise, skip nums[i] and move to the next index
    }

    cout << "Subset: ";
    for (int x : subset)
        cout << x << " ";
    cout << "\n";

    // Print DP table
    cout << "\nDP table (rows = index, columns = target):\n";
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= target; j++)
            cout << dp[i][j] << " ";
        cout << "\n";
    }

    return 0;
}

/*
reconstruct(int target)
    vector<int> ans
    

    while(idx < n && target > 0)

        if(target >= num[idx] && dp[idx+1][target-num[idx]] == true) {
            ans.push_back(nums[idx])
            target -= nums[idx];
            idx++
        }
        else{
            idx++
        }

    return ans;
*/