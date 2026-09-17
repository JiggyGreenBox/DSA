/*
Maximum Number of Vowels in a Substring of Given Length
    [https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/description/]

Given a string s and an integer k, return the maximum number of vowel 
letters in any substring of s with length k.

Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.

 

Example 1:

Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.
Example 2:

Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.
Example 3:

Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.


    
*/

#include <iostream>
#include <vector>
using namespace std;
int maxVowels(string s, int k) {

    vector<int> vows(26, 0);
    vows['a' - 'a'] = 1;
    vows['e' - 'a'] = 1;
    vows['i' - 'a'] = 1;
    vows['o' - 'a'] = 1;
    vows['u' - 'a'] = 1;

    int n = s.size();
    int max_count = 0;
    int count = 0;

    for(int i=0; i<k; i++) {
        if(vows[s[i] - 'a'] > 0)
            count++;
    }
    max_count = count;

    for(int i=k; i<n; i++) {
        if(vows[s[i-k] - 'a'] > 0)
            count--;

        if(vows[s[i] - 'a'] > 0)
            count++;

        max_count = max(max_count, count);
    }
    return max_count;
}

int maxVowels2(const string& s, int k) {
    auto is_vowel = [](char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };

    int count = 0;

    // Build first window.
    for (int i = 0; i < k; i++)
        count += is_vowel(s[i]);

    int max_count = count;

    // Slide the window.
    for (int i = k; i < s.size(); i++) {
        count -= is_vowel(s[i - k]); // outgoing
        count += is_vowel(s[i]);     // incoming

        max_count = max(max_count, count);
    }

    return max_count;
}

int main() {
    string s = "abciiidef";
    int k = 3;
    cout << maxVowels(s, k) << endl;

    s = "aeiou"; k = 2;
    cout << maxVowels(s, k) << endl;

    s = "leetcode"; k = 3;
    cout << maxVowels(s, k) << endl;
    return 0;
}