/*
Substring with Concatenation of All Words
    [https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/]

You are given a string s and an array of strings words. All the 
strings of words are of the same length.

A concatenated string is a string that exactly contains all the 
strings of any permutation of words concatenated.

For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", 
"cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated 
strings. "acdbef" is not a concatenated string because it is not the 
concatenation of any permutation of words.
Return an array of the starting indices of all the concatenated 
substrings in s. You can return the answer in any order.

 

Example 1:

    Input: s = "barfoothefoobarman", words = ["foo","bar"]

    Output: [0,9]

    Explanation:

    The substring starting at 0 is "barfoo". It is the concatenation of 
    ["bar","foo"] which is a permutation of words.
    The substring starting at 9 is "foobar". It is the concatenation of 
    ["foo","bar"] which is a permutation of words.

Example 2:

    Input: s = "wordgoodgoodgoodbestword", words = 
    ["word","good","best","word"]

    Output: []

    Explanation:

    There is no concatenated substring.

Example 3:

    Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]

    Output: [6,9,12]

    Explanation:

    The substring starting at 6 is "foobarthe". It is the concatenation 
    of ["foo","bar","the"].
    The substring starting at 9 is "barthefoo". It is the concatenation 
    of ["bar","the","foo"].
    The substring starting at 12 is "thefoobar". It is the concatenation 
    of ["the","foo","bar"].


*/

/*
Substring with Concatenation of All Words

we have strings
    s1
    s2
    s3

we want 
    any combo of these 3 strings
        in search string
            return staring idx when this is true

brute force
    for each string
        generate the combination strings
            s1s2s3
            s1s3s2
            s2s1s3
            s2s3s1
            s3s1s2
            s3s2s1
                combolen = len(s1s2s3)

        then for each char in search string
            substring curr,combolen
                for each subtring
                    check if matches
                        push idx if match

        check next char till i<n-combolen



generate all combos
    is too expensive
        K! combinations

instead we keep a hashmap of all words
    <word count>

    we need to match this

since all words have the same len
    we can check the string len by len

if len = 3
0,3,6,9
    can be checked

there could be an offset
    but this would occur at max 0<len
        0,3,6,9
        1,4,7,10
        2,5,8,11
            these ensure we check every possible combination

we can slide our window
    maybe 0,3 doesnt have anything
    continue to check ahead
        use left, right to keep the window active

    start with left, and right
        keep moving right ahead
        adjust left

        if we find that we have count == required count
            store left index

*/

#include <vector>
#include <unordered_map>
using namespace std;

vector<int> findSubstring(string s, vector<string>& words) {
    

    vector<int> ans;

    int wordLen = words[0].size();
    int wordCount = words.size();
    int totalLen = wordLen * words.size(); 

    if(s.size() < totalLen)
        return ans;

    unordered_map<string, int> need;

    for(string &word: words)
        need[word]++;

    for(int offset=0; offset<wordLen; offset++) {

        int left  = offset;
        int right = offset;
        int count = 0;

        unordered_map<string, int> window;
        
        while(right + wordLen < s.size()) {

            // extract word at right
            string word = s.substr(right, wordLen);
            right += wordLen; // move ahead for next iter

            if(!need.count(word)) {
                window.clear();
                left = right; // new window
                count = 0;
                continue;
            }

            window[word]++;
            count++;

            while(window[word] > need[word]) {
                string leftWord = s.substr(left, wordLen);
                window[leftWord]--;
                left += wordLen;
                count--;
            }

            if(count == words.size()) {
                ans.push_back(left);

                string leftWord = s.substr(left, wordLen);
                window[leftWord]--;
                left += wordLen;
                count--;
            }
        }
    }

    return ans;
}

/*
the mechanics
    "barfoothefoobarman", words = ["foo","bar"]

    scan in size of 3 len(foo) == 3
        bar, found
            foo, found
                both found, store
                remove bar
            the,
                reset window
            foo
                found
            bar 
                found
                both found, store
                remove foo
            man
                reset

    scan from abf
        continue till end
            no matches
    
    scan from rfo
        contine till end 
            no matches
                exit
                    all combinations were tried
                        for 0..len(foo)
                            try starting
            

    some notes

        use need[word]
            to check if word exists

        match word count as well
        
        need[foo] = 1
        we we find "foofoofoo"
            need[foo] = 2
                remove first foo

        if all words found
            store
                remove from front, slide window
*/