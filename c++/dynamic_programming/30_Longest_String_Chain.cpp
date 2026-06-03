#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Longest String Chain

    You are given an array of words where each word consists of lowercase 
    English letters.

    wordA is a predecessor of wordB if and only if we can insert exactly 
    one letter anywhere in wordA without changing the order of the other 
    characters to make it equal to wordB.

    For example, "abc" is a predecessor of "abac", while "cba" is not a 
    predecessor of "bcad".

    A word chain is a sequence of words [word1, word2, ..., wordk] with k 
    >= 1, where word1 is a predecessor of word2, word2 is a predecessor 
    of word3, and so on. A single word is trivially a word chain with k 
    == 1.

    Return the length of the longest possible word chain with words 
    chosen from the given list of words.
*/

/*
rules for the chain, for wordA wordB

    if(len(A) != len(B) - 1) return false

    for 0..lenB
        replace char with *
        insert lookup

    abc    
        insert * from 0..n


    string search = "abc";

    for(int i=0; i <= search.size(); i++) {
        string temp = search;
        temp.insert(i, "*");
        cout << temp << endl;
    }

    string target = "abcd";
    for(int i=0; i < target.size(); i++) {
        string temp = target;
        temp[i] = '*';
        cout << temp << endl;
    }

*/

bool isPredecessor(string &small, string &large) {    

    // you walk through both strings and allow exactly one extra character in the longer string.

    // 2 pointers
    if(large.size() != small.size() + 1) return false; // has to be 1 char diff


    int i=0, j=0;
    while(i<small.size() && j<large.size()) {
        if(small[i] == large[j]) {
            i++;
            j++;
        }
        else{
            j++;  // skip one char from larger string
        }
    }
    return i == small.size();

    // Lengths differ by exactly 1.
    // So only one extra character exists.
    // When chars match, advance both.
    // When they don't, consume the extra character.

}

int longestStringChain(vector<string>& words) {
    sort(words.begin(), words.end(), [](const string &a, const string &b) {
        return a.size() < b.size();
    });

    int max_len = 1;

    // printLIS algorithm, n^2
    int n = words.size();

    vector<int> dp(n, 1);

    for(int i=0; i<n; i++) {

        for(int j=0; j<i; j++) {

            if(isPredecessor(words[j], words[i])) {

                dp[i] = max(dp[i], dp[j]+1);                
            }
        }       
        
        max_len = max(max_len, dp[i]); 
    }
    return max_len;
}

int main() {

    // string search = "abc";

    // for(int i=0; i <= search.size(); i++) {
    //     string temp = search;
    //     temp.insert(i, "*");
    //     cout << temp << endl;
    // }

    // string target = "abcd";
    // for(int i=0; i < target.size(); i++) {
    //     string temp = target;
    //     temp[i] = '*';
    //     cout << temp << endl;
    // }

    return 0;
}