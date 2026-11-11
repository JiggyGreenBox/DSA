/*
Minimum insertions to make string palindrome
    [https://takeuforward.org/practice/dsa/minimum-insertions-to-make-string-palindrome?category=dp-on-strings&source=strivers-a2z-dsa-sheet]

Given a string s, find the minimum number of insertions needed to 
make it a palindrome. A palindrome is a sequence that reads the same 
backward as forward. You can insert characters at any position in the 
string.

Example 1:
Input: s = "abcaa"

Output: 2

Explanation: Insert 2 characters "c", and "b" to make "abcacba", 
which is a palindrome.

Example 2:
Input: s = "ba"

Output: 1

Explanation: Insert "a" at the beginning to make "aba", which is a 
palindrome.
*/


/*

LPS(i, j)
    length of longest palindrome between i,j

abcaa

    LPS(0,4, abcaa) == 3

aacbcaa
    len - LPS(s)
    5 - 3 = 2

we need to insert 'a' and 'c'

*/


