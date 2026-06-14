#include <iostream>
#include <vector>
using namespace std;

/*
Find out how many times the array is rotated

    Given an integer array nums of size n, sorted in ascending order with 
    distinct values. The array has been right rotated an unknown number 
    of times, between 0 and n-1 (including). Determine the number of 
    rotations performed on the array.

*/

/*
Invariant:
    Minimum element index is inside [l,r].

Observation:
    nums[mid] > nums[r]
        => minimum lies right of mid

    nums[mid] <= nums[r]
        => minimum lies at mid or left of mid

Discard Rule:
    nums[mid] > nums[r]
        l = mid + 1

    else
        r = mid
*/

int findKRotation(vector<int> &nums) {
    int n = nums.size();
    int l = 0, r = n-1;

    while(l < r) {
        int mid = l + (r-l)/2;

        if(nums[mid] > nums[r]) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    return l;
}

int main() {
    return 0;
}