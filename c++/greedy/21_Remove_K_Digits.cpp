/*

Remove K Digits
    [https://leetcode.com/problems/remove-k-digits/description/]

Given string num representing a non-negative integer num, and an 
integer k, return the smallest possible integer after removing k 
digits from num.

 

Example 1:

    Input: num = "1432219", k = 3
    Output: "1219"
    Explanation: Remove the three digits 4, 3, and 2 to form the new 
    number 1219 which is the smallest.

Example 2:

    Input: num = "10200", k = 1
    Output: "200"
    Explanation: Remove the leading 1 and the number is 200. Note that 
    the output must not contain leading zeroes.

Example 3:

    Input: num = "10", k = 2
    Output: "0"
    Explanation: Remove all the digits from the number and it is left 
    with nothing which is 0.

*/

/*

Remove K Digits
"1432219", k = 3

this is similar to next permutation

if we have 121
    if we remove 1, 21
    if we remove 2, 11

    we want first reduction
        if s[i-1] > s[i]
            erase s[i-1]

        we dont need to start from the beginning
        we are already in the best position


i was almost right uptill the part
where we dont start from the beginning

1594, k=2
    remove 9
    but now we have to remove 5>4, 5
*/

/*
Observation

The leftmost larger digit should be removed.

If

previous > current

then removing the previous digit makes the number
lexicographically smaller as early as possible.

Deleting a digit can create a new inversion immediately
to its left.

Therefore we repeatedly remove larger previous digits.

A stack naturally performs this repeated look-back.
*/

/*
Canonical algorithm
    for every digit

        while stack not empty
            &&
            stack.top() > digit
            &&
            k > 0

            pop
            k--

        push(digit)




for every digit

    while(previous digit > current digit && k > 0)
        remove previous digit

    push current digit

--------------------------------

if k is still left

    remove from the end
*/
#include <iostream>

using namespace std;
string removeKdigits(string num, int k) {

    string st;

    for (char c : num) {

        // Remove larger digits from the left
        // while we still have removals available.
        while (!st.empty() && k > 0 && st.back() > c) {
            st.pop_back();
            k--;
        }

        st.push_back(c);
    }

    // If removals remain, remove from the end.
    while (k > 0) {
        st.pop_back();
        k--;
    }

    // Remove leading zeros.
    int i = 0;
    while (i < st.size() && st[i] == '0')
        i++;

    string ans = st.substr(i);

    return ans.empty() ? "0" : ans;
}

#include <stack>
#include <algorithm>

string removeKdigits(string num, int k) {

    stack<int> st;

    for (char c : num) {

        int digit = c - '0';

        while (!st.empty() && k > 0 && st.top() > digit) {
            st.pop();
            k--;
        }

        st.push(digit);
    }

    // Remove remaining digits from the end
    while (k > 0) {
        st.pop();
        k--;
    }

    // Stack is reversed, so reconstruct answer
    string ans;

    while (!st.empty()) {
        ans.push_back(st.top() + '0');
        st.pop();
    }

    reverse(ans.begin(), ans.end());

    // Remove leading zeros
    int i = 0;
    while (i < ans.size() && ans[i] == '0')
        i++;

    ans = ans.substr(i);

    return ans.empty() ? "0" : ans;
}