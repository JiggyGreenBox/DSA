#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        vector<string> current;
        backtrack(0, s, current, results);
        return results;
    }

    void printResults(const vector<vector<string>>& results){
        for(auto vec : results){
            cout << "[ ";
            for(auto str : vec) cout << str << " ";
            cout << "]\n";
        }
    }
private:
    void backtrack( int idx,
                    const string& s,
                    vector<string>& current, 
                    vector<vector<string>>& results)
    {
        if(idx == s.size()){
            results.push_back(current);
            return;
        }

        for(int i=idx; i<s.size(); i++){
            int len = (i-idx+1);
            string new_str = s.substr(idx, len);
            if(isPalindrome(new_str)) {
                current.push_back(new_str);                
                backtrack(i+1, s, current, results);            
                current.pop_back();
            }   
                
        }
    }
public:
    bool isPalindrome(const string& s){
        int i=0;
        int j=s.size()-1;
        while(i<j){
            if(s[i] != s[j]) return false;
            i++;
            j--;
        }
        return true;
    }
     
};

int main() {
    Solution sol; 
    sol.printResults(sol.partition("aabaa"));    
    return 0;
}

// Start
// ├── "a"    ✅
// │   ├── "a"    ✅
// │   │   ├── "b"    ✅
// │   │   │   ├── "a"    ✅
// │   │   │   │   └── "a"    ✅  ✔️ valid
// │   │   │   └── "aa"   ✅  ✔️ valid
// │   │   └── "ba"   ❌  (branch cut)
// │   └── "ab"   ❌
// ├── "aa"   ✅
// │   ├── "b"    ✅
// │   │   ├── "a"    ✅
// │   │   │   └── "a"    ✅  ✔️ valid
// │   │   └── "aa"   ✅  ✔️ valid
// │   └── "ba"   ❌
// ├── "aab"  ❌
// └── "aabaa" ✅ ✔️ valid

// [ a a b a a ]
// [ a a b aa ]
// [ a aba a ]
// [ aa b a a ]
// [ aa b aa ]
// [ aabaa ]