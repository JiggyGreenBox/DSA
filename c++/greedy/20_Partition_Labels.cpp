#include <iostream>
#include <vector>
using namespace std;

int main() {
    return 0;
}
/*
Partition Labels
    [https://leetcode.com/problems/partition-labels/]

You are given a string s. We want to partition the string into as 
many parts as possible so that each letter appears in at most one 
part. For example, the string "ababcc" can be partitioned into 
["abab", "cc"], but partitions such as ["aba", "bcc"] or ["ab", "ab", 
"cc"] are invalid.

Note that the partition is done so that after concatenating all the 
parts in order, the resultant string should be s.

Return a list of integers representing the size of these parts.


Example 1:

    Input: s = "ababcbacadefegdehijhklij"
    Output: [9,7,8]
    Explanation:
    The partition is "ababcbaca", "defegde", "hijhklij".
    This is a partition so that each letter appears in at most one part.
    A partition like "ababcbacadefegde", "hijhklij" is incorrect, because 
    it splits s into less parts.

Example 2:

    Input: s = "eccbbbbdec"
    Output: [10]

*/

/*
observation
    in any partition we have all occurances of any character

    for first char at idx 0
        we need last idx of that char
    for any char inbetween this range
        we need last char of those

    OG partition
        0..max(last_idx for 0..last_idx[char[0]])
        push_len
    then try again for
        last+1

    till string is over
*/

// this is like jump game 2

/*
move from R to L
a b a b c b a c a d  e  f  e  g  d  e  h  i  j  h  k  l  i  j
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23

last_idx
    j=23
    i=22
    l=21
    k=20
    h=19
    e=15
    d=14
    g=13
    f=11
    a=8
    c=7
    b=5

left=0, right=0
while right
    
    farthest = last(right)
    for i in l to r
        farthest = max last(i)

    push len
    left = right+1
    right = farthest
    

*/

vector<int> partitionLabels(string s) {

    vector<int> last(26, 0);

    for (int i = 0; i < s.size(); i++)
        last[s[i] - 'a'] = i;

    vector<int> ans;

    int start = 0;
    int right = 0;

    for (int i = 0; i < s.size(); i++) {

        right = max(right, last[s[i] - 'a']);

        if (i == right) {
            ans.push_back(right - start + 1);
            start = i + 1;
        }
    }

    return ans;
}