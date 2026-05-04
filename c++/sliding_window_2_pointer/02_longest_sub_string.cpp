#include <iostream>
#include <unordered_set>
#include <vector>
#include <cstring> // memset

using namespace std;

int longestNonRepeatingSubstring1(const string& s){
    int n = s.size();
    int i=0, j=0;
    int max_len=0;

    unordered_set<char> mset;

    for(int j=0; j<n; j++) {
        
        // character already exists
        // remove from the front till valid
        while(mset.find(s[j]) != mset.end()) {
            mset.erase(s[i]);
            i++;
        }

        mset.insert(s[j]);
        max_len = max(max_len, j-i+1);
    }    
    return max_len;     
}

int longestNonRepeatingSubstring2(const string& s){
    int n = s.size();
    int i=0, j=0;
    int max_len=0;
    
    int count[26] = {0};

    while( j < n ) {        
        while( count[s[j] - 'a'] == 0 ) {
            // not duplicate            
            count[s[j] - 'a']++;
            max_len = max(max_len, (j-i+1));
            j++;
        }
        
        // remove duplicate char from the front
        while(j<n && count[s[j] - 'a'] > 0 ) {            
            count[s[i] - 'a'] = 0;
            i++;
        }
        
    }
    return max_len;     
}

int brute_force(const string& s) {
    int n = s.size();
    int i=0, j=0;
    int max_len=0;

    for(int i=0; i<n; i++){
        int hash[256] = {0};
        for(int j=i; j<n; j++){
            if(hash[s[j]]==1) break;

            int len = j-i+1;
            max_len = max(max_len, len);
            hash[s[j]] = 1;
        }
    }
    return max_len;
}

int last_seen_version(const string& s) {
    // we need to store the index of the character
    int n = s.size();
    vector<int> seen(26, -1);
    int start = 0;
    int max_len = 0;

    for(int i=0; i<n; i++){
        int c = s[i] - 'a'; // normalize to 26

        // check if character is a duplicate
        // when we come across a duplicate, we dont have the count, we have the index
        // ---a-----a----a
        // In the first pass, the window starts at index 0.
        // When we encounter a duplicate of the current character,
        // we discard the window start..last_seen[current_char].
        // The new window starts at last_seen[current_char] + 1.
        // Therefore, we only care about duplicates whose last index >= start.     
        if(seen[c] >= start) {   
            start = seen[c] + 1; // teleport start, much faster than shrinking
        }

        // store index
        seen[c] = i;
        max_len = max(max_len, i-start+1);
    }
    return max_len;
}

// START WITH THIS VERSION
int longestNonRepeatingSubstring2(string& s) {
    vector<int> seen(26, -1);
    int i = 0;
    int max_len = 0;

    for(int j=0; j<s.size(); j++) {
        int idx = s[j] - 'a';

        // duplicate char found
        // i is valid start for unique string
        if(seen[idx] >= i) { // this will always be -1 for new chars
            i = seen[idx] + 1;
        }
        seen[idx] = j;

        max_len = max(max_len, j - i + 1);
    }

    return max_len;
}


int last_seen_version2(const string& s) {
    int l=0, r=0;
    int n = s.size();
    int max_len = 0;
    int seen[26] = {-1};

    while(r<n) { // we can replace the while with a for
        if(seen[s[r]] != -1) { // extra check, just for understanding
            // duplicate
            if(seen[s[r]] >= l){
                l = seen[s[r]] + 1; // teleport l
            }
        }
        int len = r-l+1; // just for understanding
        max_len = max(max_len, len);
        seen[s[r]] = r;
        r++;
    }
    return max_len;
}

int main() {
    cout << last_seen_version("rdvfycupcugkjwsqeduutgbwlhxrxatvwvydhibtkyxqnoysgxhvjkhqydizmpyrxguwdciygzvxlclmnoanchbahfqsrrymwbgcibwyhupzndlbxnsjfoaycmnwaluznqpwl") << endl;
    // cout << longestNonRepeatingSubstring2("abba") << endl;
    return 0;
}