#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int characterReplacement1(const string& s, int k) {
    // brute force
    // n^2 
    // k distinct is allowed
    int n = s.size();
    int max_len = 0;
    unordered_map<char, int> mpp;
    
    for(int i=0; i<n; i++) {

        mpp.clear();

        for(int j=i; j<n; j++) {
            mpp[s[j]]++; // add to map

            // max_freq - string len == k
            int max_substr = 0;
            for(auto p : mpp){
                if(p.second > max_substr) max_substr = p.second;
            }

            int len = j-i+1;
            if((len - max_substr) > k) break;
            max_len = max(max_len, len);
        }
    }    
    return max_len;
}

int calc_max_freq(const vector<int>& count){
    int max_freq = 0;
    for(int c : count) {
        if(c > max_freq) max_freq = c;                    
    }
    return max_freq;
}

int calc_max_freq(const int (&count) [26]){
    int max_freq = 0;
    for(int c : count) {
        if(c > max_freq) max_freq = c;                    
    }
    return max_freq;
}

int characterReplacement2(const string& s, int k) {
    int n = s.size();

    int l=0;
    int r=0;
    int count[26] = {0};    
    int max_len = 0;
    int max_freq = 0;

    for(r=0; r<n; r++) {
        count[s[r] - 'A']++;
        
        // int max_freq = 0;
        // for(int c : count) if(c > max_freq) max_freq = c;        
        max_freq = max(max_freq, count[s[r] - 'A']); // dont bother with a freq that has reduced

        int len = r-l+1;

        // check if this len is valid
        if(len - max_freq > k) {
            count[s[l] - 'A']--;            
            l++; // for invalid len, l moves with r
        }        
    }
    return r-l;
}

int characterReplacement3(const string& s, int k) {
    int n = s.size();

    int l=0;
    int r=0;
    int count[26] = {0};    
    int max_len = 0;

    for(r=0; r<n; r++) {
        count[s[r] - 'A']++;
        
        int max_freq = 0;
        for(int c : count) if(c > max_freq) max_freq = c;

        int len = r-l+1;

        // only valid l for each r
        // goes to the max_len calc
        // so move l till len is valid
        while((r-l+1) - max_freq > k) {
            count[s[l] - 'A']--;                        
            l++;
        }  
        max_len = max(max_len, r-l+1);
    }
    return max_len;
}

// 2d practice
// O(n^2) time
// O(n) space
int characterReplacement_2nd(string s, int k) {
    int n = s.size();
    int max_len = 0;

    for(int i=0; i<n; i++) {
        unordered_map<char, int> mpp;                        
        int total = 0;
        // int max_char = 0;
        int max_char = 1;
        for(int j=i; j<n; j++) {
            mpp[s[j]]++;
            total++;
            // if(max_char == 0) max_char++;
            // else {
            //     max_char = max(max_char, mpp[s[j]]);
            // }

            max_char = max(max_char, mpp[s[j]]);

            if(total - max_char > k) break;
            max_len = max(max_len, j-i+1);
        }
    }
    return max_len;
}


int characterReplacement2_2nd(string s, int k) {
    int mpp[26] = {0};
    int i=0;
    int max_len = 0;
    int maj = 0;

    for(int j=0; j<s.size(); j++) {
        mpp[s[j] - 'A']++;
        maj = max(maj, mpp[s[j] - 'A']);

        // shrink the window till valid
        while((j-i+1) - maj > k) {
            mpp[s[i] - 'A']--;
            
            // recalculate majority element
            maj = 0;
            for(int count : mpp) maj = max(maj,count);

            i++;
        }

        max_len = max(max_len, j-i+1);
    }

    return max_len;
}

// stretch the pipe
int characterReplacement3_2nd(string s, int k) {

    unordered_map<int, int> mpp; // int, freq    
    int maj=0;

    int i=0, j;
    for(j=0; j<s.size(); j++) {
        mpp[s[j] - 'A']++;
        maj = max(maj, mpp[s[j] - 'A']);

        // total is len
        // total - maj <= k is allowed
        if((j-i+1) - maj > k) {
            mpp[s[i] - 'A']--;            
            i++;
            // We just slide the window and wait for a new max_f to break the record.s
        }        
    }
    return j-i;
}


int main() {
    cout << characterReplacement1("BAABAABBBAAA", 2) << endl;
    cout << characterReplacement1("AABABBA", 1) << endl;

    cout << characterReplacement3("BAABAABBBAAA", 2) << endl;
    cout << characterReplacement3("AABABBA", 1) << endl;
    
    return 0;
}