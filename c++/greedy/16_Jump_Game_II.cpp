#include <vector>
#include <queue>
#include <climits>
using namespace std;

/*
Jump Game II
    [https://leetcode.com/problems/jump-game-ii/description/]


You are given a 0-indexed array of integers nums of length n. You are 
initially positioned at index 0.

Each element nums[i] represents the maximum length of a forward jump 
from index i. In other words, if you are at index i, you can jump to 
any index (i + j) where:

0 <= j <= nums[i] and
i + j < n
Return the minimum number of jumps to reach index n - 1. The test 
cases are generated such that you can reach index n - 1.

 

Example 1:

    Input: nums = [2,3,1,1,4]
    Output: 2
    Explanation: The minimum number of jumps to reach the last index is 
    2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:

    Input: nums = [2,3,0,1,4]
    Output: 2
*/

/*
we can have a recursive approach
    start at idx 0

    for step in steps[idx]
        take step
        if we reach >=n-1
            ans = min(ans, steps)


next we can have a dp approach
    
    for each possible step
        take
    store min choice
    

    we want (min) dp[0]



[3,1,1,2,1,1]
[0,1,2,3,4,5]

take 1 step from idx-0 3 places ahead from 0
    0+3 = idx-3
take 1 step from idx-3 2 places
    3+2 = 5 == end

[3,1,3,0,1,1]
[0,1,2,3,4,5]

take 1 step from idx-0 2 places ahead from 0
    0+2 = idx-2
take 1 step from idx-2 3 places
    2+3 = 5 == end

how do we effective check these 2 cases?



what if we store farthest
[3,1,1,2,1,1]
[0,1,2,3,4,5]

[3,2,3,5,5,6]

*/


/*
bfs version

nums = [2,3,1,1,4]
idx  = [0,1,2,3,4]
q = [(0,0)]

process 0
    push [1,2]
        q = [(1,1),(2,1)]
process 1
    push [2,3,4]
        q = [(2,2),(3,2),(4,2)]

process 2
    push [3]
        q = [(3,2)]

eventually
    idx == end
    then return jumps

since every jump is 1 step
    bfs will return first occurance

*/

class Solution {
public:
    int jump(vector<int>& nums) {

        int n = nums.size();

        queue<pair<int, int>> q;
        vector<bool> visited(n, false);

        q.push({0, 0});              // {index, jumps}
        visited[0] = true;

        while (!q.empty()) {

            auto [idx, jumps] = q.front();
            q.pop();

            if (idx == n - 1)
                return jumps;

            for (int next = idx + 1;
                 next <= min(n - 1, idx + nums[idx]);
                 next++) {

                if (!visited[next]) { // visited is to prevent duplicate work
                    visited[next] = true;
                    q.push({next, jumps + 1});
                }
            }
        }

        return -1;
    }
};

/*

brute force is trying everything until we reach the answer
int solve(idx) {

    if (idx >= n-1)
        return 0;

    int ans = INF;

    for (int step = 1; step <= nums[idx]; step++) {

        ans = min(ans,
                  1 + solve(idx + step));
    }

    return ans;
}

*/

/*
dp is also possible
but the greedy is compression of shortest path, bfs

nums = [2,3,1,1,4]
index   0 1 2 3 4

as a graph
                 0
               /   \
              /     \
             v       v
             1 ----> 2
            /|\       \
           / | \       \
          v  v  v       v
          2  3  4       3
                 \
                  v
                  4

adjacency list
0 -> {1,2}

1 -> {2,3,4}

2 -> {3}

3 -> {4}

4 -> {}

*/


class Solution {
public:
    int dfs(int idx, vector<int>& nums, vector<int>& dp) {

        int n = nums.size();

        if (idx >= n - 1)
            return 0;

        if (dp[idx] != -1)
            return dp[idx];

        int ans = INT_MAX;

        for (int step = 1; step <= nums[idx]; step++) {

            if (idx + step < n) {

                ans = min(ans,
                          1 + dfs(idx + step, nums, dp));
            }
        }

        return dp[idx] = ans;
    }

    int jump(vector<int>& nums) {

        vector<int> dp(nums.size(), -1);

        return dfs(0, nums, dp);
    }
};



/*
1. so the greedy solution thinks in terms of steps, 
2. for each step we have a range, minReach and maxReach, 
3. we stop when maxReach includes the end
*/

int jump(vector<int>& nums) {

    int n = nums.size();

    int jumps = 0;

    // Current BFS level = [left, right]
    int left = 0;
    int right = 0;

    while (right < n - 1) {

        // Explore the current BFS level.
        int farthest = right;

        // Process every node in the current BFS level
        for (int i = left; i <= right; i++) {
            farthest = max(farthest, i + nums[i]);
        }

        // Move to the next BFS level
        left = right + 1;
        right = farthest;

        jumps++;
    }

    return jumps;
}

/*
canonical standard solution
*/
 int jump(vector<int>& nums) {

    int jumps = 0;

    int levelEnd = 0;
    int nextLevelEnd = 0;

    for (int i = 0; i < nums.size() - 1; i++) {

        nextLevelEnd = max(nextLevelEnd, i + nums[i]);

        // Finished processing the current BFS level.
        if (i == levelEnd) {
            jumps++;
            levelEnd = nextLevelEnd;
        }
    }

    return jumps;
}