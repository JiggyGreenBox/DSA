/*
Remove Invalid Parentheses
    [https://leetcode.com/problems/remove-invalid-parentheses/description/]

Given a string s that contains parentheses and letters, remove the 
minimum number of invalid parentheses to make the input string valid.

Return a list of unique strings that are valid with the minimum 
number of removals. You may return the answer in any order.

 

Example 1:

Input: s = "()())()"
Output: ["(())()","()()()"]
Example 2:

Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]
Example 3:

Input: s = ")("
Output: [""]

*/

/*
observation
    original idea was to pick and skip for each bracket
    
    instead we find the imbalance of brackets
    and then we start with those characters

    also )( is not balanced
-------
    left_remove  [(]
    right_remove [)]

    for char c : str
        if c == (
            balance++

        else if c == (
            if balance > 0
                balance--
            else
                right_remove++

        left_remove = balance

-------
    for every bracket:
        keep it
        remove it

    this is 2^n

    ()())()
        only need to consider ) and no (
            and exactly 1 )

        at each )
            keep
            remove  ← only if right_remove > 0

-------
    For '(':

        KEEP:
            curr += '('
            balance++

        REMOVE:
            only if left_remove > 0
            left_remove--


    For ')':

        KEEP:
            curr += ')'
            balance--

        REMOVE:
            only if right_remove > 0
            right_remove--
-------

    be mindful of duplicates for skip
    (()
        ()

    (a()
        a(), (a)

    for now use a set/unordered_set
-------
    what about pruning
        we use balance       [(] +1 , [)] -1
            if negative 
                break/return
            
------
    state required
        idx, 
        string s,
        curr,
        ans,

        balance,
        left_removals,
        right_removals        
------
    balance
    left_remove
    right_remove

        why 3 vars
    balance 
        tells us about the curr substring

    left,right are for future number of decisions
*/

#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

void backtrack(
    int idx,
    string &s,
    string &curr,
    unordered_set<string> &res,
    int left_remove,
    int right_remove,
    int balance
) {

    // invalid prefix
    if(balance < 0)
        return;

    // every idx processed
    if(idx == s.size()) {
        if(left_remove == 0 && 
            right_remove == 0 &&
            balance == 0)
        {
            res.insert(curr);
        }        
        return;
    }

    

    char c = s[idx];

    if(c == '(') {
        // keep
        curr.push_back(c);
        backtrack(idx + 1, s, curr, res, left_remove, right_remove, balance + 1);
        curr.pop_back();

        // skip        
        if(left_remove > 0)            
            backtrack(idx + 1, s, curr, res, left_remove-1, right_remove, balance); // doesnt change balance
    }
    else if(c == ')') {
        // keep
        curr.push_back(c);
        backtrack(idx + 1, s, curr, res, left_remove, right_remove, balance - 1);
        curr.pop_back();

        // skip
        if(right_remove > 0)            
            backtrack(idx + 1, s, curr, res, left_remove, right_remove-1, balance); // doesnt change balance
    }
    else {
        // keep
        curr.push_back(c);
        backtrack(idx + 1, s, curr, res, left_remove, right_remove, balance);
        curr.pop_back();
    }
}

vector<string> removeInvalidParentheses(string s) {
    int left_remove = 0;
    int right_remove = 0;
    int balance = 0;

    for(char c : s) {
        if( c == '(') {
            balance++;
        }
        else if( c == ')') {
            if(balance > 0)
                balance--;
            else
                right_remove++;
        }
    }
    left_remove = balance; // unbalanced (

    string curr;
    unordered_set<string> res;
    // backtrack(0, s, curr, res, left_remove, right_remove, balance); WRONG
    
     // IMPORTANT: curr is empty → balance starts at 0
    backtrack(0, s, curr, res, left_remove, right_remove, 0); // intial balance is zero

    vector<string> ans(res.begin(), res.end());
    return ans;
}

int main() {
    string s = "()())()"; // ["(())()","()()()"]
    auto x = removeInvalidParentheses(s);

    s = "(a)())()"; // ["(a())()","(a)()()"]
    x = removeInvalidParentheses(s);
    return 0;
}