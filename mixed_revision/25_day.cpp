/*
============================================
oct 10
    last oct 9
============================================

S3 — Problem 1 of 3

Remove Invalid Parentheses
Medium+

From your sheet: 04_partition/17_remove_invalid_parentheses.cpp
Given a string s containing parentheses and lowercase English 
letters, remove the minimum number of parentheses so that the 
resulting string is valid.
Return all possible results. The order of the results does not matter.
Example 1
Input:  "()())()"
Output: ["(())()", "()()()"]

Input:  "(a)())()"
Output: ["(a())()", "(a)()()"]


derivation
    we need to remove invalid parenthesis to make a valid string
    we could try to pick/ skip every parenthesis
        2^n
    
    but it is better to find imbalanced parenthesis first
        then its 2^unbalanced choices

    for now my approach to duplicates is to use a set

complexity
    2^unbalance choices
    n copies at each step

    n2^un

    space
        stack O(n)
        curr n
        res 2^n
        
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void helper(int idx, 
        string &input, 
        string &curr, 
        int left_rem, 
        int right_rem, 
        int balance, 
        unordered_set<string> &res) {

    if(balance < 0)
        return;

    // exit condition
    if(idx == input.size()) {

        if( left_rem == 0 && 
            right_rem == 0 && 
            balance == 0
        ) {            
            res.insert(curr);
        }
        return;
    }

    char c = input[idx];

    if(c == '(') {

        if(left_rem > 0) {
            // skip
            helper(idx+1, input, curr, left_rem-1, right_rem, balance, res);
        }

        // pick
        curr.push_back(c);
        helper(idx+1, input, curr, left_rem, right_rem, balance + 1, res);
        curr.pop_back();
    }
    else if(c == ')') {        

        if(right_rem > 0) {
            // skip
            helper(idx+1, input, curr, left_rem, right_rem-1, balance, res);
        }

        // pick
        curr.push_back(c);
        helper(idx+1, input, curr, left_rem, right_rem, balance - 1, res);
        curr.pop_back();
    }
    else {

        curr.push_back(c);
        helper(idx+1, input, curr, left_rem, right_rem, balance, res);
        curr.pop_back();
    }
}

vector<string> removeInvalid(string &input) {
    string curr;
    unordered_set<string> res;

    int balance = 0;
    int left_rem = 0;
    int right_rem = 0;
    for(char c : input) {
        if(c == '(') {
            balance++;
        }
        else if(c == ')') {
            if(balance > 0)
                balance--;
            else
                right_rem++;
        }
    }
    left_rem = balance;

    helper(0, input, curr, left_rem, right_rem, 0, res); // reset balance

    vector<string> ans(res.begin(), res.end());
    return ans;
}


int main() {
    string input = "(a)())()";
    auto x = removeInvalid(input);
    return 0;
}

