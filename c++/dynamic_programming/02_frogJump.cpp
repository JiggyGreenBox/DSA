#include <iostream>
#include <vector>
#include <climits>
using namespace std;


void helper_wrong(int idx, int curr_dist, vector<int> &heights, vector<int> &dist, int &min_dist) {
    
    int n = heights.size();

    // some idx reached the last
    if(idx == n-1) {
        min_dist = min(min_dist, curr_dist);
        return;
    }

    if(idx >= n) return; // invalid
        
    if(idx < n - 1) {        
        int e1 = abs(heights[idx] - heights[idx+1]) + curr_dist;

        // dist, to prevent later larger values 
        if(e1 < dist[idx+1]) {
            dist[idx+1] = e1;
            helper_wrong(idx+1, e1, heights, dist, min_dist);
        }
    }

    if(idx < n - 2) {
        int e2 = abs(heights[idx] - heights[idx+2]) + curr_dist;

        // dist, to prevent later larger values 
        if(e2 < dist[idx+2]) {
            dist[idx+2] = e2;
            helper_wrong(idx+2, e2, heights, dist, min_dist);
        }
    }
}

int helper_rec(int i, vector<int> &heights) {
    
    if(i == 0) return 0;

    int jump1 = helper_rec(i-1, heights) + abs(heights[i] - heights[i-1]);
    int jump2 = INT_MAX;
    if(i>1) {
        jump2 = helper_rec(i-2, heights) + abs(heights[i] - heights[i-2]);
    }
    return min(jump1, jump2);    
}

int frogJump_rec(vector<int>& heights) {
    int n = heights.size();
    return helper_rec(n-1, heights);
}


/*
f(5) = min(f(4),f(3))
f(4) = min(f(3), f(2))

we can see that f(3) will be calculated again

            f5
        f4       f3
     f3    f2
  f2  f1
f1 f0

*/

int helper_memo(int i, vector<int> &heights, vector<int> &dp) {

    if(i==0) return 0;

    if(dp[i] != -1) return dp[i];

    int j1 = helper_memo(i-1, heights, dp) + abs(heights[i] - heights[i-1]);

    int j2 = INT_MAX;
    if(i>1) {
        j2 = helper_memo(i-2, heights, dp) + abs(heights[i] - heights[i-2]);
    }
    return dp[i] = min(j1, j2);
}

int frogJump_memo(vector<int>& heights) {
    int n = heights.size();
    vector<int> dp(n+1, -1);
    return helper_memo(n-1, heights, dp);
}


/*
f[0] = 0
f[1] = min(f[0] + cost10, INT_MAX)
f[2] = min(f[1]+cost21, f[0]+cost20)
f[3] = min(f[2]+cost32, f[1]+cost31)
*/

int frogJump_tab(vector<int>& heights) {
    int n = heights.size();
    vector<int> dp(n, -1);

    // dp[0] = 0;
    // dp[1] = abs(heights[1] - heights[0]);

    // for(int i=2; i<n; i++) {
    //     int cost1 = abs(heights[i] - heights[i-1]);
    //     int cost2 = abs(heights[i] - heights[i-2]);
    //     dp[i] = min(dp[i-1] + cost1, dp[i-2] + cost2);
    // }
    // return dp[n-1];

    dp[0] = 0;
    for(int i=1; i<n; i++) {

        int c1 = dp[i-1] + abs(heights[i] - heights[i-1]);
        int c2 = INT_MAX;
        if(i>1) {
            c2 = dp[i-2] + abs(heights[i] - heights[i-2]);
        }
        dp[i] = min(c1, c2);
    }
    return dp[n-1];
}

int frogJump_tab2(vector<int>& heights) {
    int n = heights.size();    
    int d2 = 0;
    int d1 = 0;

    for(int i=1; i<n; i++) {
        
        int c1 = d1 + abs(heights[i] - heights[i-1]);
        int c2 = INT_MAX;
        if(i>1) c2 = d2 + abs(heights[i] - heights[i-2]);

        int curr = min(c1, c2);

        d2 = d1;
        d1 = curr;        
    }
    return d1;
}

int main() {
    vector<int> heights = {2, 1, 3, 5, 4};
    cout << frogJump_rec(heights) << endl;
    cout << frogJump_memo(heights) << endl;
    cout << frogJump_tab(heights) << endl;
    cout << frogJump_tab2(heights) << endl;
    

    heights = {7, 5, 1, 2, 6};
    cout << frogJump_rec(heights) << endl;
    cout << frogJump_memo(heights) << endl;
    cout << frogJump_tab(heights) << endl;
    cout << frogJump_tab2(heights) << endl;
    return 0;
}



