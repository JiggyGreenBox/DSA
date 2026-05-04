#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
using namespace std;



// BFS 1 brute force for neighbours
int wordLadderLength(string startWord, string targetWord,
                         vector<string> &wordList) 
{
    unordered_set<string> dict(wordList.begin(), wordList.end());        

    // no target, no solution possible
    if(dict.find(targetWord) == dict.end()) return 0;

    unordered_set<string> visited;
    visited.insert(startWord);

    queue<pair<string, int>> q;
    q.push({startWord, 1});
    
    while(!q.empty()) {
        auto [word, level] = q.front();
        q.pop();

        if(word == targetWord) return level;

        // generate all neighbours, brute force
        for(int i=0; i<word.size(); i++) {

            char old = word[i];

            for(char ch='a'; ch <= 'z'; ch++) {            
                                
                if(ch == old) continue;

                word[i] = ch;

                if(dict.find(word) != dict.end() && visited.find(word) == visited.end()) {
                    visited.insert(word);
                    q.push({word, level + 1});
                }

                word[i] = old;
            }
        }
    }
    return 0;
}


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



// word ladder 2, return the vectors
vector<vector<string>> wordLadderLength3(string startWord, string targetWord,
                         vector<string> &wordList) 
{
    vector<vector<string>> res;
    // 1. word lookup
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if(dict.find(targetWord) == dict.end()) return res; // target not in list

    // // 2. pattern lookup
    // unordered_map<string, vector<string>> patternMap;
    // for(auto word : wordList) {
    //     for(int i=0; i<word.size(); i++) {
    //         string pattern = word;
    //         pattern[i] = '*';
    //         patternMap[pattern].push_back(word);
    //     }
    // }

    // 3. visited
    // unordered_set<string> visited;
    // visited.insert(startWord);

    queue<tuple<string, vector<string>, unordered_set<string>>> q;
    // queue<pair<string, vector<string>>> q;
    q.push({startWord, {startWord}, {startWord}});

    while(!q.empty()) {
        auto [word, string_vec, visited] = q.front();
        q.pop();

        if(word == targetWord) {
            res.push_back(string_vec);            
        }

        // for(int i=0; i<word.size(); i++) {
        //     string pattern = word;
        //     pattern[i] = '*';

        //     for(auto nei : patternMap[pattern]) {
        //         if(visited.find(nei) == visited.end()){
        //             visited.insert(nei);
        //             strings.push_back(nei);
        //             q.push({nei, strings});
        //         }                
        //     }
        // }
        // generate all neighbours, brute force
        for(int i=0; i<word.size(); i++) {

            char old = word[i];

            for(char ch='a'; ch <= 'z'; ch++) {            
                                
                if(ch == old) continue;

                word[i] = ch;

                if(dict.find(word) != dict.end() && visited.find(word) == visited.end()) {
                    visited.insert(word);
                    string_vec.push_back(word);
                    cout << word << endl;
                    q.push({word, string_vec, visited});
                }

                word[i] = old;
            }
        }
    }
    
    return res;
}


void generate_pattern_map(const vector<string> wordList) {
    unordered_map<string, vector<string>> patternMap;

    for(auto& word : wordList) {
        
        for(int i=0; i<word.size(); i++) {
            string pattern = word;
            pattern[i] = '*';
            patternMap[pattern].push_back(word);
        }
    }
    int x = 5;
}

void printStrings(const vector<vector<string>> v) {
    cout << "[ ";
    for(auto& vec : v) {
        cout << "[ ";
        for(string s : vec) cout << s << " ";
        cout << "] ";
    }
    cout << "]\n";
}

int main() {

    string startWord = "der", targetWord = "dfs";
    vector<string> wordList = 
        {"des","der","dfr","dgt","dfs"};    

    cout << wordLadderLength2(startWord, targetWord, wordList) << endl;
    printStrings(wordLadderLength3(startWord, targetWord, wordList));

    startWord = "gedk";
    targetWord = "geek";
    wordList = {"geek", "gefk"};

    cout << wordLadderLength2(startWord, targetWord, wordList) << endl;
    printStrings(wordLadderLength3(startWord, targetWord, wordList));

    // generate_pattern_map(wordList);
    


    

    return 0;
}