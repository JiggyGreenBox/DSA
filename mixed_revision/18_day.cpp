/*
============================================
sep 22
    last sep 18
============================================

Session 1 — Recursion / Backtracking

============================================


Question 1 — Take / Don't Take

Subsets II

Given an integer array nums that may contain duplicates, return all 
possible subsets (the power set).

The solution set must not contain duplicate subsets.


Example

    nums = [1,2,2]

    output:
    [
    [],
    [1],
    [1,2],
    [1,2,2],
    [2],
    [2,2]
    ]

Brute force:
    
Observation
    this is a problem where we want to pick or not pick
    an element for the subsequence
    pick/skip

we can either branch
    or use a loop here
        for remaining choices
            pick
                recurse
            unpick
to prevent duplicates
    we want to prevent duplicates at each recursion level
    so once we enter the level
        if choice is 2nd or more
            check if its the same as the last one
                or well get duplicate results

algorithm
    void dfs(int idx, 
        const vector<int> &nums, 
        vector<int> &curr, 
        vector<vector<int>> &ans) {

        ans.push_back(curr);

        for(int i=idx; i<nums.size(); i++) {

            // skip dups at this level
            if(i>idx && nums[i] == nums[i-1])
                continue;

            curr.push_back(nums[i]);
            dfs(i+1, nums, curr, ans);
            curr.pop_back();
        }
    }

    vector<vector<int>> subsets2(const vector<int> &nums) {
        vector<vector<int>> ans;
        vector<int> curr;
        dfs(0, nums, curr, ans);
        return ans;
    }
Complexity
    at each step we either pick or skip
    so 2^n

    O(n*2^n) time    
    O(n) auxillary
        O(n*2^n) including input

============================================


Question 2 — Combination Sum

Given an array of distinct positive integers candidates and a target 
integer target, return all unique combinations where the chosen 
numbers sum to target.

You may use the same number unlimited times.

candidates = [2,3,6,7]
target = 7

output:
[
  [2,2,3],
  [7]
]

candidates = [2,3,5]
target = 8

output:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]

Brute force
    recursion approach is the brute force approach

Observation
    we can pick or skip the element till we reach the target

    we can pick the same element again
        so we recurse at i
    and skip
        at i+1

base case
    when we are at the last idx we stop
        or if we reach the target
        or if we cross the target

algorithm

complexity
    O(n*2^n) time
    O(n*2^n) space

============================================

Question 3 — harder transfer

Now let's make the recursion less obvious.

Word Search

Given an m x n grid of characters and a string word, return true if 
the word exists in the grid.

The word can be constructed from letters of sequentially adjacent 
cells, where adjacent cells are horizontally or vertically 
neighboring.

You cannot use the same cell more than once in the same path.


grid =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

word = "ABCCED"

→ true


Derivation
    we want to find if the word exists in the grid
    we can move in 4 dirs to check
    so we start with the first char, look in all dirs
    for the next char, till we reach the end
    no reuse allowed

    if not possible return false else true

we will use recursion to check this
    at each stage,
        we need idx of word
        visited grid to prevent duplicates
        wordgrid
        
    return true if we could reach the end of word

complexity
    O(n*m*word_len) time
    O(n*m) space
====================================

Question 1

Given an integer array nums, return the length of the shortest 
non-empty contiguous subarray whose sum is at least k.

The array may contain positive, zero, and negative numbers.

If no such subarray exists, return -1.

nums = [2,-1,2]
k = 3

answer = 3


brute force
    generate all subarrays
        if sum >= k
            track len
        n^2

    can we use sliding window
        sum++
        while(sum >=k)
            update min
            shrink

    no because the expanding and shrinking are not monotonic
    add or removing a number doesnt increase and reduce the sum 
    due to negative numbers

    we can use prefix sums
    we want a subarray sum >= k
        then we want the shortest when true

    we want
        prefix[r] - prefix[l-1] >= k

    we want to find a prefix sum that is >=k
        so at every new prefix,
        we eliminate useless candidates
        and expand and shrink the prefix deque


    -1[1,2,3,10,1]
     0[1,3,6,16,17]

    prefix[r] - prefix[l-1] >= k

    we want prefix[l-1] <= prefix[r] - k
        16-6 == 10

    use a deque
    for a prefix[r]
        search = prefix[r] - k
        if front() < search
            update minlen
            pop

        push deque


    and 
        we want shortest prefix[r] - prefix[l-1] >=k
        if we have any prefix at the back > current prefix
            it doesnt help
            idx    2    3
            prefix 5    2

            old - 2 >=k  is a larger value and shorter
            old - 5 >=k  is a smaller value and longer, useless
invariant
    

algorithm

complexity
    O(n) time
    O(n) space


*/

#include <vector>
#include <iostream>
#include <climits>
#include <unordered_map>
#include <deque>
using namespace std;


int shortest_subarray(vector<int> &nums, int k) {
    unordered_map<int, int> mpp; // <prefixsum, idx>

    int n = nums.size();
    vector<int> prefix();

    deque<int> dq; // idx

    mpp[0] = -1;

    int min_len = INT_MAX;
    

    for(int i=0; i<nums.size(); i++) {

        // prefix += nums[i];


        // while(!dq.empty() && prefix - prefix[dq.front()])


        dq.push_back(i);
        // mpp[prefix] = i;
        
    }

    return min_len == INT_MAX ? -1 : min_len;
}

int main() {
    vector<int> nums = {1,2,-1,2,-3,4};
    int k = 3;

    cout << shortest_subarray(nums, k) << endl;

    nums = {2,-1,2};k = 3;
    cout << shortest_subarray(nums, k) << endl;    
    
    return 0;
}