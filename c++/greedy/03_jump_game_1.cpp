#include <iostream>
#include <vector>
using namespace std;

void printBool(bool b) {
    if(b) cout << "true";
    else cout << "false";
    cout << "\n\n";
}


/*
Jump Game - I
    [https://takeuforward.org/plus/dsa/problems/jump-game---i?subject=dsa&approach=optimal]

    Given an array of integers nums, each element in the array represents 
    the maximum jump length at that position. Initially starting at the 
    first index of the array, determine if it is possible to reach the 
    last index. Return true if the last index can be reached, otherwise 
    return false.


Example 1

    Input : [2, 3, 1, 1, 4]

    Output : true

    Explanation : We can simply take Jump of 1 step at each index to 
    reach the last index.

Example 2

    Input : [3, 2, 1, 0, 4]

    Output : false

    Explanation : No matter how you make jumps you will always reach the 
    third index (0 base) of the array.

    The maximum jump of index three is 0, So you can never reach the last 
    index of array.

Example 3

    Input : [5, 3, 2, 1, 0]

    Output:

    true
*/



// cannonical
bool canJump(const vector<int>& nums) {
    int farthest = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        // if we cannot even reach index i
        if (i > farthest) return false;

        // update the farthest reachable index
        farthest = max(farthest, i + nums[i]);

        // early exit
        if (farthest >= n - 1)
            return true;
    }
    return true;    
}


int main() {
    printBool(canJump({2, 3, 1, 1, 4}));
    printBool(canJump({3, 2, 1, 0, 4}));
    printBool(canJump({1, 2, 2, 1, 0}));
    
    return 0;
}