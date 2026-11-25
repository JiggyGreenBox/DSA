/*
============================================
nov 21
    last nov 19
============================================
Problem 1
============================================

maximum length of a contiguous subarray whose sum is less than or 
equal to k.

brute force approach
    generate all subsequences 
        track max-len for each len where sum <= k
        
nums can contain both positive and negative integers.
so the sum is not monotonic
    adding more nums can reduce the sum and viceversa


we can use a prefix array to store queries for sum
    sum(i,j) = prefix[j+1] - prefix[i]

    we want sum <= k

    we can store a window of prefixs
    [1,-1,2,3,5,-6,7] k = 5
    [0,1,0,2,5,10,4,11]
    prefix = 

    
    prefix[right] - prefix[front] <= k
        len = right-front
        max-len = ...
        pop.front()

    what are useless additions to the dq?
        5,6,9
            this make the sum larger
                and the len shorter

        5,4,3
            we have the next best sum
            and the next best idx

GPT has made is own problem which doesnt have an optimal solution
negative numbers does not allow pruning or sliding

============================================
Problem 2
============================================
Shortest Unsorted Continuous Subarray

nums = {2, 6, 4, 8, 10, 9, 15}

we want the left, right limits of unsorted array

right is unsorted when it is below the global max
    global max increases from left to right

    max = n[0]
        for 1..n-1
            if num < max
                right = num
            else
                update max

left is unsorted when it is more than global min
    global min reduces from right to left
    min = last
    for n-2..0
        if num > min
            left = ..
        else
            update min

*/
#include <vector>
#include <deque>
#include <stack>
#include <assert.h>
using namespace std;


// o(n) time
// O(n) space
vector<int> nge(vector<int> &nums) {
    int n = nums.size();
    vector<int> ans(n, -1);
    stack<int> st;
    

    for(int i=2*n-1; i>=0; i--) {
        while(!st.empty() && nums[i%n] >= st.top())
            st.pop();

        if(i<n && !st.empty())
            ans[i] = st.top();

        st.push(nums[i%n]);
    }
    return ans;
}

int main() {
    vector<int> nums = {5,4,3,2,1};    
    auto x = nge(nums);
    // assert(maxSubarrayLength(nums, k) == 5);

    nums = {1,2,1};    
    x = nge(nums);
    // x = maxSubarrayLength(nums, k);
    // assert(maxSubarrayLength(nums, k) == 5);

    return 0;
}