#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

/*

Target sum

    Given an array nums of n integers and an integer target, build an 
    expression using the integers from nums where each integer can be 
    prefixed with either a '+' or '-' sign.

    The goal is to achieve the target sum by evaluating all possible 
    combinations of these signs.

    Determine the number of ways to achieve the target sum and return 
    your answer with modulo 109+7.

    ------
        Input: nums = [1, 2, 7, 1, 5], target = 4
        Output: 2

        Explanation: There are 2 ways to assign symbols to make the sum of 
        nums be target 4.

        +1 + 2 + 7 - 1 - 5 = 4
        -1 + 2 + 7 + 1 - 5 = 4
    ------
        Input: nums = [1], target = 1
        Output: 1

        Explanation: There is only one way to assign symbols to make the sum 
        of nums be target 1.
*/

class Solution {
    private:
        /*
        either -ve or +ve
        f(idx, target)
            
            int add = ...
            int sub = ...
            return add + sub
        */
        int f_rec_wrong_approach(int idx, int target, vector<int>& nums, int n) {
            if(idx == n) {
                if(target == 0) return 1; // 1 way found
                return 0;
            }

            int add = f_rec_wrong_approach(idx+1, target - nums[idx], nums, n);
            int sub = f_rec_wrong_approach(idx+1, target + nums[idx], nums, n);

            return add + sub;
        }
        

        int f_rec(int idx, int T, vector<int> &nums, int n) {

            const int mod = 1e9+7;

            if(idx == n) {
                if(T == 0) return 1;
                return 0;
            }

            int skip = f_rec(idx+1, T, nums, n);
            int take = 0;
            if(nums[idx] <= T) {
                take = f_rec(idx+1, T - nums[idx], nums, n);
            }
            return (take + skip) % mod;
        }

        int f_memo(int idx, int T, vector<int> &nums, int n, vector<vector<int>> &dp) {

            const int mod = 1e9+7;

            if(idx == n) {
                if(T == 0) return 1;
                return 0;
            }

            if(dp[idx][T] != -1) return dp[idx][T];

            int skip = f_memo(idx+1, T, nums, n, dp);
            int take = 0;
            if(nums[idx] <= T) {
                take = f_memo(idx+1, T - nums[idx], nums, n, dp);
            }
            return dp[idx][T] = (take + skip) % mod;
        }

    public:
        int targetSum0(int n, int target, vector<int>& nums) {
            return f_rec_wrong_approach(0, target, nums, n);
        }


                
        /*
        we split the array into 2 subsets
        P and N
        then if P-N = target then count

        try different P and N
        P - N = target
        P + N = total

        2P = total + target
        P = (total + target)/2

        dp range:
            idx 0..n-1
            P = 0..(total+target)/2

        pick skip
        dp[i][target] = pick + skip

            dp[i][sum]
            =
            number of ways
            to make sum
            using elements from i onwards

        impossible cases
            P = (total + target)/2
            so total+target cannot be ODD

            target > total? not possible
        */
        int targetSum1(int n, int target, vector<int>& nums) {
            int total = accumulate(nums.begin(), nums.end(), 0);

            if(abs(target) > total) return 0;
            if((total + target) % 2) return 0; // T cannot be a fraction
            int T = (total + target) / 2;
            return f_rec(0, T, nums, n);
        }

        
        // dp array, range, idx: 0..n-1, T:0..T        
        int targetSum2(int n, int target, vector<int>& nums) {
            int total = accumulate(nums.begin(), nums.end(), 0);

            if(abs(target) > total) return 0;
            if((total + target) % 2) return 0; // T cannot be a fraction
            
            int T = (total + target) / 2;
            vector<vector<int>> dp(n, vector<int>(T+1, -1));

            return f_memo(0, T, nums, n, dp);
        }

        int targetSum3(int n, int target, vector<int>& nums) {
            /*
            dp array, range, idx: 0..n, T:0..T
            need idx+1, so iterate backwards
            base cases from memo are prefilled in dp array
            dp[n][0] = 1, rest 0
            */
            int total = accumulate(nums.begin(), nums.end(), 0);

            if(abs(target) > total) return 0;
            if((total + target) % 2) return 0; // T cannot be a fraction
            
            int T = (total + target) / 2;

            vector<vector<int>> dp(n+1, vector<int>(T+1, 0));
            dp[n][0] = 1;

            const int mod = 1e9+7;

            for(int i=n-1; i>=0; i--) {
                for(int t=0; t<=T; t++) {

                    int skip = dp[i+1][t];

                    int take = 0;
                    if(nums[i] <= t) {
                        take = dp[i+1][t - nums[i]];                        
                    }

                    dp[i][t] = (take + skip) % mod;
                }
            }
            return dp[0][T];
        }

        int targetSum4(int n, int target, vector<int>& nums) {
            /*
            dp array, range, idx: 0..n, T:0..T
            need idx+1, so iterate backwards
            base cases from memo are prefilled in dp array
            dp[n][0] = 1, rest 0
            */
            int total = accumulate(nums.begin(), nums.end(), 0);
            if((total + target) % 2) return 0; // T cannot be a fraction
            
            int T = (total + target) / 2;

            
            vector<int> next(T+1, 0);
            next[0] = 1;

            const int mod = 1e9+7;

            for(int i=n-1; i>=0; i--) {

                vector<int> curr(T+1, 0);

                for(int t=0; t<=T; t++) {

                    int skip = next[t];

                    int take = 0;
                    if(nums[i] <= t) {
                        take = next[t - nums[i]];                        
                    }

                    curr[t] = (take + skip) % mod;
                }
                next = curr;
            }
            return next[T];
        }

        int targetSum5(int n, int target, vector<int>& nums) {
            /*
            dp array, range, idx: 0..n, T:0..T
            need idx+1, so iterate backwards
            base cases from memo are prefilled in dp array
            dp[n][0] = 1, rest 0
            */
            int total = accumulate(nums.begin(), nums.end(), 0);
            if((total + target) % 2) return 0; // T cannot be a fraction
            
            int T = (total + target) / 2;

            
            vector<int> dp(T+1, 0);
            dp[0] = 1;

            const int mod = 1e9+7;

            for(int i=n-1; i>=0; i--) {                

                // dp[10] = dp[10] + dp[7]
                // dp[7] must be calculated after dp[10]

                // ways to make t = 
                // old ways to make t + 
                // old ways to make (t-num)
                for(int t=T; t>=nums[i]; t--) {

                    int skip = dp[t];

                    int take = dp[t - nums[i]];

                    dp[t] = (take + skip) % mod;
                }                
            }
            return dp[T];
        }
};

int main() {
    Solution sol;
    vector<int> v = {1, 2, 7, 1, 5};
    int target = 4;
    cout << sol.targetSum1(v.size(), target, v) << endl;
    cout << sol.targetSum2(v.size(), target, v) << endl;
    cout << sol.targetSum3(v.size(), target, v) << endl;
    cout << sol.targetSum4(v.size(), target, v) << endl;
    cout << sol.targetSum5(v.size(), target, v) << endl;

    v = {1};
    target = 1;
    cout << sol.targetSum1(v.size(), target, v) << endl;
    cout << sol.targetSum2(v.size(), target, v) << endl;
    cout << sol.targetSum3(v.size(), target, v) << endl;
    cout << sol.targetSum4(v.size(), target, v) << endl;
    cout << sol.targetSum5(v.size(), target, v) << endl;

    return 0;
}
