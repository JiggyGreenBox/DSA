#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <climits>
using namespace std;


string minWindow_brute(string s, string t) {
    string res = "";

    // brute force 
    // n^2 check every substring
    // for each substring when all chars have the required freq
    // break    
    unordered_map<char, int> mpp;
    for(char c : t) {        
        mpp[c]++;
    }

    int n = s.size();

    for(int i=0; i<n; i++) {

        unordered_map<char, int> copy = mpp;

        for(int j=i; j<n; j++) {
            
            if( copy.count(s[j]) > 0) {

                copy[s[j]]--;

                if(copy[s[j]] == 0) 
                    copy.erase(s[j]);
            }

            // exit condition is met
            if(copy.size() == 0){
                int len = j-i+1;
                if(res == "" || len < res.size()) { // update min results
                    res =  s.substr(i, len); 
                }
                break;
            }
        }
    }
    return res;
}







string cannonical(string s, string t) {

    int n = s.size();

    if (t.empty() || s.empty()) 
        return "";

    
    int remaining = t.size();    

    // use count to check t vs s
    // chars in t have a +ve count
    // chars in s not in t make it -ve
    int count[256] = {0};
    for(char c : t) 
        count[c]++;

    int left = 0;
    int start = 0;
    int min_len = INT_MAX;

    for(int right=0; right<n; right++) {

        if(count[s[right]] > 0) // char from t found
            remaining--;

        count[s[right]]--;

        // found valid, try find smaller
        while(remaining == 0) {

            int window_len = right - left + 1;

            if(window_len < min_len) { // found a smaller window
                min_len = window_len;
                start = left;
            }

            count[s[left]]++;

            if(count[s[left]] > 0) 
                remaining++;

            left++;
        }
    }

    if(min_len == INT_MAX) 
        return "";

    return s.substr(start, min_len);
}




int main() {
    // cout << minWindow_bf1("ADOBECODEBANC", "ABC") << endl;
    // cout << minWindow_bf2("ADOBECODEBANC", "ABC") << endl;
    // cout << minWindow_sliding3("ADOBECODEBANC", "ABC") << endl;
    // cout << minWindow_sliding4("ADOBECODEBANC", "ABC") << endl;
    // cout << cannonical("ADOBECODEBANC", "ABC") << endl;
    
    
    // cout << minWindow_bf1("a","a") << endl;
    // cout << minWindow_bf2("a","a") << endl;
    // cout << minWindow_bf1("aAbBDdcC","Bc") << endl;
    // cout << minWindow_bf2("aAbBDdcC","Bc") << endl;
    // cout << minWindow_sliding2("aAbBDdcC","Bc") << endl;
    return 0;
}

