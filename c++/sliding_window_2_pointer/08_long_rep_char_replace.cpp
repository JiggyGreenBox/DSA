#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
Longest Repeating Character Replacement
    [https://takeuforward.org/plus/dsa/problems/longest-repeating-character-replacement?subject=dsa&approach=brute]

Given an integer k and a string s, any character in the string can be 
selected and changed to any other uppercase English character. This 
operation can be performed up to k times. After completing these 
steps, return the length of the longest substring that contains the 
same letter.


Example 1

    Input : s = "BAABAABBBAAA" , k = 2
    Output : 6
    Explanation : we can change the B present at index 0 , 3 (0 base 
    indexing) to A.
    The new string is "AAAAAABBBAAA".
    The substring "AAAAAA" is the longest substring having same letter 
    with length 6.

Example 2

    Input : s = "AABABBA" , k = 1
    Output : 4
    Explanation : The underlined characters are changed in the new string 
    obtained.
    The new string is "AABBBBA". The substring "BBBB" is the answer.
    There are other ways to achieve this answer.

Example 3

    Input : s = "ABCDEF" k = 1
    Output: 2
*/


/*
expand right
    ↓
add s[right]
    ↓
calculate:
windowLength - maxFrequency
    ↓
if > k:
    shrink from left
    ↓
otherwise:
    update answer
*/

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
            int max_freq = 0;
            for(auto [ch, freq] : mpp)
                max_freq = max(max_freq, freq);
            

            int len = j-i+1;
            if((len - max_freq) > k) 
                break;

            max_len = max(max_len, len);
        }
    }    
    return max_len;
}

// this version doesnt bother to shring the window
int characterReplacement2(const string& s, int k) {
    int n = s.size();

    int l = 0;
    int r = 0;
    int count[26] = {0};    
    int max_len = 0;
    int max_freq = 0;

    for(r=0; r<n; r++) {
        count[s[r] - 'A']++;
                       
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
// this version shrinks the window 
// before calculating len
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


int characterReplacement(string s, int k) {
    int count[26] = {0};

    int left = 0;
    int maxFreq = 0;    
    int right = 0;

    for (right = 0; right < s.size(); right++) {

        count[s[right] - 'A']++;

        maxFreq = max(maxFreq,
                       count[s[right] - 'A']); // dont care about decreasing maxFreq
        

        // this can be while
        // but we dont care, we want max
        if (right - left + 1 - maxFreq > k) {
            count[s[left] - 'A']--;
            left++;
        }        
    }

    return right - left; // right==n after loop
}


int main() {
    cout << characterReplacement1("BAABAABBBAAA", 2) << endl;
    cout << characterReplacement1("AABABBA", 1) << endl;

    cout << characterReplacement3("BAABAABBBAAA", 2) << endl;
    cout << characterReplacement3("AABABBA", 1) << endl;
    
    return 0;
}