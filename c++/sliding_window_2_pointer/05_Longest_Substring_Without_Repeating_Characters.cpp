#include <iostream>
#include <unordered_set>
#include <vector>
#include <cstring> // memset

using namespace std;





int brute_force(const string& s) {
    int n = s.size();
    int i=0, j=0;
    int max_len=0;

    for(int i=0; i<n; i++) {

        int hash[256] = {0};

        for(int j=i; j<n; j++) {

            if(hash[s[j]] ==1 ) 
                break;
            
            hash[s[j]] = 1;

            int len = j-i+1;
            max_len = max(max_len, len);
        }
    }
    return max_len;
}

/*
    Longest substring without repeating characters.

    Insight:
    Store the last index of each character.
    On a duplicate, teleport left to last_seen + 1.

    Important:
    Only move left forward:
        if (seen[c] >= left)
            left = seen[c] + 1;

    Time:  O(n)
    Space: O(1) for fixed alphabet
*/
int longest_non_repeating_substring(const string& s) {

    vector<int> seen(26, -1); // -1, since left starts at 0

    int left = 0;
    int max_len = 0;

    for(int right = 0; right < s.size(); right++) {

        int idx = s[right] - 'a';

        // duplicate char found        
        if(seen[idx] >= left)
            left = seen[idx] + 1;
        

        seen[idx] = right;
        max_len = max(max_len, right - left + 1);
    }

    return max_len;
}


int main() {
    cout << longest_non_repeating_substring("rdvfycupcugkjwsqeduutgbwlhxrxatvwvydhibtkyxqnoysgxhvjkhqydizmpyrxguwdciygzvxlclmnoanchbahfqsrrymwbgcibwyhupzndlbxnsjfoaycmnwaluznqpwl") << endl;
    // cout << longestNonRepeatingSubstring2("abba") << endl;
    return 0;
}