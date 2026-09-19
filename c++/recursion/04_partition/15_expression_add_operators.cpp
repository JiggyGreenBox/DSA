/*
Expression Add Operators
    [https://leetcode.com/problems/expression-add-operators/description/]

Given a string num that contains only digits and an integer target, 
return all possibilities to insert the binary operators '+', '-', 
and/or '*' between the digits of num so that the resultant expression 
evaluates to the target value.

Note that operands in the returned expressions should not contain 
leading zeros.

Note that a number can contain multiple digits.

 

Example 1:

Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.
Example 3:

Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from 
"3456237490" to evaluate to 9191.
*/

/*
Expression Add Operators
    my first approach is to add +/-/* between each gap
        by cutting the string into substrings

    evaluation seems to be hard
    mult will over ride add and sub
        so left to right processing is not possible
    
    is early pruing possible?
        negative numbers are allowed
*/

#include <iostream>
#include <vector>
#include "../../common/printer.h"
using namespace std;

bool isValid(string &s, int target) {    
    s.pop_back(); // remove last operator
    int n = s.size();

    int total = 0;
    for(int i=1; i<n-1; i++) {
        if(s[i] == '*') {
            int left = i-1;
            while(left>0 && (s[left-1] != '*' || s[left-1] != '-'  || s[left-1] != '+' ))
                left--;

            int right = i+1;

            while(right<n-1 && (s[right+1] != '*' || s[right+1] != '-'  || s[right+1] != '+' ))
                right++;

            int num1 = stoi(s.substr(left, i-left+1));
            int num2 = stoi(s.substr(i+1, right-i+1));

            total += (num1*num2);

            for(int i=left; i<=right; i++){
                s[i] = '0';
            }
        }
    }

    // do addition and subtraction
    // ...

    return true;
}

void helper(int start, string &num, int target, 
            string &curr, vector<string> &res) {
    
    if(curr.size() == 2*num.size()) {
        if(isValid(curr, target))
            res.push_back(curr);
        return;
    }

    string opts = "*+-";

    for(int end=start; end<num.size(); end++) {
        string temp = num.substr(start, end-start+1);

        for(char c : opts) {
            temp += c;

            curr += temp;

            helper(end + 1, num, target, curr, res);

            curr.resize(curr.size() - temp.size());;

            temp.pop_back();
        }
    }
}

vector<string> addOperators(string num, int target) {
    vector<string> res;
    string curr;
    helper(0, num, target, curr, res);
    return res;
}

int main() {
    string num = "123";
    int  target = 6;
    
    vector<string> res = addOperators(num, target);
    print(res);

    // num = "232";
    // target = 8;
    // res = addOperators(num, target);
    // print(res);

    // num = "3456237490"; 
    // target = 9191;
    // res = addOperators(num, target);
    // print(res);
    return 0;
}