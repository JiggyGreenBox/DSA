/*
Burst balloons
    [https://takeuforward.org/practice/dsa/burst-balloons?category=mcm-dp&source=strivers-a2z-dsa-sheet]

Given n balloons, indexed from 0 to n - 1, each balloon is painted 
with a number on it represented by an array nums. Burst all the 
balloons.

If the ith balloon is burst, the coins obtained are nums[i - 1] * 
nums[i] * nums[i + 1]. If i - 1 or i + 1 goes out of bounds of the 
array, treat it as if there is a balloon with a 1 painted on it.

Return the maximum coins that can be collected by bursting the 
balloons wisely.

Example 1:
Input : nums = [3, 1, 5, 8]

Output : 167

Explanation :

nums = [3, 1, 5, 8] --> [3, 5, 8] --> [3, 8] --> [8] --> []

coins = 3*1*5  +  3*5*8  + 1*3*8 + 1*8*1 = 167.

Example 2:
Input : nums = [1, 2, 3, 4]

Output : 40

Explanation :

nums = [1, 2, 3, 4] --> [1, 2, 4] --> [1, 4] --> [4] --> []

coins = 2*3*4 + 1*2*4 + 1*1*4 + 1*4*1 = 40.

*/

/*
10 20 30 40
we get a range
    we burst the ballons from the last backwards

    consider 20
        if last 1*20*1

        we can then have 10 on the left
        or 30 or 40 on the right

    we can add ballons to the left and right
    since we are moving backwards
    the ballon we just processed will be L or R

    the trick is to add [1][vec][1]
    to both ends to make the algorithm consistent

    f(i,j)
        best = INT_MIN;
        int k in range(i,j)
            cost = nums[i-1] * nums[k] * nums[j+1]
            cost += f(i, k-1) + f(k+1, j)
            best = max(best, cost)
        return best;
*/
#include <vector>
#include <climits>
#include <assert.h>
using namespace std;

int f(int i, int j, vector<int>& nums) {

    if(i > j)
        return 0;

    int n = nums.size();

    int best = INT_MIN;
    for(int k=i; k<=j; k++) {

        int cost = nums[i-1] * nums[k] * nums[j+1];
        cost += f(i, k-1, nums) + f(k+1, j, nums);
        best = max(best, cost);
    }
    return best;
}

int maxCoins1(vector<int>& nums) {
    int n = nums.size();

    vector<int> a(n+2, 1);

    for(int i=0; i<n; i++)
        a[i+1] = nums[i];

    return f(1, n, a);
}

int memo(int i, int j, vector<int>& nums, vector<vector<int>> &dp) {

    if(i > j)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    int best = INT_MIN;
    for(int k=i; k<=j; k++) {

        int cost = nums[i-1] * nums[k] * nums[j+1];
        cost += f(i, k-1, nums) + f(k+1, j, nums);
        best = max(best, cost);
    }
    return dp[i][j] = best;
}

int maxCoins2(vector<int>& nums) {
    int n = nums.size();

    vector<int> a(n+2, 1);

    for(int i=0; i<n; i++)
        a[i+1] = nums[i];

    vector<vector<int>> dp(n+2, vector<int>(n+2, -1));

    return memo(1, n, a, dp);
}

/*
   1 3 1 5 8 1
   0 1 2 3 4 5
0  1
1    3    [X]
2      1
3        5
4          8
5            1

f(i,j)
    k in [i,j]
        best = cost + f(i,k-1) + f(k+1,j)

    so we need k-1 at each cell (j from i to n)
    we also need k+1,j (i from n to 0)
*/

int maxCoins3(vector<int>& nums) {
    int n = nums.size();

    vector<int> a(n+2, 1);

    for(int i=0; i<n; i++)
        a[i+1] = nums[i];

    vector<vector<int>> dp(n+2, vector<int>(n+2, 0));

    for(int i=n; i>=1; i--) {
        for(int j=i; j<=n; j++) {
            int best = INT_MIN;
            for(int k=i; k<=j; k++) {
                int cost = a[i-1] * a[k] * a[j+1];
                cost += dp[i][k-1] + dp[k+1][j];
                best = max(best, cost);
            }
            dp[i][j] = best;
        }
    }
    return dp[1][n];
}

int main() {
    vector<int> nums = {3, 1, 5, 8};
    auto x = maxCoins3(nums);
    assert(maxCoins1(nums) == 167);
    assert(maxCoins2(nums) == 167);
    assert(maxCoins3(nums) == 167);

    nums = {1, 2, 3, 4};
    x = maxCoins1(nums);
    assert(maxCoins1(nums) == 40);
    assert(maxCoins2(nums) == 40);
    assert(maxCoins3(nums) == 40);
    return 0;
}