#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

// O(N) time
// O(N/3+1) space
vector<int> singleNumber3a(const vector<int>& nums) {
    // use a map
    unordered_map<int, int> mpp;
    for(auto num :  nums) {
        mpp[num]++;
    }
    vector<int> ans;
    for(auto pair : mpp) {
        if(pair.second == 1){
            ans.push_back(pair.first);
            // return pair.first;
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

// create buckets
// xor all elements
// [1, 2, 1, 3, 5, 2]
// all evens nums xored = 0
// 3^5
//  011
// ^101
// =110

// for xor set bit, each number has different bits set
// we can now use this bit to divide all numbers into 
// set and unset at this bit
// we will have 2 buckets
// within each bucket xor all numbers
// this will results in 3, in one bucket
// and 5 in the other bucket
vector<int> singleNumber3b(const vector<int>& nums) {    
    int x = 0;
    for(auto num : nums) {
        x ^= num;
    }

    // get rightmost set bit
    x = x&~(x-1);

    // 2 buckets
    // where righmost bit is set
    // and not set
    int a=0;
    int b=0;
    for(auto num : nums) {
        // set
        if(num & x) {
            a^=num;
        }
        // unset
        else{
            b^=num;
        }        
    }
    if(a>b) return {b,a};
    return {a,b};
}

// check i'th bit
// 1101
// 0010
// if 1101
//  & 0010
//  = 0000 // bit not set, else set


// adding to ans
// [1, 0, 3, 0, 1, 1, 3, 3, 10, 0]
// 1       0001
// 0       0000
// 3       0011
// 0       0000
// 1       0001
// 1       0001
// 3       0011
// 3       0011
// 10      1010
// 0       0000
// ------------
// total   1046
//         1010

void printAns(const vector<int>& results){
    cout << "[ ";
    for(auto x : results) cout << x << " ";
    cout << "]\n";
}

int main() {
    printAns(singleNumber3a({1, 2, 1, 3, 5, 2}));
    printAns(singleNumber3b({1, 2, 1, 3, 5, 2}));    
    return 0;
}