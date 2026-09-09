#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// if k is average string len
// Sorting each string: O(k log k)
// Total:               O(n * k log k)
vector<vector<string>> group_anagrams(vector<string>& strs) {
    
    unordered_map<string, vector<string>> mpp; // sorted string, vec of strings

    for(string &s : strs) {

        string key = s;

        sort(key.begin(), key.end());
        
        mpp[key].push_back(s);
    }    

    vector<vector<string>> ans;
    
    for(auto &[key, group]: mpp) {
        ans.push_back(group);        
    }

    return ans;
}


// Counting characters: O(k)
// Encoding 26 counts:   O(26)
// Total:                O(n * k)

vector<vector<string>> groupAnagrams2(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;

    for (string& s : strs) {
        vector<int> count(26, 0);

        for (char c : s)
            count[c - 'a']++;

        string key;

        for (int x : count)
            key += to_string(x) + "#";

        mp[key].push_back(s);
    }

    vector<vector<string>> ans;

    for (auto& [key, group] : mp)
        ans.push_back(group);

    return ans;
}



int main() { 

    vector<string> v = {"act", "god", "cat", "dog", "tac"};

    // vector<vector<string>> ans = group_anagrams_1(v);
    // vector<vector<string>> ans = group_anagrams_2(v);
    vector<vector<string>> ans = groupAnagrams2(v);

    for(auto group: ans){
        cout << "[";
        for(auto str: group){
            cout << str << " ";
        }
        cout << "]" << endl;
    }
    return 0;
}
