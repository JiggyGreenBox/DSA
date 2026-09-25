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


