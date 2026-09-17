#include <iostream>
#include <unordered_map>
#include <cstring> // Required for memset
#include <vector>
#include <algorithm>
using namespace std;

// brute force
// recreate the un_map after every i
int numberOfSubstrings1(string s) {
    // brute force
    // n^2 2-loop
    int total = 0;
    int n = s.size();
    unordered_map<char, int> mpp;
    for(char i='a'; i<='c';i++) mpp[i]++;
    int count = 0;
    

    for(int i=0; i<n; i++) {

        mpp.clear();
        for(char i='a'; i<='c';i++) mpp[i]++;
        count = 0;

        for(int j=i; j<n; j++) {
            mpp[s[j]]--;
            if(mpp[s[j]]==0) count++;

            // valid subtring
            if(count == 3) {
                total++;
                // break;
            }
        }
    }

    return total;
}

// brute force
// use a count array instead of un-map
int numberOfSubstrings2(string s) {
    // brute force
    // n^2 loop, count array
    int n = s.size();
    int count[3] = {0};    
    int total = 0;

    for(int i=0; i<n; i++) {
        // count[3] = {0};
        memset(count, 0, sizeof(count));
        int found = 0;
        for(int j=i; j<n; j++) {
            count[s[j]-'a']++;
            if(count[s[j]-'a'] == 1) found++;
            
            if(found == 3) total++;
        }
    }
    return total;
}

int numberOfSubstrings_sliding1(string s) {
    int n = s.size();
    int total = 0;
    int count[3] = {0};
    int l=0;
    int chars_found=0;

    for(int r=0; r<n; r++) {
        count[s[r]-'a']++;
        if(count[s[r]-'a'] == 1) chars_found++;

        while(chars_found == 3) {
            // total++; // found a valid substring
            total += n-r; // add all to the right

            // try to remove chars from the front
            count[s[l]-'a']--;
            if(count[s[l]-'a'] == 0) chars_found--;
            // else total++; // removed char didnt move the count
            l++;
        }
    }
    return total;
}

// use r while counting
int numberOfSubstrings(string s) {
    int n = s.size();
    int count[3] = {0};
    int l = 0;
    int ans = 0;

    for (int r = 0; r < n; r++) {
        count[s[r] - 'a']++;

        // shrink window while it is valid
        while (count[0] > 0 && count[1] > 0 && count[2] > 0) {
            ans += n - r;          // all extensions are valid
            count[s[l] - 'a']--;   // remove left char
            l++;
        }
    }
    return ans;
}

int numberOfSubstrings_min_index(string s) {
    
    /*
    this method is counting from the left,
        store min index for each char a,b,c
        example [0,a,b,c,0,0]
        at c there are 2 substrings
        [0,a,b,c] & [a,b,c]

    since we index at 0, we can count this with min-idx + 1
    [abcba]

    [0,-1,-1]  
    [0, 1,-1]
    [0, 1, 2] +(0+1)
    [0, 3, 2] +(0+1)
    [4, 3, 2] +(2+1)
    */

    vector<int> last(3, -1);
    int count = 0;
    for(int i=0; i<s.size(); i++) {
        last[s[i] - 'a'] = i; // last idx

        int min_idx = min({last[0], last[1], last[2]});

        // all chars found
        if(min_idx != -1) {
            count += (min_idx + 1); // left based counting
        }
    }
    return count;
}

int main() {
    // cout << numberOfSubstrings1("abcba") << endl;
    // cout << numberOfSubstrings2("abcba") << endl;    
    // cout << numberOfSubstrings1("ccabcc") << endl;
    // cout << numberOfSubstrings2("ccabcc") << endl;
    cout << numberOfSubstrings_sliding1("abcba") << endl; // 5
    cout << numberOfSubstrings_sliding1("ccabcc") << endl; // 8
    return 0;
}