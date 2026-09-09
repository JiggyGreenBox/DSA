/*
Sep 7
    last - sep 6


Today's Session 1 — Problem 1

You are given an array nums containing n integers. Every element 
appears twice except for one element, which appears exactly once.

Return the element that appears only once.

Constraints:

O(n) time
O(1) extra space


Brute force
    use a freq map
        num, count
    
    return count == 1

Observation
    since every element comes twice except for 1 element
    we can use the xor property of xorr^xorr = 0
    and 0^num = num
    so if we xorr all numbers the unique number will remain
Invariant
    xorr all numbers in which the duplicate numbers cancel out each other 
    with the single number remaining
Algorithm
    int singleNumner(vector<int> & nums) {
        int xorr = 0;

        for(int num : nums) {
            xorr ^= num;
        }
        return xorr;
    }
    int main() {
        vector<int> nums = {2, 2, 1};
        cout << singleNumner(nums) << endl; // 1
        nums = {4, 1, 2, 1, 2};
        cout << singleNumner(nums) << endl; // 4
        return 0;
    }
    
Complexity
    O(n) time
    O(1) space
-----------
    green green


Problem 2 — Mixed Revision

You are given an integer array nums and must rearrange it in-place so 
that all negative numbers and positive numbers alternate.

Assume the array contains an equal number of positive and negative 
elements.

The relative order of elements does not need to be preserved.

Example

    nums = [3, 1, -2, -5, 2, -4]

    Possible output:
    [3, -2, 1, -5, 2, -4]


Brute force
    use 2 vectors to store +ve numbers
    and -ve numbers
    then write to the answer vector in an alternate manner
Observation
    we have equal number of positive and negative numbers
    we can use 2 pointers
        when we put a positive and idx=0 then the next +ve is at idx=2
        for odd we put it at idx=1 then idx=2
Invariant
    keep 3 pointers, one for odd, one for even
    when the reader pointer find odd or even place at correct spot
    then move that pointer += 2
Algorithm
    vector<int> rearrange(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans(n);

        int pos = 0;
        int neg = 1;

        for(int i=0; i<n; i++) {
            if(nums[i] > 0) {            
                ans[pos] = nums[i];
                pos += 2;
            }
            else {            
                ans[neg] = nums[i];
                neg += 2;
            }
        }
        return ans;
    }
Complexity
    O(n) time
    O(1) extra space
    O(n) answer space

-----
    green/green

Problem 3 — Session 1

    You are given an array nums containing integers from 1 to n. Some 
    elements may appear multiple times, and some may be missing.

    Return all numbers in [1,n] that do not appear in nums.

    You must solve it in O(n) time and O(1) extra space, excluding the 
    returned answer.


nums = [4,3,2,7,8,2,3,1]

Output = [5,6]


Brute force
    run a loop from 1..n
        check for the number in nums
            if not found store

Observation
    since expected nums are from [1,n]
        we want numbers that are missing from this range
    we can encode found numbers into [0,n-1]

    if we find a number swap it into its right place
        3 should be placed at 2

    then when we check the array again
        if we find nums[i] != i+1
        it is a missing number
    
Invariant
    use encoding to place numbers at idx-1 position
    then another scan to check missing
Algorithm
    vector<int> missing(vector<int> &nums) {
        vector<int> ans;

        int n = nums.size();

        
        for(int i=0; i<n; i++) {
            while(nums[i] >= 1 && nums[i] <=n && nums[nums[i]-1] != nums[i]) {
                swap(nums[nums[i]-1], nums[i]);
            }
        }

        for(int i=0; i<n; i++) {
            if(nums[i] != i+1)
                ans.push_back(i+1);
        }

        return ans;
    }
Complexity
    O(n) time
    O(n) auxillary space
    O(1) extra space


================================================
session 2

Problem 1 — Binary Search

    You are given a sorted array nums that has been rotated at an unknown 
    pivot.

    All elements are distinct.

    Return the minimum element in the array.

    Examples
        nums = [4,5,6,7,0,1,2]
        Output: 0

        nums = [3,4,5,1,2]
        Output: 1

        nums = [1,2,3,4,5]
        Output: 1

Brute Force:
    linear scan of all elements
Observation:
    numbers are sorted but rotated
    if not rotated a simple binary search would get us the answer
    but since the array is rotated we need to find which half is sorted
    and then take the decision to discard

Invariant:
    ans lies in [l,r]
    use mid and l and r to decide which half is sorted
    find sorted half and then decide to discard half

    if mid is greater it is not a candidate
        l = m + 1
    else
        r = m, could be the min

Algorithm:

    int minRotatedArray(vector<int> & nums) {
        int n = nums.size();
        int l = 0;
        int r = n-1;

        while(l < r) {
            int m = l + (r-l)/2;

            if(nums[m] > nums[r]) {
                l = m+1;
            }
            else {
                r = m;
            }
        }
        return nums[r];
    }

Complexity:
    O(logn) time
    O(1) space

-------
    green / green

Problem 2 — Stack / Queue

    You are given an array temperatures where temperatures[i] is the 
    temperature on day i.

    For each day, return the number of days you have to wait until a 
    warmer temperature. If there is no future day with a warmer 
    temperature, return 0.

    Example 1
        temperatures = [73,74,75,71,69,72,76,73]

        Output = [1,1,4,2,1,1,0,0]

Brute force
    for each day i
        go right till greater temp found then return j-i
    n^2 time
    1 space
Observation
    we want nge for these temps
    [1,2,3,4,5]
    [2,3,4,5,-1]

    [ 5, 4, 3, 2, 1]
    [-1,-1,-1,-1,-1]

    we process R to L
    use a stack
        if a larger element than top is present pop

    we store idx
Invariant
    use a decreasing stack to get nge 
        use this nge index to calculate days
Algorithm
    vector<int> getDays(vector<int> &temps) {
        int n = temps.size();
        vector<int> ans(n, 0);

        stack<int> st;

        for(int i=n-1; i>=0; i--) {

            while(!st.empty() && temps[i] > temps[st.top()])
                st.pop();

            ans[i] = st.empty() ? 0 : (st.top() - i);

            st.push(i);
        }

        return ans;
    }
Complexity
    O(n) time
    O(n) space


------------
Review
    green / green

-----------

Problem 3 — Session 2

You are given an integer array nums.

Find the maximum absolute difference between two elements such that 
the larger element appears after the smaller element.

In other words, find:
    nums[j] - nums[i]

    where j > i


Brute force
    for each idx
        go right and find the max positive diff
        track max across all loops

    n^2 time
    1 space


Observation
Invariant
Algorithm
Complexity
    

Scan left → right. Maintain the minimum value encountered so far. 
For every current value, calculate the profit/difference against that 
minimum.

*/
#include <vector>
#include <iostream>
#include <climits>
#include <stack>
using namespace std;



int maxProfit(vector<int>& prices) {
    int minSoFar = prices[0];
    int best = 0;

    for (int i = 1; i < prices.size(); i++) {
        best = max(best, prices[i] - minSoFar);
        minSoFar = min(minSoFar, prices[i]);
    }

    return best;
}

int main() {
    

    return 0;
}


