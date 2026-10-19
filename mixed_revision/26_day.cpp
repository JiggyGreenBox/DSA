/*
============================================
oct 10
    last oct 9
============================================
Recursion S4 — Hard / Transfer.
============================================

S4 — Problem 1 of 3
From your sheet: 08_state_based/29_generateParenthesis.cpp · 
Transfer challenge

Given an integer n, generate all strings containing exactly n pairs 
of parentheses that are balanced and have exactly n pairs, with the 
additional constraint that the maximum nesting depth is exactly k.

For example, with n = 3 and k = 2, valid answers include:
- "(())()" — maximum depth 2
- "()(())" — maximum depth 2
But exclude:
- "((()))" — maximum depth 3
- "()()()" — maximum depth 1
Assume 1 <= k <= n

Your task:
    1. Explain the recursive state you would maintain.
    2. State the choices and pruning conditions.
    3. Explain how you ensure the maximum depth is exactly k, not merely 
    at most k.
    4. Write the C++ implementation.

*/

/*
lets first generate all parenthesis

void helper(
    int depth,
    int max_depth,
    int k,
    int open, 
    int close,     
    string &curr, 
    vector<string> &res) {

    if(open == 0 && close == 0) {        
        if(max_depth == k)
            res.push_back(curr);
        return;
    }    

    // at each char pos    
    if(open > 0) {        
        curr.push_back('(');
        helper(depth+1, max(max_depth, depth+1), k, open-1, close, curr, res);
        curr.pop_back();
    }

    if(close > open) {
        curr.push_back(')');        
        helper(depth-1, max(max_depth, depth-1), k, open, close-1, curr, res);
        curr.pop_back();
    }
}

vector<string> gen(int n, int k) {
    string curr;
    vector<string> res;    
    helper(0, 0, k, n, n, curr, res);
    return res;
}

int main() {
    auto x = gen(3, 2);
    return 0;
}

=====================================

You are given:
- words: an array of strings.
- letters: a collection of available letters, where each letter can 
be used only as many times as it appears.
- score: an array of 26 integers, where score[i] is the score for 
letter 'a' + i.

Return the maximum total score obtainable by choosing any subset of 
words, subject to the constraint that the chosen words can be formed 
using the available letters. Each chosen word contributes the sum of 
the scores of its letters.

Example

words = ["dog", "cat", "dad", "good"]
letters = ["a","a","c","d","d","d","g","o","o"]
score = [1,0,9,5,0,0,3,0,0,0,0,0,0,
         0,2,0,0,0,0,0,0,0,0,0,0,0]


The answer is 23, obtained by choosing "dad" and "good".

*/

/*

we have words as possible take / skip
    for a max score

        we may or may not be able to take the words
        because it depends on letters available

        if we can take it
        we get a score

        we want max score


for each word
    pick / skip

    track max_score


how to pick
    mpp<char, int>
    for each char in word
        
        if mpp[char] > 0
            --
        else
            false

    if not false
        calculate score
            try next word

    // revert for next pass

void helper(int idx, 
    int curr_score,
    int &max_score, 
    vector<string> &words, 
    unordered_map<char, int> &mpp, 
    vector<int> &score) {

    if(idx == words.size()) {
        max_score = max(max_score, curr_score);
        return;
    }
        

    // skip
    helper(idx+1, curr_score, max_score, words, mpp, score);

    // pick
    unordered_map<char, int> need;
    bool can_pick = true;
    int word_score = 0;

    for(char c : words[idx]) {
        need[c]++;
        word_score += score[c-'a'];
    }

    
    for(auto &[c,count] : need) {
        if(mpp[c] < count) {
            can_pick = false;
            break;
        }
    }

    if(!can_pick)
        return;

    for(auto &[c,count] : need) {
        mpp[c] -= count;
    }

    helper(idx+1, curr_score + word_score, max_score, words, mpp, score);

    for(auto &[c,count] : need) {
        mpp[c] += count;
    }
}

int getMaxScore(
    vector<string> &words,
    vector<char> &letters,
    vector<int> &score) {
    
    int max_score = 0;
    unordered_map<char, int> mpp;

    for(char c : letters) {
        mpp[c]++;
    }
    helper(0, 0, max_score, words, mpp, score);

    return max_score;
}

int main() {

    vector<string> words = {"dog", "cat", "dad", "good"};
    vector<char> letters = {'a','a','c','d','d','d','g','o','o'};
    vector<int> score = {1,0,9,5,0,0,3,0,0,0,0,0,0,
            0,2,0,0,0,0,0,0,0,0,0,0,0};

    auto x = getMaxScore(words, letters, score);

    return 0;
}

===================================================================

Problem 3 — Matchsticks to Square

From your sheet: 07_bucket_assignment/26_matchsticks_to_square.cpp · 
LeetCode 473

    You are given an integer array matchsticks, where matchsticks[i] is 
    the length of a matchstick. You want to use all the matchsticks 
    exactly once to form a square.
    You cannot break any matchstick, and every matchstick must belong to 
    exactly one of the four sides.
    Return true if you can form a square, otherwise return false.

Example 1
    matchsticks = [1, 1, 2, 2, 2]
    Output: true


    The four sides can each have length 2.
Example 2
    matchsticks = [3, 3, 3, 3, 4]
    Output: false


Your task
    Try to derive the solution yourself before coding.
    1. What is the necessary condition on the sum of all matchstick 
    lengths?
    2. What should the recursive state represent: the current index, four 
    side lengths, or something else?
    3. What choices do you make for each matchstick, and how do you avoid 
    exploring equivalent arrangements unnecessarily?
    4. Write the C++ implementation and explain its complexity.

*/

/*

we need to divide the given matchsticks into 4 equal parts
such that they form a square

we can make 4 buckets and try to distribute them
the target for each bucket is total/4

we need to carry the current bucket sum and remaining target

at each idx we can put them in any of the 4 buckets

4^n choices exist
    time 4^n

space O(n) for buckets

*/
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>
using namespace std;

bool helper(int idx, 
    vector<int> &buckets, 
    int target, 
    vector<int> &matchsticks) {

    // exit condition
    if(idx == matchsticks.size()) {
        return true;
    }

    int num = matchsticks[idx];

    // if(num > target)
    //     return false;

    for(int b=0; b<4; b++) {
        if(buckets[b] + num > target)
            continue;

        buckets[b] += num;

        if(helper(idx+1, buckets, target, matchsticks))
            return true;

        buckets[b] -= num;
    }
    return false;
}

bool possible(vector<int> &matchsticks) {
    int total = accumulate(matchsticks.begin(), matchsticks.end(), 0);

    if(total % 4 != 0)
        return false;

    int target = total / 4;
    vector<int> buckets(4);

    
    sort(matchsticks.begin(), matchsticks.end(), greater<int>());

    return helper(0, buckets, target, matchsticks);
}

int main() {
    vector<int> matchsticks = {1, 1, 2, 2, 2};
    matchsticks = {3, 3, 3, 3, 4};
    auto x = possible(matchsticks);
    return 0;
}