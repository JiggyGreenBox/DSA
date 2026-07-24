#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include "../common/printer.h"
#include <climits>
#include <unordered_set>
#include <unordered_map>
using namespace std;

void dfs(string word, string startWord,
            unordered_map<string, vector<string>> &parents,
            vector<string> &path, 
            vector<vector<string>> &ans) 
{
    path.push_back(word);

    if(word == startWord) {
        vector<string> temp = path;
        reverse(temp.begin(), temp.end());
        ans.push_back(temp);
    }
    else {    
        for(auto &parent : parents[word])
            dfs(parent, startWord, parents, path, ans);
    }

    path.pop_back();
}

vector<vector<string>> findSequences(string beginWord, string endWord,
                                         vector<string> &wordList)
{
    // 1. build dictionary
    // 2. store parents
    // 3. BFS
    // 4. DFS on parents
    // 5. Remember words discovered in this BFS level
    // 6. Remove them after the level finishes

    unordered_set<string> dict(wordList.begin(), wordList.end());

    if(!dict.count(endWord))
        return {};

    unordered_map<string, vector<string>> parents;
    unordered_map<string, int> levels;

    queue<string> q;
    q.push(beginWord);
    levels[beginWord] = 0;
    dict.erase(beginWord);

    bool found = false; // stopping condition

    while(!q.empty() && !found) {
        int sz = q.size();

        unordered_set<string> visitedThisLevel; // levelwise book keeping

        while(sz--) {
            auto curr = q.front();
            q.pop();

            int cur_level = levels[curr];

            string next = curr;

            for(int i=0; i<next.size(); i++) {
                char og = next[i];

                for(char c = 'a'; c<= 'z'; c++) {

                    if(c == og)
                        continue;

                    next[i] = c;

                    if(dict.count(next)) {                        

                        // exit bfs
                        if(next == endWord)
                            found = true;

                        // we found a valid word
                        // we need to manage levels
                        // maybe this is the first time we have seen it
                        // maybe we have seen it for the second time
                        // if 2nd, then does it have same level as prev

                        if(!levels.count(next)) {

                            visitedThisLevel.insert(next);

                            levels[next] = cur_level + 1;                        
                            q.push(next);

                            // we walk from endWord to startWords
                            // latest points to prev
                            parents[next].push_back(curr);
                        }
                        // did we find another next from curr?
                        else if(levels[next] == cur_level + 1) {
                            parents[next].push_back(curr);
                        }                        
                    }
                }
                next[i] = og;
            }
        }

        for(const auto &s : visitedThisLevel)
            dict.erase(s);
    }

    // DFS on parents
    vector<vector<string>> ans;
    vector<string> path;
    dfs(endWord, beginWord, parents, path, ans);
    return ans;
}

int main() {    

    string startWord = "der", targetWord = "dfs";
    vector<string> wordList = 
        {"des","der","dfr","dgt","dfs"};
    
    ;    
    print(findSequences(startWord, targetWord, wordList));

    return 0;
}

/*
why levelwise set?
why map for levels?
why found flag?
    to prevent deeper searches
*/

/*
Word Ladder II

levels:
- Records the shortest distance from beginWord.
- Prevents enqueueing the same word multiple times.
- Allows adding multiple parents only if they reach the same shortest level.

visitedThisLevel:
- Tracks words first discovered in the current BFS level.
- Erase them from the dictionary only after the entire level finishes.
- Allows multiple nodes in the same level to become parents of the same word.

found:
- Stop BFS after finishing the level where endWord is first discovered.
- Prevents exploring longer paths while still collecting all shortest paths.

parents:
- parents[child] = {parent1, parent2, ...}
- Stores all shortest predecessors.
- DFS walks backward from endWord to beginWord.
*/

// First discovery:
//   assign level, enqueue, remember parent
//
// Same shortest level:
//   remember another parent only
//
// Longer path:
//   ignore


/*
Time:
BFS : O(N * L * 26)
DFS : O(number of shortest paths)

Space:
O(N * L)

N = number of words
L = word length
*/