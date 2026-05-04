#include <iostream>
#include <climits>
#include <vector>
using namespace std;

/*
index backwards from n-1 to 0

now we track min over [i+1, i+k]
0,1,2,3,4,5,6,7,8,9

k=4

9-4 = 5
9-3 = 6
9-2 = 7
9-1 = 8

backwards this becomes [n-k..n-1]

for any idx range is [idx-k..idx-1]    

*/

int helper_rec(int idx, vector<int>& heights, int k) {
    if(idx == 0) return 0;    

    int min_step = INT_MAX;

    for(int j=1; j<=k; j++){
        
        int i = idx-j;

        if(i<0) break;

        int jump =  abs(heights[idx] - heights[i]) 
                    + helper_rec(i, heights, k);
        min_step = min(min_step, jump);
    }
    return min_step;
}
int frogJump_rec(vector<int>& heights, int k) {
    int n = heights.size();
    return helper_rec(n-1, heights, k);
}

int helper_memo(int idx, vector<int> &heights, int k, vector<int> &dp) {
    if(idx == 0) return 0;

    if(dp[idx] != -1) return dp[idx];

    int min_step = INT_MAX;

    for(int j=1; j<=k; j++) {
        int i = idx - j;
        if(i<0) break;
        int jump = abs(heights[idx] - heights[i]) + helper_memo(i, heights, k, dp);
        min_step = min(min_step, jump);
    }
    return dp[idx] = min_step;
}

int frogJump_memo(vector<int>& heights, int k) {
    int n = heights.size();
    vector<int> dp(n, -1);
    return helper_memo(n-1, heights, k, dp);
}


/*
int frogJump_tab(vector<int>& heights, int k) {
    int n = heights.size();
    vector<int> dp(n, -1);
    dp[0] = 0;
    
    for(int i=1; i<n; i++) {
        int min_step = INT_MAX;
        for(int j=k; j>=1; j--) {
            int idx = i-j;
            if(idx < 0) continue;
            int jump = dp[idx] + abs(heights[i]- heights[idx]);
            min_step = min(min_step, jump);
        }
        dp[i] = min_step;
    }
    return dp[n-1];
}
*/

int frogJump_tab(vector<int>& heights, int k) {
    int n = heights.size();
    vector<int> dp(n, INT_MAX);
    dp[0] = 0;

    // f[0] = 0

    // f[1] = 0 + c[0,1]

    // f-min can be carried ahead but not cost

    // f[2] = min(f[1]+c[2,1], f[2] + c[2,1])


    // 15, 4, 1, 14, 15
    // k=3

    // dp[0] = 0
    // dp[1] = 11
    // dp[2] = 14 
    // dp[3] = 1
    // dp[4] = 2


    for(int i=1; i<n; i++) {
        int min_step = INT_MAX;
        for(int j=1; j<=k; j++) { // sub [1..k] for each i
            int idx = i-j;
            if(idx < 0) break; // only valid idx
            
            dp[i] = min(dp[i], dp[idx] + abs(heights[idx] - heights[i]));
        }
        
    }
    return dp[n-1];
}


/*
0,1,2,3,4,5,6,7,8,9
k=3

f[9] = min(f[8], f[7], f[6])
f[8] = min(f[7], f[6], f[5])
f[3] = min(f[2], f[1], f[0])

f[1] = min(f[0], INT_MAX, INT_MAX)
*/


int frogJump_tab2(vector<int>& heights, int k) {
    int n = heights.size();
    // vector<int> dp(n, -1);
    // dp[0] = 0;
    vector<int> dp(k, 0);
        
    for(int i=1; i<n; i++) {
        int min_step = INT_MAX;
        for(int j=1; j<=k; j++) {
            int idx = i-j;            
            if(idx < 0) break;

            int jump = dp[idx % k] + abs(heights[i]- heights[idx]);
            min_step = min(min_step, jump);
        }
        dp[i % k] = min_step;
    }
    return dp[(n-1) % k];
}

int main() {
    vector<int> heights = {10, 5, 20, 0, 15};
    int k = 2;
    cout << frogJump_rec(heights, k) << endl;
    cout << frogJump_memo(heights, k) << endl;
    cout << frogJump_tab(heights, k) << endl;
    cout << frogJump_tab2(heights, k) << endl;
    

    heights = {15, 4, 1, 14, 15};
    k = 3;
    cout << frogJump_rec(heights, k) << endl;
    cout << frogJump_memo(heights, k) << endl;
    cout << frogJump_tab(heights, k) << endl;
    cout << frogJump_tab2(heights, k) << endl;

    return 0;
}