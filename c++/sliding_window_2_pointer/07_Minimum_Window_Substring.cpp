#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <climits>
using namespace std;

string minWindow_bf1(string s, string t) {
    string res = s;

    // brute force 
    // n^2 check every substring
    // for each substring when all chars have the required freq
    // break
    unordered_set<char> mset;
    unordered_map<char, int> mpp;
    for(char c : t) {
        mset.insert(c);
        mpp[c]++;
    }

    int n = s.size();

    for(int i=0; i<n; i++) {
        unordered_map<char, int> mpp_local = mpp;
        for(int j=i; j<n; j++) {
            // only check valid chars
            if(mset.count(s[j]) > 0) {
                mpp_local[s[j]]--;
                if(mpp_local[s[j]] == 0) mpp_local.erase(s[j]);
            }

            // exit condition is met
            if(mpp_local.size() == 0){
                int len = j-i+1;
                if(len < res.size()) { // update min results
                    res =  s.substr(i, len); 
                }
                break;
            }
        }
    }
    return res;
}

string minWindow_bf2(string s, string t) {
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
        unordered_map<char, int> mpp_local = mpp;
        for(int j=i; j<n; j++) {
            // only check valid chars
            // if( mpp_local.find(s[j]) != mpp_local.end() && 
            //     mpp_local[s[j]] > 0) 
            if( mpp_local.find(s[j]) != mpp_local.end() )                
            {            
                mpp_local[s[j]]--;
                if(mpp_local[s[j]] == 0) mpp_local.erase(s[j]);
            }

            // exit condition is met
            if(mpp_local.size() == 0){
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

string minWindow_sliding1(string s, string t) {
    string res = "";
    int l = 0;
    int n = s.size();
    int valid_chars = t.size();
    int chars_found = 0;

    unordered_map<char, int> mpp_s;
    unordered_map<char, int> mpp_t;
    for(auto c : t) {
        mpp_t[c]++;
    }

    for(int r=0; r<n; r++) {
        if(mpp_t.find(s[r]) != mpp_t.end()){            
            mpp_s[s[r]]++;
        }

        // when both maps have the same size
        // range is valid
        // can there br a smaller range?
        // how do we move beyond that

        if(mpp_s.size() == mpp_t.size()){  // WRONG because freq not considered, AABC, ABC 
            // try smaller valid 
            while(true){
                if( mpp_t.find(s[l]) == mpp_t.end()) l++;
                else if( mpp_t.find(s[l]) == mpp_t.end() && 
                    mpp_s[s[l]] > mpp_t[s[l]] )
                {
                    mpp_s[s[l]]--;
                    if(mpp_s[s[l]] == 0) mpp_s.erase(s[l]);
                    l++;
                }
                else{
                    break;
                }
            }

            int len = r-l+1;
            if(res == "" || len < res.size()) {
                res = s.substr(l, len);
            }

            // move ahead
            mpp_s[s[l]]--;
            if(mpp_s[s[l]] == 0) mpp_s.erase(s[l]);
            l++;
        }        
    }

    return res;
}

bool isValid(const unordered_map<char, int>& mp_s, const unordered_map<char, int>& mp_t){    
    // every t should be present in s
    for(auto p : mp_t) {
        if(mp_s.find(p.first) == mp_s.end()) return false;  // char is missing
        if(mp_s.at(p.first) < p.second) return false;       // char freq is not sufficient
    }
    return true;
}

string minWindow_sliding2(string s, string t) {
    int n = s.size();
    string res = "";
    unordered_map<char, int> mp_s;
    unordered_map<char, int> mp_t;
    for(char c : t) mp_t[c]++;

    int l=0;
    for(int r=0; r<n; r++) {
        // expand window
        if(mp_t.find(s[r]) != mp_t.end()) {
            mp_s[s[r]]++;
        }

        // valid string
        while(isValid(mp_s, mp_t)){
            int len = r-l+1;
            if(res == "" || len < res.size()){
                res = s.substr(l, len);
            }

            mp_s[s[l]]--;
            l++;
        }        
    }
    return res;
}

string minWindow_sliding3(string s, string t) {
    string res = "";
    int n = s.size();
    int chars_remaining = t.size();
    unordered_map<char, int> mpp;
    // only track chars we need
    for(char c : t) mpp[c]++;
    int l=0;
    for(int r=0; r<n; r++) {
        // char is in t
        if(mpp.find(s[r]) != mpp.end()){
            mpp[s[r]]--;
            if(mpp[s[r]] == 0) chars_remaining--;
        }

        // valid string found
        while(chars_remaining == 0) {
            int len = r-l+1;
            if(res == "" || len < res.size()){
                res = s.substr(l, len);
            }

            if(mpp.find(s[l]) != mpp.end()){
                mpp[s[l]]++;
                if(mpp[s[l]] > 0) chars_remaining++;
            }
            l++;
        }
    }
    return res;
}

string minWindow_sliding4(string s, string t) {
    string res = "";
    int n = s.size();
    int unique_chars_remaining = 0;
    // unordered_map<char, int> mpp;
    int count[256] = {0};
    // only track chars we need
    for(auto c : t){
        if(count[c] == 0) unique_chars_remaining++;
        count[c]++;
    } 
    int l=0;
    for(int r=0; r<n; r++) {
        // char is in t
        count[s[r]]--;
        if(count[s[r]] == 0) unique_chars_remaining--; // meaning 1->0 cuz of char
        

        // valid string found
        while(unique_chars_remaining == 0) {
            int len = r-l+1;
            if(res == "" || len < res.size()){
                res = s.substr(l, len);
            }

            
            count[s[l]]++;
            if(count[s[l]] == 1) unique_chars_remaining++;
            l++;
        }
    }
    return res;
}

string cannonical(string s, string t) {
    int n = s.size();
    if (t.empty() || s.empty()) return "";

    int remaining = t.size();
    int count[256] = {0};

    for(char c : t) count[c]++;

    int l=0;
    int start = 0;
    int minLen = INT_MAX;

    for(int r=0; r<n; r++) {
        if(count[s[r]] > 0) remaining--;
        count[s[r]]--;

        // found valid, try find smaller
        while(remaining == 0) {
            if((r-l+1) < minLen) {
                minLen = r-l+1;
                start = l;
            }

            count[s[l]]++;
            if(count[s[l]] > 0) remaining++;
            l++;
        }
    }

    if(minLen == INT_MAX) return "";

    return s.substr(start, minLen);
}

string minWindow_sw_cannonical_gpt(string s, string t) {
    
    if(t.size() > s.size()) return "";
    
    unordered_map<char, int> need, window;    
    for(char c: t) need[c]++;

    int required = need.size();
    int formed = 0;

    int left = 0, right = 0;
    int start = 0;
    int min_len = INT_MAX;

    while(right < s.size()) {

        char c = s[right];
        window[c]++;

        // does current char satisfy requirements
        if(need.count(c) && window[c] == need[c]) {
            formed++;
        }

        // all chars valid
        while(left <= right && formed == required) {
            if(right - left + 1 < min_len) {
                min_len = right - left + 1;
                start = left;
            }

            // shrink window
            char ch = s[left];
            window[ch]--;

            if(need.count(ch) && window[ch] < need[ch]) {
                formed--;
            }

            left++;
        }


        right++;
    }

    return min_len == INT_MAX ? "" : s.substr(start, min_len);
}


int main() {
    // cout << minWindow_bf1("ADOBECODEBANC", "ABC") << endl;
    cout << minWindow_bf2("ADOBECODEBANC", "ABC") << endl;
    cout << minWindow_sliding3("ADOBECODEBANC", "ABC") << endl;
    cout << minWindow_sliding4("ADOBECODEBANC", "ABC") << endl;
    cout << cannonical("ADOBECODEBANC", "ABC") << endl;
    
    
    // cout << minWindow_bf1("a","a") << endl;
    // cout << minWindow_bf2("a","a") << endl;
    // cout << minWindow_bf1("aAbBDdcC","Bc") << endl;
    // cout << minWindow_bf2("aAbBDdcC","Bc") << endl;
    // cout << minWindow_sliding2("aAbBDdcC","Bc") << endl;
    return 0;
}

class Solution {
public:
    string minWindow(string s, string t) {
        if(s.size() == 0 || t.size() == 0) return "";

        int n = s.size();
        int l = 0, start = 0;

        int remaining = t.size();
        int min_len = INT_MAX;

        int count[256] = {0};
        for(char c : t) count[c]++;

        for(int r=0; r<n; r++) {
            if(count[s[r]] > 0) remaining--; // found a valid char
            count[s[r]]--; // non valid become negative

            // found a valid len, try shrinking
            while(remaining == 0) {
                if((r-l+1) < min_len) {
                    min_len = r-l+1;
                    start = l;
                }

                count[s[l]]++;
                if(count[s[l]] > 0) remaining++; // removed valid char
                l++;
            }
        }

        return (min_len == INT_MAX) ? "" : s.substr(start, min_len) ;
    }
};