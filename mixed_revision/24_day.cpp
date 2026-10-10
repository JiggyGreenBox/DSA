/*
============================================
oct 9
    last oct 7/8
============================================

Recon → S1 → S2 → S3 → S4 framework we used for Graphs.

============================================
Recursion S1 — Easy → Medium.
============================================

S1 — Problem 1 of 3

Pow(x, n)
we have 2 approaches here
    we can have a recursive approach or a iterative one

    the basic property we are using is:
        x^4 = x^2 * x^2
        = (x*x)^2

        or
        x^3 = x*x^2

        so we peel off 1 x if odd
        or we tackle the exponent in halves
            even
            x^n = (x*x)^n/2

            odd
            x^n = x*x^n-1

    double myPow(double x, long long n) {
        if(n == 0)
            return 1.0;

        if(n < 0)
            return (1.0 / myPow(x, -n)); // overflow?

        double half = myPow(x, n/2);

        if(n & 1)
            return x * half * half;

        return half * half;
    }


    double myPow2(double x, int n) {
        long long N = n;

        if(N < 0) {
            x = 1/x;
            N = -n;
        }

        double ans = 1.0;
        while(N) {
            if(N & 1) {
                ans *= x;
            }

            x *= x;

            N >>= 1; // divide by 2
        }
        return ans;
    }


complexity
    recursive
        time logn
        space logn stack space

    iterative
        log n time
        1 space


============================================
S1 — Problem 2 of 3

Next, let's test a different recursive structure from your sheet: 
02_take_dont_take/02_powerSet.cpp.
Given an array of distinct integers, return all possible subsets (the 
power set). The order of the subsets does not matter.

for each idx we can either take it or skip it
    then we move forward
    
code
    void helper(int idx, 
        vector<int> &nums, 
        vector<int> &curr, 
        vector<vector<int>> &res) {
        
        res.push_back(curr);

        for(int i=idx; i<nums.size(); i++) {
            curr.push_back(nums[i]);
            helper(i+1, nums, curr, res);
            curr.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int> &nums) {
        vector<int> curr;
        vector<vector<int>> res;
        helper(0, nums, curr, res);
        return res;
    }


complexity:
    2^n choices
    copy at each call O(n)
    time O(n*2^n)

    space
        rec stack O(n)
        O(n) for curr
        O(n*2^n) for res

============================================
Problem: Combination Sum II
Given an array of positive integers candidates and a target integer 
target, return all unique combinations whose elements sum to target.
Each element in candidates may be used at most once. The input may 
contain duplicates, but the output must not contain duplicate 
combinations.


approach
    here we want subsequences whose sum is equal to the target

    we might have duplicates in the input
    so we have to handle that

    we sort to keep duplicated next to each other
    then at each recursion level, we dont allow duplicates

complexity:
    2^n choices pick/skip
    n copy at each iter

    time
        n*2^n

    space
        stack n
        curr n
        output space n*2^n


void helper(int idx, 
    vector<int> &nums, 
    int target, 
    vector<int> &curr, 
    vector<vector<int>> &res) {


    if(target == 0) {        
        res.push_back(curr);        
        return;
    }

    for(int i=idx; i<nums.size(); i++) {

        if(i>idx && nums[i] == nums[i-1])
            continue;

        if(nums[i] > target)
            continue;

        curr.push_back(nums[i]);
        helper(i+1, nums, target - nums[i], curr, res);
        curr.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int> &nums, int target) {

    if(nums.empty())
        return {};

    sort(nums.begin(), nums.end());

    if(nums[0] > target)
        return {}; // assuming positives

    vector<vector<int>> res;
    vector<int> curr;
    helper(0, nums, target, curr, res);
    return res;
}

============================================
Recursion S2 — Medium.
============================================

Permutations II
Medium

From your sheet: 03_choose_unchoose/08_permutations_ii.cpp
Given an integer array nums that may contain duplicates, return all 
unique permutations in any order.

Input:  [1,1,2]

Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]

Explain your reasoning before coding:
1. What state represents a partial permutation?
    we need to use all elements in the vector in some order
2. How do you know which elements are still available?
    we use a used vector to know which was used
3. How will you avoid duplicate permutations when values repeat?
    
    if we enter the recursion and [1,1,2]
        then at the same level we see 1,1
        usually the rec is
            if not used
                use
                backtrack
                unuse

            so for the second 1 if unused, then
                siblings at same level, skip

4. What are the time and space complexities?
    possible answers n!
    at each step
        we copy so
            n*n!

    recursive stack space is n

code
    void helper(
        vector<int> &nums,
        vector<bool> &used, 
        vector<int> &curr, 
        vector<vector<int>> &res) {

        if(curr.size() == nums.size()) {
            res.push_back(curr);
            return;
        }

        for(int i=0; i<nums.size(); i++) {
            if(used[i])
                continue;

            if(i>0 && nums[i] == nums[i-1] && !used[i-1])
                continue; // used at same level before

            used[i] = true;
            curr.push_back(nums[i]);
            helper(nums, used, curr, res);
            curr.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        vector<int> curr;
        vector<vector<int>> res;
        vector<bool> used(nums.size(), false);
        helper(nums, used, curr, res);
        return res;
    }

============================================

S2 — Problem 2 of 3
Next, let's use another problem from your sheet: 
04_partition/14_restore_ip_addresses.cpp.


time complexity
    3^4 time

    space
        n rec stack
        O(4) chunks
        O(3^4) result


bool isValid(string &s, int start, int end){
    
    int len = end-start+1;

    if(len > 3)
        return false;

    if(len > 1 && s[start] == '0')
        return false;

    int num = stoi(s.substr(start, len));

    return num <= 255;
}

void helper(int idx, 
    vector<string> &chunks,
    string &s, 
    vector<string> &res) {
    
    // exit condition
    if(idx == s.size()) {

        if(chunks.size() != 4)
            return;

        string ip = chunks[0] + '.' + 
                    chunks[1] + '.' + 
                    chunks[2] + '.' + 
                    chunks[3];

        res.push_back(ip);
        return;
    }

    // for(int i=idx; i<s.size(); i++) {
    for (int i = idx; i < min((int)s.size(), idx + 3); i++) {
        if(isValid(s, idx, i)) {
            chunks.push_back(s.substr(idx, i-idx+1));
            helper(i+1, chunks, s, res);
            chunks.pop_back();
        }
    }
}

vector<string> restoreIpAddresses(string s) {

    if (s.size() < 4 || s.size() > 12)
        return {};

    vector<string> chunks;
    vector<string> res;
    helper(0, chunks, s, res);
    return res;
}

============================================

Expression Add Operators


for this problem we need to know how operator preference workks
    2 + 3 * 4
        is 2 + 12 = 14

    if we go in a linear fashion,
        then we have 2 + 3 = 5
            but to have * 4
                we need to have 5-3 + 3*4 = 2 + 12 = 14

        mulitplication means we must be able to undo the previous operation
            2 + 3, then curr = 5, curr - prev = 5-3 = 2
            3 - 1, then curr = 2, curr - prev = 2 - (-1) = 3

            2+3*4, curr = 14, prev = 12, we want to go back to before mulitplication
                here prev is 3*4

State: What information must each recursive call carry?
    we must have curr and prev

Choices: How do you decide the next number, and which operators can 
precede it?
    for the first number we do nothing, for every next digit
        we try - + *

    we also try number combinations
        123
            1...23
                ops
            12...3
                ops
            123
                if == s.size
                    return


Precedence: How will you handle multiplication taking precedence over 
addition and subtraction, without evaluating the entire expression 
from scratch?

Leading zeros: How will you prevent "05" from being treated as a 
valid number?
    when making substrings
        if s[start] = 0
            dont proceed


complexity
    we have n-1 gaps
        and 4 choices at each gap

    4^n-1
    we do n work at each step
        n*4^n-1

    space
        stack n
        expr n
        res 4^n-1
*/
#include <bits/stdc++.h>
using namespace std;

