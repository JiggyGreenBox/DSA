#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;

/*

generate 1-char diff strings 
for input till output
a valid sequence should be present in the word list

wordList = ["des","der","dfr","dgt","dfs"], startWord = "der", targetWord = "dfs"

start der
    d*r
        found dfr
            df*
                found dfs
    d*s
        found des
            d*s
                found dfs
*/


/*
generate combinations of words with s1[c] being different
*/
vector<string> generate_words(string s1, int c){
    vector<string> res;
    char old_char = s1[c];
    
    for(int i=0;i<26; i++) {

        char new_char = (i + 'a');

        // if(old_char != new_char) {
            s1[c] = new_char;
            res.push_back(s1);
        // }        
    }
    return res;
}

void print(const vector<string> &v) {
    cout << "[ ";
    for(auto w : v) cout << w << ", ";
    cout << "]\n";
}


string get_next_word(string startWord, int c, unordered_set<string>& wmap, unordered_set<string>& used) {    
    vector<string> x = generate_words(startWord, c);
    for(auto s : x) {
        // not in used
        if(used.find(s) == used.end()) {
            // in wmap
            if(wmap.find(s) != wmap.end()) {
                return s;
            }
        }
        
    }
    return "";
}

vector<string> get_all_words(string startWord, unordered_set<string>& wmap, unordered_set<string>& used) {    
    vector<string> words;
    
    for(int j=0; j<startWord.size(); j++) {
        for(int i=0;i<26; i++) {

            char old = startWord[j];
            char new_char = (i + 'a');

            if(new_char == old) continue;

            
            startWord[j] = new_char;
            string s = startWord;
            if(used.find(s) == used.end() && wmap.find(s) != wmap.end()) {
                words.push_back(s);  
            }                      
            startWord[j] = old;            
        }
    }
    
    return words;
}

int wordLadderLength(string startWord, string targetWord,
                         vector<string> &wordList) 
{
    // // 1, build char bank for efficient string generation
    // int n = startWord.size();
    // vector<char> candidates[n];
    
    // for(int i=0; i<n; i++) {
    //     for(int j=0; j<wordList.size(); j++) {
    //         char new_char = wordList[j][i];
    //         if(candidates[i].empty() || find(candidates[i].begin(), candidates[i].end(), new_char) == candidates[i].end()) {
    //             candidates[i].push_back(new_char);
    //         }
    //     }
    // }


    int n = startWord.size();
    unordered_set<string> wmap;
    unordered_set<string> used;
    for(int j=0; j<wordList.size(); j++) {
        wmap.insert(wordList[j]);
    }

    if(wmap.find(targetWord) == wmap.end()) return 0;
    
    queue<pair<string, int>> q;
    
    used.insert(startWord);
    q.push({startWord, 1});

    while(!q.empty()) {
        auto p = q.front();
        q.pop();

        string word = p.first;
        int level = p.second;        
        
        if(word == targetWord) return level;

        vector<string> it_words = get_all_words(word, wmap, used);
        for(auto it_word : it_words) {
            used.insert(it_word);
            q.push({it_word, level + 1});
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

    // auto x = generate_words("dfs",0);
    // print(x);
    

    return 0;
}