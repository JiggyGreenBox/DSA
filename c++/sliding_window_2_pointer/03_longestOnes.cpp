#include <iostream>
#include <vector>

using namespace std;

int longestOnes(const vector<int>& nums, int k) {
    int i=0, n = nums.size();
    int max_len = 0;
    int flipped = 0;
    for(int j=0; j<n; j++) {

        // 3 cases
        // 1. nums[j] == 1, calc len
        // 2. nums[j] == 0, can flip, calc len
        // 3. nums[j] == 0, can NOT flip, move i, calc len

        // check if shrink is required, before processing j
        if(nums[j] == 0 && flipped == k){
            // shrink window
            while(nums[i] != 0) i++;
            i++; // i is at next element after 1st zero
            flipped--;
        }
        
        // expand window        
        if(nums[j] == 0) flipped++;
        int len = j-i+1;
        max_len = max(max_len, len);        
    }
    return max_len;
}

int longestOnes2(const vector<int>& nums, int k) {
    int i=0, n = nums.size();
    int max_len = 0;
    int zeros = 0;
    for(int j=0; j<n; j++) {
        // if we see a zero, count it        
        if(nums[j] == 0) zeros++;

        // never allow more than k, zeros
        while(zeros > k) {
            if(nums[i] == 0) zeros--;
            i++;
        }

        max_len = max(max_len, j-i+1);
    }
    return max_len;
}

int longestOnes3(const vector<int>& nums, int k) {
    int i=0, n = nums.size();
    int max_len = 0;
    int zeros = 0;
    for(int j=0; j<n; j++) {
        // if we see a zero, count it        
        if(nums[j] == 0) zeros++;

        // never allow more than k, zeros
        if(zeros > k) {
            if(nums[i] == 0) zeros--;
            i++;
        }

        if(zeros <= k){
            max_len = max(max_len, j-i+1);
        }        
    }
    return max_len;
}

int longestOnes4(const vector<int>& nums, int k) {
    int i=0, j;    
    for(j=0; j<nums.size(); j++) {        
        if(nums[j] == 0) k--;        
        if(k < 0) { // window is invalid, take care of i, runs till k is zero again
            if(nums[i] == 0) k++; // a zero was found, increase k
            i++; // we are clipping from the start
        }        
    }
    // j becomes n, after the loop
    // thats why no + 1, for len calc
    return j-i;
}

int main() {
    // cout << longestOnes({1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 3) << endl;
    cout << longestOnes4({0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1}, 3) << endl;
    
    return 0;
}