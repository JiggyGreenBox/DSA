#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int kDistinctChar1(const string& s, int k) {
    // brute force
    // loop n^2, when distinct chars exceeds k, break
    // return max_len
    int max_len = 0;    
    int n = s.size();

    for(int i=0; i<n; i++){

        unordered_set<char> mset;

        for(int j=i; j<n; j++){
            mset.insert(s[j]);
            if(mset.size() > k){                
                break;
            } 
            max_len = max(max_len, j-i+1);
        }
    }
    return max_len;
}

int kDistinctChar2(const string& s, int k) {
    // expand window
    // allowing distinct elements <= k

    // when >= k
    // we must remove characters till == k

    // calc max_len

    int max_len = 0;
    int n = s.size();
    // we have options for tracking distinct elements
    //  - count array, we cannot use a count array or vector    
    //  - unordered_set, we cannot use a set here either
    //  - unordered_map
            // - can store last seen idx
            // we can jump
    
    unordered_map<char, int> mpp;
    int l = 0;

    for(int r=0; r<n; r++) {
        // add char to map
        char c = s[r];
        mpp[c]++;

        // only allow 2 distinct chars
        while(mpp.size() > k){
            mpp[s[l]]--;
            if(mpp[s[l]] == 0) mpp.erase(s[l]);
            l++;
        }

        max_len = max(max_len, r-l+1);
    }
    return max_len;
}

int kDistinctChar3(const string& s, int k) {    
    int max_len = 0;
    int n = s.size();
    int count[256] = {0};
    int distinct = 0;
    int l = 0;
    int r = 0;

    for(r=0; r<n; r++) {
                
        if(count[s[r]] == 0) distinct++;
        count[s[r]]++;

        // lets not shrink the window
        // we are finding max_len        
        if(distinct > k){
            count[s[l]]--;
            if(count[s[l]] == 0) distinct--;
            l++;
        }

        // max_len = max(max_len, r-l+1);
    }
    // return max_len;
    // cout << "L:" << l << endl;
    // cout << "R:" << r << endl; // for[0..n-1], r ends up at r==n, 1 index ahead
    return r-l;
}


int main() {
    // cout << kDistinctChar1("aababbcaacc", 2) << endl;
    // cout << kDistinctChar2("aababbcaacc", 2) << endl;
    // cout << kDistinctChar3("aababbcaacc", 2) << endl;
    // // cout << kDistinctChar1("abcddefg", 3) << endl;
    // cout << kDistinctChar2("abcddefg", 3) << endl;
    // cout << kDistinctChar3("abcddefg", 3) << endl;

    cout << kDistinctChar3("12345678", 10) << endl;
    return 0;
}