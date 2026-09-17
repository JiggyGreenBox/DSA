/*
Find_All_Anagrams_in_a_String
    [https://leetcode.com/problems/find-all-anagrams-in-a-string/description/]

Given two strings s and p, return an array of all the start indices 
of p's anagrams in s. You may return the answer in any order.

 

Example 1:

Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of 
"abc".
The substring with start index = 6 is "bac", which is an anagram of 
"abc".
Example 2:

Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of 
"ab".
The substring with start index = 1 is "ba", which is an anagram of 
"ab".
The substring with start index = 2 is "ab", which is an anagram of 
"ab".


*/
#include <vector>
#include <string>
using namespace std;
vector<int> findAnagrams(string s, string p) {

    vector<int> count(26, 0);

    vector<int> ans;

    for(char c : p)
        count[c - 'a']++;

    int remaining = p.size();
    int k = p.size();

    for(int i=0; i<k; i++) {
        int c = s[i] - 'a';

        if(count[c] > 0)
            remaining--;

        count[c]--;
    }

    if(remaining == 0)  
        ans.push_back(0);

    for(int right = k; right < s.size(); right++) {
        int out = s[right-k] - 'a';
        int in = s[right] - 'a';

        if(count[out] == 0)
            remaining++;
        count[out]++;

        if(count[in] > 0)
            remaining--;
        count[in]--;

        if(remaining == 0) {
            ans.push_back(right - k + 1);
        }
        // [abc] right=2-k+1
        // [012]
    }
    return ans;
}

vector<int> findAnagrams2(const string& s, const string& p) {
    vector<int> count(26, 0);

    for (char c : p)
        count[c - 'a']++;

    int remaining = p.size();
    int k = p.size();

    vector<int> ans;

    for (int right = 0; right < s.size(); right++) {
        int in = s[right] - 'a';

        if (count[in] > 0)
            remaining--;

        count[in]--;

        if (right >= k) {
            int out = s[right - k] - 'a';

            if (count[out] >= 0)
                remaining++;

            count[out]++;
        }

        if (remaining == 0)
            ans.push_back(right - k + 1);
    }

    return ans;
}

int main() {
    string s = "cbaebabacd";
    string  p = "abc";
    auto x1 = findAnagrams(s, p);
    int x = 5;

    s = "abab"; p = "ab";
    auto x2 = findAnagrams(s, p); // Output: [0,1,2]
    int y = 5;
    return 0;
}