/*
Count of Range Sum
    [https://leetcode.com/problems/count-of-range-sum/description/]

Given an integer array nums and two integers lower and upper, return 
the number of range sums that lie in [lower, upper] inclusive.

Range sum S(i, j) is defined as the sum of the elements in nums 
between indices i and j inclusive, where i <= j.

 

Example 1:

Input: nums = [-2,5,-1], lower = -2, upper = 2
Output: 3
Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their 
respective sums are: -2, -1, 2.
Example 2:

Input: nums = [0], lower = 0, upper = 0
Output: 1
*/

/*
we want sum(i,j) >= lower && <= upper

    (prefix[r] - prefix[l-1]) >= lower && <= upper
        
    10 - 5 >= 4 && <= 7
    10 >= 9 && <= 14


    prefix[r] >= L+prefix[l-1] && <=U+prefix[l-1]

    we cant look for 1 exact match here
        we need to query a range

    we want sum(l,r) >= L && <= U

    so L <= sum(i,j) <= U

    L <= sum(i,j) <= U

    L <= pre[r] - pre[l-1] <= U

    L <= p[r] - p[l] <= U

    sub p[r]
        L - p[r] <= -p[l] <= U - p[r]

    mult -1
        then < becomes >
        p[r] - L >= p[l] >= p[r] - U


    


*/


#include <vector>
#include <unordered_map>
using namespace std;
int countRangeSum(vector<int>& nums, int lower, int upper) {

    unordered_map<int,int> mpp; // prefix, count

    int prefix = 0;

    for(int num : nums) {
        prefix += num;


    }
}
