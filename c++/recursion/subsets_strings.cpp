#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    vector<string> generateSubsets(const string s){
        vector<string> results;        
        string current;
        backtrack_s(0, current, s, results);
        return results;
    }

    void printPerms(const vector<vector<string>>& perms) {
        for(vector<string> perm : perms){
            cout << "[ ";
            for(string s: perm) cout << "\""<< s << "\" ";
            cout << "]\n";
        }
    }

    void printPerms(const vector<string>& perms) {        
        cout << "[ ";
        for(string s: perms) cout << "\""<< s << "\", ";
        cout << "]\n";        
    }

private:
    void backtrack_s( int idx, 
                    // vector<string>& current,
                    string& current,
                    const string& s,
                    vector<string>& results)
    {
        // save at every iteration        
        results.push_back(current);                

        for(int i=idx; i<s.size(); i++){
            char c = s[i];
            // string str = {c};
            current.push_back(c);
            backtrack_s(i+1, current, s, results);
            current.pop_back();
        }
    }

    void filter_results(vector<string>& current, vector<vector<string>>& results) {
        int i = 0;
        int j = current.size()-1;
        while(i<j){
            if(current[i]==current[j]){
                i++;
                j--;
            }
            else{
                return;
            }
        }
        results.push_back(current);
    }
};

int main() {
    Solution sol;
    // sol.printPerms(sol.generateSubsets("aabaa"));
    // sol.printPerms(sol.generateSubsets("baa"));
    sol.printPerms(sol.generateSubsets("aba"));
    // aba
    // ""
    // "a"
    // "ab"
    // "aba"
    // "ba"
    // "b"

    
    return 0;
}