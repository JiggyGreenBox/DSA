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
we get a range
    for each ballon in the range
    burst it then add the left and right

    f(i,j)
        for k=i; k<=j; k++
            cost = ...
            total = cost + f(i,k-1) + f(k+1, j)
            best = ...
        return best
*/
#include <vector>
#include <climits>
#include <assert.h>
using namespace std;

int f(int i, int j, vector<int>& nums) {

    if(i > j || j < i)
        return 0;

    int n = nums.size();

    int best = INT_MIN;
    for(int k=i; k<=j; k++) {

        int left = 1;
        int right = 1;
        if(k-1 >= 0)
            left = nums[k-1];

        if(k+1 < n)
            right = nums[k+1];

        int cost = left * nums[k] * right;
        int total = cost + f(i, k-1, nums) + f(k+1, j, nums);
        best = max(best, total);
    }
    return best;
}

int maxCoins1(vector<int>& nums) {
    int n = nums.size();
    return f(0, n-1, nums);
} 

int main() {
    vector<int> nums = {3, 1, 5, 8};
    auto x = maxCoins1(nums);
    // assert(maxCoins1(nums) == 167);

    nums = {1, 2, 3, 4};
    x = maxCoins1(nums);
    // assert(maxCoins1(nums) == 40);
    return 0;
}