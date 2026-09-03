/*
Remove Duplicates from Sorted Array II
    [https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/description/]

Given an integer array nums sorted in non-decreasing order, remove 
some duplicates in-place such that each unique element appears at 
most twice. The relative order of the elements should be kept the 
same.

Since it is impossible to change the length of the array in some 
languages, you must instead have the result be placed in the first 
part of the array nums. More formally, if there are k elements after 
removing the duplicates, then the first k elements of nums should 
hold the final result. It does not matter what you leave beyond the 
first k elements.

Return k after placing the final result in the first k slots of nums.

Do not allocate extra space for another array. You must do this by 
modifying the input array in-place with O(1) extra memory.

Example 1:

    Input: nums = [1,1,1,2,2,3]
    Output: 5, nums = [1,1,2,2,3,_]
    Explanation: Your function should return k = 5, with the first five 
    elements of nums being 1, 1, 2, 2 and 3 respectively.
    It does not matter what you leave beyond the returned k (hence they 
    are underscores).

Example 2:

    Input: nums = [0,0,1,1,1,1,2,3,3]
    Output: 7, nums = [0,0,1,1,2,3,3,_,_]
    Explanation: Your function should return k = 7, with the first seven 
    elements of nums being 0, 0, 1, 1, 2, 3 and 3 respectively.
    It does not matter what you leave beyond the returned k (hence they 
    are underscores).
*/

/*
read pointer and write pointer

1 1 2 2 3



if j != j+1
    j++
    i++
else if n[j] != n[j-2]
    i++
    j++
else
    j++

1 2 3 3 3 3 3 4 5
        i
              j

*/

#include <vector>
using namespace std;

int removeDuplicates(vector<int>& nums) {
    int n = nums.size();

    int i = 0;  // reader
    int j = 0;  // writer

    while (i < n) {

        // First 2 elements are always allowed.
        // After that, don't allow nums[i] to match
        // the element 2 positions behind the writer.
        if (j < 2 || nums[i] != nums[j - 2]) {
            nums[j] = nums[i];
            j++;
        }

        i++;
    }

    return j;
}

int removeKDuplicates(vector<int>& nums) {
    int n = nums.size();

    int i = 0;  // reader
    int j = 0;  // writer

    int k = 3;

    while (i < n) {

        // First 2 elements are always allowed.
        // After that, don't allow nums[i] to match
        // the element 2 positions behind the writer.
        if (j < k || nums[i] != nums[j - k]) {
            nums[j] = nums[i];
            j++;
        }

        i++;
    }

    return j;
}