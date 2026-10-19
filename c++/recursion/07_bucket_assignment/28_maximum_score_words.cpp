/*
maximum_score_words

words = ["dog","cat","dad","good"], 
 letters = ["a","a","c","d","d","d","g","o","o"], score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]



letters are resources
words are choices

for each word

    if idx == words.size()
        return score

    pick a word
        do we have enough letters?
            add score
            recurse
    skip word

    */

#include <bits/stdc++.h>
using namespace std;

void helper(
    int idx,
    int curr_score,
    int &max_score,
    vector<string> &words,
    unordered_map<char, int> &mpp,
    vector<int> &score
) {
    if (idx == words.size()) {
        max_score = max(max_score, curr_score);
        return;
    }

    // Don't pick this word
    helper(idx + 1, curr_score, max_score, words, mpp, score);

    // Check whether the entire word can be formed
    unordered_map<char, int> need;
    bool canPick = true;
    int word_score = 0;

    for (char c : words[idx]) {
        need[c]++;
        word_score += score[c - 'a'];
    }

    for (auto &[c, count] : need) {
        if (mpp[c] < count) {
            canPick = false;
            break;
        }
    }

    if (!canPick)
        return;

    // Pick the word
    for (auto &[c, count] : need) {
        mpp[c] -= count;
    }

    helper(
        idx + 1,
        curr_score + word_score,
        max_score,
        words,
        mpp,
        score
    );

    // Backtrack: restore exactly what was consumed
    for (auto &[c, count] : need) {
        mpp[c] += count;
    }
}

int getMaxScore(
    vector<string> &words,
    vector<char> &letters,
    vector<int> &score) {
    
    int max_score = 0;
    unordered_map<char, int> mpp;

    for(char c : letters) {
        mpp[c]++;
    }
    helper(0, 0, max_score, words, mpp, score);

    return max_score;
}

int main() {

    vector<string> words = {"dog", "cat", "dad", "good"};
    vector<char> letters = {'a','a','c','d','d','d','g','o','o'};
    vector<int> score = {1,0,9,5,0,0,3,0,0,0,0,0,0,
            0,2,0,0,0,0,0,0,0,0,0,0,0};

    auto x = getMaxScore(words, letters, score);

    return 0;
}