void helper(int idx, 
    string &expr, 
    string &num, 
    int target,
    int curr,
    int prev, 
    vector<string> &res) {

    // exit
    if(idx == num.size()) {
        if(curr == target)
            res.push_back(expr);

        return;
    }

    for(int i=idx; i<num.size(); i++) {
        // first number of the expression

        if(i>idx && num[idx] == '0')
            break;; // no leading zeros

        string str = num.substr(idx, i-idx+1);

        // if(str.size() > 1 && str[0] == '0')
        //     continue;

        int val = stoi(str);
        int old_size = expr.size();
        
        if(idx == 0) {
            expr += str;
            helper(i+1, expr, num, target, val, val, res);
            expr.resize(old_size);
        }
        else {
            // +
            expr += "+" + str;
            helper(i+1, expr, num, target, curr + val, val, res);
            expr.resize(old_size);

            // -
            expr += "-" + str;
            helper(i+1, expr, num, target, curr - val, -val, res);
            expr.resize(old_size);

            // *
            expr += "*" + str;
            helper(i+1, expr, num, target, curr - prev + prev * val, prev * val, res);
            expr.resize(old_size);
        }
    }
}

vector<string> exprOperators(string &num, int target) {
    string expr;
    vector<string> res;
    helper(0, expr, num, target, 0, 0, res);
    return res;
}


int main() {
    string num = "105";
    int target = 5;
    auto x = exprOperators(num, target);

    return 0;
}