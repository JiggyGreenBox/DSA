#include <iostream>
#include <vector>
using namespace std;


int numSubarraysWithSum1(const vector<int>& nums, int goal) {
    // brute force
    // n^2 loop
    int n = nums.size();
    int total = 0;

    for(int i=0; i<n ; i++) {
        int sum = 0;
        for(int j=i; j<n; j++) {
            sum += nums[j];

            if(sum == goal) total++;

            if(sum > goal) break;
        }
    }
    return total;
}

int numSubarraysWithSum2(const vector<int>& nums, int goal) {
    int n = nums.size();
    int total = 0;
    int sum = 0;
    int l = 0, r = 0;
    int leading_zeros = 0;
    

    for(int r=0; r<n; r++) {
        sum += nums[r];

        if(sum == goal) total++;

        while(sum > goal) {
            sum -= nums[l];
            if(sum == goal) total++;
            l++;
        }
    }

    return total;
}

int numSubarraysWithSum3(const vector<int>& nums, int goal) {
    int n = nums.size();
    int total = 0;
    int sum = 0;
    int l = 0, r = 0;
    int leading_zeros = 0;

    // take care of leading zeros
    while(nums[r] == goal) {
        leading_zeros++;
        total += leading_zeros;
        r++;
    }

    while(r<n) {
        sum += nums[r];

        if(sum == goal) total++;

        while(l<r && sum > goal) {
            sum -= nums[l];
            if(sum == goal) total++;
            l++;
        }
        r++;
    }

    return total;
}



int atMost(const vector<int>& nums, int goal) {
    if(goal < 0) return 0;
    int l=0;
    int count = 0, sum = 0;

    for(int r=0; r < nums.size(); r++) {
        sum += nums[r];

        while(sum > goal) {
            sum -= nums[l];
            l++;
        }
        // if(sum <= goal) count += (r-l+1);            
        count += (r-l+1);            
    }

    return count;
}

int cannoical(const vector<int>& nums, int goal) {
    return atMost(nums, goal) - atMost(nums, goal-1);
}

int main() {    
    // cout << numSubarraysWithSum1({1, 1, 0, 1, 0, 0, 1}, 3) << endl;
    // // cout << numSubarraysWithSum2({1, 1, 0, 1, 0, 0, 1}, 3) << endl;
    // // cout << numSubarraysWithSum1({0, 0, 0, 0, 1}, 0) << endl;
    // // cout << numSubarraysWithSum2({0, 0, 0, 0, 1}, 0) << endl;
    // cout << numSubarraysWithSum3({1, 1, 0, 1, 0, 0, 1}, 3) << endl;
    cout << cannoical({0, 0, 0, 0, 1}, 1) << endl;
    return 0;
}


// 0           +1
// 0 0         +2
// 0 0 0       +3
// 0 0 0 0     +4