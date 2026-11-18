/*
Matrix chain multiplication
    [https://takeuforward.org/practice/dsa/matrix-chain-multiplication?category=mcm-dp&source=strivers-a2z-dsa-sheet&tab=problem]

Given a chain of matrices A1, A2, A3,.....An, you have to figure out 
the most efficient way to multiply these matrices. In other words, 
determine where to place parentheses to minimize the number of 
multiplications.

Given an array nums of size n. Dimension of matrix Ai ( 0 < i < n ) 
is nums[i - 1] x nums[i].Find a minimum number of multiplications 
needed to multiply the chain.

Example 1:
    Input : nums = [10, 15, 20, 25]

    Output : 8000

    Explanation : There are two ways to multiply the chain - A1*(A2*A3) 
    or (A1*A2)*A3.

    If we multiply in order- A1*(A2*A3), then number of multiplications 
    required are 11250.

    If we multiply in order- (A1*A2)*A3, then number of multiplications 
    required are 8000.

    Thus minimum number of multiplications required is 8000.

Example 2:
    Input : nums = [4, 2, 3]

    Output : 24

    Explanation : There is only one way to multiply the chain - A1*A2.

    Thus minimum number of multiplications required is 24.
*/

/*

for A1 x A2 x A3

    we can have (A1*A2)*A3
        or      A1*(A2*A3)

    both give the same result
        but not computation costs

    cost of multiplying an axb with bxc matrix
        is (a x b x c )


A1 10 x 20
A2 20 x 30
A3 30 x 40

    option 1
        (A1*A2) * A3
        (10*20)(20*30)
            cost 10*20*30 = 6000
        
        (10*30)*(30*40)
            cost 10*30*40 = 12000
        
        total = 6000 + 12000 = 18000

    option 2
        A1* (A2*A3)
        (20*30)(30*40)
            cost 20*30*40 = 24000
        
        (10*20)*(20*40)
            cost 10*20*40 = 8000
        
        total = 24000 + 8000 = 32000

    option 1 is optimal

f(i,j)
    minimal cost to multiply matrices Ai to Aj

        A[i]..A[k] | A[k+1]..A[j]
            
        so the problem becomes subproblems by
            cost of base matrices (a*b*c) + f(i,k) + f(k+1,j)


    

*/

#include <vector>
#include <string>
#include <climits>
#include <assert.h>
using namespace std;

/*
    nums = {10, 20, 30, 40};
        f(1,3)
            f(1,1) + f(2,3)
                    f(1,1)
                        0
                    f(2,3)
                        24000
                    final cost = (10*20*40) + 0 + 24000
                               = 8000 + 24000 = 32000
                32000
            f(1,2) + f(3,3)
                    f(1,2) 
                        = 6000
                    f(3,3) 
                        = 0
                    final cost
                        = (10*30*40) + 0 + 6000
                        = 12000 + 6000
                18000


time complexity
    T(n) exponential
    or (4^n  /sqr_root(n))
*/
int f(int i, int j, vector<int> &nums) {

    if(i == j) 
        return 0; // need 2 matrices to multiply between them
    

    // axb bxc
    // cost is axbxc
    // 10x.....x50
    // final shape becomes 10x50
    // we only carry cost

    int best = INT_MAX;

    for(int k=i; k<=j-1; k++) {

        int cost = nums[i-1] * nums[k] * nums[j]; //i-1, j are extreme boundaries

        int total_ops = cost + f(i,k, nums) + f(k+1, j, nums);

        best = min(best, total_ops);
    }

    return best;
}

int matrixMultiplication1(vector<int>& nums) {
    int n = nums.size();
    return f(1, n-1, nums);
}
/*
There are O(n^2) possible interval states (i,j). 
Due to memoization, each state is computed only once. 
For each state, we try every possible partition point k, 
which takes O(n) time in the worst case. 
Therefore, the total time complexity is O(n^3). 
The DP table takes O(n^2) space, and the recursion stack takes O(n), 
giving O(n²) auxiliary space overall.
*/
int memo(int i, int j, vector<int> &nums, vector<vector<int>> &dp) {

    if(i == j) 
        return 0; // need 2 matrices to multiply between them

    if(dp[i][j] != -1)
        return dp[i][j];
    

    // axb bxc
    // cost is axbxc
    // 10x.....x50
    // final shape becomes 10x50
    // we only carry cost

    int best = INT_MAX;

    for(int k=i; k<=j-1; k++) {

        int cost = nums[i-1] * nums[k] * nums[j]; //i-1, j are extreme boundaries

        int total_ops = cost + memo(i,k, nums, dp) + memo(k+1, j, nums, dp);

        best = min(best, total_ops);
    }

    return dp[i][j] = best;
}

int matrixMultiplication2(vector<int>& nums) {
    int n = nums.size();
    // what are the possible states for i,j?
    // lets just use i..n-1, j..n-1
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return memo(1, n-1, nums, dp);
}

/*
dp[i][j]

    best = 
    needs k=i; k<j; k++
        best = cost + dp[i][k] + dp[k+1][j]
    dp[i][j] = best

    we should start at j==i=0
        j==n-1; j>=1;j--
            i=j; i>=1; i--
                
*/
int matrixMultiplication3(vector<int>& nums) {
    int n = nums.size();
    // what are the possible states for i,j?
    // lets just use i..n-1, j..n-1
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return memo(1, n-1, nums, dp);
}

int main() {
    
    vector<int> nums = {10, 15, 20, 25};
    // auto x = matrixMultiplication1(nums);
    assert(matrixMultiplication1(nums) == 8000);
    assert(matrixMultiplication2(nums) == 8000);
    nums = {10, 20, 30, 40};
    // x = matrixMultiplication1(nums);
    assert(matrixMultiplication1(nums) == 18000);
    assert(matrixMultiplication2(nums) == 18000);
    return 0;
}