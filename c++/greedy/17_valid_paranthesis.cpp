#include <iostream>
using namespace std;

void printB(bool b){
    if(b) cout << "true";
    else cout << "false";
    cout << "\n\n";
}

bool isValid(string s){    
    // when we get a * char
    // we can assign a '(' or a ')' or ''
    // so we can have no change, +1 or -1
    // need to track 2 possibilities at each step
    int min_open = 0;
    int max_open = 0;

    for(char c : s ) {
        if(c == '('){
            min_open++;
            max_open++;
        }
        else if(c == ')'){            
            // cap at zero, because we can choose nothing
            // meaning if all are already balanced, and we come across a new *, we can set it as blank
            min_open = max(--min_open, 0); 
            if(--max_open < 0) return false;
        }
        else if(c == '*'){            
            // cap at zero, because we can choose nothing
            // meaning if all are already balanced, and we come across a new *, we can set it as blank
            min_open = max(--min_open, 0);            
            max_open++;
        }
    }
    // either we closed every open
    // or we chose some blanks to balance every open
    return min_open==0;
}

int main(){

    // printB(isValid("(*))")); // true

    // printB(isValid("**((")); // false
    // printB(isValid("((**")); // true

    printB(isValid(")******)")); // false
    return 0;
}
/*
Valid Paranthesis Checker

Find the validity of an input string s that only contains the letters 
'(', ')' and '*'.

A string entered is legitimate if

Any left parenthesis '(' must have a corresponding right parenthesis 
')'.
Any right parenthesis ')' must have a corresponding left parenthesis 
'('.
Left parenthesis '(' must go before the corresponding right 
parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single 
left parenthesis '(' or an empty string "".

Example 1

    Input : s = (*))

    Output : true

    Explanation : The * can be replaced by an opening '(' bracket. The 
    string after replacing the * mark is "(())" and is a valid string.

Example 2

    Input : s = *(()

    Output : false

    Explanation : The * replaced with any bracket does not form a valid 
    string
*/


/*
Valid Paranthesis Checker
observations
    if have a '(' we need a ')' for balance
    if we have a '*' and ')' or a '*' and a '('


    we can decide * value when we see it

    the hint is we can maintain states

    min_open
    max_open

    ()
    char 1
        min_open = 1
        max_open = 1
    char 2
        min_open = 0
        max_open = 0

    (*
    char 1
        min_open = 1
        max_open = 1
    char 2
        min_open = 0
        max_open = 2


    ((**
    char 1
        min_open = 1
        max_open = 1
    char 2
        min_open = 2
        max_open = 2

    char 3
        min_open = 1
        max_open = 3
    char 4
        min_open = 0
        max_open = 4



    (
        increase min, max
    )
        reduce min, max
            clamp at 0, because then we consider * as empty
    *
        max++, * is (
        min-- * is )
            clamp at 0, because then we consider * as empty
*/

/*
(
    min++
    max++

)
    min--
    max--
    clamp min to 0 (minimum unmatched '(' cannot be negative)
    if max < 0 -> invalid

*
    // Best case
    min--
    clamp min to 0 (treat '*' as ')' or empty)

    // Worst case
    max++        (treat '*' as '(')
*/

/*
Invariant

min = minimum possible unmatched '('
max = maximum possible unmatched '('

'('
    min++, max++

')'
    min = max(0, min-1)
    max--
    if max < 0 return false

'*'
    min = max(0, min-1)   // '*' = ')' or empty
    max++                 // '*' = '('

Answer: min == 0
*/


// if max < 0 return false, because early )) cannot be balanced later

/*
    '('
        low++, high++

    ')'
        low--, high--

    '*'
        low--, high++

    clamp low
    check high
*/
