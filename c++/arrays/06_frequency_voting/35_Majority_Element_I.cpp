/*
Majority Element-I

Given an integer array nums of size n, return the majority element of 
the array.



The majority element of an array is an element that appears more than 
n/2 times in the array. The array is guaranteed to have a majority 
element.


Example 1

Input: nums = [7, 0, 0, 1, 7, 7, 2, 7, 7]

Output: 7

Explanation:

The number 7 appears 5 times in the 9 sized array

Example 2

Input: nums = [1, 1, 1, 2, 1, 2]

Output: 1

Explanation:

The number 1 appears 4 times in the 6 sized array

Example 3

Input: nums = [-1, -1, -1, -1]

Output:

-1
*/

/*
only 1 element can appear more than n/2 times
    so just keep the candidate by count
*/
#include <vector>
#include <iostream>

using namespace std;

int majorityElement(vector<int>& nums) {
    int candidate = 0;
    int count = 0;

    for(int n : nums) {
        if(count == 0) {
            candidate = n;            
        }

        if(candidate == n)
            count++;
        else
            count--;            
    }

    return candidate;
}

int majorityElement2(vector<int>& nums) {
    int n = nums.size();
    
    int candidate = nums[0];
    int count = 1;

    for(int i=1; i<n; i++) {
        if(count == nums[i]) {
            count++;
        }
        else{
            count--;
        }

        if(count == 0) {
            candidate = nums[i];
            count = 1;
        }            
    }

    return candidate;
}

int main() {
    vector<int> v = {7, 0, 0, 1, 7, 7, 2, 7, 7};
    cout << majorityElement(v) << endl;

    v = {1, 1, 1, 2, 1, 2};
    cout << majorityElement(v) << endl;
    return 0;
}