#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
Reorganize String
    [https://leetcode.com/problems/reorganize-string/description/]


Given a string s, rearrange the characters of s so that any two 
adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

 

Example 1:

Input: s = "aab"
Output: "aba"
Example 2:

Input: s = "aaab"
Output: ""


is this similar to task scheduler

we look for highest frequency
    gap is now 1 char

    essentially all chars will be 1 char apart
    edge case is having mulitple chars with same max freq
*/

#include <queue>

string reorganizeString(string s) {

    unordered_map<char, int> freq;

    for (char c : s)
        freq[c]++;

    priority_queue<pair<int, char>> pq;

    for (auto &[c, count] : freq)
        pq.push({count, c});

    string ans;

    pair<int, char> prev = {0, '#'};

    while (!pq.empty()) {

        auto [count, c] = pq.top();
        pq.pop();

        ans.push_back(c);
        count--;

        // Previous character becomes available again
        if (prev.first > 0)
            pq.push(prev);

        // Hold current character out of heap
        prev = {count, c};
    }

    if (ans.size() != s.size())
        return "";

    return ans;
}

int main() {
    return 0;
}