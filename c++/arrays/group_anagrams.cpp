#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;


vector<vector<string>> group_anagrams_1(vector<string>& v) {

    vector<vector<string>> ans;    

    string header(30, '=');

    // 1. sorting arranges by first alphabet
    // cout << header << endl;

    // for(auto x:v) {
    //     cout << x << endl;
    // }
    // cout << header << endl;

    // sort(v.begin(), v.end());

    // for(auto x:v) {
    //     cout << x << endl;
    // }
    // cout << header << endl;


    // 2. sorting withing each string
    cout << header << endl;

    int n = v.size();
    unordered_map<string, vector<int>> mpp; // sorted string, vec of indexs

    for(auto x:v) {
        cout << x << endl;
    }
    cout << header << endl;

    

    for(int i=0; i<n; ++i) {
        string temp = v[i];
        sort(temp.begin(), temp.end());
        cout << temp << endl;
        mpp[temp].push_back(i);
    }
    cout << header << endl;

    for(auto pair: mpp){
        cout << pair.first << endl;
        vector<string> temp;
        for(auto idx: pair.second){
            cout << idx << " ";
            temp.push_back(v[idx]);
        }
        ans.push_back(temp);
        cout << endl;
    }

    return ans;
}

vector<vector<string>> group_anagrams_2(vector<string>& v) {

    vector<vector<string>> ans;    

    string header(30, '=');

    // 2. sorting withing each string
    cout << header << endl;

    int n = v.size();
    unordered_map<string, vector<string>> mpp; // sorted string, store string directly

    for(auto x:v) {
        cout << x << endl;
    }
    cout << header << endl;

    

    for(int i=0; i<n; ++i) {
        string temp = v[i];
        sort(temp.begin(), temp.end());
        cout << temp << endl;
        mpp[temp].push_back(v[i]);
    }
    cout << header << endl;

    // my solution
    // involves copying
    for(auto pair: mpp){
        cout << pair.first << endl;
        vector<string> temp;
        for(auto str: pair.second){
            cout << str << " ";
            temp.push_back(str);
        }
        ans.push_back(temp);
        cout << endl;
    }

    // optimal
    // involves copying pointers only 
    for(auto &pair :mpp){
        ans.push_back(move(pair.second)); // move vector<string> pointers directly
    }


    cout << header << endl;
    vector<string> v1 = {"eat", "tea"};
    vector<vector<string>> ans1;

    ans1.push_back(v1);              // copy v into ans[0]
    cout << v1.size() << endl;
    ans1.push_back(move(v1));        // move v into ans[1]
    cout << v1.size() << endl;
    cout << header << endl;

    return ans;
}

vector<vector<string>> group_anagrams_3(vector<string>& v) {

    vector<vector<string>> ans;    

    string header(30, '=');

    // 2. sorting withing each string
    cout << header << endl;

    int n = v.size();
    
    unordered_map<string, vector<string>> mpp; // hash_string, grouped_strings

    for(int i=0; i<n; ++i) {

        vector<int> count(26, 0); // count array

        string str = v[i]                ;

        // increment count array
        for(auto c : str ){
            // cout << c << endl;
            count[c-'a']++;
        }

        string hash = "";
        // convert into hash
        // issue here, need a delimiter
        for(auto x : count ){            
            // hash += to_string(x);
            hash += "#" + to_string(x);
        }
        // then "11" could mean:
        // one 'a' and one 'b' → count = [1,1,0,0,…]
        // OR eleven 'a' → count = [11,0,0,0,…]
        // both give "11" as the hash, which causes collisions.

        cout << hash << endl;

        // put into map
        mpp[hash].push_back(str);
    }
    cout << header << endl;

    for(auto &pair : mpp) {
        ans.push_back(move(pair.second));
    }

    return ans;
}



int main() { 

    vector<string> v = {"act", "god", "cat", "dog", "tac"};

    // vector<vector<string>> ans = group_anagrams_1(v);
    // vector<vector<string>> ans = group_anagrams_2(v);
    vector<vector<string>> ans = group_anagrams_3(v);

    for(auto group: ans){
        cout << "[";
        for(auto str: group){
            cout << str << " ";
        }
        cout << "]" << endl;
    }
    return 0;
}
