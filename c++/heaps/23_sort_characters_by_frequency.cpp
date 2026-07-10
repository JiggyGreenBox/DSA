/*
Sort Characters By Frequency
    [https://leetcode.com/problems/sort-characters-by-frequency/description/]

Given a string s, sort it in decreasing order based on the frequency 
of the characters. The frequency of a character is the number of 
times it appears in the string.

Return the sorted string. If there are multiple answers, return any 
of them.

 

Example 1:

    Input: s = "tree"
    Output: "eert"
    Explanation: 'e' appears twice while 'r' and 't' both appear once.
    So 'e' must appear before both 'r' and 't'. 
    Therefore "eetr" is also a valid answer.

Example 2:

    Input: s = "cccaaa"
    Output: "aaaccc"
    Explanation: Both 'c' and 'a' appear three times, so both 
    "cccaaa" and "aaaccc" are valid answers.
    Note that "cacaca" is incorrect, as the same characters must be 
    together.

Example 3:

    Input: s = "Aabb"
    Output: "bbAa"
    Explanation: "bbaA" is also a valid answer, but "Aabb" is  incorrect.
    Note that 'A' and 'a' are treated as two different characters.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/*
can we use a map
    but then we would have to reverse it

    heap and pop back into string
*/


string frequencySort(string s) {
    string ans;
    unordered_map<char, int> freq;

    for(char c : s) {
        freq[c]++;
    }

    priority_queue<pair<int, char>> pq;

    for(auto &[c, count] : freq) {
        pq.push({count, c});
    }

    while(!pq.empty()) {
        for(int i=0;i<pq.top().first; i++) 
            ans.push_back(pq.top().second);
        pq.pop();
    }

    return ans;
}

int main() {
    string s = "tree";
    cout << frequencySort(s) << endl;
    s = "cccaaa";
    cout << frequencySort(s) << endl;
    s = "Aabb";
    cout << frequencySort(s) << endl;
    return 0;
}

// we can use bucket sort, better solution, next pass