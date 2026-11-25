/*
============================================
nov 24
    last nov 23
============================================
Problem 1
============================================
jump game 2


Input:  nums = [2,3,1,1,4]
Output: 2

we can always reach the end

derivation
    at each idx we have a number which is the max steps 
    we can jump
        idx0 = 1,  we can take 1 step from idx0 = 1
        idx1 = 2,  we can take 2 steps from idx1 = [2,3]

    so we can see that we have a min-range and a max-range
    for each step we take
    once max-range reaches n-1
    we will have the ans
    this is like bfs


time complexity
    O(n) time
    O(1) space


code
int jumpgame2(vector<int> &nums) {
    int left = 0;
    int right = 0;
    int n = nums.size();

    int steps = 0;
    while(right < n-1) {

        steps++;
        int furthest = 0;

        for(int i=left; i<=right; i++) {
            furthest = max(furthest, i + nums[i]);
        }        
        left = right+1;
        right = furthest;
    }
        
    return steps;
}


vector<int> jumpgame3(vector<int> &nums) {
    int left = 0;
    int right = 0;
    int n = nums.size();
    vector<int> parent(n);
    iota(parent.begin(), parent.end(), 0);    

    int steps = 0;
    // nextUnassigned always points to the first index 
    // that hasn't received a parent yet.
    int next_unassigned = 1;

    while(right < n-1) {

                
        int furthest = right;

        for(int i=left; i<=right; i++) {

            int reach = min(n-1, i + nums[i]);

            while(next_unassigned <= reach) {
                parent[next_unassigned] = i;
                next_unassigned++;
            }

            furthest = max(furthest, reach);         
        }        
        left = right + 1;
        right = furthest;
        steps++;
    }
        
    
    vector<int> ans;
    int i = n-1;
    while(i != 0) {
        ans.push_back(i);
        i = parent[i];
    }
    ans.push_back(0);
    reverse(ans.begin(), ans.end());
    
    return ans;
}

============================================
Problem 2
============================================

Product of Array Except Self — LC 238

    [2,3,4,5]
    [60,40,30,24]

    for each i
        we need ans[i] = prefix[i] * suffix[i]

    prefix[i]
        product upto i but not including i

    suffix[i]
        product upto i from the right not including i



    so we can use a loop where
        prefix[i] = prefix;
        prefix *= num[i]; // for next idx

    so we can use a loop where
        suffix[i] = suffix;
        suffix *= num[i]; // for next idx

    we can share the prefix/suffix array as ans
    then on 2nd pass ans[i] *= suffix

    
code  
    vector<int> maxsub(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans(n);

        int prefix = 1;
        for(int i=0; i<n; i++) {
            ans[i] = prefix;
            prefix *= nums[i];
        }

        int suffix = 1;
        for(int i=n-1; i>=0; i--) {
            ans[i] *= suffix;
            suffix *= nums[i];
        }
        return ans;
    }


============================================
Problem 3
============================================
gas station

There are n gas stations arranged in a circle.
- gas[i] is the amount of gas available at station i.
- cost[i] is the gas required to travel from station i to station i+1.
- Your tank starts empty.
- Return the starting station index if you can complete the circuit, 
    otherwise return -1.

You are guaranteed at most one valid answer.

gas  = [1, 2, 3, 4, 5]
cost = [3, 4, 5, 1, 2]

Output = 3


derivation
    at any station idx
        we get gas[idx]
        we need cost[idx] to move ahead

    the station is connected in a circle
    some station would give us a surplus
    while some stations might require a surplus 
    to pass them

    hence where we start matters
    this leads us to the brute force
    from each idx
        wrap around loop till idx-1
            if we can reach, return true

    if the total gas is less than cost then a solution is possible

    if the diff is less than zero
    we must start from the next idx

    diff = gas[idx] - cost[idx]

    and if total-diff < 0, no solution

    combining both of these we can get a 1 pass solution
*/
#include <vector>
#include <assert.h>
#include <numeric>
#include <algorithm>
using namespace std;

// time O(n), space O(1)
int gasStation(vector<int> &gas, vector<int> &cost) {
    int n = gas.size();

    int total = 0;
    int curr = 0;
    int start = 0;
    for(int i=0; i<n; i++) {
        int diff = gas[i] - cost[i];
        curr += diff;
        if(curr < 0) {            
            start = i+1; // ran out of gas, but also no station from before reset till here will work
            curr = 0; // reset 
        }

        total += diff;
    }

    if(total >=0)
        return start;
    return -1;
}

int main() {
    vector<int> gas, cost;
    gas  = {1, 2, 3, 4, 5};
    cost = {3, 4, 5, 1, 2};
    
    auto x = gasStation(gas, cost);

    gas  = {1, 1, 1, 1, 1};
    cost = {3, 2, 5, 2, 2};
    x = gasStation(gas, cost);
    
  
    return 0;
}