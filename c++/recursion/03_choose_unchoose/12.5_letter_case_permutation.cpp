/*

LC 784
Letter Case Permutation
    [https://leetcode.com/problems/letter-case-permutation/description/]

Given a string s, you can transform every letter individually to be 
lowercase or uppercase to create another string.

Return a list of all possible strings we could create. Return the 
output in any order.

 

Example 1:

Input: s = "a1b2"
Output: ["a1b2","a1B2","A1b2","A1B2"]
Example 2:

Input: s = "3z4"
Output: ["3z4","3Z4"]
 

*/

/*
for a string
    every char can be toggled

    we have n! permutations for a string
        where n are upper/lower chars

    
    in a loop
    
    for each char
        if number
            continue

        if not used
            toggle
                backtrack

        untoggle


    when idx == end
        push curr into ans
        
*/

/*
if (ch >= 'a' && ch <= 'z') {
    std::cout << "It is lowercase.\n";
} 
else if (ch >= 'A' && ch <= 'Z') {
    std::cout << "It is uppercase.\n";
} 
*/

#include <vector>
#include <string>
#include <cctype> // isdigit, toupper, tolower
using namespace std;

void backtrack(int idx, string& s, vector<string>& ans) {
    if (idx == s.size()) {
        ans.push_back(s);
        return;
    }

    // If it's a digit, only one choice
    if (isdigit(s[idx])) {
        backtrack(idx + 1, s, ans);
        return;
    }

    // lowercase
    s[idx] = tolower(s[idx]);
    backtrack(idx + 1, s, ans);

    // uppercase
    s[idx] = toupper(s[idx]);
    backtrack(idx + 1, s, ans);
}

vector<string> letterCasePermutation(string s) {
    vector<string> ans;
    backtrack(0, s, ans);
    return ans;
}

int main() {
    string s = "a1b2";
    auto x = letterCasePermutation(s);

    s = "3z4";
    x = letterCasePermutation(s);
    return 0;
}