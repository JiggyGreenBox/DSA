/*
Count_Number_of_Nice_Subarrays
    we have a prefix approach

        that could work for negative numbers

    but constraint is >=1

    so we can use atMost(goal) - atMost(goal-1)
        instead of sum
            we have odd_count
*/

#include <iostream>
#include <vector>
using namespace std;

int atMost(const vector<int> &nums, int goal) {
    int left = 0;
    int odd_count = 0;
    int total = 0;
    for(int right=0; right<nums.size(); right++) {
        if(nums[right] & 1)
            odd_count++;

        while(odd_count > goal) {
            if(nums[left] & 1)
                odd_count--;
            left++;
        }

        total += right - left + 1;
    }
    return total;
}

int numberOfSubarrays(vector<int>& nums, int k) {
    return atMost(nums, k) - atMost(nums, k-1);
}

int main() {
    vector<int> nums = {1,1,2,1,1};
    int k = 3;
    cout << numberOfSubarrays(nums, k) << endl;

    nums = {2,4,6}; k = 1;
    cout << numberOfSubarrays(nums, k) << endl;

    nums = {2,2,2,1,2,2,1,2,2,2}; k = 2;
    // nums = {2, 1}; k = 1;
    cout << numberOfSubarrays(nums, k) << endl;
    return 0;
}