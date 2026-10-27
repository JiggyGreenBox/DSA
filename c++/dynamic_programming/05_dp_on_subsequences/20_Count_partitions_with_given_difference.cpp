#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
/*
Count partitions with given difference

    Given an array arr of n integers and an integer diff, count the 
    number of ways to partition the array into two subsets S1 and S2 such 
    that:

    ∣S1−S2∣ = diff and S1 ≥ S2
    Where |S1| and |S2| are sum of Subsets S1 and S2 respectively.    
*/

/*
∣S1−S2∣ = diff and S1 ≥ S2


    s1 + s2 = total

    s1 - s2 = diff

    2s1 = total + diff

    sum = (total+diff)/2
*/

int f_rec(int idx, int target, vector<int> &arr, int n) {
    if(idx == n) {        
        if(target == 0) return 1;
        return 0;
    }

    int skip = f_rec(idx+1, target, arr, n);

    int take = 0;
    if(arr[idx] <= target) { // s1 >= s2
        take = f_rec(idx+1, target - arr[idx], arr, n);
    }

    return skip + take;
}
int countPartitions1(int n, int diff, vector<int>& arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);

    if((total + diff)%2) return 0; // target not integer

    int target = (total + diff)/2;
    return f_rec(0, target,  arr, n);
}

// ===========================================================
int f_memo(int idx, int target, vector<int> &arr, int n, vector<vector<int>> &dp) {
    if(idx == n) {        
        if(target == 0) return 1;
        return 0;
    }

    if(dp[idx][target] != -1) return dp[idx][target];

    int skip = f_memo(idx+1, target, arr, n, dp);

    int take = 0;
    if(arr[idx] <= target) { // s1 >= s2
        take = f_memo(idx+1, target - arr[idx], arr, n, dp);
    }

    return dp[idx][target] = skip + take;
}
int countPartitions2(int n, int diff, vector<int>& arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);

    if((total + diff)%2) return 0; // target not integer

    int target = (total + diff)/2;

    vector<vector<int>> dp(n, vector<int>(target+1, -1));

    return f_memo(0, target,  arr, n, dp);
}

// ===========================================================
/*
tabulation
    base cases are prefilled
    dp[n][0] = true

*/
int countPartitions3(int n, int diff, vector<int>& arr) {
        int total = accumulate(arr.begin(), arr.end(), 0);

    // if((total + diff)%2) return 0; // target not integer
    if(total < diff || (total + diff)%2) return 0;

    int target = (total + diff)/2;

    vector<vector<int>> dp(n+1, vector<int>(target+1, 0));
    dp[n][0] = 1;

    for(int i=n-1; i>=0; i--) {
        for(int s=0; s<=target; s++) {
            // int skip = f_memo(idx+1, target, arr, n, dp);
            int skip = dp[i+1][s];

            int take = 0;
            if(arr[i] <= s) { // s1 >= s2
                // take = f_memo(idx+1, target - arr[idx], arr, n, dp);
                take = dp[i+1][s - arr[i]];
            }

            dp[i][s] = skip + take;   
        }
    }
    return dp[0][target];
}

int countPartitions4(int n, int diff, vector<int>& arr) {
        int total = accumulate(arr.begin(), arr.end(), 0);

    // if((total + diff)%2) return 0; // target not integer
    if(total < diff || (total + diff)%2) return 0;

    int target = (total + diff)/2;

    
    vector<int> next(target+1, 0);
    next[0] = 1;

    for(int i=n-1; i>=0; i--) {

        vector<int> curr(target+1, 0);

        for(int s=0; s<=target; s++) {
            
            int skip = next[s];

            int take = 0;
            if(arr[i] <= s) { // s1 >= s2
                // take = f_memo(idx+1, target - arr[idx], arr, n, dp);
                take = next[s - arr[i]];
            }

            curr[s] = skip + take;
        }
        next = curr;
    }
    return next[target];
}


int main() {
    vector<int> v = {1, 2, 3, 4};
    int diff = 2;
    cout << countPartitions1(v.size(), diff, v) << endl;
    cout << countPartitions2(v.size(), diff, v) << endl;
    cout << countPartitions3(v.size(), diff, v) << endl;
    cout << countPartitions4(v.size(), diff, v) << endl;
    
    

    v = {1, 1, 2, 3};
    diff = 1;
    cout << countPartitions1(v.size(), diff, v) << endl;
    cout << countPartitions2(v.size(), diff, v) << endl;
    cout << countPartitions3(v.size(), diff, v) << endl;
    cout << countPartitions4(v.size(), diff, v) << endl;
    return 0;
}