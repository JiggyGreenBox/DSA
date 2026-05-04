#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    // each digit has 3 letters mapped
    // backtrack chooses / ignores current digit
    // append to string
     
    // what is the base case?
    //      when we reach the end of the string
    // need an idx/strlen
    // need a curr_string
    // need results
    vector<string> letterCombinations(string digits) {
        vector<string> results;
        string current;
        // unordered_map<char, vector<char>> mpp;
        // mpp['2'] = {'a','b','c'};
        // mpp['3'] = {'d','e','f'};
        // mpp['4'] = {'g','h','i'};
        // mpp['5'] = {'j','k','l'};
        // mpp['6'] = {'m','n','o'};
        // mpp['7'] = {'p','q','r','s'};
        // mpp['8'] = {'t','u','v'};
        // mpp['9'] = {'w','x','y','z'}; 
        
        vector<string> mapping = {"","", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        // backtrack(0, current, digits, mpp, results);
        backtrack(0, current, digits, mapping, results);
        return results;
    }

    void printResults(const vector<string>& res){
        cout << "[ ";
        for(auto x : res) {
            cout << x << " ";
        }
        cout << "]\n";
    }
private:
    void backtrack( int idx, 
                    string& current, 
                    string& digits,
                    // unordered_map<char, vector<char>>& mpp,
                    const vector<string>& mapping,
                    vector<string>& results) 
    {
        // 1. base cases
        if(idx == digits.size()){
            results.push_back(current);
            return;
        }

        // pick / ignore
        // for(char c : mpp[digits[idx]]){
        for(char c : mapping[digits[idx]-'0']){
            current.push_back(c);
            // backtrack(idx+1, current, digits, mpp, results);
            backtrack(idx+1, current, digits, mapping, results);
            current.pop_back();
        }
    }
};


int main() {
    Solution sol;    
    sol.printResults(sol.letterCombinations("34"));
    // sol.printResults(sol.letterCombinations("3"));
    return 0;
}