#include <iostream>
#include <vector>
using namespace std;


void printAns(const vector<string>& ans){
    for (auto x : ans)
    {
        cout << x << endl;
    }
    cout << "\n";
}

void dfs(int left, int right,
         string& curr,
         vector<string>& ans)
{
    if (left == 0 && right == 0) {
        ans.push_back(curr);
        return;
    }

    // put '('
    if (left > 0) {
        curr.push_back('(');

        dfs(left - 1, right, curr, ans);

        curr.pop_back();
    }

    // put ')'
    if (right > left) {
        curr.push_back(')');

        dfs(left, right - 1, curr, ans);

        curr.pop_back();
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> results;
    string current;    
    dfs(n, n, current, results);
    return results;
}

int main() {
    vector<string> ans;

    // for(int i=0; i<5; i++){
        ans = generateParenthesis(3);
        printAns(ans);
    // }    

    return 0;
}