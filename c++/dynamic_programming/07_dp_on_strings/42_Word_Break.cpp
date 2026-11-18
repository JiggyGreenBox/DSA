/*
Word_Break
    [https://takeuforward.org/practice/dsa/word-break?category=dp-on-strings&source=strivers-a2z-dsa-sheet]

Given a string s and a dictionary of strings wordDict, return true if 
s can be segmented into a space-separated sequence of one or more 
dictionary words otherwise return false.

Note : The same word in dictionary can be used multiple times in 
segmentation.

Example 1:
Input : s = "takeuforward" , wordDict = ["take" , "forward" , "you", 
"u"]

Output : true

Explanation : Return true because "takeuforward" can be segmented as 
"take" , "u" , "forward".

Example 2:
Input : s = "applepineapple" , wordDict = ["apple"]

Output : false

Explanation : Return false because "applepineapple" can be segmented 
as "apple" , "pine" , "apple" but here we do not have "pine" word in 
dictionary.

*/

/*

can we form any word from l onwards, using wordlist

f(idx)

    if(idx==end)
        return true

    can we form words from the wordList 
    using string idx onwards

    for(i in [idx, n-1])
        if substr(idx,i) in wordList
            if(f(i+1))
                return true

    return false

*/

#include <string>
#include <vector>
#include <assert.h>
#include <unordered_set>
using namespace std;



bool f(int i, string &s, unordered_set<string> &wordDict) {
    int n = s.size();

    if(i == n)
        return true;

    for(int j=i; j<n; j++) {
        if(wordDict.count(s.substr(i, j-i+1))) {
            if(f(j+1, s, wordDict))
                return true;
        }
    }
    return false;
}

bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> words(wordDict.begin(), wordDict.end());
    return f(0, s, words);
}

// 
bool memo(int i, string &s, unordered_set<string> &wordDict, vector<int> &dp) {
    int n = s.size();

    if(i == n)
        return true;
    
    if(dp[i] != -1)
        return dp[i];

    for(int j=i; j<n; j++) {
        if(wordDict.count(s.substr(i, j-i+1))) {
            if(memo(j+1, s, wordDict, dp))
                return dp[i] = true;
        }
    }
    return dp[i] = false;
}

// n states
// but n scans might be required at each state
// and substring takes O(n) time
// n^3 time
// n stack space
// n dp vector space
bool wordBreak2(string s, vector<string>& wordDict) {
    unordered_set<string> words(wordDict.begin(), wordDict.end());
    int n = s.size();
    vector<int> dp(n, -1);
    return memo(0, s, words, dp);
}

/*
tabulation
    at each idx we check till the end if any

    takeuforwa r d 
    01234567891011

    we start at idx 12 = T
    i goes backwards
        then j goes from i to end
    at i=5
        at j==11, we have forward
    
    but we need the true value to move backwards
        dp[i] = true if dp[j+1] = true
                            , dp[12] = T
    
    at s[i] = u
        dp[j] = T if dp[j+1] = T, (forward)

    at dp[0]
        take, checks
            dp[j+1] = u/true


n^3 time
n space
1 stack
*/
bool wordBreak3(string s, vector<string>& wordDict) {
    unordered_set<string> words(wordDict.begin(), wordDict.end());
    int n = s.size();
    vector<bool> dp(n+1, false);
    dp[n] = true;
    
    // flip the loop of recursion
    for(int i=n-1; i>=0; i--) {
        for(int j=i; j<n; j++) {
            string word = s.substr(i, j-i+1);
            // at
            if(words.count(word) > 0 && dp[j+1]) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[0];
}

int main() {

    string s = "takeuforward";
    vector<string> wordDict = {"take" , "forward" , "you", "u"};
    assert(wordBreak(s, wordDict) == true);
    assert(wordBreak2(s, wordDict) == true);
    auto x = wordBreak3(s, wordDict);

    s = "applepineapple";
    wordDict = {"apple"};
    assert(wordBreak(s, wordDict) == false);
    assert(wordBreak2(s, wordDict) == false);
    x = wordBreak3(s, wordDict);

    return 0;
}