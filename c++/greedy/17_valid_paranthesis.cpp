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