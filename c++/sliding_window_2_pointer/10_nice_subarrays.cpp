#include <iostream>
#include <vector>
using namespace std;

// Given an array nums and an integer k. An array is called
// nice if and only if it contains k odd numbers. Find the number
// of nice subarrays in the given array nums.  
/*
[1,2,4,2,4,2,1,1]
k=2
    valid subarrays
        [1,2,4,2,4,2,1]
        [2,4,2,4,2,1,1]
        [4,2,4,2,1,1]
        [2,4,2,1,1]
        [4,2,1,1]
        [2,1,1]
        [1,1]
*/


int atMost(const vector<int>& nums, int k) {
    if(k<0) return 0;

    int l=0;
    int n = nums.size();
    int count = 0;
    int odds = 0;

    for(int r=0; r<n; r++) {
        if(nums[r] & 1) odds++;

        while(l<=r && odds > k){
            if(nums[l] & 1) odds--;
            l++;
        }
        count+= r-l+1;
    }

    return count;
}

int numberOfOddSubarrays(const vector<int>& nums, int k) {
    return atMost(nums, k) - atMost(nums, k-1);
}

int main() {
    cout << numberOfOddSubarrays({1, 1, 2, 1, 1}, 3) << endl;
    cout << numberOfOddSubarrays({4, 8, 2}, 1) << endl;    
    return 0;
}