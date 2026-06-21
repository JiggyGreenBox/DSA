#include <iostream>
#include <vector>
using namespace std;

/*

Split array - largest sum

    Given an integer array a of size n and an integer k. Split the array 
    a into k non-empty subarrays such that the largest sum of any 
    subarray is minimized. Return the minimized largest sum of the split.


    Example 1

        Input: a = [1, 2, 3, 4, 5], k = 3
        Output:6

        Explanation: There are many ways to split the array a[] into k 
        consecutive subarrays. The best way to do this is to split the array 
        a[] into [1, 2, 3], [4], and [5], where the largest sum among the 
        three subarrays is only 6.

    Example 2

        Input: a = [3,5,1], k = 3
        Output: 5

        Explanation: There is only one way to split the array a[] into 3 
        subarrays, i.e., [3], [5], and [1]. The largest sum among these 
        subarrays is 5.
*/


/*

Split array - largest sum
    split into k subarrays with min of the max_sum of any subarray

    fix X and find min subarrays possible

    small X = more subarrays
    large X = less subarrays

    Feasible:
        required(X) <= k

    F F F F T T T T
    find first true

    required(X):
        int sum = 0
        int count = 1
        for(num : nums)
            if(sum + num) <= X
                sum += num
            else
                sum = num
                count++
        return count
*/

int largestSubarraySumMinimized(vector<int> &a, int k) {

}

int main() {
    return 0;
}