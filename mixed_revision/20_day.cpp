/*
============================================
sep 24
    last sep 23
============================================

Let's start

Question 1 — LC 239: Sliding Window Maximum

nums = [1,3,-1,-3,5,3,6,7]
k = 3

    [3,3,5,5,6,7]   

brute force:
    enumerate all windows of size k
        track max
observation
    for a window we can keep a decreasing deque
    when the window reaches its full size the front
    is the max

    then shrink from the front
    add from the back

    an incoming element may be greater than the back
    in that case pop till the back is greater
    to maintain the decreasing deque

why the obvious approach is too slow
data structure
    deque
invariant
    use a deque to slide over the array
        the
algorithm
    vector<int> sliding_max(vector<int> &nums, int k) {
        vector<int> ans;
        deque<int> dq;

        for(int i=0; i<nums.size(); i++) {        

            // remove expired indices        
            while(!dq.empty() && dq.front() <= i-k) 
                dq.pop_front();

            // remove dominated indices
            while(!dq.empty() && nums[i] >= nums[dq.back()]) 
                dq.pop_back();
            

            dq.push_back(i);

            // window is ready
            // push ans
            if(i >= k-1) {
                ans.push_back(nums[dq.front()]);
            }
        }
        return ans;
    }
complexity
    O(n) time
    O(k) space

===================================

Question 2 — LC 862: Shortest Subarray with Sum at Least K

Given an integer array nums and an integer k, return the length of 
the shortest non-empty subarray of nums with a sum of at least k.

If there is no such subarray, return -1.

A subarray is a contiguous part of the array.

derivation
    if numbers were only positive
    then a simple sliding window approach would be sufficient

    there are negative numbers
    we can use prefix sums

    we want prefix[r] - prefix[l-1] >= k
    if we are looking for a exact match then we can store
    prefix in a hashmap for lookups
    but we want a range

    so we precompute all prefixs in a prefix array
    then using a monotonic deque
    we maintain a
        prefix[i] - prefix[dq.front()] >= k
            dq.pop()
            min_len = ..

    what about domination
        for a prefix[idx] = 2
        if prefix[idx-1] = 5

        then idx give us a better sum
        and a smaller length
            do discard idx-1

        while dq and prefix[dq.back] > prefix[idx]
            dq.pop_back

algo
    int shortest(vector<int> &nums, int k) {
        int n = nums.size();

        vector<long long> prefix(n+1, 0);
        for(int i=0; i<n; i++) {
            prefix[i+1] += prefix[i] + nums[i];
        }
        
        deque<int> dq;

        int min_len = n+1;

        for(int i=0; i<=n; i++) {

            // remove dominated
            while(!dq.empty() && prefix[dq.back()] >= prefix[i])
                dq.pop_back();

            dq.push_back(i);

            // update valid window minlen
            while(!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
                min_len = min(min_len, i - dq.front());
                dq.pop_front();
            }
        }

        return min_len == n+1 ? -1 : min_len;
    }
complexity
    O(n) time
    O(n) space

=========================================

Sliding Window Minimum

Given an integer array nums and an integer k, return the minimum 
value in every contiguous window of size k.


brute force:
    enumerate all windows of size k
        track min for each window

observation:
    we can keep a monotonic increasing deque
        to store ans

    once the window is valid
        the deque has the min at the front

    remove from the front to the window as we slide across

    remove dominated elements
    [2,5,6]  3
    3 dominates 6 and 5 as it is smaller than them
        remove these elements

invariant:
    monotonic increasing deque store min elements at the front
    as we pop the next minimum candidate is kept in the deuque
    incoming elements dominate stored larger elements 

algo
    vector<int> slidingmin(vector<int> &nums, int k) {
        vector<int> ans;

        deque<int> dq;

        for(int i=0; i<nums.size(); i++) {

            // remove invalid indices
            while(!dq.empty() && i-k >= dq.front())
                dq.pop_front();

            // remove dominated elements
            while(!dq.empty() && nums[i] <= nums[dq.back()])
                dq.pop_back();

            // push
            dq.push_back(i);

            // valid window
            // store ans
            if(i >= k-1) {
                ans.push_back(nums[dq.front()]);
            }
        }

        return ans;
    }

complexity:
    O(n) time
    O(k) space
=========================================

session 2
    recursion

=========================================

Question 1 — Subset Sum Count

Given an array of positive integers nums and an integer target, 
return the number of subsequences whose sum is exactly target.

A subsequence is formed by choosing or skipping each element while 
preserving order.

nums = [1, 2, 3]
target = 3

Output: 2

nums = [2, 3, 5, 6, 8, 10]
target = 10

Output: 3


brute force
    recursion is the brute force approach 
    optimal is dp for large inputs

    we want to use recursion to check all combinations
    at each idx we either pick or skip
    we subtract from target
    if at any step we get a target of zero
    we have found 1 subsequence

algorithm
    int dfs(int idx, vector<int> &nums, int target) {
        if(target == 0)
            return 1;

        if(idx == nums.size())
            return 0;

        int count = 0;

        // pick
        if(nums[idx] <= target)
            count += dfs(idx+1, nums, target - nums[idx]);

        // skip
        count += dfs(idx+1, nums, target);

        return count;
    }

    int subset_sum_count(vector<int> &nums, int target) {    
        return dfs(0, nums, target);
    }

complexity
    at each step we have 2 choices
    so we have 2^n
    time complexity is 2^n
    and stack space is n
================================================

Question 2 — Recursion: Partition / Backtracking

Given a string s, partition it such that every substring in the 
partition is a palindrome.

Return all possible palindrome partitions.

s = "aab"

[
    ["a","a","b"],
    ["aa","b"]
]

derivation
    we want to select characters in such a way that each partition
    is a palindrome

    so we divide our string into substrings
        we only proceed if the current string
        is a palindrom

    then if we reach the end
        this is a valid selection

at each idx
    we can have a substring of
        idx->n-1
            then recurse

algo
    bool isPalin(string &s, int start, int end) {
        
        while(start < end) {
            if(s[start] != s[end])
                return false;

            start++;
            end--;
        }
        return true;
    }

    void dfs(int idx, string &s, 
            vector<string> &curr, 
            vector<vector<string>> &res) {
        // base cases
        if(idx == s.size()) {
            res.push_back(curr);
            return;
        }            


        for(int i=idx; i<s.size(); i++) {

            if(isPalin(s, idx, i)) {

                string palin = s.substr(idx, i-idx+1);

                curr.push_back(palin);

                dfs(i+1, s, curr, res);

                curr.pop_back();
            }
        }
    }

    vector<vector<string>> palin_part(string &s) {
        vector<vector<string>> res;
        vector<string> curr;
        dfs(0, s, curr, res);
        return res;
    }
complexity:
    time exponential
    space exponential stack space

==========================================

Question 3 — Constraint Backtracking

Given a 9 × 9 Sudoku board, fill the empty cells so that:

Each row contains 1–9 without repetition.
Each column contains 1–9 without repetition.
Each 3 × 3 sub-box contains 1–9 without repetition.

Empty cells are represented by '.'.

Return/modify the board with a valid solution.

Don't code immediately.


we have some rules for sudoku
    we can have repeated digits in the row or col
    we also cant have repeated digits in the 3x3 subgrid 

    lets keep a hashmap to store these
        rowseen
        colseen
        gridseen

    then for each blank spot
        we try to place a digit from 1-9
            recurse
        return if not possible
        try a different digit

complexity:
    if e is empty cells
    9^e time

    

    space 
        9*9*3 space
        stack space?

*/
#include <iostream>
#include <vector>
#include <deque>
using namespace std;


