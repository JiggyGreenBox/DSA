#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/*
WORD LADDER

words = graph nodes

edge exists if:
    two words differ by exactly 1 character

every edge has cost 1

        ↓

shortest path in unweighted graph

        ↓

BFS

        ↓

don't build graph explicitly

generate neighbors:
    L positions × 26 characters

dictionary provides O(1) lookup

erase discovered words:
    dictionary doubles as visited set
*/

int wordLadderLength(string startWord, string targetWord,
                         vector<string> &wordList) 
{

    // O(1) search
    unordered_set<string> dict(wordList.begin(), wordList.end());

    if(!dict.count(targetWord))
        return 0;    

    queue<pair<string, int>> q; // word, level
    q.push({startWord, 1});

    dict.erase(startWord);

    while(!q.empty()) {
        auto [word, level] = q.front();
        q.pop();

        if(word == targetWord)
            return level;

        for(int i=0; i<word.size(); i++) {

            char og = word[i];

            for(char c='a'; c <= 'z'; c++) {

                if(c == word[i])
                    continue;                

                word[i] = c;

                if(dict.count(word)) {
                    q.push({word, level + 1});

                    dict.erase(word);
                }                
            }

            word[i] = og;
        }
    }
    return 0;
}


/*
Optimization:

instead of generating 26L candidates,

precompute wildcard patterns:

hot
 ↓
*ot
h*t
ho*

pattern → all matching words

BFS using pattern map
*/

// BFS 2, optimized for neighbour generation
int wordLadderLength2(string startWord, string targetWord,
                         vector<string> &wordList) 
{

    // 1. word lookup
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if(dict.find(targetWord) == dict.end()) return 0; // target not in list

    // 2. pattern lookup
    unordered_map<string, vector<string>> patternMap;
    for(auto word : wordList) {
        for(int i=0; i<word.size(); i++) {
            string pattern = word;
            pattern[i] = '*';
            patternMap[pattern].push_back(word);
        }
    }

    // 3. visited
    unordered_set<string> visited;
    visited.insert(startWord);

    queue<pair<string, int>> q;
    q.push({startWord, 1});

    while(!q.empty()) {
        auto [word, level] = q.front();
        q.pop();

        if(word == targetWord) return level;

        for(int i=0; i<word.size(); i++) {
            string pattern = word;
            pattern[i] = '*';

            for(auto nei : patternMap[pattern]) {
                if(visited.find(nei) == visited.end()){
                    visited.insert(nei);
                    q.push({nei, level + 1});
                }                
            }
        }
    }
    
    return 0;
}

int main() {

    string startWord = "der", targetWord = "dfs";
    vector<string> wordList = 
        {"des","der","dfr","dgt","dfs"};

    startWord = "gedk";
    targetWord = "geek";
    wordList = {"geek", "gefk"};

    cout << wordLadderLength(startWord, targetWord, wordList) << endl;
    

    return 0;
}



/*

Word ladder I
    words are a graph of single char transformations
    if targetword doesnt exist in the list then return 0
    if startword exists we start with count 1


Example 1

    Input: wordList = ["des","der","dfr","dgt","dfs"], startWord = "der", 
    targetWord = "dfs"

    Output: 3

    Explanation: 

    The length of the smallest transformation sequence from "der" to 
    "dfs" is 3
    i.e. "der" -> (replace ‘e’ by ‘f’) -> "dfr" -> (replace 
    ‘r’ by ‘s’) -> "dfs".
    So, it takes 3 different strings for us to reach the targetWord. Each 
    of these strings are present in the wordList.

Example 2

    Input: wordList = ["geek", "gefk"], startWord = "gedk", targetWord= 
    "geek"

    Output: 2

    Explanation: 

    The length of the smallest transformation sequence from "gedk" to 
    "geek" is 2
    i.e. "gedk" -> (replace ‘d’ by ‘e’) -> "geek" .
    So, it takes 2 different strings for us to reach the targetWord. Each 
    of these strings are present in the wordList.

Example 3

    Input: wordList = ["hot", "dot", "dog", "lot", "log"], startWord = 
    "hit", targetWord = "cog"

    Output: 0
*/

/*
Time
    N words
    L len of each word

    we check Lx26xN
    O(NL)

space
    N = number of words
    L = word length

    dictionary = O(NL)
    queue       = O(NL)

*/