/*
Sep 6
    last - sep 2 

Problem 1 — Arrays

You are given an array nums containing n integers.

Find the length of the shortest continuous subarray which, if sorted 
in ascending order, makes the entire array sorted in ascending order.

nums = [2, 6, 4, 8, 10, 9, 15]
Output: 5


6>5
4>6
    no
    right = idx4
5 [11,4] 8

Brute force
    n^2 from left to find the largest out of place element from left (6)
    n^2 from right to find smallest element out of place (9)
        return len

Observation
    we can find the first inversion from the left
        where nums[i] > nums[i+1]

    we can find the first inversion from the right
        where nums[j-1] > nums[j]

    then for the range [i,j]
        we want min and max in this range

    we check if there are any elements left of i, larger than min
    we check if there are any elements right of j smaller than max
        if found extend the range

    this is the sub array that needs to be sorted
    return len
Invariant
Algorithm
    int subArray(vector<int> &nums) {
        int n = nums.size();

        if(n == 0)
            return 0;
        
        int left = 0;

        int right = n-1;
        int rightMax = INT_MIN;
        int leftMin = INT_MAX;

        while(left < n - 1 && nums[left] < nums[left+1])
            left++;
        
        if(left == n-1)
            return 0;

        while(right > 0 && nums[right-1] < nums[right])
            right--;

        
        while(int k = left= k<=right; k++) {
            leftMin = min(leftMin, nums[k]);
            rightMax = max(rightMax, nums[k]);
        }

        while(left>0 && nums[left-1] > leftMin)
            left--;

        while(right<n-1 && rightMax > nums[right+1])
            right++;
            
        return right - left + 1;
    }
Complexity
    O(n) time
    O(1) space


Review
    green/ yellow

implementaion could have been better


-----------

Problem 2 — Arrays / Two Pointers

You are given an integer array nums sorted in non-decreasing order.

Remove duplicates in-place such that each unique element appears at 
most twice.

Return the number of elements k remaining after the modification.

The first k elements of nums should contain the valid result. You may 
ignore everything after k.



Brute force
    push into frequency map
        push freq map into ans, limited to 2 times per num

Observation
    array is sorted
    we can use 2 pointer with a reader and writer
    
Invariant

    if reader - 2 places is same skip this num
    else write
Algorithm
    void removeDups(vector<int> &nums) {
        int i = 0; // writer        
        int n = nums.size();

        // j reader
        for(int j=0; j<n; j++) {
            if(j<2 || nums[j] != nums[j-2]) {
                nums[i] = nums[j];
                i++;
            }
        }
    }
Complexity
    O(n) time
    O(1) space

didnt return
    return j;

also typos in implementation

green / yellow


--------------

Problem 3 — Mixed Revision

You are given an integer array nums of length n containing values 
from 1 to n.

Exactly one number appears twice, and all other numbers appear 
exactly once.

Find the duplicate number.

Constraints:

You must not modify nums.
Use O(1) extra space.
Aim for O(n) time.

nums = [1,3,4,2,2]
Output: 2


Brute force
    for range in [1,n] check is element exists
    N^2 
Observation
    we can model this like a linked list

    nums = [1,3,4,2,2]
    idx  = [0,1,2,3,4]

    0->1
    1->3
    2->4
    3->2
    4->2

    which becomes 0->1->3->2-4
                           | |
                           --

    there is a cycle there
Invariant
    model the array as a linked list
        one duplicate ensures a loop

    using flyods algorithm we can detect the loop starting point
        which will be our duplicate number
Algorithm
    int findDup(vector<int> &nums) {
        int slow = nums[0];
        int fast = nums[nums[0]];

        while(slow != fast) {
            slow = nums[slow];
            fast = nums[nums[slow]];
        }
        
        slow = nums[0];
        while(slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
Complexity
    O(n) time
    O(1) space

*/