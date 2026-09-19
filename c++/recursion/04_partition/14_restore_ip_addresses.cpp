/*
Restore IP Addresses
    [https://leetcode.com/problems/restore-ip-addresses/description/]

A valid IP address consists of exactly four integers separated by 
single dots. Each integer is between 0 and 255 (inclusive) and cannot 
have leading zeros.

For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, 
but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP 
addresses.
Given a string s containing only digits, return all possible valid IP 
addresses that can be formed by inserting dots into s. You are not 
allowed to reorder or remove any digits in s. You may return the 
valid IP addresses in any order.

 

Example 1:

Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]
Example 2:

Input: s = "0000"
Output: ["0.0.0.0"]
Example 3:

Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

*/

/*
input is a string
    we want to partition into chunks
        if the chunk is not valid
            stop

        valid chunk/substr
            has no leading zeros
            is less than 255

    we can only partition the string into 4 parts
*/


#include <iostream>
#include <vector>
#include "../../common/printer.h"
using namespace std;

class Solution {
public:

    bool isValid(const string& s, int start, int end) {

        int len = end - start + 1;

        // IP component can have at most 3 digits
        if (len > 3)
            return false;

        // Leading zero
        if (len > 1 && s[start] == '0')
            return false;

        // Convert/check value
        int num = stoi(s.substr(start, len));        

        return num <= 255;
    }

    void backtrack(int start,
                   const string& s,
                   vector<string>& curr,
                   vector<string>& ans) {

        // We have 4 components
        if (curr.size() == 4) {

            // Accept only if entire string was consumed
            if (start == s.size()) {

                string ip = curr[0] + "." +
                            curr[1] + "." +
                            curr[2] + "." +
                            curr[3];

                ans.push_back(ip);
            }

            return;
        }

        // Try every possible next component
        for (int end = start; end < s.size(); end++) {

            // Prune invalid component
            if (!isValid(s, start, end))
                continue;

            // Choose
            curr.push_back(s.substr(start, end - start + 1));

            // Explore
            backtrack(end + 1, s, curr, ans);

            // Unchoose
            curr.pop_back();
        }
    }

    vector<string> restoreIpAddresses(string s) {

        vector<string> ans;
        vector<string> curr;

        backtrack(0, s, curr, ans);

        return ans;
    }
};

int main() {
    string s = "25525511135";
    Solution sol;
    vector<string> res = sol.restoreIpAddresses(s);
    print(res);

    s = "0000";
    res = sol.restoreIpAddresses(s);
    print(res);

    s = "101023";
    res = sol.restoreIpAddresses(s);
    print(res);

    return 0;
}

/*
time complexity
    4 chucks of 3 chars
        so n.len ^ 4

    chunk 1: up to 3 choices
    chunk 2: up to 3 choices
    chunk 3: up to 3 choices
    chunk 4: up to 3 choices

    so 3^4
*/