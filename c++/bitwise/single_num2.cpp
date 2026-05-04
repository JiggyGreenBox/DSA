#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// O(N) time
// O(N/3+1) space
int singleNumber2a(const vector<int>& nums) {
    // use a map
    unordered_map<int, int> mpp;
    for(auto num :  nums) {
        mpp[num]++;
    }
    
    for(auto pair : mpp) {
        if(pair.second == 1){
            return pair.first;
        }
    }
    return -1;
}

// O(32*N) time
// O(1) space
int singleNumber2b(const vector<int>& nums) {    
    int k = 3; // generalize for k
    // int count[32];

    int ans = 0;
    
    for(int i=0; i<32; i++) {
        int cnt=0;
        for(auto num : nums) {
            // check i'th bit
            if(num & (1<<i)) {
                // bit is 1
                // count[i]++;
                cnt++;
            }            
        }

        // for k==3, 3 bits mean
        // if(count[i]%k != 0) {
        if(cnt%k != 0) {
            ans |= (1<<i);
        }
    }
    return ans;
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


// O(n) time
// O(1) space
int singleNumber2c(const vector<int>& nums) {
    // most optimal solution
    // need log2(n) masks
    // so only practical for k==3

    int ones  = 0;
    int twoes = 0;
    // we dont care about threes

    for(auto num : nums) {
        ones  = (ones^num)  & ~twoes;
        twoes = (twoes^num) & ~ones;
    }
    return ones;

    // 2  010
    // 2  010
    // 2  010
    // 3  011

    // first pass, add to ones
    // ones  000^010 = 010 & ~(000) = 010
    // twos  000^010 = 010 & ~(010) = 000

    // second pass, add to twoes, remove from ones
    // ones  010^010 = 000 & ~(000) = 000
    // twos  000^010 = 010 & ~(000) = 010

    // third pass, removed from twoes and ones
    // ones  000^010 = 010 & ~(010) = 000
    // twos  010^010 = 000 & ~(000) = 000



}

int main() {
    cout << singleNumber2a({2, 2, 2, 3}) << endl;
    cout << singleNumber2b({2, 2, 2, 3}) << endl;
    cout << singleNumber2c({2, 2, 2, 3}) << endl;    
    return 0;
}