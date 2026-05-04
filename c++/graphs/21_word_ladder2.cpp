#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;


vector<vector<string>> findSequences(string beginWord, string endWord,
                                         vector<string> &wordList) 
{
    vector<vector<string>> ans;

    // 1. lookup
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if(dict.find(endWord) == dict.end()) return ans;

    // 2. BFS
    // since this isnt a shortest sequence we must explore branches
    // this means once a level is completed the options should be marked as visited

    // we store the path of strings, we will only consider size == shortest
    queue<vector<string>> q;
    q.push({beginWord});
    int level = 0;

    // if we have 2 or 3 branches at a level
    // we will go down all of them
    vector<string> wordsUsedOnLevel;

    while(!q.empty()) {
        auto vec = q.front();
        q.pop();

        // new level, words are remove at this stage
        if(vec.size() > level) {
            level++;
            for(auto wordUsed : wordsUsedOnLevel) {
                dict.erase(wordUsed);
            }
            wordsUsedOnLevel.clear();
        }

        string curr_word = vec.back();

        if(curr_word == endWord) {
            if(ans.size() == 0){
                ans.push_back(vec);
            }
            else if(ans[0].size() == vec.size()) {
                ans.push_back(vec);
            }
        }
        
        /*
        demonstration of "bum" being used 2 times on level 3
            source: bat
            dest:   bum

            bat  ➡️  but
            ⬇️       ⬇️  
            bam  ➡️  bum

            bat ➡️ but ➡️ bum
            bat ➡️ bam ➡️ bum
        */

        // generate next word
        for(int i=0; i<curr_word.size(); i++) {
            for(char ch='a'; ch<='z'; ch++) {
                char original = curr_word[i];

                curr_word[i] = ch;
                if(dict.find(curr_word) != dict.end()) {
                    vec.push_back(curr_word);
                }

                curr_word[i] = original;
            }
        }
    }

}

int main() {

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    /* Function to determine number of steps
    to reach from start ward to target word */
    vector<vector<string>> findSequences(string beginWord, string endWord,
                                         vector<string> &wordList) {
        // To store the answer
        vector<vector<string>> ans;
        
        /* Queue data structure to store 
        the sequence of transformations */
        // store paths
        queue <vector<string>> q;
        
        // Add all the words to a hashset
        unordered_set<string> dict(wordList.begin(), wordList.end());
        
        // Add the sequence containing starting word to queue
        q.push({beginWord});
        
        // Erase starting word from set if it exists
        dict.erase(beginWord);
        
        /* Set to store the words that must be deleted 
        after traversal of a level is complete */
        unordered_set <string> toErase;
        
        // Until the queue is empty
        while(!q.empty()) {
            
            // Size of queue
            int size = q.size();
            
            // Traversing all words in current level
            for(int i=0; i<size; i++) {
                
                // Sequence 
                vector<string> seq = q.front();
                
                // Last added word in sequence
                string word = seq.back();
                q.pop();
                
                // If the Last word same as end word
                if(word == endWord) {
                    // Add the sequence to the answer
                    if(ans.empty()) {
                        ans.push_back(seq);
                    }
                    else if(ans.back().size() == seq.size()) {
                        ans.push_back(seq);
                    }
                }
                
                // Iterate on every character
                for(int pos = 0; pos < word.length(); pos++){
                    
                    // Original letter
                    char original = word[pos];
                    
                    /* Replacing current character with
                    letters from 'a' to 'z' to match 
                    any possible word from set */
                    for(char ch = 'a'; ch <= 'z'; ch++) {
                        word[pos] = ch;
                        
                        // Check if it exists in the set
                        if(dict.find(word) != dict.end()) {
                            // Update the sequence
                            seq.push_back(word);
                            
                            // Push in the queue
                            q.push(seq); 
                            
                            // Add the word to erase map
                            toErase.insert(word);
                            
                            // Backtracking step
                            seq.pop_back();
                        }
                    }
                    
                    // Update the original letter back
                    word[pos] = original;
                }
            }
            
            /* Erase all the words in set after
            traversal of a level is completed */
            for(auto it : toErase) dict.erase(it);
            toErase.clear();
            
            // If answer is found, break
            // dont explore longer sequences?
            if(!ans.empty()) break;
        }
        
        // Return the result found
        return ans;
    }
};

int main() {
    
    string beginWord = "der", endWord = "dfs";
    vector<string> wordList = 
        {"des","der","dfr","dgt","dfs"};
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function call to determine number of 
    steps to reach from start ward to target word */
    vector<vector<string>> ans = 
        sol.findSequences(beginWord, endWord, wordList);
    
    // Output
    cout << "The different sequences are:\n";
    for(int i=0; i < ans.size(); i++) {
        for(int j=0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}