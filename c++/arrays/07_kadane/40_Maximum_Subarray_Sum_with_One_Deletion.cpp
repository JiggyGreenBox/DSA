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

/*
dp approach
    nums = [1,-2,0,3]
    best = [1+2+3]
        we exclude -2

    start with normal kadane
        keep[i] = max(a[i], keep[i-1] + a[i])

    add a state
        one deletion used
        drop[i] = max sum ending at i by dropping exactly 1 element

        this state has 2 options
        extend the drop state by adding CURR
        or use the keep[i-1] state and skip CURR

        drop[i] = max(drop[i-1] + a[i], keep[i-1])

            drop[0] = -INF



*/

#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <climits>
using namespace std;


int maximumSum1(vector<int>& arr) {
    int n = arr.size();

    vector<int> keep(n);
    vector<int> drop(n);

    keep[0] = arr[0];
    drop[0] = INT_MIN;

    int ans = arr[0];

    for(int i = 1; i < n; i++) {

        keep[i] = max(
            arr[i],
            keep[i-1] + arr[i]
        );

        drop[i] = max(
            drop[i-1] == INT_MIN
                ? INT_MIN
                : drop[i-1] + arr[i],
            keep[i-1]
        );

        ans = max({ans, keep[i], drop[i]});
    }

    return ans;
}

// Maximum Subarray Sum with One Deletion
int maximumSum2(vector<int>& arr) {
    

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
    int keep = arr[0];
    int drop = arr[0];
    int best = arr[0];

    for(int i = 1; i<n; i++) {

        int x = arr[i];

        int old_keep = keep; // dp[i-1] / keep[i-1]
        int old_drop = drop; // dp[i-1] / drop[i-1]

        keep = max(x, keep + x);

        // either skip this x, or add to prev skipped 
        drop = max(old_keep, old_drop + x);

        best = max({best, keep, drop});

    }
    return best;
}

int main() {
    vector<int> arr = {1,-2,0,3};
    cout << maximumSum1(arr) << endl; // 4
    assert(maximumSum1(arr) == 4);
    assert(maximumSum2(arr) == 4);

    arr = {1,-2,-2,3};
    cout << maximumSum1(arr) << endl; // 3
    assert(maximumSum1(arr) == 3);
    assert(maximumSum2(arr) == 3);

    arr = {-1,-1,-1,-1};
    cout << maximumSum1(arr) << endl; // -1
    assert(maximumSum1(arr) == -1);
    assert(maximumSum2(arr) == -1);

    return 0;
}