#include <iostream>
#include <vector>
using namespace std;

void printBool(bool b) {
    if(b) cout << "true";
    else cout << "false";
    cout << "\n\n";
}

// this version is wrong 
// if we stop at the last index it returns false
bool canJump1(const vector<int>& nums) {
    // take a step at each num

    int steps_left = 0;
    for(auto num : nums) {
        steps_left = max(steps_left-1, num);
        if(steps_left <= 0) return false;
    }
    return true;
}

bool canJump2(const vector<int>& nums) {
    // take a step at each num

    int steps_left = 0;
    int n = nums.size();
    for(int i=0; i<n; i++){
        steps_left = max(steps_left-1, nums[i]);
        if(steps_left <= 0 && i<n-1) return false;
    }
    return true;
}

// cannonical
bool canJump3(const vector<int>& nums) {
    int farthest = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        // if we cannot even reach index i
        if (i > farthest) return false;

        // update the farthest reachable index
        farthest = max(farthest, i + nums[i]);
    }
    return true;

    // int dist_covered = 0;
    // int n = nums.size();
    // for(int i=0; i<n; i++) {
    //     if(dist_covered < i) return false;

    //     dist_covered = max(dist_covered, i+nums[i]);
    // }
    // return true;
}


int main() {
    printBool(canJump2({2, 3, 1, 1, 4}));
    printBool(canJump2({3, 2, 1, 0, 4}));
    printBool(canJump3({1, 2, 2, 1, 0}));
    
    return 0;
}