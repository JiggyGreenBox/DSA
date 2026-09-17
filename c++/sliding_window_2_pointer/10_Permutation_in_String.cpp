/*
Permutation_in_String
    [https://leetcode.com/problems/permutation-in-string/description/]

Given two strings s1 and s2, return true if s2 contains a permutation 
of s1, or false otherwise.

In other words, return true if one of s1's permutations is the 
substring of s2.

 

Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input: s1 = "ab", s2 = "eidboaoo"
Output: false

*/

/*
slide a window of size s1 over s2
    if count of chars matches
        return true
    else 
        return false

*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// O(|s1| + |s2|) time
// O(1) space
bool checkInclusion(string s1, string s2) {

    // use a similar approach to remaining and count
    vector<int> count(26, 0);

    for(char c : s1)
        count[c - 'a']++;

    int remaining = s1.size();
    int k = s1.size();

    // first window
    for(int i=0; i<k; i++) {
        int c = s2[i] - 'a';

        if(count[c] > 0)
            remaining--;
        
        count[c]--;
    }

    if(remaining == 0)
        return true;

    for(int right = k; right<s2.size(); right++) {

        int out = s2[right-k] - 'a';
        int in = s2[right] - 'a';

        if(count[out] == 0)
            remaining++;

        count[out]++;

        if(count[in] > 0)
            remaining--;

        count[in]--;

        if(remaining == 0)
            return true;
    }
    return false;
}

int main() {
    string s1 = "ab"; string s2 = "eidbaooo";
    auto x1 = checkInclusion(s1, s2);

    s1 = "ab"; s2 = "eidboaoo";
    auto x = checkInclusion(s1, s2);
    return 0;
}