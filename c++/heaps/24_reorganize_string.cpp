/*
reorganize_string
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

*/


/*
hint from gpt

    we can use char frequency 
    to rearrange

    if we had max heap and we use the max freq
        dont push back into the heap imm
    that way we can alternate
*/ 


#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

string reorganizeString(string s) {
    unordered_map<char, int> freq;
    for(char c : s)
        freq[c]++;

    priority_queue<pair<int, char>> pq;

    for(auto &[c, count] : freq) {
        pq.push({count, c});
    }

    string ans="";

    char prev = pq.top().second;

    while(!pq.empty()) {
        auto [count, c] = pq.top();
        pq.pop();

        if(count == 0)
            continue;

        freq[c]--;
        ans.push_back(c);

        if(c != prev) {
            pq.push({freq[prev], prev});
            prev = c;
        }
    }
    return ans.size() == s.size() ? ans : "";
}

string canon(string s) {
    unordered_map<char, int> freq;
    for(char c : s)
        freq[c]++;

    priority_queue<pair<int, char>> pq;

    for(auto &[c, count] : freq) {
        pq.push({count, c});
    }

    string ans="";

    pair<int, char> prev = {0, '#'};

    while(!pq.empty()) {

        auto [count, c] = pq.top();
        pq.pop();

        
        ans.push_back(c);
        count--;

        // basically skip first
        // then avoid 0 count
        // so give it 0 count for first pass        
        if(prev.first > 0)
            pq.push(prev);
        
        // store current as prev
        prev = {count, c};
    }
    return ans.size() == s.size() ? ans : "";
}

int main() {
    string s = "aab";
    cout << reorganizeString(s) << endl;
    s = "aaab";
    cout << reorganizeString(s) << endl;
    return 0;
}