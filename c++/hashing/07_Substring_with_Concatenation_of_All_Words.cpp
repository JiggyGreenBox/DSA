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
    put in hashmap

then slide window
    make window of combolen
        add 1 char remove 1 char till end
            look for match with hashmap
*/