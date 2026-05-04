#include <iostream>
#include <vector>
using namespace std;

void helper(int n, int open, int closed, string current, vector<string>& results) {

    // exit condition for recursion
    if(open == n && closed == n) {
        results.push_back(current);
        return;
    }    

    if(open < n){        
        helper(n, open + 1, closed, current + "(", results);
    }

    if(closed < open){        
        helper(n, open, closed + 1, current + ")", results);
    }
}

void backtrack(int open, int closed, int n, string& current, vector<string>& results) {
    // base case
    if(current.length() == 2*n) {
        results.push_back(current);
        return;
    }

    // choice "("
    if(open < n) {
        current.push_back('(');
        backtrack(open + 1, closed, n, current, results);
        current.pop_back();
    }

    // choice ")"
    if(closed < open) {
        current.push_back(')');
        backtrack(open, closed + 1, n, current, results);
        current.pop_back();
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> results;
    string current;
    // helper(n, 0, 0, current, results);
    backtrack(0, 0, n, current, results);
    return results;
}

    

void printAns(const vector<string>& ans){
    for (auto x : ans)
    {
        cout << x << endl;
    }
    cout << "\n";
}

int main() {
    vector<string> ans;

    // for(int i=0; i<5; i++){
        ans = generateParenthesis(3);
        printAns(ans);
    // }    

    return 0;
}

