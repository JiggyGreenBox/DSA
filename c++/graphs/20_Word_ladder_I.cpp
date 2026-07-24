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
observations
    words are a graph of single char transformations
    if targetword doesnt exist in the list then return 0
    if startword exists we start with count 1
    

    is this a graph problem
    words can be nodes and they are connected if they differ
    with one char

    each edge has the same weight to 1

    find min transformations
        then bfs to find targetword

    we generate neighbours
        eg. for word = dog
                check if    dag
                            dbg
                            dcg
                            ...
                            aog
                            bog
                            cog
                            ...
                            doa
                            dob
                            doc
                            ...
        26*word_len
    then we scan word array, 26*word_len * list_size
    make this a dict for O(1) search
*/