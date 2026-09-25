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


void helper(int start,          // idx
            const string& num,
            long long target,
            string& expr,       // aka curr
            long long value,    // value of expr/curr
            long long prev,     // required to handle multiplication
            vector<string>& ans) {
    
    if(start == num.size()) {
        if(value == target)
            ans.push_back(expr);
    }

    for(int end=start; end<num.size(); end++) {

        // no leading zeros
        if(end > start && num[start] == '0')
            break;

        string curr = num.substr(start, end-start+1);
        long long x = stoll(curr);

        int oldSize = expr.size();

        // First number: no operator
        if(start == 0) {
            expr += curr;

            helper(end + 1, num, target,
                   expr, x, x, ans);

            expr.resize(oldSize);
        }
        // now we can add operators
        else {

            // +
            expr += '+' + curr;            
            helper(end + 1, num, target,
                   expr, value + x, x, ans);
            expr.resize(oldSize);

            // -
            expr += '-' + curr;            
            helper(end + 1, num, target,
                   expr, value - x, -x, ans);
            expr.resize(oldSize);


            // *
            expr += '*' + curr;            
            helper(end + 1, num, target,
                   expr,
                   value - prev + prev * x, 
                   prev * x, 
                   ans);
            expr.resize(oldSize);
        }
    }
}


vector<string> addOperators(string num, int target) {
    vector<string> ans;
    string expr;

    helper(0, num, target, expr, 0, 0, ans);

    return ans;
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

/*

Example 1: 
    2 + 3 * 4 * 5

2+3
    value = 5
    prev  = 3

now *4
    5 - 3 + (3 * 4)
    = 14
    prev = 3 * 4 = 12

    value = 14
    prev  = 12

now *5
    14-12 = 2, 2+(12*5)
          = 60 + 2
          = 62
    prev = 60

        prev allows us to separate the addition/subtraction from multiplication
----
Example2
    2 * 3 + 4 * 5

After 2 * 3:
    value = 6
    prev  = 6       // 2*3

+4
    value = 10
    prev  = 4

Then * 5:
    value = 10 - 4 + (4*5)
      = 26

    prev = 4*5 = 20

-------

*/