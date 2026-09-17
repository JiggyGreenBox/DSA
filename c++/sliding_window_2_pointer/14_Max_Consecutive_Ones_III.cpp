#include <iostream>
#include <vector>

using namespace std;


/*
    Longest subarray containing at most k zeros.

    Invariant:
    window has <= k zeros.

    If zeros > k:
        shrink from left until valid.

    Time:  O(n)
    Space: O(1)
*/
int longestOnes(const vector<int>& nums, int k) {
    
    int left = 0;
    int zeros = 0;
    int max_len = 0;
    for(int right=0; right<nums.size(); right++) {
        // if we see a zero, count it        
        if(nums[right] == 0) zeros++;

        // never allow more than k, zeros
        while(zeros > k) {
            if(nums[left] == 0) 
                zeros--;
            left++;
        }

        max_len = max(max_len, right - left + 1);
    }
    return max_len;
}


int main() {
    // cout << longestOnes({1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 3) << endl;
    cout << longestOnes({0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1}, 3) << endl;
    
    return 0;
}