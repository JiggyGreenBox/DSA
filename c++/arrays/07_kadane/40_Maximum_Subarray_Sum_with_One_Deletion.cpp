/*
Maximum Subarray Sum with One Deletion
    [https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/description/]

Given an array of integers, return the maximum sum for a non-empty 
subarray (contiguous elements) with at most one element deletion. In 
other words, you want to choose a subarray and optionally delete one 
element from it so that there is still at least one element left and 
the sum of the remaining elements is maximum possible.

Note that the subarray needs to be non-empty after deleting one 
element.

 

Example 1:

    Input: arr = [1,-2,0,3]
    Output: 4
    Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus 
    the subarray [1, 0, 3] becomes the maximum value.

Example 2:

    Input: arr = [1,-2,-2,3]
    Output: 3
    Explanation: We just choose [3] and it's the maximum sum.

Example 3:

    Input: arr = [-1,-1,-1,-1]
    Output: -1
    Explanation: The final subarray needs to be non-empty. You can't 
    choose [-1] and delete -1 from it, then get an empty subarray to make 
    the sum equals to 0.
*/

/*
we can pick or start a new sub array in normal kadane


[1,-2,-2,3]

1,-2

int x = nums[i]
if i - lastidx == 0
    max({x, curr, curr + x})
else
    max(x, curr + x)
lastIdx = i;

*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

// Maximum Subarray Sum with One Deletion
int maximumSum(vector<int>& arr) {
    

    // we can delete 1 number
    // but we dont know when is the optimal deletion
    // [5, -10, -100]
    // here 5 is the best answer
    // [5, -10, 5] = 10

    // at every stage we can do a normal kadane
    // add or start a new subarray
    // then, either we skip this to normal kadane, or add to prevSkip

    // so we have noDelete, and oneDelete
    // noDelete is normal kadane, oneDelete is prev deleted once

    int n = arr.size();
    int noDelete = arr[0];
    int oneDelete = arr[0];
    int best = arr[0];

    for(int i = 1; i<n; i++) {

        int x = arr[i];

        int oldNoDelete = noDelete;
        int oldOneDelete = oneDelete;

        noDelete = max(x, oldNoDelete + x);

        // either skip this x, or add to prev skipped 
        oneDelete = max(oldNoDelete, oldOneDelete + x);

        best = max({best, noDelete, oneDelete});

    }
    return best;
}

int main() {
    vector<int> arr = {1,-2,0,3};
    cout << maximumSum(arr) << endl;

    arr = {1,-2,-2,3};
    cout << maximumSum(arr) << endl;

    arr = {-1,-1,-1,-1};
    cout << maximumSum(arr) << endl;

    return 0;
}