bool backtrack( vector<string> &board,
                vector<vector<bool>> &rowseen,
                vector<vector<bool>> &colseen,
                vector<vector<bool>> &gridseen,
                int remaining ) {

    if(remaining == 0)
        return true;

    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            if(board[i][j] == '.') {


                // try to place a number in this grid
                for(int num=0; num < 9; num++) {                  
                    int grid_idx = (i/3)*3 + j/3;  
                    if(!rowseen[i][num] && !colseen[j][num] && !gridseen[grid_idx][num]) {
                        rowseen[i][num] = true;
                        colseen[j][num] = true;
                        gridseen[grid_idx][num] = true;
                        board[i][j] = (num+1) + '0';

                        if(backtrack(board, rowseen, colseen, gridseen, remaining - 1))
                            return true;

                        rowseen[i][num] = false;
                        colseen[j][num] = false;
                        gridseen[grid_idx][num] = false;
                        board[i][j] = '.';
                    }
                }
                return false; // empty squares but no solution
            }
        }
    }
    return true; // no empty found
}
    

void solve_sudoku(vector<string> &board) {
    vector<vector<bool>> rowseen(9, vector<bool>(9,false));
    vector<vector<bool>> colseen(9, vector<bool>(9,false));
    vector<vector<bool>> gridseen(9, vector<bool>(9,false));
    int remaining = 0;

    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            if(board[i][j] != '.') {
                int num = (board[i][j] - 1) - '0';
                rowseen[i][num] = true;
                colseen[j][num] = true;
                gridseen[(i/3)*3 + (j/3)][num] = true;
            }
            else {
                remaining++;
            }
        }
    }

    backtrack(board, rowseen, colseen, gridseen, remaining);
}

int main() {
    vector<string> board = {
        "53..7....",
        "6..195...",
        ".98....6.",
        "8...6...3",
        "4..8.3..1",
        "7...2...6",
        ".6....28.",
        "...419..5",
        "....8..79"
    };
    solve_sudoku(board);


    return 0;
}