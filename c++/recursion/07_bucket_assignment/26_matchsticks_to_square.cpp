/*
# LC 473
Matchsticks to Square

You are given an integer array matchsticks where matchsticks[i] is 
the length of the ith matchstick. You want to use all the matchsticks 
to make one square. You should not break any stick, but you can link 
them up, and each matchstick must be used exactly one time.

Return true if you can make this square and false otherwise.

Example 1:

    Input: matchsticks = [1,1,2,2,2]
    Output: true
    Explanation: You can form a square with length 2, one side of the 
    square came two sticks with length 1.

Example 2:

    Input: matchsticks = [3,3,3,3,4]
    Output: false
    Explanation: You cannot find a way to form a square with all the 
    matchsticks.
*/  


/*

we need to divide the total into 4 equal parts
if total % 4 != 0
    not possible


for each number we try each bucket
    if we can place the last element
        success

    

*/


#include <vector>
#include <numeric>
using namespace std;
bool dfs(int idx, 
        vector<int> &buckets, 
        vector<int> &nums,
        int target) {

    // all numbers have been assigned
    if(idx == nums.size())
        return true;

    int num = nums[idx];
    
    for(int b=0; b<4; b++) {

        if(buckets[b] + num > target)
            continue;

        buckets[b] += num;

        if(dfs(idx+1, buckets, nums, target))
            return true;

        buckets[b] -= num;
    }
    return false;
}

bool makesquare(vector<int>& nums) {
    
    int total = accumulate(nums.begin(), nums.end(), 0);

    if(total % 4 != 0)
        return false;

    vector<int> buckets(4, 0);

    int target = total / 4;

    return dfs(0, buckets, nums, target);
}

int main() {

    vector<int> matchsticks = {1,1,2,2,2};
    // matchsticks = {3,3,3,3,4};
    auto x = makesquare(matchsticks);
    return 0;
}